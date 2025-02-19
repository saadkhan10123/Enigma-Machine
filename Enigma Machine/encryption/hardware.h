#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../common/settings.h"

void rotateRotor(int* rotor);
void initializeRotorSettings(Settings* settings);
void rotateRotors(Settings* settings, int rotationNumber);

int putThroughReflector(Settings* settings, int index);
int putThroughPlugBoard(Settings* settings, int index);