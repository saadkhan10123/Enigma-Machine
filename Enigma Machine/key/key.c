#include "../common/helper.h"
#include "key.h"
#include "../common/colours.h"
#include <time.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)

void inputRotorsUsed(int* rotor) {
	// Clear the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	// String buffer for input
	char input[20] = "";

	printf(GREEN"\n-Set Rotors Used-\n"COLOR_RESET);

	for (int i = 0; i < 3; i++) {
		// Prompt user for rotor input
		printf(YELLOW"Rotor %d: "COLOR_RESET, i + 1);

		// Read user input
		if (scanf("%s", input) != 1) {
			// Handle input reading error
			printf(RED"Error reading input\n"COLOR_RESET);
			exit(EXIT_FAILURE);
		}

		// Convert input to a long integer
		char* endptr;
		long rotorPosition = strtol(input, &endptr, 10);

		// Check for conversion errors or out-of-range values
		if (*endptr != '\0' || rotorPosition < 1 || rotorPosition > 5) {
			// Handle invalid input
			printf(RED"Enter a Valid Number between 1 and 5\n"COLOR_RESET);
			i--;
			continue;
		}

		// Convert char into a number and store in the rotor array
		rotor[i] = (int)rotorPosition - 1;

		// Check for repetition
		for (int j = 0; j < i; j++) {
			if (rotor[i] == rotor[j]) {
				// Handle repeated input
				printf(RED"Enter a Distinct Number\n"COLOR_RESET);
				i--;
				break; // Break out of the repetition check loop
			}
		}
	}
}

void inputRotorPositions(int* position) {
	// Clear the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	// String buffer for input 
	char input[20] = "";

	printf(GREEN"\n-Set Rotor Positions-\n"COLOR_RESET);

	for (int i = 0; i < 3; i++) {
		printf(YELLOW"Position Rotor %d: "COLOR_RESET, i + 1);

		// Read a string
		if (scanf("%s", input) != 1) {
			printf(RED"Error reading input\n"COLOR_RESET);
			exit(EXIT_FAILURE);
		}

		// Convert string to integer
		char* endptr;
		long rotorPosition = strtol(input, &endptr, 10);

		// Check for conversion errors or out-of-range values
		if (*endptr != '\0' || rotorPosition < 0 || rotorPosition > 25) {
			printf(RED"Enter a Valid Number between 0 and 25\n"COLOR_RESET);
			i--;
			continue;
		}

		position[i] = (int)rotorPosition;
	}
}

void createPairs(char* plug, Settings* settings) {
	// Split plugs into pairs of 2
	for (int i = 0; i < strlen(plug) / 2; i++) {
		settings->plugBoard[i][0] = convertToIndex(plug[2 * i]);
		settings->plugBoard[i][1] = convertToIndex(plug[(2 * i) + 1]);
	}
}

void inputPlugs(Settings* settings) {
	// Clear the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	// Array of plugs
	char plug[21] = "";
	bool isValid;

	// Get input for plugs
	for (;;) {
		printf(GREEN"\n-Set Plug Configurations: "COLOR_RESET);
		scanf("%s", plug);

		isValid = true;
		// Invalid Input
		for (int i = 0; i < strlen(plug); i++) {
			if (!isalpha(plug[i])) {
				printf(RED"Invalid Input\n"COLOR_RESET);
				isValid = false;
			}

			// Check for repition
			for (int j = i + 1; j < strlen(plug); j++) {
				if (plug[i] == plug[j]) {
					printf(RED"Enter Distinct Plugs\n"COLOR_RESET);
					isValid = false;
				}
			}
		}

		// Check if number of plugs is a multiple of 2
		if (strlen(plug) % 2 != 0) {
			printf(RED"Plugs Should be in Pairs of 2\n"COLOR_RESET);
			continue;
		}

		/*
			Conditions checked for valid input of plugs:
			1. All plugs are alphabets
			2. No plug is repeated
			3. Number of plugs should be a multiple of 2
		*/
		// Exit loop if all conditions are valid

		if (!isValid) {
			continue;
		}

		break;

	} 

	uppercase(plug); // Convert all characters to uppercase
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
	fflush(stdout); // Clear the output buffer
	
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
	
	char key[30] = " ";
	char plug[21] = " ";

	// Conditions to check validity of key
	bool keyValid = true;

	for (;;) {
		// Get user input
		printf(CYAN"Enter the Key: "COLOR_RESET);
		scanf("%s", key);

		uppercase(key);

		bool rotorsValid = true;
		// Validity of Rotors in the key
		for (int i = 0; i < 3; i++) {
			// Rotors used between 1 and 5
			if (!(key[i] >= '1' && key[i] <= '5')) {
				printf(RED"\nRotors Must Be Between 1 and 5"COLOR_RESET);
				rotorsValid = false;
				break;
			}

			// Check for repetition
			if (i < 2 && key[i] == key[i + 1]) {
				printf(RED"\nRotors Must Be Distinct"COLOR_RESET);
				rotorsValid = false;
				break;
			}
		}


		bool positionsValid = true;
		// Validity of positions in the key
		for (int i = 3; i < 9; i++) {
			// Rotor position between 00 and 25
			if (!(key[i] >= '0' && key[i] <= '2' && key[i + 1] >= '0' && key[i + 1] <= '9')) {
				printf(RED"\nPositions Must Be Between 00 and 25"COLOR_RESET);
				positionsValid = false;
				break;
			}

			i++; // Skip the second digit of the two-digit number
		}

		bool plugsValid = true;
		// Validity of plugs in the key
		for (int i = 9; i < strlen(key); i++) {
			// Plugs between A and Z
			if (!isalpha(key[i])) {
				printf(RED"\nPlugs Can Only Be Alphabets"COLOR_RESET);
				plugsValid = false;
				break;
			}

			// Check for repetition
			if (key[i] == key[i + 1]) {
				printf(RED"\nPlugs Must Be Distinct"COLOR_RESET);
				plugsValid = false; // Not valid if plugs are repeated
				break;
			}
		}

		// AND condition for key validity
		keyValid = rotorsValid && positionsValid && plugsValid;

		// Check if plugs are in pairs
		if (strlen(key) % 2 == 0) {
			printf(RED"\nPlugs Must Be in Pairs of 2"COLOR_RESET);
			keyValid = false;
		}

		// Display message for success or failure
		if (!keyValid) {
			printf(RED"\nEncryption Key is Invalid\n"COLOR_RESET);
			continue;
		}

		printf("\nKey Entered Successfully!\n");

		// Exit loop when key is valid
		break;
	}

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
	 
}
