#pragma once
#ifndef LORAA39C_UTILS_H
#define LORAA39C_UTILS_H

#include <Arduino.h>

void bufClear(Stream &);

enum class CheckRecReturn {
    OK = 0,
    WRONG = 1,
    TIMEOUT = 2,
};
CheckRecReturn checkRec(Stream &, byte[], size_t, unsigned long);

#endif
