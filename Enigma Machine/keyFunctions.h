#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Settings.h"

// all functions in key.c

void inputRotorsUsed(int rotors[]);
void inputRotorPositions(int positions[]);
void createPairs(char* plug, Settings* settings);
void inputPlugs(Settings* settings);
void manualConfiguration(Settings* settings);
void randomKey(Settings* settings);
void directKeyInput(Settings* settings);

