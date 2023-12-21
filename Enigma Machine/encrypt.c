#include <string.h>
#include <ctype.h>


typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

int putThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	int indexToFind = findIndex(settings->rotors[rotorUsed], index);
	return settings->rotorPositions[rotorNumber][indexToFind];
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