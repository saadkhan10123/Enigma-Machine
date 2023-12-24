#include <stdio.h>

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void rotateRotor(int* rotor);

void initializeRotorSettings(Settings* settings) {
	// Initialize rotors used
	int rotorsUsedSettings[3] = { 0 };
	inputRotorsUsed(rotorsUsedSettings);

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

	// Initialize rotor positions
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 26; j++) {
			settings->rotorPositions[i][j] = j;
		}
	}

	// Rotate rotors to the correct position
	int rotorPositionsSettings[3] = { 0 };
	//inputRotorPositions(rotorPositionsSettings);


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < rotorPositionsSettings[i]; j++) {
			rotateRotor(settings->rotors[settings->rotorsUsed[i]]);
		}
	}

	// Initialize reflector
	int reflectorSettings[26] = { 24, 17, 20, 7, 16, 18, 11, 3, 15, 23, 13, 6, 14, 10, 12, 8, 4, 1, 5, 25, 2, 22, 21, 9, 0, 19 };
	for (int i = 0; i < 26; i++) {
		settings->reflector[i] = reflectorSettings[i];
	}

	// Initialize plugboard
	// This contains pairs of numbers which are non-repeating
	inputPlugs(settings);
}

void rotateRotor(int* rotor) {
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
	rotateRotor(settings->rotorPositions[0]);
	if (rotationNumber % 26 == 0) {
		rotateRotor(settings->rotors[settings->rotorsUsed[1]]);
		rotateRotor(settings->rotorPositions[1]);
		if (rotationNumber % 676 == 0) {
			rotateRotor(settings->rotors[settings->rotorsUsed[2]]);
			rotateRotor(settings->rotorPositions[2]);
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