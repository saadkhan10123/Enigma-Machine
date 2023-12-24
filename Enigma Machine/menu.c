
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct {
	int rotors[5][26];
	int rotorPositions[3][26];
	int reflector[26];
	int rotorsUsed[3];
	int plugBoard[10][2];
} Settings;

void startEncryption();
void startDecryption();

void printMenu() {
	// This function prints the options
	printf("1. Encrypt\n");
	printf("2. Decrypt\n");
	printf("3. Generate Key\n");
	printf("4. Exit\n");

	int option = 1;
	scanf("%d", &option);

	switch (option)	{
	case 1:
		startEncryption();
		break;
	case 2:
		// Decrypt
		startDecryption();
		break;
	case 3:
		// Generate Key
		randomKey();
		break;
	case 4:
		// Exit
		break;
	default:
		break;
	}
}

void startEncryption() {
	// This function starts the encryption process
	char* str = NULL;
	Settings *settings = malloc(sizeof(Settings));

	initializeRotorSettings(settings);

	inputString(&str);

	char* output = malloc(sizeof(char) * (strlen(str) + 1));
	uppercase(str);
	encrypt(settings, str, output);

	printf("Encrypted: %s\n", output);
}

void startDecryption() {
	// This function starts the decryption process
	char* str = NULL;
	Settings* settings = malloc(sizeof(Settings));

	initializeRotorSettings(settings);

	inputString(&str);

	char* output = malloc(sizeof(char) * (strlen(str) + 1));
	uppercase(str);
	decrypt(settings, str, output);

	printf("Decrypted: %s\n", output);
}