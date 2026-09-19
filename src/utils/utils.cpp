#include "utils.h"

// clear stream buffer
void bufClear(Stream &serial) {
    while (serial.read() >= 0) {
    }
}

/**
 * @brief check received content of stream
 *
 * @param serial the stream to check
 * @param buf the expected received content
 * @param len the length of the buffer
 * @param timeoutMs the timeout, in milliseconds
 * @return 0 if ok, 1 if has wrong byte, 2 if timeout
 */
CheckRecReturn checkRec(Stream &serial, byte buf[], size_t len,
                        unsigned long timeoutMs) {
    // NOTE: might run forever
    size_t cnt = 0;
    unsigned long start = millis();
    while (cnt < len) {
        // timeout
        if (millis() - start >= timeoutMs) {
            bufClear(serial);
            return CheckRecReturn::TIMEOUT;
        }

        // try read
        if (serial.available() > 0) {
            byte ret = serial.read();

            if (ret != buf[cnt]) {
                // wrong value
                bufClear(serial);
                return CheckRecReturn::WRONG;
            }
            cnt++;
        }
    }
    bufClear(serial);
    return CheckRecReturn::OK;
}
