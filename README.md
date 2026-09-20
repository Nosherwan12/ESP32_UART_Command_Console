# ESP32 UART Command Console

A modular UART-based command console for the ESP32, developed with **ESP-IDF and FreeRTOS**.

The project implements a reusable command-line interface over UART, including line buffering, command parsing, command dispatch, argument validation, hardware control, system information, and controlled system restart.

## Features

* UART console at **115200 baud**
* Character-by-character command input
* Line buffering with CR/LF handling
* Command parsing with whitespace-separated arguments
* Argument-count validation
* Command lookup using a command table
* Modular command handlers
* Command buffer overflow detection
* LED control and status reporting
* ESP32 system information reporting
* Software-triggered system reboot
* Formatted UART output using a `printf`-style interface
* Modular ESP-IDF component architecture

## Supported Commands

| Command      | Description                                              |
| ------------ | -------------------------------------------------------- |
| `help`       | Show available commands                                  |
| `led on`     | Turn the LED on                                          |
| `led off`    | Turn the LED off                                         |
| `led status` | Report the current LED state                             |
| `info`       | Display chip, heap, flash, ESP-IDF and build information |
| `reboot`     | Restart the ESP32                                        |

### Example

```text
> help
=== Available Commands ===
Command    Description
help       Show available commands
led        Control LED
info       Show system information
reboot     Restart the ESP32
==============================

> led on
LED turned ON

> led status
LED is ON

> led off
LED turned OFF

> info
=== System Info ===
Chip:      ESP32-S3 (2 cores)
Free Heap: 372 KB
Flash:     16 MB
IDF:       v5.3.1-dirty
Build:     Sep 20 2026 22:18:06
====================

> hello
Unknown command: hello
Type 'help' for available commands

> reboot
SYSTEM REBOOTING...
```

## Command Processing Architecture

The console follows a layered command-processing flow:

```text
UART Input
    │
    ▼
UART Console
    │
    ▼
Line Buffering
    │
    ▼
Command Parser
    │
    ▼
Command Dispatcher
    │
    ├── help
    ├── led
    ├── info
    └── reboot
         │
         ▼
   Command Handlers
         │
         ├── LED Driver
         ├── ESP System APIs
         └── Restart
```

The application is intentionally separated into independent components so that the UART interface, parser, dispatcher, command handlers, and LED control can be developed and maintained independently.

## Project Structure

```text
UART Command Console/
├── CMakeLists.txt
├── README.md
├── sdkconfig
│
├── main/
│   ├── CMakeLists.txt
│   └── main.c
│
└── components/
    ├── uart_console/
    │   ├── CMakeLists.txt
    │   ├── uart_console.c
    │   └── include/
    │       └── uart_console.h
    │
    ├── command_parser/
    │   ├── CMakeLists.txt
    │   ├── command_parser.c
    │   └── include/
    │       └── command_parser.h
    │
    ├── command_dispatcher/
    │   ├── CMakeLists.txt
    │   ├── command_dispatcher.c
    │   └── include/
    │       └── command_dispatcher.h
    │
    ├── command_handlers/
    │   ├── CMakeLists.txt
    │   ├── command_handlers.c
    │   └── include/
    │       └── command_handlers.h
    │
    └── led/
        ├── CMakeLists.txt
        ├── led.c
        └── include/
            └── led.h
```

## Hardware

The console uses the ESP32-S3 development board's UART interface.

| Function  |    GPIO |
| --------- | ------: |
| UART TX   | GPIO 17 |
| UART RX   | GPIO 18 |
| LED       |  GPIO 6 |
| Baud rate |  115200 |

A USB-to-UART interface can be used to communicate with the console from a PC.

## Software

* **MCU:** ESP32-S3
* **Framework:** ESP-IDF
* **Language:** C
* **RTOS:** FreeRTOS
* **Build system:** CMake
* **Development environment:** VS Code / ESP-IDF

## Build

Activate the ESP-IDF environment and navigate to the project directory.

Build the project:

```bash
idf.py build
```

Flash the firmware:

```bash
idf.py flash
```

Open the serial monitor:

```bash
idf.py monitor
```

Or combine flashing and monitoring:

```bash
idf.py flash monitor
```

## Design Concepts Demonstrated

This project focuses on practical embedded firmware concepts:

* UART peripheral configuration
* Hardware abstraction
* Character-stream processing
* Fixed-size buffer management
* Input validation
* Tokenization and argument parsing
* Function pointers
* Command tables
* Modular firmware architecture
* ESP-IDF component dependencies
* Error handling with `esp_err_t`
* Hardware control through a dedicated driver
* Defensive handling of oversized input

## Future Improvements

Potential extensions include:

* Command auto-completion
* Backspace/editing support
* Command history
* Additional peripheral-control commands
* Non-blocking UART input
* More structured command/response handling
* Unit testing for the parser and dispatcher
