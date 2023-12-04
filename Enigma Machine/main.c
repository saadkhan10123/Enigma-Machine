#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996)
#pragma warning(disable:6031)

// String typedefinition
typedef char string;

// Function prototypes
void machineRotors(int[]);
void rotorPositions(int[]);
void IOPlugs(string*, int);

void uppercase(string*);

void createPairs(string*, string[10][2]);
void printKey(int[], int[], string*, string[10][2]);

int main() {
	// Arrays in the key
	int rotors[3];
	int positions[3];
	
	string plugs[21] = "";
	string plugPairs[10][2];

	int count = 0; // Indicates no. of valid plugs
	
	// Configure the rotors
	machineRotors(rotors);

	// Set the positions
	rotorPositions(positions);

	// Input For Plugs
	IOPlugs(plugs, plugPairs, count);
	uppercase(plugs);

	// Group plugs into pairs of 2
	createPairs(plugs, plugPairs);

	// Output the encryption key
	printKey(rotors, positions, plugs, plugPairs);

	return 0;
}

void machineRotors(int rotor[])
{
	printf("Set Rotor Configuration\n");

	for (int i = 0; i < 3; i++) {
		printf("Rotor %d: ", i + 1);
		scanf("%d", &rotor[i]);

		if (rotor[i] < 1 || rotor[i] > 5) {
			printf("Enter a Valid Number\n");
			i--;

			continue;
		}

		if (i != 0 && rotor[i] == rotor[i - 1]) {
			printf("Enter Distinct Values\n");
			i--;

			continue;
		}

	}
}

void rotorPositions(int position[]) 
{	
	printf("\nSet Rotor Positions\n");
	
	for (int i = 0; i < 3; i++) {
		printf("Position Rotor %d: ", i + 1);
		scanf("%d", &position[i]);

		if (position[i] < 1 || position[i] > 26) {
			printf("Enter a Valid Number\n");
			i--;
			continue;
		}
	}
}

void IOPlugs(string* plug, int n)
{
	do
	{
		printf("\nSet Plug Configurations: ");
		scanf("%s", plug);

		for (int i = 0; i < strlen(plug); i++) {

			// Invalid Input
			if (plug[i] < 'A' || plug[i] > 'z') {
				continue;
			}

			// Add no. of valid plugs if no invalid input
			else {
				n++;
			}

			for (int j = i + 1; j < strlen(plug); j++) {
				if (plug[i] == plug[j]) {
					n--; // Decrease no. of valid plugs by 1
				}
			}

		}

		// Error messages
		if (n < strlen(plug)) {
			printf("Enter a Valid Configuration\n");
		}

		if (strlen(plug) % 2 != 0) {
			printf("Plugs Should be in Pairs of 2\n");
		}

		/*
			2 Conditions are checked for valid input of plugs:

			1. No plug is invalid
			2. Number of plugs should be a multiple of 2
		*/

	} while (n < strlen(plug) || strlen(plug) % 2 != 0);

}

void createPairs(string* plug, string plugPair[10][2]) {


	// Split plugs into pairs of 2
	for (int i = 0; i < strlen(plug) / 2; i++) {
		plugPair[i][0] = plug[2 * i];
		plugPair[i][1] = plug[(2 * i) + 1];
	}
}

void printKey(int rotor[], int position[], string* plug, string plugPair[10][2]) {

	// Print out the encryption key
	printf("Key: ");

	//Print Rotors
	for (int i = 0; i < 3; i++) {
		printf("%d", rotor[i]);
	}

	// Print Positions
	for (int i = 0; i < 3; i++) {
		if (position[i] < 10) {
			printf("0%d", position[i]);
		}

		else {
			printf("%d", position[i]);
		}
	}

	// Print Plugs
	for (int i = 0; i < strlen(plug) / 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%c", plugPair[i][j]);
			
		}
	}
}

void uppercase(string* text)
{
	for (int i = 0; i < strlen(text); i++) {
		
		// Change lowercase to uppercase
		if (text[i] >= 'a' && text[i] <= 'z') {
			text[i] -= ' ';
		}

		else {
			continue;
		}
	}
}
