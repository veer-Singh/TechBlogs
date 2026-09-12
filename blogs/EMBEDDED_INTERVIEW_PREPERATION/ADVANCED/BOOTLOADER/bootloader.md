# Bootloader Interview Questions and Answers

> Embedded systems study notes with examples, code, and update-flow diagrams.

## Basic Questions

### 1. What is a bootloader?

A bootloader is a small program that runs immediately after reset and before the main application. It initializes hardware, verifies firmware integrity, supports firmware updates, and transfers execution to the application.

### 2. Why do we need a bootloader?
Firmware updates without debugger
Recovery from corrupted firmware
Secure firmware validation
OTA updates
Manufacturing/programming support
### 3. What happens after MCU reset?
```text
Reset
 |
CPU loads MSP
 |
CPU loads Reset Handler
 |
Bootloader starts
 |
Initialize HW
 |
Validate firmware
 |
Jump to Application
```
### 4. What is the difference between Boot ROM and a bootloader?
| Boot ROM | Bootloader |
| --- | --- |
| Factory programmed | User programmed |
| Cannot modify | Can modify |
| Limited functionality | Custom functionality |
| Permanent | Upgradeable |

Example:
STM32 ROM Bootloader supports UART/USB flashing.

### 5. Where is the bootloader stored?

Usually in a protected Flash region.

Example:

0x08000000 - 0x0800FFFF  Bootloader
0x08010000 - End         Application
## STM32-Specific Questions

### 6. What is MSP?

MSP = Main Stack Pointer.

First word of vector table contains MSP value.

```c
__set_MSP(*(uint32_t*)APP_ADDR);
```
### 7. Why must MSP be changed before jumping to the application?

The application has its own stack location.

Without updating MSP:

Application uses Bootloader stack
Stack corruption occurs
### 8. What is VTOR?

VTOR = Vector Table Offset Register.

Points to interrupt vector table.

```c
SCB->VTOR = APP_ADDR;
```
### 9. Why update VTOR before jumping?

Otherwise interrupts will still use bootloader ISR addresses.

```text
Interrupt
 |
Bootloader ISR
 |
Crash
```
### 10. What happens if VTOR is not updated?

Interrupts execute wrong handlers.

Common symptoms:

HardFault
Random resets
Unexpected behavior
## Firmware Validation

### 11. How do you verify firmware before execution?

Methods:

Checksum
CRC
SHA Hash
Digital Signature
### 12. What is the difference between a checksum and CRC?

Checksum:

Simple addition
Fast
Weak detection

CRC:

Polynomial based
Strong error detection
Widely used
### 13. Why is CRC preferred?

Better detection of:

Single-bit errors
Burst errors
Communication corruption
### 14. Can CRC provide security?

No.

CRC checks integrity only.

For security use:

SHA256
RSA
ECC
## Jumping to the Application

### 15. How does a bootloader jump to the application?
```c
uint32_t resetHandler =
    *(uint32_t*)(APP_ADDR + 4);

((void (*)(void))resetHandler)();
```
### 16. Why is `APP_ADDR + 4` used?

Vector table:

Offset 0 = MSP
Offset 4 = Reset Handler
### 17. What checks should be performed before jumping?

Verify:

Valid Stack Pointer
Valid Reset Handler
CRC OK
Application Exists

Example:

if((*APP_ADDR & 0x2FFE0000)==0x20000000)
{
   Jump();
}
## Firmware Update Questions

### 18. What interfaces can be used for bootloader updates?
UART
CAN
USB
SPI
Ethernet
BLE
WiFi
LTE
### 19. Explain the UART bootloader flow.
Enter Boot Mode
Receive Image
Erase Flash
Write Flash
Verify CRC
Reset MCU
### 20. How is flash programmed?

Steps:

Unlock Flash
Erase Sector
Program Data
Verify Data
Lock Flash
### 21. Why erase flash before programming?

Flash bits:

1 → 0 possible
0 → 1 impossible

Need erase first.

### 22. What happens if power fails during an update?

Firmware may become corrupted.

Solutions:

Dual bank
Backup image
Rollback
## OTA Questions

### 23. What is OTA?

Over-The-Air update.

Firmware downloaded remotely via:

WiFi
LTE
BLE
### 24. How do you prevent a device from being bricked during OTA?

Use:

A/B partitions
Rollback
Image validation
Watchdog recovery
### 25. What is A/B partitioning?
Bootloader
 |
App A (Current)
App B (New)

Update inactive partition first.

### 26. What is rollback?

If new firmware fails:

Bootloader restores old image
## Secure Boot Questions

### 27. What is Secure Boot?

Only authenticated firmware is allowed to execute.

### 28. What is the difference between integrity and authentication?

Integrity:

Firmware modified?

Authentication:

Firmware source trusted?
### 29. How is firmware authentication implemented?
SHA256 Hash
RSA Signature
ECC Signature
### 30. Why is CRC not enough for Secure Boot?

Attacker can recalculate CRC.

CRC doesn't verify source authenticity.

### 31. Explain the Secure Boot flow.
Power On
 |
Verify Signature
 |
Valid ?
 /    \
Yes   No
 |      |
Run    Halt
## Advanced Questions

### 32. What is a dual-bank bootloader?
Bootloader
 |
Bank A
Bank B

One bank runs while other is updated.

### 33. What are the benefits of a dual-bank update?
No downtime
Rollback possible
Safer OTA
### 34. What is chain loading?

One bootloader loads another bootloader.

ROM Bootloader
 |
Stage 1
 |
Stage 2
 |
Application
### 35. What is a second-stage bootloader?

Advanced bootloader loaded by ROM bootloader.

Example:

ESP32 ROM Bootloader
 |
Second Stage Bootloader
 |
Application
### 36. Why disable interrupts before the jump?
```c
__disable_irq();
```

To avoid ISR execution during transition.

### 37. What should be cleaned before jumping?
Interrupts
Pending IRQs
SysTick
DMA
Peripherals
### 38. Why stop SysTick?

Bootloader SysTick configuration may conflict with application.

### 39. What happens if the watchdog expires during an update?

MCU resets.

Bootloader should resume update or rollback.

### 40. How do you protect the bootloader from accidental overwrite?

Using Flash protection:

Write Protection
Read Protection
Option Bytes
## Real-Project Questions (6-8 Years Experience)

### 41. How would you design a production OTA bootloader?

Expected answer:

Secure Boot
AES Encryption
SHA256 Verification
Dual Bank Firmware
Rollback
Watchdog Recovery
Version Control
### 42. How would you detect corrupted firmware?
CRC
SHA Hash
Signature Verification
### 43. How would you recover if firmware is corrupted?
Stay in Bootloader
Recovery Mode
UART/USB Update
Rollback
### 44. How would you update 1000 deployed devices remotely?
OTA Server
Version Management
A/B Images
Rollback
Secure Boot
### 45. Why do automotive ECUs require robust bootloaders?

Because failed firmware can affect:

Engine Control
Braking
Steering
Safety Systems

Hence they use:

Secure Boot
Dual-bank update
Rollback
CAN/Ethernet flashing
## Interview Favorite

### Explain the Bootloader Jump Sequence
```text
Disable Interrupts

Validate Firmware

Set MSP

SCB->VTOR = APP_ADDR

Read Reset Handler

Jump to Application
```

A concise answer:

"The bootloader validates the firmware, disables interrupts, updates MSP and VTOR to the application's vector table, fetches the application's reset handler address from APP_ADDR + 4, and branches to it. After that, the application runs as if it had booted directly after reset."

## Detailed OTA Walkthrough

### OTA Firmware Update Process

OTA allows a device to update its firmware remotely without physical access.

Examples:

Smart TVs
Smart Watches
ESP32 Devices
IoT Sensors
Automotive ECUs
Cameras (like GoPro)
#### High-Level OTA Flow
Developer
    |
Build Firmware
    |
Upload to Server
    |
Cloud/OTA Server
    |
Internet/WiFi/LTE
    |
Device Downloads Firmware
    |
Verify Image
    |
Store in Inactive Partition
    |
Reboot
    |
Bootloader Verification
    |
Switch Partition
    |
New Firmware Runs
#### Flash Layout for OTA
Single Image (Unsafe)
Flash
+------------------+
| Bootloader       |
+------------------+
| Application      |
+------------------+

Problem:

Power Failure During Update
        ↓
Device Bricked
Dual Partition (Recommended)
Flash

+------------------+
| Bootloader       |
+------------------+
| App A (Running)  |
+------------------+
| App B (OTA)      |
+------------------+

Current Firmware:

App A → Active
App B → Empty

New firmware goes into App B.

#### Step 1: Firmware Creation

Developer builds firmware:

app_v1.0.bin

Example:

arm-none-eabi-gcc

Produces:

firmware.bin
#### Step 2: Generate Metadata

Additional information created:

Version
Size
CRC
Hash
Signature

Example:

Version = 2.0
Size    = 512KB
CRC     = 0xABCD1234
SHA256  = xxxxxx
#### Step 3: Upload Firmware to the OTA Server

Stored on:

AWS
Azure
GCP
Private Server

Example:

https://server.com/fw/v2.bin
#### Step 4: Device Checks for an Update

Periodic task:

```c
void ota_task()
{
    check_server();
}
```

Flow:

Device
  |
HTTP GET
  |
Server

Request:

{
  "device":"camera01",
  "version":"1.0"
}

Server Response:

{
  "latest":"2.0",
  "url":"firmware.bin"
}
#### Step 5: Version Comparison

Current:

1.0

Server:

2.0

Check:

```c
if(server_version > current_version)
{
    start_update();
}
```
#### Step 6: Download Firmware

Protocols:

HTTP
HTTPS
MQTT
FTP

Mostly:

HTTPS

for security.

Download occurs in chunks.

Example:

Chunk 1 → 1024 bytes
Chunk 2 → 1024 bytes
Chunk 3 → 1024 bytes
...

Reason:

Firmware may be:

500 KB
1 MB
10 MB

Cannot keep entire image in RAM.

#### Step 7: Store the Image in the Inactive Partition

Current:

App A Running

New Image:

Write to App B

Example:

Bootloader

App A
0x08010000

App B
0x08100000

Write flow:

Erase Flash
Write Chunk
Verify Chunk
Repeat
#### Step 8: Verify the Downloaded Firmware
CRC Check

Calculate:

crc = CalculateCRC();

Compare:

if(crc == received_crc)
SHA256 Check
Generated Hash
Stored Hash

Must match.

Digital Signature Check

Verify:

RSA
ECC

Ensures firmware is from trusted source.

Why Signature Verification?

Without signature:

Attacker Uploads Fake Firmware

Device installs malware.

With signature:

Invalid Signature
      ↓
Rejected
#### Step 9: Mark the Update as Pending

Store flag:

```c
OTA_PENDING = TRUE;
```

Stored in:

Flash
EEPROM
NVS

Example:

```c
ota_flag = PENDING;
```
#### Step 10: Reboot the Device
```c
NVIC_SystemReset();
```

Device resets.

#### Step 11: Bootloader Starts
Power ON
   |
Bootloader

Checks:

OTA Pending?

If:

NO

Boot App A.

If:

YES

Continue OTA verification.

#### Step 12: Validate the New Firmware Again

Bootloader checks:

CRC
SHA256
Signature
Header
Version

Example:

```c
if(image_valid())
{
    activate_image();
}
```
#### Step 13: Switch the Active Partition

Before:

Active = App A

After:

Active = App B

Stored in:

Flash Config
EEPROM
Metadata Sector
#### Step 14: Jump to the New Firmware

Bootloader:

Set MSP

Set VTOR

Jump Reset Handler
New Firmware Starts
#### Step 15: Self-Test

New firmware runs diagnostics:

RAM Test
Sensor Test
Network Test
Filesystem Test

Example:

```c
if(all_tests_pass())
{
    OTA_SUCCESS = TRUE;
}
```
#### Step 16: Confirm the Firmware

New firmware informs bootloader:

Firmware Healthy

Store:

BOOT_OK = TRUE
#### Rollback Mechanism

Suppose:

New Firmware Crashes

before confirmation.

Bootloader sees:

BOOT_OK = FALSE

then:

Rollback

Flow:

Bootloader
      |
New Firmware
      |
Crash
      |
Reset
      |
Bootloader
      |
Rollback
      |
Old Firmware
#### A/B OTA Update Example
Bootloader

App A  ← Running
App B  ← Empty

Download:

Write New Firmware to App B

After verification:

Bootloader

App A
App B ← Active
#### Security in OTA
HTTPS

Protects:

Man-in-the-middle attack
SHA256

Protects:

Corruption Detection
RSA/ECC Signature

Protects:

Unauthorized Firmware
AES Encryption

Protects:

Firmware Confidentiality
#### Failure Scenarios
Case 1: WiFi Lost During Download
Resume Download
Case 2: Power Failure During Download
App A still active

Device safe.

Case 3: Corrupted Firmware
CRC Fail

Reject update.

Case 4: Firmware Crash
Rollback
#### OTA State Machine
IDLE
 |
CHECK_VERSION
 |
DOWNLOAD
 |
VERIFY
 |
STORE
 |
REBOOT
 |
BOOTLOADER_VERIFY
 |
ACTIVATE
 |
SELF_TEST
 |
CONFIRM
 |
SUCCESS
### Production OTA Design Summary

Expected answer:

Bootloader
A/B Partition
HTTPS Download
SHA256 Verification
RSA Signature Check
AES Encryption
Watchdog Recovery
Rollback Support
Version Control
Power Failure Recovery
### 6-8 Years Experience Interview Answer

"In OTA, the device periodically checks a server for a newer firmware version. If available, it downloads the image in chunks and stores it in an inactive partition. After download, the image is verified using CRC, SHA256, and digital signature checks. An OTA pending flag is set and the device reboots. The bootloader validates the new image again, switches the active partition, and boots the new firmware. The application performs self-tests and confirms successful boot. If confirmation is not received due to crashes or resets, the bootloader rolls back to the previous firmware, ensuring the device never becomes unusable."

## SHA-256 and AES Study Notes

### SHA-256 versus AES: the key difference

Absolutely. For an embedded/IoT interview, the most important thing is to understand that SHA-256 and AES solve different security problems.

#### SHA-256 versus AES
Feature	SHA-256	AES
Type	Cryptographic hash	Symmetric encryption
Main purpose	Integrity / fingerprint	Confidentiality
Reversible?	No	Yes, with the key
Key required?	No	Yes
Output	256 bits = 32 bytes	Same size as plaintext for block encryption
Typical use	Firmware verification, passwords, signatures	Encrypt firmware/data
Example	SHA256(firmware)	AES(key, firmware)
Simple analogy

Suppose your firmware is a document.

SHA-256:

"Give me a unique fingerprint of this document."

AES:

"Lock this document so only someone with the key can read it."

So:

SHA-256 → "Has the data changed?"
AES     → "Can someone read the data?"
#### SHA-256 in Detail

SHA-256 stands for:

Secure Hash Algorithm – 256 bit

It belongs to the SHA-2 family.

It takes an input of practically any length and produces exactly:

256 bits
= 32 bytes
= 64 hexadecimal characters

For example:

Input:
Hello

produces a 256-bit hash.

If the input changes even slightly:

Hello

vs

hello

the resulting hash changes dramatically.

#### SHA-256 Properties
Fixed-size output

Whether input is:

10 bytes

or:

10 MB

SHA-256 produces:

256 bits
One-way

You cannot practically take:

SHA256(data)

and recover the original data.

That's why SHA-256 is called a one-way cryptographic hash.

Avalanche effect

A tiny change in input causes a very different hash.

Conceptually:

Firmware V1
     |
     v
SHA-256
     |
     v
ABC123.........


Firmware V1 + 1 bit changed
     |
     v
SHA-256
     |
     v
91F8A2.........

The hashes should be drastically different.

#### How SHA-256 Works Internally

For an interview, know the high-level pipeline:

Input
  |
  v
Padding
  |
  v
512-bit blocks
  |
  v
Initialize hash state
  |
  v
Message schedule
  |
  v
64 compression rounds
  |
  v
256-bit hash

SHA-256 operates on 512-bit message blocks.

Its internal state consists of eight 32-bit words:

H0
H1
H2
H3
H4
H5
H6
H7

Together:

8 × 32 = 256 bits
#### SHA-256 Padding

The input is padded before processing.

Conceptually:

Original message
      |
      v
Append 1 bit
      |
      v
Append 0 bits
      |
      v
Append original message length

The resulting message is divided into:

512-bit blocks
#### SHA-256 Compression

Each 512-bit block goes through 64 rounds.

The algorithm uses operations such as:

XOR
AND
NOT
Right rotation
Right shift
Addition modulo 2³²

Two important functions are:

Ch(x,y,z)  = (x AND y) XOR (~x AND z)

Maj(x,y,z) = (x AND y) XOR (x AND z) XOR (y AND z)

There are also the Σ and σ functions involving bit rotations and shifts.

You normally do not need to memorize all 64 rounds for an embedded interview unless you're implementing cryptography yourself.

#### SHA-256 in OTA

This is particularly important for your bootloader/OTA preparation.

Suppose the server has:

firmware.bin

The server calculates:

SHA256(firmware.bin)

and stores:

Expected Hash

The device downloads the firmware.

Then the device calculates:

SHA256(downloaded_firmware)

Comparison:

Expected Hash
      |
      | compare
      v
Calculated Hash

If:

Expected == Calculated

the image has not been altered/corrupted with respect to that hash.

If:

Expected != Calculated

reject the image.

#### Interview Trap: Is SHA-256 Enough for Secure OTA?

No.

This is a very important answer.

Suppose an attacker replaces:

Original firmware

with:

Malicious firmware

and also replaces the expected SHA-256 hash with the malicious firmware's hash.

Then:

SHA256(malicious firmware)
=
attacker's supplied hash

The hash comparison passes.

Therefore, a plain SHA-256 hash does not authenticate who created the firmware.

For secure firmware authentication, use a digital signature, for example:

Firmware
   |
SHA-256
   |
Hash
   |
Private Key
   |
Digital Signature

The device uses the manufacturer's public key to verify the signature.

#### SHA-256 versus Encryption

This is a very common interview question.

SHA-256
Data
 |
 v
SHA256
 |
 v
Hash

You cannot decrypt the hash.

AES
Plaintext
 |
AES + Key
 |
 v
Ciphertext

Using the appropriate key, ciphertext can be decrypted.

Therefore:

Hashing is not encryption.

#### AES in Detail

AES means:

Advanced Encryption Standard

It is a symmetric-key block cipher.

Symmetric means:

Same secret key
     |
Encrypt
     |
Decrypt

Conceptually:

Plaintext
    |
    | AES + Key
    v
Ciphertext
    |
    | AES + Same Key
    v
Plaintext
#### AES Key Sizes

AES supports:

AES-128 → 128-bit key
AES-192 → 192-bit key
AES-256 → 256-bit key

A very common embedded choice is:

AES-128

or:

AES-256
#### AES Block Size

An important interview point:

AES always has a 128-bit block size.

That means:

128 bits = 16 bytes

This is independent of whether the key is:

128 bits
192 bits
256 bits

For example:

AES-256

Key size   = 256 bits
Block size = 128 bits

Don't confuse these two.

#### AES Encryption Structure

At a high level:

Plaintext
    |
    v
Initial AddRoundKey
    |
    v
Round 1
    |
    v
Round 2
    |
    v
...
    |
    v
Final Round
    |
    v
Ciphertext

The number of rounds depends on the key size:

| AES | Key | Rounds |
| --- | --- | --- |
| AES-128 | 128 bits | 10 |
| AES-192 | 192 bits | 12 |
| AES-256 | 256 bits | 14 |
#### AES Main Operations

Each AES round primarily uses:

##### 1. SubBytes

Each byte is substituted using the AES S-box.

Input byte
    |
    v
S-box
    |
    v
Substituted byte
##### 2. ShiftRows

Rows of the AES state are cyclically shifted.

Before:

A B C D
E F G H
I J K L
M N O P

After shifting:

A B C D
F G H E
K L I J
P M N O

Conceptually, this spreads information across the block.

##### 3. MixColumns

Bytes within each column are mathematically mixed.

This provides diffusion.

The final AES round omits MixColumns.

##### 4. AddRoundKey

The state is XORed with a round key.

State
  XOR
Round Key
  =
New State

This is where the encryption key directly influences the state.

#### AES Modes of Operation

This is extremely important.

AES itself works on a 16-byte block. To securely encrypt larger amounts of data, you generally use a mode of operation.

Common modes:

ECB
CBC
CTR
GCM
CCM
#### ECB: Generally Avoid It

ECB encrypts each block independently:

Block 1 → AES → Cipher 1
Block 2 → AES → Cipher 2
Block 3 → AES → Cipher 3

Problem:

Identical plaintext blocks produce identical ciphertext blocks.

This can reveal patterns.

Therefore:

ECB is generally not recommended for encrypting structured data.

#### CBC

CBC = Cipher Block Chaining.

Conceptually:

Plaintext 1
    XOR
    IV
    |
   AES
    |
Ciphertext 1

Then:

Plaintext 2
    XOR
Ciphertext 1
    |
   AES
    |
Ciphertext 2

CBC requires an IV (Initialization Vector).

Important:

IV does not need to be secret, but it should be unpredictable/unique according to the scheme's requirements.

CBC by itself provides confidentiality, not authentication/integrity.

#### CTR

CTR = Counter mode.

Conceptually:

Key + Counter
     |
    AES
     |
Keystream
     |
     XOR
     |
Plaintext
     |
     v
Ciphertext

CTR turns a block cipher into a stream-like construction.

The counter/nonce must never repeat with the same key.

#### AES-GCM

For modern embedded/IoT systems, AES-GCM is particularly important.

GCM provides:

Confidentiality
+
Integrity
+
Authentication

Conceptually:

Plaintext
    |
AES-GCM + Key + Nonce
    |
    +----> Ciphertext
    |
    +----> Authentication Tag

During decryption:

Ciphertext
    |
AES-GCM + Key + Nonce
    |
Verify Tag
    |
    +---- Valid → Plaintext
    |
    +---- Invalid → Reject

This is called an AEAD mode:

Authenticated Encryption with Associated Data.

#### Why AES-GCM Is Useful for OTA

Suppose firmware is:

firmware.bin

You can encrypt it:

Firmware
   |
AES-GCM
   |
Encrypted Firmware + Authentication Tag

The device decrypts only after successful authentication.

This protects the firmware's confidentiality and detects unauthorized modification of the encrypted data.

For firmware authenticity, production secure-boot designs commonly also use a digital signature or another authenticated trust mechanism.

#### AES and SHA-256 Together in OTA

A common conceptual architecture is:

             OTA SERVER
                 |
        Firmware Image
                 |
          SHA-256 Hash
                 |
       Digital Signature
                 |
              Encrypt
                 |
                 v
              Internet
                 |
                 v
              DEVICE
                 |
            Download
                 |
        AES Decryption
                 |
          SHA-256 / Signature
             Verification
                 |
             Bootloader
                 |
             Application

The exact order depends on the product's security architecture.

#### AES versus SHA-256 in OTA
| Requirement | SHA-256 | AES |
| --- | --- | --- |
| Detect modification | Yes, as a hash primitive | Not by encryption alone |
| Encrypt firmware | No | Yes |
| Decrypt firmware | No | Yes |
| Hide firmware contents | No | Yes |
| Requires secret key | No | Yes |
| Used for digital signatures | Hash is part of signature process | No |
| Confidentiality | No | Yes |
#### Important: Hashing Is Not Authentication

Interviewers often ask:

"If I calculate SHA-256 on firmware, is the firmware secure?"

Answer:

Not by itself. SHA-256 provides a cryptographic digest, but a publicly known or attacker-replaceable hash does not authenticate the firmware source. For secure boot/OTA, use a digital signature or a properly designed authenticated mechanism.

#### Important: AES Does Not Provide Integrity by Itself

Another interview question:

"If firmware is encrypted using AES, is it automatically secure?"

Answer:

No. Encryption primarily provides confidentiality. You also need integrity/authentication, such as AES-GCM/CCM or a separate authenticated signature mechanism.

#### Where Are Keys Stored in an Embedded System?

This is a major embedded security question.

Possible locations:

Secure Element
OTP Memory
eFuse
Protected Flash
TPM
Hardware Security Module
MCU Security/Key Storage

Ideally, secret keys should not be stored as ordinary plaintext constants in application Flash.

For example, avoid simply doing:

```c
#define AES_KEY "1234567890123456"
```

in production firmware.

#### Hardware Crypto Acceleration

Many modern MCUs have a cryptographic accelerator.

Instead of performing everything using software:

CPU
 |
Software AES

you may have:

CPU
 |
Crypto Hardware
 |
AES/SHA

Benefits can include:

Lower CPU usage
Better performance
Lower energy consumption
Sometimes stronger key isolation

The exact capabilities depend on the MCU.

#### Embedded Example

Suppose your device receives:

firmware_v2.bin

The OTA metadata says:

Version = 2
Size = 512 KB
SHA256 = ABCD...
Signature = XYZ...

Device:

Step 1

Downloads encrypted firmware.

Step 2

Decrypts/authenticates it using the configured AES scheme.

Step 3

Checks firmware hash/signature.

Step 4

Stores it in inactive Flash partition.

Step 5

Bootloader verifies image again.

Step 6

Bootloader starts firmware.

Step 7

Firmware performs self-test.

Step 8

Firmware marks update successful.

If anything fails:

Rollback → Previous Firmware
### Quick Interview Review
#### Q1. What is SHA-256?

Answer: SHA-256 is a cryptographic hash function from the SHA-2 family that maps arbitrary-length input to a fixed 256-bit digest. It is primarily used for integrity checking and as a component of digital signatures.

#### Q2. Is SHA-256 encryption?

No. It is hashing and is not reversible.

#### Q3. What is AES?

AES is a symmetric block cipher with a 128-bit block size and 128-, 192-, or 256-bit keys.

#### Q4. What does AES-256 mean?

It means:

256-bit key

not a 256-bit block.

#### Q5. How many rounds does AES-256 have?

14 rounds.

#### Q6. What is an IV or nonce?

It is additional per-operation input used by many encryption modes. Its required properties depend on the mode. For GCM, nonce reuse with the same key is especially dangerous and must be prevented.

#### Q7. Why use AES-GCM?

Because it provides authenticated encryption—confidentiality plus integrity/authentication.

#### Q8. Can SHA-256 protect against a malicious firmware replacement?

A bare hash comparison cannot authenticate the firmware source. Use a digital signature or another authenticated mechanism.

#### Q9. Can AES alone guarantee firmware authenticity?

No. Encryption alone does not establish who created the firmware.

#### Q10. SHA-256 plus AES: why use both?

A typical design may use:

AES       → confidentiality
SHA-256   → cryptographic digest
Signature → firmware authenticity

or use an authenticated encryption mode such as AES-GCM for confidentiality + data authentication, while still using a digital signature for firmware publisher authenticity.

The 30-second interview answer

"SHA-256 and AES are fundamentally different. SHA-256 is a one-way 256-bit cryptographic hash used to create a fingerprint of data and is commonly used for integrity checking and as part of digital signatures. AES is a symmetric encryption algorithm used to provide confidentiality using a secret key. AES supports 128-, 192-, and 256-bit keys and always has a 128-bit block size. In a secure OTA system, AES can protect firmware confidentiality, while SHA-256 can be used as part of firmware integrity verification, and a digital signature is normally used to authenticate that the firmware came from a trusted manufacturer. For authenticated encryption, AES-GCM is commonly used."