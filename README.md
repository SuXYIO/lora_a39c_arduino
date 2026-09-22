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

<details>

<summary>

The `SendAndReceive` example, which implements a "walkie-talkie" with lora:

</summary>

```cpp
#include <LoraA39C.h>
#include <SoftwareSerial.h>

// define stuff
const byte pinLoraRX = 2;  // connect pinLoraRX to TX on Lora module
const byte pinLoraTX = 3;  // and connect pinLoraTX to RX on Lora module
const byte pinLoraMD0 = 4; // MD0 to MD0
const byte pinLoraMD1 = 5; // MD1 to MD1
const LoraA39C::Address localAddr = { 42, 67, 1 };
const LoraA39C::Address targetAddr = { 42, 67, 2 };

// initialize serial and driver
SoftwareSerial loraSerial(pinLoraRX, pinLoraTX);
LoraA39C::Config loraConfig = {
  .address = localAddr,
  // other fields has default values, you can override them
};
LoraA39C lora = LoraA39C(
  loraSerial,
  pinLoraMD0,
  pinLoraMD1,
  loraConfig);

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);

  // use default serial as logging output
  lora.setLog(&Serial);
  // and start the module
  if (!lora.begin()) {
    Serial.println(F("ERROR: Lora begin failed, entering infinite loop."));
    Serial.println(F("TIP: you might wanna check your wire connections, and try again."));
    while (true) {
      delay(1000);
    }
  }

  // send a sentence
  lora.send(targetAddr, F("Hello world!\n"));
}

void loop() {
  // write to remote
  // sends to remote if received in default serial
  if (Serial.available() > 0) {
    String send = Serial.readStringUntil('\n');
    lora.send(targetAddr, send + "\n");
  }
  // read from remote
  // sends to default serial if received from remote
  if (lora.available() > 0) {
    String received = lora.readStringUntil('\n');
    Serial.println(received);
  }
}
```

</details>

See `examples/` directory in source for more.

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
