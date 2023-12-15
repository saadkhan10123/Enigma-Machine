/*
	Muhammad Saad Khan 
	Ali Ahmad
	28-11-2023
	Enigma Machine
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
	int rotors[5][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void rotateRotor(int *rotor);
int convertToIndex(char c);
void uppercase(char* text);

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

void createPairs(char* plug, Settings *settings) {
	// Split plugs into pairs of 2
	for (int i = 0; i < strlen(plug) / 2; i++) {
		settings->plugBoard[i][0] = convertToIndex(plug[2 * i]);
		settings->plugBoard[i][1] = convertToIndex(plug[(2 * i) + 1]);
	}
}

void inputPlugs(Settings *settings) {
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

void printString(char* str) {
	// This function prints a string
	for (int i = 0; i < strlen(str); i++) {
		printf("%c", str[i]);
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

void initializeRotorSettings(Settings* settings) {
	// Initialize rotors used
	int rotorsUsedSettings[3] = { 0 };
	inputRotorsUsed(rotorsUsedSettings);
	printArray(rotorsUsedSettings, 3);

	for (int i = 0; i < 3; i++) {
		settings->rotorsUsed[i] = rotorsUsedSettings[i];
	}

	// Initialize rotors
	int rotorSettings[5][26] = {
		{4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9},
		{0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4},
		{1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14},
		{4, 18, 14, 21, 15, 25, 9, 0, 24, 16, 20, 8, 17, 7, 23, 11, 13, 5, 19, 6, 10, 3, 2, 12, 22, 1},
		{21, 25, 1, 17, 6, 8, 19, 24, 20, 15, 18, 3, 13, 7, 11, 23, 0, 22, 12, 9, 16, 14, 5, 4, 2, 10}
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 26; j++) {
			settings->rotors[i][j] = rotorSettings[i][j];
		}
	}

	// Rotate rotors to the correct position
	int rotorPositionsSettings[3] = { 0 };
	inputRotorPositions(rotorPositionsSettings);


	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < rotorPositionsSettings[i]; j++) {
			rotateRotor(settings->rotors[settings->rotorsUsed[i]]);
		}
	}
	printf("First rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[0]], 26);
	printf("-------------------- \n");
	printf("Second rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[1]], 26);
	printf("-------------------- \n\n");
	printf("Third rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[2]], 26);
	printf("-------------------- \n\n");

	// Initialize reflector
	int reflectorSettings[26] = { 24, 17, 20, 7, 16, 18, 11, 3, 15, 23, 13, 6, 14, 10, 12, 8, 4, 1, 5, 25, 2, 22, 21, 9, 0, 19 };
	for (int i = 0; i < 26; i++) {
		settings->reflector[i] = reflectorSettings[i];
	}

	// Initialize plugboard
	// This contains pairs of numbers which are non-repeating
	inputPlugs(settings);
}

int putThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	return settings->rotors[rotorUsed][index];
}

int decryptThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor to decrypt it
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	int rotorIndex = findIndex(settings->rotors[rotorUsed], index);
	return rotorIndex;
}

void rotateRotor(int *rotor) {
	// This function rotates a single rotor
	int temp = rotor[0];
	for (int i = 0; i < 25; i++) {
		rotor[i] = rotor[i + 1];
	}
	rotor[25] = temp;
}

void rotateRotors(Settings* settings, int rotationNumber) {
	// This function rotates all the rotors
	rotateRotor(settings->rotors[settings->rotorsUsed[0]]);
	if (rotationNumber % 26 == 0) {
		rotateRotor(settings->rotors[settings->rotorsUsed[1]]);
		if (rotationNumber % 676 == 0) {
			rotateRotor(settings->rotors[settings->rotorsUsed[2]]);
		}
	}
}

int putThroughReflector(Settings* settings, int index) {
	// This function puts a value through the reflector
	return settings->reflector[index];
}

int putThroughPlugBoard(Settings* settings, int index) {
	// This function puts a value through the plugboard
	for (int i = 0; i < 10; i++) {
		if (settings->plugBoard[i][0] == index) {
			return settings->plugBoard[i][1];
		}
		else if (settings->plugBoard[i][1] == index) {
			return settings->plugBoard[i][0];
		}
	}
	return index;
}

void encrypt(Settings* settings, char* str, char* output) {
	// Iterate through the string
	for (int i = 0; i < strlen(str); i++) {
		int index = convertToIndex(str[i]);
		int j;

		// Put through plugboard
		index = putThroughPlugBoard(settings, index);

		// Put through rotors
		for (j = 0; j < 3; j++) {
			index = putThroughRotor(settings, j, index);
		}

		// Put through reflector
		index = putThroughReflector(settings, index);

		// Put through rotors again
		for (j = 2; j >= 0; j--) {
			index = putThroughRotor(settings, j, index);
		}
		// Rotate rotors
		rotateRotors(settings, i);

		// Put through plugboard again
		index = putThroughPlugBoard(settings, index);

		// Convert the output to a character and store it in the output string
		output[i] = convertToChar(index);
	}
	output[strlen(str)] = '\0';
}

void decrypt (Settings* settings, char* str, char* output) {
	// Iterate through the string
	for (int i = 0; i < strlen(str); i++) {
		int index = convertToIndex(str[i]);
		int j;

		// Put through plugboard
		index = putThroughPlugBoard(settings, index);

		// Put through rotors to decrypt
		for (j = 0; j < 3; j++) {
			index = decryptThroughRotor(settings, j, index);
		}

		// Put through reflector
		index = putThroughReflector(settings, index);

		// Put through rotors again to decrypt
		for (j = 2; j >= 0; j--) {
			index = decryptThroughRotor(settings, j, index);
		}
		// Rotate rotors
		rotateRotors(settings, i);

		// Put through plugboard again
		index = putThroughPlugBoard(settings, index);

		// Convert the output to a character and store it in the output string
		output[i] = convertToChar(index);
	}
	output[strlen(str)] = '\0';
}

void test() {
	// This is a test function to test the enigma machine
	/*Settings* settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);*/

	/*printf("First rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[0]], 26);
	printf("-------------------- \n");
	printf("Second rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[1]], 26);
	printf("-------------------- \n\n");
	printf("Third rotor: \n");
	printArray(settings->rotors[settings->rotorsUsed[2]], 26);
	printf("-------------------- \n\n");*/

	// Test the encrypt and decrypt functions with a rendomly generated string
	for (int i = 0; i < 100000; i++) {
		Settings* settings = malloc(sizeof(Settings));
		initializeRotorSettings(settings);

		char str[1000];
		char output[1000];
		char decryptOutput[1000];

		int stringLength = rand() % 900;
		makeRandomString(str, stringLength);

		encrypt(settings, str, output);
		decrypt(settings, output, decryptOutput);

		for (int i = 0; i < strlen(str); i++) {
			int index = convertToIndex(str[i]);
			index = putThroughReflector(settings, index);

			output[i] = convertToChar(index);

			index = putThroughReflector(settings, index);

			decryptOutput[i] = convertToChar(index);

			decryptOutput[i + 1] = '\0';
			output[i + 1] = '\0';
		}

		bool isSame = true;
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] != decryptOutput[i]) {
				isSame = false;
				printf("Original string: ");
				printf("%s \n", str);
				printf("Encrypted string: ");
				printf("%s \n", output);
				printf("Decrypted string: ");
				printf("%s \n", decryptOutput);
				exit(0);
				break;
			}
		}

		printf("String %2d secceded \n", i + 1);

		/*printf("Original String: %s \n", str);
		printf("First Pass: %s \n", output);
		printf("Second Pass: %s \n", decryptOutput);*/

		/*printf("First rotor: \n");
		rotateRotors(settings, i);
		printArray(settings->rotors[settings->rotorsUsed[0]], 26);
		printf("-------------------- \n");
		printf("Second rotor: \n");
		printArray(settings->rotors[settings->rotorsUsed[1]], 26);
		printf("-------------------- \n\n");*/
		free(settings);
	}
}


int main(void) {
	srand(time(NULL));

	// Comment this out to test the enigma machine with a randomly generated string
	// Uncomment this to test the enigma machine with a string entered by the user
	/*Settings *settings = malloc(sizeof(Settings));
	initializeRotorSettings(settings);

	char str[1000];

	printf("Enter a string to encrypt: ");
	scanf_s("%s", str, 1000);
	char* output = malloc(sizeof(char) * strlen(str));

	encrypt(settings, str, output);

	printf("Encrypted string: ");
	printString(output);

	initializeRotorSettings(settings);
	char* decryptOutput = malloc(sizeof(char) * strlen(str));
	decrypt(settings, output, decryptOutput);

	printf("Decrypted string: ");
	printString(decryptOutput);*/

	// Comment the test() function to test the enigma machine with a string entered by the user
	test();
	return 0;
}
