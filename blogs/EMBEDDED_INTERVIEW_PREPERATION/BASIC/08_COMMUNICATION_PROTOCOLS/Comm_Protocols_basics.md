# Embedded Communication Protocol Interview Questions

## UART

### What is UART?

UART is an asynchronous serial interface using independently configured baud rate, framing, and optional flow control. A frame commonly contains a start bit, data bits, optional parity, and stop bit.

### What is baud rate?

Baud rate is the number of symbols transmitted per second. In common binary UART configurations, one symbol represents one bit, but the terms are not universally identical for every physical modulation scheme.

## SPI

### Why is SPI faster than I2C in many designs?

SPI uses push-pull clock/data signaling and commonly allows higher transfer rates with simpler framing overhead. The trade-off is more wires and typically one chip-select per slave.

### Full duplex?

SPI can transmit and receive simultaneously because separate MOSI and MISO lines are typically used.

## I2C

### Why does I2C use open-drain/open-collector style signaling?

Devices pull lines low and external pull-up resistors restore the high level. This allows multiple devices to share the bus without actively driving opposing logic levels.

### What is clock stretching?

A slave can hold SCL low to delay the master, subject to the capabilities/limitations of the specific device and controller.

## CAN

### Why is CAN robust in noisy environments?

CAN uses differential signaling and arbitration mechanisms designed for multi-node bus communication. Nodes monitor the bus and can detect several classes of communication errors.

### What is arbitration?

When multiple nodes start transmitting, the bus arbitration mechanism lets the message with the higher-priority identifier continue while losing nodes stop transmitting without corrupting the winning frame.

## Modbus

### RTU vs TCP?

Modbus RTU commonly runs over a serial physical link such as RS-485. Modbus TCP carries Modbus application data over TCP/IP, usually using Ethernet or another IP transport.

## MQTT

### Why is MQTT used in IoT?

MQTT is a lightweight publish/subscribe messaging protocol designed for constrained devices and unreliable or bandwidth-limited links. It decouples publishers from subscribers through a broker.

### What is QoS?

MQTT defines delivery levels such as at-most-once, at-least-once, and exactly-once semantics. Reliability, bandwidth, latency, and duplicate processing must be considered together.

## Interview Exercise

Given a sensor MCU connected to a modem, explain how you would choose between UART, SPI, I2C, CAN, and MQTT. A strong answer starts from distance/topology/electrical layer, then throughput/latency, reliability, addressing, software complexity, and system architecture.
