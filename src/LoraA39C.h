#ifndef LORAA39C_H
#define LORAA39C_H

#include "Arduino.h"

// the status the module is in
enum class Modes {
    Config,
    Work,
    // NOTE: Not supported yet:
    // LowPower,
};

// NOTE: this is a very limited subset of the config
struct Config {
    byte channel;
    byte group;
    byte addr;
};

class LoraA39C {
  public:
    LoraA39C(Stream &, byte, byte, Config);

    Stream &serial;
    byte pin_md0;
    byte pin_md1;
    Config config;

    void enterMode(Modes);
    bool handshake();
    bool reset();
    bool configure();
    size_t send(const String &);
};

#endif
