#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char chassisNumber[30];
	char make[30];
	char model[30];
	int yearOfManufacture;
	double cost;
	double currentValuation;
	double currentMileage;
	double nextServiceMileage;
	char ownerName[50];
	char ownerEmail[50];
	char ownerPhone[20];
	char machineType[15];
	char breakdownFrequency[30];
} machineT;


//Display the contents of the machine list
void displayAll(machineT* dB, int size);

//Search for an individual machine in the machine list
void searchMachine(machineT* dB, int size);

//Add a single book to the machine list
void addMachine(machineT* dB, int size);

//Edit an individual machine in the list
void editMachine(machineT* dB, int size);

//Save the contents of the machine list to the backup file
void saveMachine(machineT* dB, int size);

//Initialise the machine list from a file
void loadMachine(machineT** dB, int* size);

// Function to get password input with asterisks
void getPassword(char* password) {
	int i = 0;
	char ch;

	while ((ch = getch()) != '\r') {  
		if (ch == '\b') {  
			if (i > 0) {
				i--;
				printf("\b \b");  
			}
		}
		else if (i < 30 - 1) {
			password[i++] = ch;
			printf("*");
		}
	}

	password[i] = '\0';
	printf("\n");
}
void main()
{
	int numMachines;
	machineT* myMachine;
	FILE* fp;
	int option, option2;

	char usernames[3][30];
	char passwords[3][30];
	char inputUsername[30], inputPassword[30];
	int i, found = 0;

	// Open the file for reading
	fp = fopen("credentials.txt", "r");
	if (fp == NULL) {
		printf("Error opening file.\n");
		return 1;
	}


	// Read 3 records from the file
	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s %s", usernames[i], passwords[i]);
	}
	fclose(fp);

	fp = fopen("login.txt", "r");

	// Ask user for username and password
	printf("Enter username: ");
	scanf("%s", inputUsername);

	printf("Enter password: ");
	getPassword(inputPassword);

	// Compare with stored records
	for (i = 0; i < 3; i++) {
		if (strcmp(inputUsername, usernames[i]) == 0 && strcmp(inputPassword, passwords[i]) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		printf("Login successful!\n");
	}
	else {
		printf("Invalid username or password.\n");
	}

	return 0;




}