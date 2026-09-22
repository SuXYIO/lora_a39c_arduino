# lora_a39c_arduino

Arduino library for [A39C-T400A22D1a Lora wireless module](https://www.ashiningtech.com/products/00000002-0017-0000-0000-000000000017).

Note that this library has not implemented full functionalities of the module yet, but it should be enough for simple cases.

Refer to [feature list](https://codeberg.org/UwaEng/lora_a39c_arduino/issues/3) for current implemented features.

## Compatibility

The library is tested on Arduino UNO R3.

Theoretically supports all Arduino boards.

## Installation

You can search for `LoraA39C` in your ArduinoIDE library panel, select a version, and click install.

For manual installation, download or clone the source code on this page, decompress it, and put the directory under your Arduino libraries path.

Arduino libraries path quick reference:

- Linux: `~/Arduino/libraries`
- Windows: `Documents\Arduino\libraries`
- MacOS: `~/Documents/Arduino/libraries`

## Example

You can get an overview of the library with SendAndReceive example (in `examples/SendAndReceive/SendAndReceive.ino`), which implements a "walkie-talkie" with lora.

See `examples/` directory for more.

## Docs

Class `LoraA39C`:
| Name | Functionality |
| ---- | ------------- |
| `Address`| address representation for module |
| `Config`| config representation for module |
| `LoraA39C()`| LoraA39C class constructor |
| `setLog()`| sets a stream (serial) as log output, use `nullptr` for disable log |
| `begin()` | configures the module and makes the module enter work mode |
| `end()` | sets the module to lowpower mode, and set pinMd0 and pinMd1 to input |
| `send()` | send message with lora fix-point |
| `pinMd0()` | get pin number of MD0 |
| `pinMd1()` | get pin number of MD1 |
| `config()` | get configuration struct |

The `LoraA39C` class also inherited `available()`, `read()`, `peek()`, `find()`, `findUntil()`, `getTimeout()`, `parseFloat()`, `parseInt()`, `readBytes()`, `readBytesUntil()`, `readString()`, `readStringUntil()`, `setTimeout()` from the [`Stream` class](https://docs.arduino.cc/language-reference/en/functions/communication/stream/), for conveniency reading from lora serial.

You can also run `doxygen` in the project, for generated documentation.
