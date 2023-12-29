#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void inputRotorsUsed(int rotor[]) {
	fflush(stdin); // Clear the input buffer
	
	printf(YELLOW);
	// This function takes input from user and sets the rotors used
	printf("Set Rotor Configuration\n");

	for (int i = 0; i < 3; i++) {
		
		// Get input for rotors used
		printf("Rotor %d: ", i + 1);
		scanf_s("%d", &rotor[i]);

		rotor[i]--; // Convert to index [0, 4]

		// Check for valid input
		if (rotor[i] < 0 || rotor[i] > 4) {
			printf("Enter a Valid Number\n");
			i--;
			continue;
		}

		// Check for repition
		for (int j = 0; j < i; j++) {
			if (rotor[i] == rotor[j]) {
				printf("Enter a Distinct Number\n");
				i--;
			}
		}
	}
	printf(COLOR_RESET);
}

void inputRotorPositions(int position[]) {
	fflush(stdin); // Clear the input buffer
	
	printf(YELLOW);
	printf("\nSet Rotor Positions\n");

	for (int i = 0; i < 3; i++) {

		// Get input for rotor positions
		printf("Position Rotor %d: ", i + 1);
		scanf_s("%d", &position[i]);
		position[i]--;

		// Check for valid input
		if (position[i] < 0 || position[i] > 25) {
			printf("Enter a Valid Number\n");
			i--;
			continue;
		}
	}
	printf(COLOR_RESET);
}

void createPairs(char* plug, Settings* settings) {
	// Split plugs into pairs of 2
	for (int i = 0; i < strlen(plug) / 2; i++) {
		settings->plugBoard[i][0] = convertToIndex(plug[2 * i]);
		settings->plugBoard[i][1] = convertToIndex(plug[(2 * i) + 1]);
	}
}

void inputPlugs(Settings* settings) {
	fflush(stdin); // Clear the input buffer
	
	printf(YELLOW);
	
	int n = 0;
	char plug[21];
	do {
		printf("\nSet Plug Configurations: ");
		scanf_s("%s", plug, 21);

		for (int i = 0; i < strlen(plug); i++) {

			// Invalid Input
			if (plug[i] < 'A' || plug[i] > 'z') {
				continue;
			}

			// Add number of valid plugs if no invalid input
			else {
				n++;
			}

			// Check for repition
			for (int j = i + 1; j < strlen(plug); j++) {
				if (plug[i] == plug[j]) {
					n--; // Decrease no. of valid plugs by 1
				}
			}
		}

		// Error messages
		if (n < strlen(plug)) {
			printf("Enter a Valid Configuration\n");
		}

		if (strlen(plug) % 2 != 0) {
			printf("Plugs Should be in Pairs of 2\n");
		}

		/*
			Two conditions are checked for valid input of plugs:

			1. No plug is invalid
			2. Number of plugs should be a multiple of 2
		*/

	} while (n < strlen(plug) || strlen(plug) % 2 != 0);
	printf(COLOR_RESET);

	uppercase(plug); // Convert all characters to uppercase)
	createPairs(plug, settings);
}

void manualConfiguration(Settings* settings) {

	// This function takes input from user and sets the encryption key
	inputRotorsUsed(settings->rotorsUsed);
	inputRotorPositions(settings->defaultPositions);
	inputPlugs(settings);
}

// Function to generate random values for rotor, position, and plug arrays
void randomKey(Settings* settings) {
	fflush(stdout); // Clear the input buffer
	
	srand((unsigned)time(NULL));

	char plug[21] = " ";

	// Generate random values for rotor 
	for (int i = 0; i < 3; i++) {
		settings->rotorsUsed[i] = rand() % 5;  // Values between 0 and 4

		// Check for repetition
		for (int j = 0; j < i; j++) {
			if (settings->rotorsUsed[i] == settings->rotorsUsed[j]) {
				i--;
				break;
			}
		}
	}

	// Generate random values for position 
	for (int i = 0; i < 3; i++) {
		settings->defaultPositions[i] = (rand() % 26);  // Values between 0 and 25
	}

	int plugsUsed; // Number of plugs used
	for (;;) {
		plugsUsed = (rand() % 19) + 2; // Values between 2 and 20

		// Number should be a multiple of 2
		if (plugsUsed % 2 != 0) {
			continue;
		}

		// Exit loop when number of plugs is valid
		break;
	}
	
	// Generate random values for plug 
	for (int i = 0; i < plugsUsed; i++) {
		plug[i] = 'A' + (rand() % 26);  // Random capital letter

		// Check for repetition
		for (int j = 0; j < i; j++) {
			if (plug[i] == plug[j]) {
				i--;
				break;
			}
		}
		// Add null character at the end of the string
		plug[i + 1] = '\0';

		// Convert plugs to pairs
		createPairs(plug, settings);

	}
}

// Get key directly from user
void directKeyInput(Settings *settings) {
	fflush(stdin); // Clear the input buffer
	
	char key[30] = " ";
	char plug[21] = " ";

	// Conditions to check validity of key
	bool keyValid = true;

	do {
		// Get user input
		printf("Enter the Encryption Key: ");
		scanf("%s", key);

		uppercase(key);

		bool rotorsValid = true;
		// Validity of rotors in the key
		for (int i = 0; i < 3; i++) {
			// Rotors used between 1 and 5
			if (!(key[i] >= '1' && key[i] <= '5')) {
				rotorsValid = false;
				break;
			}

			// Check for repetition
			if (key[i] == key[i + 1]) {

				rotorsValid = false; // Not valid if rotors used are repeated
				break;
			}
		}

		bool positionsValid = true;
		// Validity of positions in the key
		for (int i = 3; i < 9; i++) {
			// Rotor position between 00 and 25
			if (!(key[i] >= '0' && key[i] <= '2' && key[i + 1] >= '0' && key[i + 1] <= '9')) {

				positionsValid = false;
				break;
			}
			i++; // Skip the second digit of the two-digit number
		}

		bool plugsValid = true;
		// Validity of plugs in the key
		for (int i = 9; i < strlen(key); i++) {
			// Plugs between A and Z
			if (!(key[i] >= 'A' && key[i] <= 'Z')) {
				plugsValid = false;
				break;
			}

			// Check for repetition
			if (key[i] == key[i + 1]) {

				plugsValid = false; // Not valid if plugs are repeated
				break;
			}
		}

		keyValid = rotorsValid && positionsValid && plugsValid;

		// Check if plugs are in pairs
		if (strlen(key) % 2 == 0) {
			keyValid = false;
		}

		// Display message for success or failure
		if (keyValid) {
			printf("\nKey Entered Successfully!");
		}
		else
		{
			printf("\nEncryption Key is Invalid");
		}

		printf("\n");

		// Get values for rotors used
		for (int i = 0; i < 3; i++) {
			settings->rotorsUsed[i] = (int)(key[i]) - '1'; // Values between 0 and 5
		}

		// Get values for rotor position
		for (int i = 3, j = 0; i < 9; i += 2, j++) {

			// Extract two digits from the string and convert them to an integer
			int number = (key[i] - '0') * 10 + (key[i + 1] - '0');

			// Assign the extracted number to the array
			settings->defaultPositions[j] = number; // Values Between 0 and 25
		}

		// Get values for plugs connected
		for (int i = 0, j = 0; key[i] != '\0'; i++) {

			// Check for alphabets (plugs)
			if (isalpha(key[i])) {
				plug[j] = key[i]; // Assign value to plug
				j++;
			}
			plug[j] = '\0'; // Add null character at the end of the string]
		}

		// Convert plugs to pairs
		createPairs(plug, settings);
	} while (!keyValid);
}
