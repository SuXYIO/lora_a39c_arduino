# LoraA39C - SendAndReceive example

This example implements a "walkie-talkie" with LoraA39C library.

## Usage

Assemble two separate Arduinos, each with:

| Arduino Pin | Lora Pin |
| ----------- | -------- |
| `D2`        | `TX`     |
| `D3`        | `RX`     |
| `D4`        | `MD0`    |
| `D5`        | `MD1`    |
| `5V`        | `VCC`    |
| `GND`       | `GND`    |

Upload one with the program, then swap the values of `localAddr` and `targetAddr` (so that they can send to each other) and upload to another.

Open the serial monitor, use 9600 baud rate, 8N1, newline end character, and you can send messages to the other end!
