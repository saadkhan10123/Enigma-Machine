/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

// Colored Text
#define GREEN "\033[1;92m"
#define RED "\033[1;91m"
#define CYAN "\033[1;96m" 
#define YELLOW "\033[1;93m" 

// Reset Color
#define COLOR_RESET "\033[0m"

void printArray(int arr[], int size) {
	// This function prints an array
	for (int i = 0; i < size; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

int convertToIndex(char c) {
	// This function converts a character to an index
	return (int)c - 65;
}

char convertToChar(int i) {
	// This function converts an index to a character
	return (char)(i + 65);
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

// Print out the encryption key
void printKey(int rotor[], int position[], char* plug, char plugPair[10][2]) {

	printf(GREEN"-Encryption Key: "COLOR_RESET);

	//Print Rotors
	for (int i = 0; i < 3; i++) {
		printf(GREEN"%d"COLOR_RESET, rotor[i] + 1);
		Sleep(50);
	}

	// Print Positions
	for (int i = 0; i < 3; i++) {
		if (position[i] < 10) {
			printf(GREEN"0%d"COLOR_RESET, position[i]);
			Sleep(50);
		}

		else {
			printf(GREEN"%d"COLOR_RESET, position[i]);
			Sleep(50);
		}
	}

	// Print Plugs
	for (int i = 0; i < strlen(plug) / 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf(GREEN"%c"COLOR_RESET, plugPair[i][j]);
			Sleep(50);
			
		}
	}

	printf("\n");
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
	// This function pushes a character to a string of variable length using realloc
	*str = (char *)realloc(*str, (size + 1) * sizeof(char));
	(*str)[size] = c;
}

void inputString(char** str) {
	// This function takes input from the user
	printf("Enter a string: ");
	char input = ' ';
	int i = 0;
	getchar();
	while (input != '\n') {
		input = getchar();
		pushToString(str, input, i);
		i++;
	}
	(*str)[i - 1] = '\0';
}

