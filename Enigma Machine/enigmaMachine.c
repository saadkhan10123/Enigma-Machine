/*
	Muhammad Saad Khan 
	Ali Ahmad
	28-11-2023
	Enigma Machine
*/
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

int convertToIndex(char c);
void uppercase(char* text);



void test() {
	// This is a test function to test the enigma machine
	/*Settings* settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);*/

	/*printf("First rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[0]], 26);
	printf("-------------------- \n");
	printf("Second rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[1]], 26);
	printf("-------------------- \n\n");
	printf("Third rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[2]], 26);
	printf("-------------------- \n\n");*/

	// Test the encrypt and decrypt functions with a rendomly generated string
	for (int i = 0; i < 100000; i++) {
		Settings* settings = malloc(sizeof(Settings));
		initializeRotorSettings(settings);

		char str[1000];
		char output[1000];
		char decryptOutput[1000];

		int stringLength = rand() % 900;
		makeRandomString(str, stringLength);

		encrypt(settings, str, output);
		decrypt(settings, output, decryptOutput);

		for (int i = 0; i < strlen(str); i++) {
			int index = convertToIndex(str[i]);
			index = putThroughReflector(settings, index);

			output[i] = convertToChar(index);

			index = putThroughReflector(settings, index);

			decryptOutput[i] = convertToChar(index);

			decryptOutput[i + 1] = '\0';
			output[i + 1] = '\0';
		}

		bool isSame = true;
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] != decryptOutput[i]) {
				isSame = false;
				printf("Original string: ");
				printf("%s \n", str);
				printf("Encrypted string: ");
				printf("%s \n", output);
				printf("Decrypted string: ");
				printf("%s \n", decryptOutput);
				exit(0);
				break;
			}
		}

		printf("String %2d secceded \n", i + 1);

		/*printf("Original String: %s \n", str);
		printf("First Pass: %s \n", output);
		printf("Second Pass: %s \n", decryptOutput);*/

		/*printf("First rotor: \n");
		rotateRotors(settings, i);
		printArray(settings->rotors[settings->rotorsUsed[0]], 26);
		printf("-------------------- \n");
		printf("Second rotor: \n");
		printArray(settings->rotors[settings->rotorsUsed[1]], 26);
		printf("-------------------- \n\n");*/
		free(settings);
	}
}


int main(void) {
	srand(time(NULL));

	// Comment this out to test the enigma machine with a randomly generated string
	// Uncomment this to test the enigma machine with a string entered by the user
	Settings *settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);

	char str[1000];

	printf("Enter a string to encrypt: ");
	scanf_s("%s", str, 1000);
	char* output = malloc(sizeof(char) * strlen(str));

	encrypt(settings, str, output);

	printf("Encrypted string: ");
	printString(output);

	initializeRotorSettings(settings);
	char* decryptOutput = malloc(sizeof(char) * strlen(str));
	decrypt(settings, output, decryptOutput);

	printf("Decrypted string: ");
	printString(decryptOutput);

	// Comment the test() function to test the enigma machine with a string entered by the user
	//test();
	return 0;
}
