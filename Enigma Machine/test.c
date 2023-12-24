#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Settings.h"

#pragma warning(disable : 4996)

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