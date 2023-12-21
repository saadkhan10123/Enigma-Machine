#include <string.h>

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

int decryptThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor to decrypt it
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	int indexToFind = findIndex(settings->rotorPositions[rotorNumber], index);
	return settings->rotors[rotorUsed][indexToFind];
}

void decrypt(Settings* settings, char* str, char* output) {
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