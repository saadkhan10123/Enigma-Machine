#pragma once

#include "../common/settings.h"

int encryptThroughRotor(Settings* settings, int rotorNumber, int index);
void encrypt(Settings* settings, char* str, char* output);