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

#pragma warning(disable : 4996)

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

int main(void) {
	printMenu();


	//testEncryptDecrypt();
	return 0;
}
