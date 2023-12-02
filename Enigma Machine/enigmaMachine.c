/*
	Muhammad Saad Khan 
	Ali Ahmed
	28-11-2023
	Enigma Machine
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
	int rotors[5][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void rotateRotor(int *rotor);
void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

int convertToIndex(char c) {
	return (int)c - 97;
}

char convertToChar(int i) {
	return (char)(i + 97);
}

void printString(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

int findIndex(int arr[], int value) {
	for (int i = 0; i < 26; i++) {
		if (arr[i] == value) {
			return i;
		}
	}
	return -1;
}

// Make a random string of specified length
void makeRandomString(char* str, int length) {
	for (int i = 0; i < length; i++) {
		str[i] = convertToChar(rand() % 26);
	}
	str[length] = '\0';
}

void initializeRotorSettings(Settings* settings) {
	// Initialize rotor positions to 0

	int rotorsUsedSettings[3] = { 0, 1, 2 };

	for (int i = 0; i < 3; i++) {
		settings->rotorsUsed[i] = rotorsUsedSettings[i];
	}

	// Initialize rotors
	int rotorSettings[5][26] = {
		{4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9},
		{0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4},
		{1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14},
		{4, 18, 14, 21, 15, 25, 9, 0, 24, 16, 20, 8, 17, 7, 23, 11, 13, 5, 19, 6, 10, 3, 2, 12, 22, 1},
		{21, 25, 1, 17, 6, 8, 19, 24, 20, 15, 18, 3, 13, 7, 11, 23, 0, 22, 12, 9, 16, 14, 5, 4, 2, 10}
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 26; j++) {
			settings->rotors[i][j] = rotorSettings[i][j];
		}
	}

	int rotorPositionsSettings[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < rotorPositionsSettings[i]; j++) {
			rotateRotor(settings->rotors[settings->rotorsUsed[i]]);
		}
	}

	// Initialize reflector
	int reflectorSettings[26] = { 24, 17, 20, 7, 16, 18, 11, 3, 15, 23, 13, 6, 14, 10, 12, 8, 4, 1, 5, 25, 2, 22, 21, 9, 0, 19 };
	for (int i = 0; i < 26; i++) {
		settings->reflector[i] = reflectorSettings[i];
	}

	// Initialize plugboard
	// This contains reflexive pairs of numbers
	int plugBoardSettings[10][2] = { {0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {10, 11}, {12, 13}, {14, 15}, {16, 17}, {18, 19} };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			settings->plugBoard[i][j] = plugBoardSettings[i][j];
		}
	}
}

int putThroughRotor(Settings* settings, int rotorNumber, int index) {
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	return settings->rotors[rotorUsed][index];
}

int decryptThroughRotor(Settings* settings, int rotorNumber, int index) {
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	int rotorIndex = findIndex(settings->rotors[rotorUsed], index);
	return rotorIndex;
}

void rotateRotor(int *rotor) {
	int temp = rotor[0];
	for (int i = 0; i < 25; i++) {
		rotor[i] = rotor[i + 1];
	}
	rotor[25] = temp;
}

void rotateRotors(Settings* settings, int rotationNumber) {
	rotateRotor(settings->rotors[settings->rotorsUsed[0]]);
	if (rotationNumber % 26 == 0) {
		rotateRotor(settings->rotors[settings->rotorsUsed[1]]);
		if (rotationNumber % 676 == 0) {
			rotateRotor(settings->rotors[settings->rotorsUsed[2]]);
		}
	}
}

int putThroughReflector(Settings* settings, int index) {
	return settings->reflector[index];
}

int putThroughPlugBoard(Settings* settings, int index) {
	for (int i = 0; i < 10; i++) {
		if (settings->plugBoard[i][0] == index) {
			return settings->plugBoard[i][1];
		}
		else if (settings->plugBoard[i][1] == index) {
			return settings->plugBoard[i][0];
		}
	}
	return index;
}

void encrypt(Settings* settings, char* str, char* output) {
	// Iterate through the string
	for (int i = 0; i < strlen(str); i++) {
		int index = convertToIndex(str[i]);
		int j;

		index = putThroughPlugBoard(settings, index);

		for (j = 0; j < 3; j++) {
			index = putThroughRotor(settings, j, index);
		}

		index = putThroughReflector(settings, index);

		for (j = 2; j >= 0; j--) {
			index = putThroughRotor(settings, j, index);
		}
		rotateRotors(settings, i);
		index = putThroughPlugBoard(settings, index);

		output[i] = convertToChar(index);
	}
	output[strlen(str)] = '\0';
}

void decrypt (Settings* settings, char* str, char* output) {
	// Iterate through the string
	for (int i = 0; i < strlen(str); i++) {
		int index = convertToIndex(str[i]);
		int j;

		index = putThroughPlugBoard(settings, index);

		for (j = 0; j < 3; j++) {
			index = decryptThroughRotor(settings, j, index);
		}

		index = putThroughReflector(settings, index);

		for (j = 2; j >= 0; j--) {
			index = decryptThroughRotor(settings, j, index);
		}
		rotateRotors(settings, i);
		index = putThroughPlugBoard(settings, index);

		output[i] = convertToChar(index);
	}
	output[strlen(str)] = '\0';
}

void test() {

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

	/*Settings *settings = malloc(sizeof(Settings));
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
	printString(decryptOutput);*/

	test();
	return 0;
}