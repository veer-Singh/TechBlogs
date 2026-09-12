# ESP32 Interview Questions

## 1. What is ESP-IDF?

ESP-IDF is Espressif's official framework for ESP32-family development. It exposes drivers, networking, FreeRTOS integration, build/configuration tooling, and chip-specific APIs.

## 2. Arduino framework vs ESP-IDF?

Arduino provides a simpler programming model and ecosystem. ESP-IDF gives lower-level control and broader access to ESP-specific capabilities. For production firmware, the framework should be selected according to requirements for control, maintainability, performance, and team expertise.

## 3. Why is FreeRTOS relevant on ESP32?

ESP-IDF integrates FreeRTOS concepts such as tasks, queues, semaphores, and timers into the application environment. Some ESP32 variants use multicore architectures, so task affinity and cross-core synchronization can also matter.

## 4. How would you design Wi-Fi reconnect logic?

Treat connection as a state machine: DISCONNECTED -> CONNECTING -> CONNECTED -> LOST -> BACKOFF -> CONNECTING. Add bounded retry/backoff and avoid blocking application-critical work while the network is down.

## 5. What is NVS?

Non-volatile storage in ESP-IDF provides a key-value storage mechanism commonly used for configuration/calibration/state that must survive reset. The exact storage characteristics and wear behavior should be considered for frequently updated data.

## 6. What is the typical embedded approach for OTA?

Download the image safely, verify integrity/authenticity as required, write it to an inactive update slot/partition, mark the new image for boot, and support rollback or recovery if startup validation fails. Exact mechanism depends on ESP-IDF version and partition scheme.

## 7. How would you debug a crash?

Capture the panic/backtrace, decode the call stack against the exact firmware binary, identify whether the root cause is memory corruption, stack overflow, invalid access, watchdog timeout, or another fault class, then reproduce with instrumentation.

## 8. What should you consider for low-power ESP32 firmware?

Reduce wakeups, choose appropriate sleep mode, shut down unused peripherals/radios, batch work, and measure actual current with the real board. The correct design depends on radio duty cycle, wake latency, RAM retention, and external hardware.

## References

- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/
