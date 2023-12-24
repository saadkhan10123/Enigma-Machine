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

	char *str = NULL;
	char *output;
	char *decryptOutput;

	inputString(&str);
	
	uppercase(str);
	encrypt(settings, str);
	printf("Encrypted: %s\n", str);
	output = str;

	initializeRotorSettings(settings);
	uppercase(output);
	decrypt(settings, output);
	decryptOutput = output;

	printf("Decrypted: %s\n", str);

	if (strcmp(str, decryptOutput) == 0) {
		printf("Test Passed\n");
	}

	else {
		printf("Test Failed\n");
	}

	free(str);
}

void testKey() {

}

void testEncrypt() {

}

void testDecrypt() {

}

void testEverything() {

}