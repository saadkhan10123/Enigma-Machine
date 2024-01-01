#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Settings.h"

#pragma warning(disable : 4996)

// This file is for debugging and testing purposes only
// You don't need to know how it works :)


void printSettings(Settings settings);

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
	Settings *settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);

	printSettings(*settings);

	char *str = malloc(sizeof(char) * 100);
	char *output = malloc(sizeof(char) * 100);
	printf("Enter String: ");
	scanf_s("%s", str, 100);

	uppercase(str);
	encrypt(settings, str, output);
	printf("Encrypted: %s\n", output);
}

void testDecrypt() {

}

void testEverything() {

}

void printSettings(Settings settings) {
	// This function prints the settings
	// Print Rotors
	printf("Rotors Used: ");
	printArray(settings.rotorsUsed, 3);

	// Print Positions for Rotors
	printf("Rotor Positions: ");
	printArray(settings.defaultPositions, 3);

	// Print the Plugboard
	printf("Plugboard: ");

	for (int i = 0; i < 10; i++) {
		printf("%c%c ", convertToChar(settings.plugBoard[i][0]), convertToChar(settings.plugBoard[i][1]));
	}

	printf("\n");

	printf("Rotors: \n");
	for (int i = 0; i < 5; i++) {
		printArray(settings.rotors[i], 26);
	}
}

void makeRandomString(char* str, int length) {
	// This function makes a random string of specified length
	for (int i = 0; i < length; i++) {
		str[i] = convertToChar(rand() % 26);
	}
	str[length] = '\0';
}