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
#include "Settings.h"

#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(void) {
	// Title Screen and Main Menu
	titleScreen();
	printMenu();

	getchar();

	// Clear the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	// Return back to title screen
	system("cls");
	main();

	return 0;
}
