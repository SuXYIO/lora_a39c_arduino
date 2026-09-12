#include "utils.h"

// clear stream buffer
void bufClear(Stream &serial) {
    while (serial.read() >= 0) {
    }
}

// check return of stream
bool checkRet(Stream &serial, byte buf[], size_t len) {
    // NOTE: might run forever
    size_t cnt = 0;
    while (true) {
        if (cnt >= len)
            break;
        if (serial.available() > 0) {
            byte ret = serial.read();

            if (ret != buf[cnt]) {
                // wrong value
                return false;
            }
            cnt++;
        }
    }
    bufClear(serial);
    return true;
}
