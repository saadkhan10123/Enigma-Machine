#pragma once

#include "../common/settings.h"

int decryptThroughRotor(Settings* settings, int rotorNumber, int index);
void decrypt(Settings* settings, char* str, char* output);