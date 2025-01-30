#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <stdbool.h>
#include "settings.h"

void printArray(int* arr, int size);

int convertToIndex(char c);
char convertToChar(int i);

void uppercase(char* text);

// Print out the encryption key
void printKey(Settings* settings);

int findIndex(int* arr, int value);

void expandString(char** str);
void inputString(char** str);

void inputFile(char** str, char* fileName);
void outputFile(char* str, char* fileName);