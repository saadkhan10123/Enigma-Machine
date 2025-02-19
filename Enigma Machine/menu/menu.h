#pragma once

#include "../common/helper.h"
#include "../encryption/hardware.h"
#include "../common/settings.h"

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