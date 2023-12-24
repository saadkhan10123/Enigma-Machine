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

void pushToString(char** str, char c, int size) {
	// This function pushes a character to a string of variable length
	char* temp = malloc(sizeof(char) * (size + 1));
	for (int i = 0; i < size; i++) {
		temp[i] = (*str)[i];
	}
	temp[size] = c;
	*str = temp;
}

void inputString(char* str) {
	// This function takes input from the user
	printf("Enter a string: ");
	char input = ' ';
	int i = 0;
	getchar();
	while (input != '\n') {
		input = getchar();
		pushToString(&str, input, i);
		i++;
	}
	str[i] = '\0';
}

