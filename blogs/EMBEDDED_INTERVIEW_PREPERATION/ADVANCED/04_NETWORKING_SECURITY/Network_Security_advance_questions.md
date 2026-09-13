# Advanced Networking and Embedded Security Questions

## 1. TCP vs UDP in firmware?

TCP provides a connection-oriented byte stream with retransmission/congestion behavior. UDP is datagram-oriented and leaves delivery/reliability to the application. Choose based on latency, reliability, connection management, and protocol requirements.

## 2. What is a socket?

A socket is an OS API abstraction for network communication. Typical client/server steps are create -> configure -> bind/listen/accept or connect -> send/receive -> close, depending on protocol and role.

## 3. Why can a TCP receive return fewer bytes than requested?

TCP is a byte stream, not a message protocol. A receive call can return any positive number of available bytes up to the requested size. Applications need framing on top of TCP.

## 4. HTTP vs HTTPS?

HTTPS is HTTP carried over TLS, providing encryption and server authentication when certificates/trust anchors are validated correctly.

## 5. What is TLS doing in an IoT device?

TLS can provide confidentiality, integrity, and peer authentication. Embedded implementation must consider certificate storage, entropy, session lifecycle, memory footprint, algorithm availability, credential provisioning, and failure handling.

## 6. Symmetric vs asymmetric cryptography?

Symmetric algorithms such as AES use shared secret keys and are efficient for bulk encryption. Asymmetric algorithms use key pairs and are useful for authentication/key establishment, but are generally more computationally expensive.

## 7. What is SHA-256?

SHA-256 is a cryptographic hash function producing a 256-bit digest. It provides integrity properties but is not an encryption algorithm.

## 8. How should device credentials be protected?

Do not hard-code reusable secrets into public source code. Prefer secure provisioning and protected key storage when the hardware supports it. Limit credentials to required permissions and define rotation/revocation procedures.

## 9. How would you secure firmware OTA?

Authenticate the image before activation, protect transport with appropriate security, use version/rollback protection, keep an interrupted update recoverable, and log failures without exposing secrets. Product security requirements should determine the exact design.

## 10. Why is entropy important?

Randomness is required for many security operations such as nonce generation and key generation. A cryptographically secure RNG/entropy source is preferable to predictable counters or timestamps alone for security-sensitive randomness.

## 11. What is a MAC (Message Authentication Code) and how does it differ from a hash?

A MAC (e.g., HMAC-SHA256) combines a secret key with the message to produce a tag that verifies both integrity and authenticity — only someone with the key can produce a valid tag. A plain hash (e.g., SHA-256 alone) only verifies integrity; anyone can compute it, so it cannot prove who sent the data. HMAC is commonly used to authenticate firmware update packets or sensor payloads over unauthenticated transports like UDP.

## 12. What is AEAD (Authenticated Encryption with Associated Data), and what is an embedded example

AEAD (e.g., AES-GCM, ChaCha20-Poly1305) provides confidentiality and integrity/authenticity in a single primitive, avoiding the pitfalls of combining encryption and MAC separately (e.g., padding oracle issues). It also supports "associated data" — fields authenticated but not encrypted, such as a packet header or sequence number. AES-GCM is widely used in embedded TLS stacks (mbedTLS, wolfSSL) because it's efficient with hardware AES acceleration, but it requires a unique nonce per encryption — nonce reuse with the same key catastrophically breaks confidentiality.

## 13. Why is nonce/IV reuse dangerous in stream ciphers and counter-mode block ciphers?

In modes like AES-CTR or AES-GCM, the keystream is derived from key + nonce. Reusing the same (key, nonce) pair produces the same keystream, so XOR-ing two ciphertexts cancels the keystream and leaks the XOR of the two plaintexts — often enough to recover both messages. In constrained devices this can happen after a reset if the nonce counter isn't persisted in non-volatile storage, so designs must either persist counters, derive nonces from a monotonic source, or use random nonces sized to keep collision probability negligible.

## 14. What is a replay attack, and how would you prevent it in an embedded protocol?

An attacker captures a valid, legitimately signed/encrypted message and re-sends it later to cause an unintended repeated action (e.g., replaying an "unlock door" command). Mitigations include monotonically increasing sequence numbers or timestamps included in the authenticated data, short validity windows, and rejecting/tracking recently seen message IDs. This matters even when messages are encrypted and authenticated, since AEAD alone doesn't prevent replay of a captured ciphertext.

## 15. Explain a TLS handshake at a level relevant to an MCU with limited RAM/flash

The handshake negotiates a cipher suite, exchanges/validates certificates (or uses pre-shared keys, PSK, for constrained devices), performs a key exchange (e.g., ECDHE) to derive a shared session key, then switches to symmetric encryption for application data. On MCUs, full X.509 chain validation and RSA are expensive in RAM/flash and time, so embedded TLS often prefers ECC (smaller keys, less compute) or TLS-PSK/session resumption to avoid the full asymmetric handshake on every connection, trading off some forward-secrecy/flexibility for footprint.

## 16. What is Perfect Forward Secrecy (PFS) and why does it matter for IoT fleets?

PFS means that if a long-term private key is compromised later, past captured session traffic still cannot be decrypted, because each session uses an ephemeral key (e.g., ECDHE) that's discarded afterward. For IoT fleets where a device key might eventually be extracted (physical access, side-channel attack), PFS limits the damage to future/active sessions rather than exposing an entire history of recorded traffic.

## 17. How do you defend against buffer overflows in a network-facing parser on an MCU?

Validate all length fields against buffer capacity before copying, avoid unbounded functions (`strcpy`, `sprintf`, unchecked `memcpy`), use fixed-size buffers with explicit bounds checks, and prefer a state-machine parser that consumes bytes incrementally rather than requiring the whole packet in one buffer. Where available, enable stack canaries, MPU-based stack/heap separation, and compiler flags like `-fstack-protector`. Because embedded systems often lack ASLR/DEP, a single overflow in a network parser is a much higher-severity bug than on a general-purpose OS.

## 18. What is a side-channel attack, and how does it apply to embedded crypto?

A side-channel attack extracts secret information (keys) from physical characteristics of execution — timing, power consumption, electromagnetic emissions — rather than breaking the algorithm mathematically. Example: a naive AES implementation with data-dependent branch timing or table lookups can leak key bits through timing variance measurable on the device's power rail. Mitigations include constant-time crypto implementations, avoiding secret-dependent branches/array indices, and power-analysis-resistant hardware crypto accelerators for high-assurance products.

## 19. Secure Boot vs Secure/Authenticated OTA — how do they relate?

Secure Boot ensures the bootloader only executes firmware images signed by a trusted key, establishing a chain of trust rooted in immutable/protected boot code. Authenticated OTA ensures a firmware update received over the network is verified (signature/hash check) before being written and marked bootable. They're complementary: OTA authentication stops an attacker from delivering malicious firmware over the air, while secure boot stops a malicious image from running even if it somehow got onto the device (e.g., via a debug port or fallback update path).

## 20. What is a Root of Trust (RoT) in an embedded security architecture?

The RoT is the minimal set of hardware and/or immutable code that is inherently trusted and cannot be bypassed — e.g., an on-chip secure element, a hardware unique key (HUK) burned in fuses, or a boot ROM that cannot be reflashed. All higher-level security guarantees (secure boot, secure storage, attestation) are built on top of it, since if the RoT itself is compromised, the whole chain of trust collapses.

---

## Socket Programming Questions and Answers

## 21. Walk through a basic TCP server socket lifecycle (C, POSIX/BSD sockets)

```c
int sfd = socket(AF_INET, SOCK_STREAM, 0);
setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
listen(sfd, backlog);
int cfd = accept(sfd, NULL, NULL);
read(cfd, buf, sizeof(buf));
write(cfd, resp, resp_len);
close(cfd);
close(sfd);
```

`socket()` creates the endpoint, `bind()` assigns a local address/port, `listen()` marks it passive and sets the pending-connection backlog, `accept()` blocks until a client connects and returns a new connected socket (the listening socket keeps listening), and `read`/`write` (or `recv`/`send`) transfer the byte stream. Each accepted connection gets its own file descriptor.

## 22. Client-side TCP socket lifecycle?

```c
int sfd = socket(AF_INET, SOCK_STREAM, 0);
connect(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
write(sfd, req, req_len);
read(sfd, buf, sizeof(buf));
close(sfd);
```

`connect()` performs the TCP three-way handshake with the server. No `bind()` call is required — the OS auto-assigns an ephemeral local port unless the client needs a specific source port.

## 23. Blocking vs non-blocking sockets — when would you use non-blocking on an embedded system?

A blocking socket call (`recv`, `accept`, `connect`) suspends the calling task/thread until the operation completes. Non-blocking sockets (`fcntl(fd, F_SETFL, O_NONBLOCK)` or platform equivalent) return immediately with `EWOULDBLOCK`/`EAGAIN` if no data is ready. On a resource-constrained embedded system without an RTOS or with a single-threaded main loop, non-blocking sockets combined with `select()`/`poll()` (or an OS-specific event API like lwIP's callback/netconn API) let one task service multiple connections or interleave networking with sensor polling without dedicating a thread per socket.

## 24. What does `select()` (or `poll()`) do, and why is it used in embedded network stacks?

`select()`/`poll()` lets a single thread monitor multiple file descriptors (sockets) simultaneously and block until at least one is ready for read/write/exception, returning which ones. This avoids spinning a thread per connection — important on MCUs with limited RAM per stack — and is the classic pattern for a lightweight single-threaded server handling several clients (e.g., a small HTTP server on lwIP/FreeRTOS+TCP).

## 25. TCP socket vs UDP socket API differences?

TCP (`SOCK_STREAM`) requires `connect()` (client) and `accept()` (server) to establish a connection before `send`/`recv` work, and the connection persists across calls. UDP (`SOCK_DGRAM`) has no connection setup — the server just `bind()`s and calls `recvfrom()`/`sendto()`, specifying the peer address on every packet (or optionally `connect()`s a UDP socket to fix the peer address for `send`/`recv`). UDP sockets can also lose or reorder datagrams silently since there is no built-in reliability.

## 26. Why must you handle partial reads/writes on a TCP socket?

Because TCP is a byte stream (see Q3), a single `send()`/`write()` call may write fewer bytes than requested (e.g., if the send buffer is full), and a single `recv()`/`read()` may return fewer bytes than the sender transmitted in one call. Correct code loops until all bytes are sent/received or an error occurs:

```c
size_t total = 0;
while (total < len) {
    ssize_t n = send(fd, buf + total, len - total, 0);
    if (n <= 0) { /* handle error/EINTR */ break; }
    total += n;
}
```

## 27. How do you implement message framing over a raw TCP stream?

Since TCP has no message boundaries, the application protocol must define them. Common approaches: (1) fixed-length messages, (2) a length-prefix header (e.g., a 2 or 4-byte length field before the payload) so the receiver knows exactly how many bytes to read, or (3) a delimiter (e.g., newline for text protocols) that the receiver scans for. Length-prefixing is generally preferred in embedded binary protocols since it avoids scanning and handles arbitrary binary payloads.

## 28. What is the difference between `close()` and `shutdown()` on a socket?

`close()` releases the file descriptor and, once all references are closed, tears down the connection — it also stops the ability to read or write entirely. `shutdown(fd, SHUT_WR)` half-closes the connection: it sends a TCP FIN so the peer knows no more data is coming, while still allowing this side to read any remaining incoming data. This is useful in protocols where a client sends a request, signals "done sending," and waits to read the full response before actually closing.

## 29. How do you set socket-level timeouts (important for embedded clients that must not hang forever)?

Use `setsockopt()` with `SO_RCVTIMEO`/`SO_SNDTIMEO`:

```c
struct timeval tv = { .tv_sec = 5, .tv_usec = 0 };
setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
```

Without this, a `recv()` on a dead peer/dropped Wi-Fi link can block indefinitely, which is unacceptable on a device that must remain responsive (e.g., keep servicing a watchdog or other tasks). Alternatively, use non-blocking sockets with `select()`/`poll()` and an explicit timeout value, which is often preferred in single-threaded embedded stacks.

## 30. How do you secure a raw socket connection with TLS on an embedded target (e.g., mbedTLS)?

Rather than encrypting manually, wrap the already-connected TCP socket file descriptor in a TLS context: perform the TLS handshake over that fd (mbedTLS's `mbedtls_ssl_handshake()` with BIO callbacks bound to `send`/`recv` on the socket), validate the peer certificate against a trusted CA (or use a pre-shared key for constrained devices), and then use `mbedtls_ssl_read()`/`mbedtls_ssl_write()` in place of raw `recv`/`send` for all application data. The underlying socket API (create/connect/close) is unchanged — TLS sits as a layer on top of the transport.

## 31. What is the SO_REUSEADDR option and why is it commonly set on embedded servers that restart frequently?

`SO_REUSEADDR` allows a socket to bind to a local address/port that's in the `TIME_WAIT` state from a previous connection using the same port (common right after a server process/task restarts). Without it, `bind()` can fail with "address already in use" for up to a couple of minutes after a restart, which is problematic for an embedded device that reboots or resets its network stack and needs to reopen a listening socket immediately.

## 32. What socket error should you specifically handle for a peer that abruptly disconnects, and why does it matter on embedded systems?

`recv()` returning 0 indicates a graceful peer close (FIN received); a negative return with `errno`/error code `ECONNRESET` indicates the peer reset the connection (e.g., it crashed or sent data after closing). Writing to a socket after the peer has reset it can raise `SIGPIPE` on POSIX systems, which by default terminates the process — on an embedded target this can crash the whole application, so servers typically ignore `SIGPIPE` (or use `MSG_NOSIGNAL` on `send()`) and treat `ECONNRESET`/`EPIPE` as a signal to clean up that connection's resources rather than treating it as a fatal error.
