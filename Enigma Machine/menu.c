
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <Windows.h>
#include "Settings.h"

#pragma warning(disable:4996)
#pragma warning(disable:6031)

// Colored Text
#define GREEN "\033[1;92m"
#define RED "\033[1;91m"
#define CYAN "\033[1;96m" 
#define YELLOW "\033[1;93m" 

// Reset Color
#define COLOR_RESET "\033[0m"

// Function prototypes
void startEncryption();
void startDecryption();
void printMenu();
void useMenuOption(int option);
void generateKey();

// Title screen for the program
void titleScreen()
{
	// ASCII Art for title
	char title[] =
		GREEN"_______________________________________________________________\n"
		"    ______   _   _   _____    _____   __  __                   \n"
		"   |  ____| | \\ | | |_   _|  / ____| |  \\/  |     /\\           \n"
		"   | |__    |  \\| |   | |   | |  __  | \\  / |    /  \\          \n"
		"   |  __|   | . ` |   | |   | | |_ | | |\\/| |   / /\\ \\         \n"
		"   | |____  | |\\  |  _| |_  | |__| | | |  | |  / ____ \\        \n"
		"   |______| |_| \\_| |_____|  \\_____| |_|  |_| /_/    \\_\\       \n"
		"                                                               \n"
		"                                                               \n"
		"  __  __               _____   _    _   _____   _   _   ______ \n"
		" |  \\/  |     /\\      / ____| | |  | | |_   _| | \\ | | |  ____|\n"
		" | \\  / |    /  \\    | |      | |__| |   | |   |  \\| | | |__   \n"
		" | |\\/| |   / /\\ \\   | |      |  __  |   | |   | . ` | |  __|  \n"
		" | |  | |  / ____ \\  | |____  | |  | |  _| |_  | |\\  | | |____ \n"
		" |_|  |_| /_/    \\_\\  \\_____| |_|  |_| |_____| |_| \\_| |______|\n"
		"_______________________________________________________________"COLOR_RESET;


	// Print every character of the title until the null character is reached
	for (char* c = title; *c != '\0'; ++c) {

		// Print character
		putchar(*c);
		fflush(stdout); // Clear the output buffer

		// Time delay on new line to make it more stylish
		if (*c == '\n') {
			Sleep(150);
		}
	}

	printf("\n\n");

	// Blinking text
	bool isVisible = true;

	for (;;) { // Wait for key press
		printf("\r"); // Move cursor to the start

		// Create a blinking effect
		if (isVisible) {
			printf(CYAN"\t\t -PRESS ENTER TO START- "COLOR_RESET); // Print text
		}

		else {
			for (int i = 0; i < 40; ++i) {
				printf(" "); // Hide text
			}
		}

		fflush(stdout); // Clear the output buffer
		
		// Blink timer
		Sleep(500);
		isVisible = !isVisible;

		// Exit title screen when enter pressed
		if (GetAsyncKeyState(VK_RETURN) & 0x8001) {
			MessageBeep(MB_OK); // Play Sound
			Sleep(300); // Input Delay
			break;
		}
	}

	system("cls");
}

// Displays the main menu
void printMenu() {
	fflush(stdin); // Clear the input buffer
	
	int option = 1;
	printf(GREEN"--------------------\n"COLOR_RESET);
	printf(GREEN"-Select Your Option-\n"COLOR_RESET);
	printf(GREEN"--------------------\n\n"COLOR_RESET);
	for (;;) {
		
		// Check for arrow key input
		// Right or up
		if (GetAsyncKeyState(VK_RIGHT) & 0x8001 || GetAsyncKeyState(VK_UP) & 0x8001) {
			MessageBeep(MB_OK); // Play Sound
			option++;
			Sleep(150); // Input Delay
		}

		// Left or down
		if (GetAsyncKeyState(VK_LEFT) & 0x8001 || GetAsyncKeyState(VK_DOWN) & 0x8001) {
			MessageBeep(MB_OK); // Play Sound
			option--;
			Sleep(150); // Input Delay
		}
		
		// Keep an arrow over the option currently selected
		switch (option)	
		{
		case 1:
			printf(CYAN"\r> Encrypt    Decrypt    Exit"COLOR_RESET);
			break;
		case 2:
			printf(CYAN"\rEncrypt    > Decrypt    Exit"COLOR_RESET);
			break;
		case 3:
			printf(CYAN"\rEncrypt    Decrypt    > Exit"COLOR_RESET);
			break;
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
			MessageBeep(MB_OK); // Play Sound
			Sleep(300); // Input Delay
			break;
		}
	}
	// Clear the screen when enter is pressed
	system("cls");
	
	useMenuOption(option);
}

// Menu for method of string input
int stringInputMenu() {
	int option = 1;
	fflush(stdin);
	
	getchar(); // Clear the input buffer
	getchar();

	printf(GREEN"--------------------------------\n"COLOR_RESET);
	printf(GREEN"-Select Method for String Input-\n"COLOR_RESET);
	printf(GREEN"--------------------------------\n\n"COLOR_RESET);

	for (;;) {
		// Check for arrow key input
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			
			case 75: // Left arrow
				MessageBeep(MB_OK); // Play Sound
				option--;
				Sleep(150); // Input Delay
				break;
			
			case 77: // Right arrow
				MessageBeep(MB_OK); // Play Sound
				option++;
				Sleep(150); // Input Delay
				break;
			}

			// Make sure options are within range
			if (option > 2) {
				option = 1;
			}
			if (option < 1) {
				option = 2;
			}
		}

		// Keep an arrow over the option currently selected
		switch (option) {
		case 1:
			printf(CYAN"\r> Enter String    Get String From File"COLOR_RESET);
			break;
		case 2:
			printf(CYAN"\rEnter String    > Get String From File"COLOR_RESET);
			break;
		}

		// Break out of the loop when enter key is pressed
		if (_kbhit() && _getch() == 13) { // 13 is the ASCII code for Enter key
			MessageBeep(MB_OK); // Play Sound
			Sleep(300); // Input Delay
			break;
		}

	}

	// Clear the screen when enter is pressed
	system("cls");

	return option;
}

void useMenuOption (int option) {
	
	switch (option)	{
	// Encrypt
	case 1:
		startEncryption();
		break;
	
	// Decrypt
	case 2:
		startDecryption();
		break;
	
	// Exit
	case 3:
		exit(EXIT_SUCCESS);
		break;
	
	default:
		break;
	}
}

// Generate the encryption key
void generateKey() {
	Settings *settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);
	printKey(settings);
}


// Menu to determine how the key will be generated
void keyConfigurationType(Settings* settings) {
	fflush(stdin); // Clear the input buffer
	
	int option = 1;

	printf(GREEN"-------------------------------\n"COLOR_RESET);
	printf(GREEN"-Choose Key Configuration Type-\n"COLOR_RESET);
	printf(GREEN"-------------------------------\n\n"COLOR_RESET);

	for (;;) {
		
		// Check for arrow key input
		// Right or up
		if (GetAsyncKeyState(VK_RIGHT) & 0x8001 || GetAsyncKeyState(VK_UP) & 0x8001) {
			MessageBeep(MB_OK); // Play Sound
			option++;
			Sleep(150); // Input Delay
		}

		// Left or down
		if (GetAsyncKeyState(VK_LEFT) & 0x8001 || GetAsyncKeyState(VK_DOWN) & 0x8001) {
			MessageBeep(MB_OK); // Play Sound
			option--;
			Sleep(150); // Input Delay
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

			// Make sure options are  within range
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
			MessageBeep(MB_OK); // Play Sound
			Sleep(300); // Input Delay
			break;
		}
	}
	system("cls");

	// Call function depending upon user choice
	// Call function depending upon user choice
	switch (option)	{
		case 1:
			// Manually set up encryption settings
			// Manually set up encryption settings
			manualConfiguration(settings);
			break;
			break;
		case 2:
			// Generate random encryption key
			randomKey(settings);
			break;
		case 3:
			// Directly get an input for encryption key
			directKeyInput(settings);
			break;
		default:
			break;
	}
}

// Ask the user if he/she wants to read output from a file
void askInput(char** str) {
	system("cls");
	// Get method for string input
	int option = stringInputMenu();

	switch (option) {
	// Get input on the console
	case 1:
		printf(GREEN"-Enter String-\n\n"COLOR_RESET);
		printf(GREEN"-Press Enter Twice to Confirm-\n\n"COLOR_RESET);
		inputString(str);
		break;

	// Get input from file
	case 2:
		// File name
		printf(GREEN"-Enter File Name-\n\n"COLOR_RESET);
		char fileName[100] = "";

		for (;;) {
			// Check for valid file name
			scanf("%s", fileName);
			if (strlen(fileName) > 0) {
				if (fileName[strlen(fileName) - 1] == '\n') {
					fileName[strlen(fileName) - 1] = '\0';
				}
				break;
			}

			else {
				printf(RED"Invalid input\n"COLOR_RESET);
			}
		}

		// Get input from a file
		inputFile(str, fileName);
		break;

	default:
		break;
	}

}

// Ask the user if he/she wants to write output to a file
void askFileOutput(char* output) {
	printf(GREEN"-----------------------------------------------\n"COLOR_RESET);
	printf(GREEN"Do you want to save the output to a file? (y/n)\n"COLOR_RESET);
	printf(GREEN"-----------------------------------------------\n"COLOR_RESET);

	// Get input for user choice
	char choice;

	// Error handing
	for(;;) {
		scanf("%c", &choice);
		
		// User entered yes
		if (choice == 'y' || choice == 'Y') {
			break;
		}

		// User entered no
		else if (choice == 'n' || choice == 'N') {
			return;
		}

		// Invalid input
		else {
			printf(RED"Invalid input\n"COLOR_RESET);
		}
	}

	// File name
	printf(GREEN"-Enter File Name-\n\n"COLOR_RESET);
	char fileName[100] = "";

	for (;;) {
		scanf("%s", fileName);
		// Check for valid file name
		if (strlen(fileName) > 0) {
			if (fileName[strlen(fileName) - 1] == '\n') {
				fileName[strlen(fileName) - 1] = '\0';
			}
			break;
		}

		else {
			printf(RED"Invalid input\n"COLOR_RESET);
		}
	}
	// Write the output to a file
	outputFile(output, fileName);
}

void startEncryption() {
	
	// This function starts the encryption process
	char* str = NULL;
	Settings *settings = malloc(sizeof(Settings));

	// Get the key 
	keyConfigurationType(settings);

	// Initialize the Machine
	initializeRotorSettings(settings);

	// Get the input from the user
	askInput(&str);

	// Make a string to store the output
	char* output = malloc(sizeof(char) * (strlen(str) + 1));

	// Make the string uppercase
	uppercase(str);

	// Encrypt the string
	encrypt(settings, str, output);
	
	// Print the output
	printf(GREEN"Encrypted string: \n%s"COLOR_RESET, output);

	printf("\n\n");

	// Ask the user if he/she wants to save the output to a file
	askFileOutput(output);

	// Print the key
	printKey(settings);
}

void startDecryption() {
	// This function starts the decryption process
	// Make a String
	char* str = NULL;
	Settings* settings = malloc(sizeof(Settings));

	// Get the key
	directKeyInput(settings);

	// Initialize the Machine
	initializeRotorSettings(settings);

	// Get the input from the user
	askInput(&str);

	// Make a string to store the output
	char* output = malloc(sizeof(char) * (strlen(str) + 1));

	// Make the string uppercase
	uppercase(str);

	// Decrypt the string
	decrypt(settings, str, output);

	// Print the output
	printf(CYAN"Decrypted string: \n%s\n"COLOR_RESET, output);

	printf("\n\n");

	// Ask the user if he/she wants to save the output to a file
	askFileOutput(output);
}
