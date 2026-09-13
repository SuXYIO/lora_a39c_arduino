#include <LoraA39C.h>
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3);
LoraA39C lora = LoraA39C(loraSerial, 4, 5, LoraA39C::Config{42, 1, 1});

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  lora.begin();
  lora.send(F("Lora module initialized\n"));
}

void loop() {
  if (Serial.available() > 0) {
    String send = loraSerial.readStringUntil('\n');
    lora.send(send + "\n");
  }
  if (loraSerial.available() > 0) {
    String received = loraSerial.readStringUntil('\n');
    Serial.println(received);
  }
}
