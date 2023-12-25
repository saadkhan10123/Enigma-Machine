
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Settings.h"

#pragma warning(disable:4996)

// Colored Text
#define GREEN "\033[1;92m"
#define RED "\033[1;91m"
#define CYAN "\033[1;96m" 
#define YELLOW "\033[1;93m" 

// Reset Color
#define COLOR_RESET "\033[0m"

void startEncryption();
void startDecryption();

int printMenu() {
	int option = 1;
	int keyOption = 0;

	printf(GREEN"-Select Your Option-\n\n"COLOR_RESET);
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

		switch (option)	
		{
		case 1:
			printf(CYAN"\r> Encrypt    Decrypt    Generate Key    Exit"COLOR_RESET);
			break;
		case 2:
			printf(CYAN"\rEncrypt    > Decrypt    Generate Key    Exit"COLOR_RESET);
			break;
		case 3:
			printf(CYAN"\rEncrypt    Decrypt    > Generate Key    Exit"COLOR_RESET);
			break;
		case 4:
			printf(CYAN"\rEncrypt    Decrypt    Generate Key    > Exit"COLOR_RESET);
			break;
		default:
			// Make sure options within range
			if (option > 4) {
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
	// Clear the screen when enter is pressed
	system("cls");
	
	return option;
}

/*
	This function will get input for user
	to determine how the key will be generated
*/
int configurationType() 
{

	int option = 1;
	printf(GREEN"-Choose Key Configuration Type-\n\n"COLOR_RESET);
	
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

void startEncryption() {
	// This function starts the encryption process
	char* str = NULL;
	Settings *settings = malloc(sizeof(Settings));

	initializeRotorSettings(settings);

	inputString(&str);

	char* output = malloc(sizeof(char) * (strlen(str) + 1));
	uppercase(str);
	encrypt(settings, str, output);

	printf("Encrypted: %s\n", output);
}

void startDecryption() {
	// This function starts the decryption process
	char* str = NULL;
	Settings* settings = malloc(sizeof(Settings));

	initializeRotorSettings(settings);

	inputString(&str);

	char* output = malloc(sizeof(char) * (strlen(str) + 1));
	uppercase(str);
	decrypt(settings, str, output);

	printf("Decrypted: %s\n", output);
}
