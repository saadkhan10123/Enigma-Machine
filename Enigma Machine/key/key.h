#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once

#include <stdbool.h>
#include <ctype.h>
#include "../common/settings.h"

void inputRotorsUsed(int* rotor);
void inputRotorPositions(int* position);
void createPairs(char* plug, Settings* settings);
void inputPlugs(Settings* settings);

void manualConfiguration(Settings* settings);
void randomKey(Settings* settings);
void directKeyInput(Settings* settings);
