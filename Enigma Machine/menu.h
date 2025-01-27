#pragma once

#include "helper.h"
#include "hardware.h"
#include "settings.h"

void startEncryption();
void startDecryption();

void printMenu();

void useMenuOption(int option);
void generateKey();

void titleScreen();

int stringInputMenu();
void generateKey();

void keyConfigurationType(Settings* settings);

void askInput(char** str);

void askFileOutput(char* output);