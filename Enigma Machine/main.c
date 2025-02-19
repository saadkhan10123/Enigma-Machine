#include "menu/menu.h"

#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main() 
{
	while (true) 
	{
		// Title Screen and Main Menu
		titleScreen();
		printMenu();

		// Clear the input buffer
		getchar();
		int c;
		while ((c = getchar()) != '\n' && c != EOF);

		// Return back to title screen
		system("cls");
	}

	return 0;
}
