# Embedded Communication Protocol Interview Questions

## UART

### What is UART?

UART is an asynchronous serial interface using independently configured baud rate, framing, and optional flow control. A frame commonly contains a start bit, data bits, optional parity, and stop bit.

### What is baud rate?

Baud rate is the number of symbols transmitted per second. In common binary UART configurations, one symbol represents one bit, but the terms are not universally identical for every physical modulation scheme.

### What are the parts of a UART frame?

A typical frame is: one start bit (always 0, signals the beginning of a frame), 5-9 data bits (8 is most common), an optional parity bit (error detection), and 1-2 stop bits (always 1, signals the frame is complete and the line is returning to idle). Both sides must agree on all of these settings in advance since there's no shared clock to negotiate them.

### What is a start bit and a stop bit used for?

The start bit is a falling edge (idle-high to low) that tells the receiver "a new frame is beginning right now," letting it start sampling at the correct moments even without a shared clock. The stop bit(s) return the line to its idle (high) state and guarantee a minimum gap before the next frame, giving the receiver time to finish processing the current byte.

### What is the difference between synchronous and asynchronous communication?

Synchronous communication (like SPI) shares a clock signal between sender and receiver, so both sides know exactly when to sample each bit. Asynchronous communication (like UART) has no shared clock — both sides must be pre-configured with the same timing (baud rate) and agree on frame structure so the receiver can recover bit boundaries on its own.

### What is UART hardware flow control?

RTS (Request To Send) and CTS (Clear To Send) are extra signal lines that let a receiver tell the sender to pause transmission when its buffer is getting full, preventing data loss when one side is temporarily slower than the other. It's optional — many simple UART links (like debug consoles) don't use it at all.

## SPI

### Why is SPI faster than I2C in many designs?

SPI uses push-pull clock/data signaling and commonly allows higher transfer rates with simpler framing overhead. The trade-off is more wires and typically one chip-select per slave.

### Full duplex?

SPI can transmit and receive simultaneously because separate MOSI and MISO lines are typically used.

### What are the four SPI signal lines?

SCK/SCLK (serial clock, driven by the master), MOSI (Master Out Slave In, data from master to slave), MISO (Master In Slave Out, data from slave to master), and SS/CS (Slave Select / Chip Select, an active-low line the master uses to pick which slave is currently active on the shared bus).

### Why does SPI need a separate chip-select line per slave?

MOSI, MISO, and SCK are shared across all slaves on the bus, so there's nothing that inherently identifies which slave should respond. The master pulls exactly one slave's CS line low before a transaction; every other slave ignores the clock/data lines while its own CS is high, preventing bus contention.

### What are SPI clock polarity (CPOL) and clock phase (CPHA)?

CPOL sets the clock's idle state (0 = idle low, 1 = idle high). CPHA sets which clock edge data is sampled on (0 = first edge, 1 = second edge). Together they define the four SPI "modes" (0-3); the master and slave must be configured to the same mode or data will be sampled at the wrong instant and come out corrupted.

### Does SPI have a standard addressing scheme like I2C?

No. SPI has no built-in addressing — it relies entirely on physical chip-select lines to pick a device, and there's no standard packet format either, so the data format is entirely up to the specific chip/application. This is part of why SPI is simple and fast but needs more pins than I2C as the number of devices grows.

## I2C

### Why does I2C use open-drain/open-collector style signaling?

Devices pull lines low and external pull-up resistors restore the high level. This allows multiple devices to share the bus without actively driving opposing logic levels.

### What is clock stretching?

A slave can hold SCL low to delay the master, subject to the capabilities/limitations of the specific device and controller.

### What are the two signal lines in I2C, and what does each do?

SDA (Serial Data) carries the actual data bits, and SCL (Serial Clock) is the clock signal driven by the master/controller that all devices use to synchronize when to read/write SDA. Only two wires are needed regardless of how many devices are on the bus, which is I2C's main advantage over SPI for many-device systems.

### How does I2C addressing work?

Every device on the bus has a unique address (commonly 7-bit, giving 128 possible addresses, though 10-bit addressing also exists). The master starts a transaction by sending the target device's address plus a read/write bit; every device on the bus "listens" to the address, but only the one matching that address responds with an acknowledgment (ACK) and participates in the rest of the transaction.

### What is an ACK/NACK in I2C?

After every byte transferred (including the address byte), the receiving side pulls SDA low for one clock pulse to acknowledge (ACK) successful receipt. If the receiver doesn't pull it low (leaves it high), that's a NACK — signaling either "no device at that address," "I can't accept more data," or an error condition, depending on context.

### What is the difference between Standard mode, Fast mode, and Fast mode+ in I2C?

These describe the maximum bus clock speed: Standard mode runs up to 100 kHz, Fast mode up to 400 kHz, and Fast mode+ up to 1 MHz (with High-speed mode going up to 3.4 MHz). Higher speeds generally need stronger pull-up resistors and shorter, less capacitive bus wiring to keep signal edges clean.

## CAN

### Why is CAN robust in noisy environments?

CAN uses differential signaling and arbitration mechanisms designed for multi-node bus communication. Nodes monitor the bus and can detect several classes of communication errors.

### What is arbitration?

When multiple nodes start transmitting, the bus arbitration mechanism lets the message with the higher-priority identifier continue while losing nodes stop transmitting without corrupting the winning frame.

### What are CANH and CANL?

CAN uses two wires, CAN High and CAN Low, carrying a differential signal — the receiver looks at the *difference* between them rather than either wire's absolute voltage. This makes the signal much less sensitive to electrical noise picked up equally by both wires (common-mode noise), which is why CAN is popular in electrically noisy environments like vehicles and industrial equipment.

### What is a dominant bit versus a recessive bit in CAN?

A dominant bit (logical 0) actively drives the bus to a specific differential voltage, while a recessive bit (logical 1) just lets the bus float back to its passive/idle state. If one node drives dominant while another drives recessive at the same time, dominant always wins on the shared bus — this is exactly the mechanism arbitration relies on.

### What are the main fields in a CAN frame?

A standard CAN frame includes: a Start of Frame bit, an 11-bit (or 29-bit for extended CAN) identifier, a control field with the data length code (DLC), 0-8 bytes of data payload, a CRC field for error detection, an ACK slot, and an End of Frame marker. There's no destination address field — the identifier represents the *meaning* of the message, and every node decides for itself whether to accept a given identifier.

### Is CAN a master-slave protocol?

No, CAN is multi-master — any node can attempt to transmit whenever the bus is idle, and the arbitration mechanism (based on identifier priority) resolves which node actually gets to send if two or more start at the same time. There's no single node that controls bus access like the master in SPI or I2C.

## Modbus

### RTU vs TCP?

Modbus RTU commonly runs over a serial physical link such as RS-485. Modbus TCP carries Modbus application data over TCP/IP, usually using Ethernet or another IP transport.

### Is Modbus master-slave or peer-to-peer?

Modbus is a master-slave (also called client-server in newer terminology) protocol. The master/client initiates every request; slaves/servers only ever respond when addressed — they never send data unprompted. This makes Modbus simple to implement but means the master must poll each device for updates rather than being pushed new data.

### What is a function code in Modbus?

A function code is a number in the request that tells the slave what operation to perform — for example, reading holding registers, reading coils (single-bit outputs), or writing a single register. The slave's response echoes the same function code (or a modified version with an error flag set) so the master can match the response to what it asked for.

## MQTT

### Why is MQTT used in IoT?

MQTT is a lightweight publish/subscribe messaging protocol designed for constrained devices and unreliable or bandwidth-limited links. It decouples publishers from subscribers through a broker.

### What is QoS?

MQTT defines delivery levels such as at-most-once, at-least-once, and exactly-once semantics. Reliability, bandwidth, latency, and duplicate processing must be considered together.

### What is a topic in MQTT?

A topic is a hierarchical, slash-separated string (e.g., `home/livingroom/temperature`) that identifies what a message is about. Publishers send messages to a specific topic, and subscribers register interest in one or more topics (including using wildcards) — the broker is responsible for routing each published message to every currently interested subscriber.

### What is a broker in MQTT, and why is it needed?

The broker is the central server that all clients (publishers and subscribers) connect to. It receives every published message and forwards it to the subscribers of that topic, so publishers and subscribers never need to know about each other directly — they only need to know the broker's address and agree on topic names. This decoupling is what makes MQTT convenient for IoT systems with many devices.

### What transport does MQTT normally run over, and why?

MQTT typically runs over TCP (often further wrapped in TLS for security), since it relies on TCP's reliable, ordered delivery rather than reimplementing that itself. This is also why MQTT is considered "lightweight" compared to protocols like HTTP — its own message headers are much smaller, which matters on bandwidth-constrained or metered IoT links.

## USB

### What is USB, and why is it used in embedded systems?

USB (Universal Serial Bus) is a widely supported standard for connecting peripherals to a host, offering a common connector/protocol, hot-plug capability, and often power delivery to the connected device over the same cable. In embedded systems it's commonly used for firmware flashing/debugging, connecting to a PC as a virtual COM port, mass storage, or acting as a HID device (keyboard/mouse-like input).

### What is the difference between USB host and USB device roles?

The host is the device that controls the bus, initiates all communication, and supplies power (in most configurations) — typically a PC. The device (sometimes called a "function" or peripheral) only responds when addressed by the host and cannot initiate communication on its own. Some embedded systems support USB OTG (On-The-Go), letting the same port act as either a host or a device depending on what it's connected to.

### What are common USB connector/speed classes an embedded engineer should know?

USB has evolved through several speed tiers: Low Speed (1.5 Mbps, simple HID devices), Full Speed (12 Mbps), High Speed (480 Mbps, USB 2.0), and SuperSpeed (5 Gbps and beyond, USB 3.x). Most simple embedded peripherals (sensors, debug interfaces) only need Full Speed or High Speed, since their actual data rates are far below what SuperSpeed offers.

## Ethernet

### What is Ethernet, and what does an Ethernet frame contain at a basic level?

Ethernet is the standard wired networking technology for local area networks, defining both the physical/electrical signaling and the frame format used to carry data. At a basic level, a frame contains a destination MAC address, a source MAC address, a type/length field, the actual payload data, and a trailing checksum (FCS) used to detect transmission errors.

### What is a MAC address?

A MAC (Media Access Control) address is a 48-bit hardware address, typically assigned by the manufacturer and burned into the network interface, used to identify a device uniquely on its local network segment. It's different from an IP address — the MAC address operates at the link layer (local delivery), while the IP address operates at the network layer (routing across networks).

### What is the difference between a switch and a hub in an Ethernet network?

A hub simply repeats every incoming signal out to all other ports, so all connected devices share the same collision domain (only one can transmit at a time without collision). A switch inspects the destination MAC address of each frame and forwards it only to the specific port where that device is connected, letting multiple devices communicate simultaneously without colliding — virtually all embedded Ethernet designs today connect through switches rather than hubs.

## TCP/IP

### What is the difference between TCP and UDP at a basic level?

TCP is connection-oriented: it establishes a connection first, guarantees ordered and reliable delivery (retransmitting lost data), and manages flow/congestion automatically — at the cost of some overhead and setup time. UDP is connectionless: it just sends datagrams with no guarantee of delivery, ordering, or duplicate protection, but with much lower overhead and latency — commonly chosen for simple sensor telemetry or streaming where an occasional dropped packet is acceptable.

### What is an IP address, and what is the difference between IPv4 and IPv6?

An IP address identifies a device on a network for routing purposes. IPv4 addresses are 32 bits (written as four decimal numbers like `192.168.1.10`), giving about 4.3 billion possible addresses — a number the internet has essentially exhausted. IPv6 addresses are 128 bits, written in hexadecimal groups, providing a vastly larger address space and built-in features like simplified auto-configuration, which is gradually becoming more common in newer IoT deployments.

### What is a port number used for?

A port number (0-65535) identifies a specific application or service running on a device, on top of the IP address that identifies the device itself. For example, a device's IP address gets you to the right machine, but the port number (like 80 for HTTP or 1883 for MQTT) tells the operating system which running application should receive the incoming data.

## Interview Exercise

Given a sensor MCU connected to a modem, explain how you would choose between UART, SPI, I2C, CAN, and MQTT. A strong answer starts from distance/topology/electrical layer, then throughput/latency, reliability, addressing, software complexity, and system architecture.
