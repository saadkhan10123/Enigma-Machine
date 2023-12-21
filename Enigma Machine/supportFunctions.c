/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printArray(int arr[], int size) {
	// This function prints an array
	for (int i = 0; i < size; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

int convertToIndex(char c) {
	// This function converts a character to an index
	return (int)c - 97;
}

char convertToChar(int i) {
	// This function converts an index to a character
	return (char)(i + 97);
}

void uppercase(char* text) {
	for (int i = 0; i < strlen(text); i++) {
		// Change lowercase to uppercase
		if (text[i] >= 'a' && text[i] <= 'z') {
			text[i] -= ' ';
		}

		else {
			continue;
		}
	}
}

void printString(char* str) {
	// This function prints a string
	for (int i = 0; i < strlen(str); i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

void printKey(int rotor[], int position[], char* plug, char plugPair[10][2]) {
	// Print out the encryption key
	printf("Key: ");

	//Print Rotors
	for (int i = 0; i < 3; i++) {
		printf("%d", rotor[i] + 1);
	}

	// Print Positions
	for (int i = 0; i < 3; i++) {
		if (position[i] < 10) {
			printf("0%d", position[i]);
		}

		else {
			printf("%d", position[i]);
		}
	}

	// Print Plugs
	for (int i = 0; i < strlen(plug) / 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%c", plugPair[i][j]);

		}
	}
}

int findIndex(int arr[], int value) {
	// This function finds the index of a value in an array
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