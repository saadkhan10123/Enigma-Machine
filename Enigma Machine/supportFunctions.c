/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <stdbool.h>
#include "Settings.h"

// Colored Text
#define GREEN "\033[1;92m"
#define RED "\033[1;91m"
#define CYAN "\033[1;96m" 
#define YELLOW "\033[1;93m" 

// Reset Color
#define COLOR_RESET "\033[0m"

#pragma warning(disable : 4996)

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
void printKey(Settings *settings) {

	printf(GREEN"-Encryption Key: "COLOR_RESET);

	//Print Rotors
	for (int i = 0; i < 3; i++) {
		printf(GREEN"%d"COLOR_RESET, settings->rotorsUsed[i] + 1);
		Sleep(50);
	}

	// Print Positions
	for (int i = 0; i < 3; i++) {
		if (settings->defaultPositions[i] < 10) {
			printf(GREEN"0%d"COLOR_RESET, settings->defaultPositions[i]);
			Sleep(50);
		}

		else {
			printf(GREEN"%d"COLOR_RESET, settings->defaultPositions[i]);
			Sleep(50);
		}
	}

	// Print Plugs
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			printf(GREEN"%c"COLOR_RESET, convertToChar(settings->plugBoard[i][j]));
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

void pushToString(char** str, char c) {
	// This function pushes a character to a string of variable length using malloc
	int size = (int)strlen(*str);
	char* temp = (char*)malloc(size + 2);
	strcpy(temp, *str);
	temp[size] = c;
	temp[size + 1] = '\0';
	free(*str);
	*str = temp;
}

void inputString(char** str) {
	// Clear the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	// This function takes input from the user
	system("cls");
	printf("Press Enter twice to confirm input\n");
	char input = 2;
	int i = 0;
	while (true) {
		input = getchar();
		pushToString(str, input);
		if (input == '\n') {
			if (i == 0) {
				printf("Enter a valid string: \n");
				continue;
			}
			else if ((*str)[i - 1] == '\n') {
				break;
			}
		}
		i++;
	}
}


void printSettings(Settings settings) {
	// This function prints the settings
	printf("Rotors Used: ");
	printArray(settings.rotorsUsed, 3);
	printf("Rotor Positions: ");
	printArray(settings.defaultPositions, 3);
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
