#pragma once

// Machine configuration
typedef struct {
	int rotors[5][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
	int defaultPositions[3];
} Settings;

