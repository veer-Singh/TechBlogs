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
