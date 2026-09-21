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
  // write
  // sends to remote if received in default serial
  if (Serial.available() > 0) {
    String send = Serial.readStringUntil('\n');
    lora.send(targetAddr, send + "\n");
  }
  // read
  // sends to default serial if received from remote
  if (lora.available() > 0) {
    String received = lora.readStringUntil('\n');
    Serial.println(received);
  }
}
