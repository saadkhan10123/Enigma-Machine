#include <string.h>
#include <ctype.h>
#include "Settings.h"

int putThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	return settings->rotors[rotorUsed][index];
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

		/*printArray(settings->rotorPositions[0], 26);
		printArray(settings->rotors[settings->rotorsUsed[0]], 26);*/

		// Put through plugboard again
		index = putThroughPlugBoard(settings, index);

		// Convert the output to a character and store it in the output string
		output[i] = convertToChar(index);
	}
	output[strlen(str)] = '\0';
}