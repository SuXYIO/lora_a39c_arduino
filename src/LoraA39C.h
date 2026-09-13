#pragma once
#include "Stream.h"
#ifndef LORAA39C_H
#define LORAA39C_H

#include "Arduino.h"

class LoraA39C : private Stream {
  public:
    // NOTE: this is a very limited subset of the config
    struct Config {
        byte channel;
        byte group;
        byte addr;
    };

    LoraA39C(Stream &, byte, byte, Config);

    bool begin();
    size_t send(const String &);

    // read-only fields access functions
    byte pinMd0() { return _pinMd0; }
    byte pinMd1() { return _pinMd1; }
    Config config() { return _config; }

    // override basic read stuff from Stream
    int available() override { return _serial.available(); };
    int read() override { return _serial.read(); };
    int peek() override { return _serial.peek(); };
    // only expose read stuff from Stream
    // NOTE: do not expose flush()
    using Stream::find;
    using Stream::findUntil;
    using Stream::getTimeout;
    using Stream::parseFloat;
    using Stream::parseInt;
    using Stream::readBytes;
    using Stream::readBytesUntil;
    using Stream::readString;
    using Stream::readStringUntil;
    using Stream::setTimeout;

  private:
    Stream &_serial;
    byte _pinMd0;
    byte _pinMd1;
    Config _config;

    // the status the module is in
    enum class Modes {
        Config,
        Work,
        // NOTE: Not supported yet:
        // LowPower,
    };

    bool handshake();
    bool reset();
    bool configure();
    void enterMode(Modes);

    // HACK: this is purely for satisfying inheritance,
    // and MUST NOT BE EXPOSED!
    // use send() instead
    size_t write(uint8_t) override { return 0; }
};

#endif
