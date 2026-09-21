#pragma once
#include "Stream.h"
#ifndef LORAA39C_H
#define LORAA39C_H

#include "Arduino.h"

/**
 * @brief driver for Lora A39C module
 */
class LoraA39C : private Stream {
  public:
    /**
     * @brief address representation for module
     */
    struct Address {
        byte channel; /**< channel */
        byte group;   /**< group number */
        byte addr;    /**< address */
    };
    /**
     * @brief configuration representation for module
     */
    struct Config {
        Address address;               /**< local address */
        unsigned long timeoutMs = 500; /**< timeout waiting for response */

        // fuck you c++, literally piece of shit

        /**
         * @brief constructor for config
         */
        Config(Address address, unsigned long timeoutMs = 500)
            : address(address), timeoutMs(timeoutMs) {};
    };

    /**
     * @brief LoraA39C constructor
     */
    LoraA39C(Stream &, byte, byte, Config);

    /**
     * @brief sets the log output stream for library
     * @param logStream stream for log, nullptr for disable logging
     */
    void setLog(Stream *);
    /**
     * @brief configures the module and makes the module enter work mode.
     * Also sets pinMd0 and pinMd1 to output.
     * Please make sure that the stream
     * object is initialized before calling this.
     * @return true if successful
     */
    bool begin();
    /**
     * @brief sets the module to lowpower mode, and set pinMd0 and pinMd1 to
     * input
     */
    void end();
    /**
     * @brief send with lora fix-point
     * @param targetAddress the address of the fix-point target
     * @param str the string to send
     * @return length of sent stuff
     */
    size_t send(LoraA39C::Address targetAddress, const String &);
    /**
     * @overload
     */
    size_t send(LoraA39C::Address targetAddress, const char *);
    /**
     * @overload
     */
    size_t send(LoraA39C::Address targetAddress, const __FlashStringHelper *);
    /**
     * @overload
     */
    size_t send(LoraA39C::Address targetAddress, const uint8_t *, size_t);

    // read-only fields access functions

    /**
     * @brief read pin number of MD0
     */
    byte pinMd0() { return _pinMd0; }
    /**
     * @brief read pin number of MD1
     */
    byte pinMd1() { return _pinMd1; }
    /**
     * @brief read configuration struct
     */
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
    byte _pinMd0; // pin number
    byte _pinMd1; // pin number
    Config _config;
    Stream *_log = nullptr;

    // the status the module is in
    enum class Modes {
        Config,
        Work,
        LowPower,
    };

    // try to log
    void log(const __FlashStringHelper *);
    void log(const String &);

    // try handshake
    bool handshake();
    // try to reset
    bool reset();
    // try to configure module
    bool configure();
    // let the module enter a work mode
    void enterMode(Modes);
    // send fix-point message header
    size_t sendHeader(Address);

    // HACK: this is purely for satisfying inheritance,
    // and MUST NOT BE EXPOSED!
    // use send() instead
    size_t write(uint8_t) override { return 0; }
};

#endif
