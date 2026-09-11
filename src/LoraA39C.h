#ifndef LORAA39C_H
#define LORAA39C_H

#include "Arduino.h"

// the status the module is in
enum class ModuleModes {
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

class LoraA39C : public Stream {
  public:
    LoraA39C(Stream &, byte, byte, Config);

    Stream &serial;
    byte pin_md0;
    byte pin_md1;
    Config config;

    void toMode(ModuleModes);
    bool handshake();
    bool reset();
    bool configure();
    size_t print(String);
};

#endif
