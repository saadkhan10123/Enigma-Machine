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

/*
	This function will get input for user
	to determine how the key will be generated
*/
int configurationType() 
{

	int option = 1;
	printf(GREEN"-Choose Configuration Type-\n\n"COLOR_RESET);
	
	// Prompt user to input value
	for (;;) {
		

		// Check for arrow key input
		// Right or up
		if (GetAsyncKeyState(VK_RIGHT) & 0x8001 || GetAsyncKeyState(VK_UP) & 0x8001) {
			option++;
			Sleep(150);
		}

		// Left or down
		if (GetAsyncKeyState(VK_LEFT) & 0x8001 || GetAsyncKeyState(VK_DOWN) & 0x8001) {
			option--;
			Sleep(150);
		}

		// Keep an arrow over the option currently selected
		switch (option)
		{
		case 1:
			printf(CYAN"\r> Manual Configuration    Randomly Generated Key    Enter Pre-Existing Key"COLOR_RESET);
			break;

		case 2:
			printf(CYAN"\rManual Configuration    > Randomly Generated Key    Enter Pre-Existing Key"COLOR_RESET);
			break;

		case 3:
			printf(CYAN"\rManual Configuration    Randomly Generated Key    > Enter Pre-Existing Key"COLOR_RESET);

		default:

			// Make sure options within range
			if (option > 3) {
				option = 1;
			}

			if (option < 1) {
				option = 3;
			}

			break;
		}

		// Break out of the loop when enter key is pressed
		if (GetAsyncKeyState(VK_RETURN) & 0x8001) {
			Sleep(250);
			break;
		}
	}

	system("cls");

	return option;
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

