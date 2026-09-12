#pragma once
#ifndef LORAA39C_UTILS_H
#define LORAA39C_UTILS_H

#include <Arduino.h>

void bufClear(Stream &);
bool checkRet(Stream &, byte[], size_t);

#endif
