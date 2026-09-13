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
    String send = lora.readStringUntil('\n');
    lora.send(send + "\n");
  }
  if (lora.available() > 0) {
    String received = lora.readStringUntil('\n');
    Serial.println(received);
  }
}
