#pragma once
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
  private:
    byte _pin_md0;
    byte _pin_md1;
    Config _config;
    bool handshake();
    bool reset();
    bool configure();
    void enterMode(Modes);

  public:
    LoraA39C(Stream &, byte, byte, Config);

    Stream &serial;

    // read-only fields access functions
    byte pin_md0() { return _pin_md0; }
    byte pin_md1() { return _pin_md1; }
    Config config() { return _config; }

    bool begin();
    size_t send(const String &);
};

#endif
