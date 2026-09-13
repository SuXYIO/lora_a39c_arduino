#include "LoraA39C.h"
#include "utils/utils.h"

LoraA39C::LoraA39C(Stream &serial, byte pinMd0, byte pinMd1, Config config)
    : serial(serial), _pinMd0(pinMd0), _pinMd1(pinMd1), _config(config) {}

bool LoraA39C::begin() {
    if (_config.channel > 0b01111111)
        return false;

    pinMode(_pinMd0, OUTPUT);
    pinMode(_pinMd1, OUTPUT);

    enterMode(Modes::Config);

    if (!handshake())
        return false;
    if (!configure())
        return false;

    enterMode(Modes::Work);

    return true;
}

bool LoraA39C::handshake() {
    byte msg[] = {0, 0, 1};
    serial.write(msg, 3);
    delay(100);

    return checkRet(serial, msg, 3); // yes, correct is same as msg
}

bool LoraA39C::reset() {
    byte msg[] = {0x80, 0x23, 0x01};
    serial.write(msg, 3);
    delay(140);

    byte correct_buf[] = {13, 10, 79, 75, 13, 10};
    return checkRet(serial, correct_buf, 6);
}

void LoraA39C::enterMode(Modes mode) {
    switch (mode) {
    case Modes::Config:
        digitalWrite(_pinMd0, LOW);
        digitalWrite(_pinMd1, LOW);
        delay(120);
        break;
    case Modes::Work:
        digitalWrite(_pinMd0, HIGH);
        digitalWrite(_pinMd1, LOW);
        delay(120);
        break;
    }
}

size_t LoraA39C::send(const String &str) {
    // and don't ask me why sending to local address results in sending to other
    serial.write(_config.group);
    serial.write(_config.addr);
    serial.write(_config.channel);
    return serial.print(str) + 3;
}

/*
 * These are definitions for the config options that i did not abstract and made
 * available in Config class, I really recommend going through the module docs
 * if you want to modify this, since it's raw register values.
 */
// Baud Rate
#define LORA_BAUDRATE 0x00, 0x00, 0x25, 0x80
// LoraSerial Arguments
/* bit5[stopBits = 1 (0b0)],
      bit4[frameLen = dataBits + correctionBits = 8 (0b0)],
      bit(2,1)[correctionBits = NONE (0b00)]
  therefore data = 0b000000 */
#define LORA_SERIAL_ARGS 0x00
// Transmission Mode
// 0x01 for transparent, 0x02 for fix-point, others in the docs
#define LORA_WORKMODE 0x00, 0x02
// Main Mode or Follow Mode
#define LORA_MAINORFOLLOW 0x00
// Pack Size
#define LORA_PACKSIZE 64
// Sleep Time
#define LORA_SLEEPTIME 0
// Group & Addr
#define LORA_TARGGROUP 0 // unused in fix point mode
#define LORA_TARGADDR 0  // unused in fix point mode

bool LoraA39C::configure() {
    // NOTE: serial must be 9600, 8N1
    byte buf[] = {
        0x80, 0x04,
        0x1E,             // cmd, 0x80 write local success, return if error
        LORA_BAUDRATE,    // 0x04
        LORA_SERIAL_ARGS, // 0x05

        // Transmission Arguments
        /* bit(11,5)[channel = 20 (0b0010100)],
                  bit(4,3)[power = 21dBm (0b11)],
                  bit(2,0)[airSpeed = 4.8K (0b010)]
          therefore data = 0b001010011010 */
        (byte)(_config.channel >> 3),
        (byte)((_config.channel << 5) + 0b11010), // 0x06

        LORA_WORKMODE, // 0x07
        0x05, 0x03,
        0xE8,              // 0x08 to 0x09, preserved
        LORA_MAINORFOLLOW, // 0x0A
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, // AES key, set to anything you like
        0x7C, 0x7C, 0x7C, 0x7C, 0x7C,
        0x05,          // 0x0C to 0x0D, preserved
        LORA_PACKSIZE, // 0x0E
        0x00, 0x23, 0x00, 0x00, 0x00, 0x3C,
        0x3C,           // 0x0F to 0x13, preserved
        LORA_SLEEPTIME, // 0x14
        0x0A,
        0x19, // 0x15 to 0x16, preserved
        0x00,
        0x80,           // 0x17, default, which is enable wireless wake code
        _config.group,  // 0x18
        _config.addr,   // 0x19
        LORA_TARGGROUP, // 0x1A
        LORA_TARGADDR,  // 0x1B
        0x00, 0x00, 0x00, 0x00, 0x17,
        0x02 // 0x1C to 0x21, related to relay mode
    };

    serial.write(buf, 61);
    byte correct_buf[] = {0x80, 0x04, 0x1E};
    delay(100);
    if (!checkRet(serial, correct_buf, 3)) {
        return false;
    }

    return true;
}
