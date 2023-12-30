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

// This function prints an array
void printArray(int* arr, int size) {

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

void expandString(char** str) {
	// This function expands the size of a string by 100 characters
	char* temp = (char*)malloc((strlen(*str) + 100) * sizeof(char));

	if (temp == NULL) {
		perror(RED"Unable to Allocate Memory\n"COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	strcpy(temp, *str);
	//free(*str);
	*str = temp;
}

void inputString(char** str) {
	fflush(stdin); // Clear the input buffer
	
	// This function takes input from the user
	*str = (char*)malloc(100 * sizeof(char));

	if (*str == NULL) {
		perror(RED"Unable to Allocate Memory\n"COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	/*printf("Press Enter twice to confirm input\n");
	printf("Enter a string:\n");*/
	char input;
	int i = 0;

	for (;;) {
		if ((i + 1) % 100 == 0) {
			(*str)[i] = '\0';
			expandString(str);
		}

		input = getchar();

		// Break loop with double enter
		if (input == '\n') {
			if (i > 1 && (*str)[i - 1] == '\n') {
				break;
			}
			else if (i == 0) {
				printf("Invalid input\n");
				continue;
			}
		}

		(*str)[i] = input;
		i++;
	}
	(*str)[i - 1] = '\0';
}

// This function takes input from a file
void inputFile(char** str, char* fileName) {

	FILE* fp = fopen(fileName, "r");
	
	if (fp == NULL) {
		perror(RED"File Does Not Exist\n"COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	// Create a string for input
	*str = (char*)malloc(100 * sizeof(char));

	// Unable to allocate memory to string
	if (*str == NULL) {
		perror(RED"Unable To Allocate Memory\n"COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	char input;
	int i = 0;

	for (;;) {
		// Expand the buffer size
		if ((i + 1) % 100 == 0) {
			(*str)[i] = '\0';
			expandString(str);
		}

		// Get input from file
		input = fgetc(fp);

		// Break loop with double enter
		if (input == EOF) {
			break;
		}

		// Put input into string
		(*str)[i] = input;
		i++;
	}

	
	(*str)[i] = '\0';

	// Check for empty file
	if (i == 0) {
		perror(RED"File is Empty\n"COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	fclose(fp);
}

// This function prints the settings
void printSettings(Settings settings) {
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

void outputFile(char* str, char* fileName) {
	// This function outputs to a file
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("File not found\n");
		exit(1);
	}

	for (int i = 0; i < strlen(str); i++) {
		fputc(str[i], fp);
	}
	fclose(fp);
}