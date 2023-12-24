#include <stdio.h>
#include <stdbool.h>

#pragma warning(disable : 4996)

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void inputRotorsUsed(int rotor[]) {
	// This function takes input from user and sets the rotors used
	printf("Set Rotor Configuration\n");

	for (int i = 0; i < 3; i++) {
		printf("Rotor %d: ", i + 1);
		scanf_s("%d", &rotor[i]);
		rotor[i]--; // Convert to index [0, 4]

		if (rotor[i] < 0 || rotor[i] > 4) {
			printf("Enter a Valid Number\n");
			i--;
			continue;
		}

		for (int j = 0; j < i; j++) {
			if (rotor[i] == rotor[j]) {
				printf("Enter a Distinct Number\n");
				i--;
			}
		}
	}
}

void inputRotorPositions(int position[]) {
	printf("\nSet Rotor Positions\n");

	for (int i = 0; i < 3; i++) {
		printf("Position Rotor %d: ", i + 1);
		scanf_s("%d", &position[i]);
		position[i]--;

		if (position[i] < 0 || position[i] > 25) {
			printf("Enter a Valid Number\n");
			i--;
			continue;
		}
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
	int n = 0;
	char plug[20];
	do {
		printf("\nSet Plug Configurations: ");
		scanf_s("%s", plug, 20);

		for (int i = 0; i < strlen(plug); i++) {

			// Invalid Input
			if (plug[i] < 'A' || plug[i] > 'z') {
				continue;
			}

			// Add number of valid plugs if no invalid input
			else {
				n++;
			}

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

	uppercase(plug); // Convert all characters to uppercase)
	createPairs(plug, settings);
}

// Function to generate random values for rotor, position, and plug arrays
void randomKey(int rotor[3], int position[3], char plug[21]) {
	srand((unsigned)time(NULL));

	// Generate random values for rotor 
	for (int i = 0; i < 3; i++) {
		rotor[i] = rand() % 5;  // Values between 0 and 4

		// Check for repetition
		for (int j = 0; j < i; ++j) {
			if (rotor[i] == rotor[j]) {

				--i;
				break;
			}
		}
	}

	// Generate random values for position 
	for (int i = 0; i < 3; i++) {
		position[i] = (rand() % 26);  // Values between 0 and 25
	}

	// Generate random values for plug 
	for (int i = 0; i < 20; i++) {
		plug[i] = 'A' + (rand() % 26);  // Random capital letter

		// Check for repetition
		for (int j = 0; j < i; j++) {
			if (plug[i] == plug[j]) {

				--i;
				break;
			}
		}
	}
}

// Get key directly from user
void directKeyInput(int rotor[3], int position[3], char plug[21]) {
	char key[30] = " ";

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
			rotor[i] = (int)(key[i]) - '1'; // Values between 0 and 5
		}

		// Get values for rotor position
		for (int i = 3, j = 0; i < 9; i += 2, j++) {

			// Extract two digits from the string and convert them to an integer
			int number = (key[i] - '0') * 10 + (key[i + 1] - '0');

			// Assign the extracted number to the array
			position[j] = number; // Values Between 0 and 25
		}

		// Get values for plugs connected
		for (int i = 0, j = 0; key[i] != '\0'; i++) {

			// Check for alphabets (plugs)
			if (isalpha(key[i])) {
				plug[j] = key[i]; // Assign value to plug
				j++;
			}
		}

	} while (!keyValid);

}