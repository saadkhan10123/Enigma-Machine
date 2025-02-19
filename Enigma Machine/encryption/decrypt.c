#include <string.h>
#include "decrypt.h"
#include "../common/helper.h"
#include "hardware.h"

int decryptThroughRotor(Settings* settings, int rotorNumber, int index) {
	// This function puts a value through a rotor to decrypt it
	int rotorUsed = settings->rotorsUsed[rotorNumber];
	return findIndex(settings->rotors[rotorUsed], index);
}

void decrypt(Settings* settings, char* str, char* output) {
	// Iterate through the string
	for (int i = 0; i < strlen(str); i++) {
		// Convert the character to an index
		int index = convertToIndex(str[i]);

		if (index < 0 || index > 25) {
			output[i] = str[i];
			continue;
		}
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