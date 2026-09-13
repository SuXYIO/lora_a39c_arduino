#pragma once
#ifndef LORAA39C_H
#define LORAA39C_H

#include "Arduino.h"

class LoraA39C {
  public:
    // NOTE: this is a very limited subset of the config
    struct Config {
        byte channel;
        byte group;
        byte addr;
    };

    LoraA39C(Stream &, byte, byte, Config);

    Stream &serial;

    // read-only fields access functions
    byte pinMd0() { return _pinMd0; }
    byte pinMd1() { return _pinMd1; }
    Config config() { return _config; }

    bool begin();
    size_t send(const String &);

  private:
    // the status the module is in
    enum class Modes {
        Config,
        Work,
        // NOTE: Not supported yet:
        // LowPower,
    };

    byte _pinMd0;
    byte _pinMd1;
    Config _config;
    bool handshake();
    bool reset();
    bool configure();
    void enterMode(Modes);
};

#endif
