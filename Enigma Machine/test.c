#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#pragma warning(disable : 4996)

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void testEncryptDecrypt() {
	Settings* settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);

	char* str = NULL;
	char output[1000];
	char decryptOutput[1000];

	inputString(str);
	printf("Input: %s", str);
}

void testKey() {

}

void testEncrypt() {

}

void testDecrypt() {

}

void testEverything() {

}