#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure for storing machine details
typedef struct machine {
long chassisNum;
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
struct machine* next;
} machineT;


//Function to ignore casing of machines from user entry
int compareIgnoreCase(const char* s1, const char* s2) {
while (*s1 && *s2) {
	if (tolower(*s1) != tolower(*s2)) {
		return 0;
	}
	s1++;
	s2++;
}
//They are equal
return *s1 == *s2;
}



//Display the contents of the machine list
void displayAll(machineT* dB);


//display machine details for specific machine based on chassis number
void displayMachineDetails(machineT* dB);

//Add a single book to the machine list
void addMachine(machineT* dB);

//Edit an individual machine in the list
void editMachine(machineT* dB);

//delete a machine from list
void deleteMachine(machineT** head);

//generating statistics of breakdowns
void generateStat(machineT* head, const char* type);

//save contents of machines to file
void printToReportFile(machineT* head);

//listing the machines in order of valuation
void listByValuation(machineT* head);


int compareIgnoreCase(const char* s1, const char* s2);


// Function to get password input with asterisks
void getPassword(char* password) {
	int i = 0;
	char ch;
	// the /r is when enter key is pressed
	while ((ch = getch()) != '\r') {
		//below deals with the back space
		if (ch == '\b') {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		}
		//below is limit
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
	int user;
	int numMachines;
	machineT* myMachine = NULL;
	FILE* fp;
	int option, option2;

	char usernames[3][30];
	char passwords[3][30];
	char inputUsername[30], inputPassword[30];
	int i, found = 0;

	// Open the file for reading password and username
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
		user = 1;
	}
	else {
		printf("Invalid username or password.\n");
		return 0;
	}


	if (user == 1)//confirming the login is sucessfull and user can continue
	{
		int option;
		char subOption;

		printf("1) Add machine\n");
		printf("2) Display all machines to screen\n");
		printf("3) Display machine details\n");
		printf("4) Update a machine's details\n");
		printf("5) Delete machine\n");
		printf("6) Generate statistics (a - e) based on the machinery type:\n");
		printf("7) Print all machine details into a report file\n");
		printf("8) List all the machinery in order of current valuation\n");
		printf("-1) Exit\n");

		scanf("%d", &option);

		while (option != -1)
		{
			switch (option)
			{
			case 1:
				addMachine(&myMachine);
				break;
			case 2:
				displayAll(myMachine);
				break;
			case 3:
				displayMachineDetails(myMachine);
				break;
			case 4:
				editMachine(&myMachine);
				break;
			case 5:
				deleteMachine(&myMachine);
				break;
			case 6:
				printf("\nChoose machinery type:\n");
				printf("A. Tractor\n");
				printf("B. Excavator\n");
				printf("C. Roller\n");
				printf("D. Crane\n");
				printf("E. Mixer\n");
				printf("Enter option (A-E): ");
				scanf(" %c", &subOption);

				switch (toupper(subOption))
				{
				case 'A':
					generateStat(myMachine, "Tractor");
					break;
				case 'B':
					generateStat(myMachine, "Excavator");
					break;
				case 'C':
					generateStat(myMachine, "Roller");
					break;
				case 'D':
					generateStat(myMachine, "Crane");
					break;
				case 'E':
					generateStat(myMachine, "Mixer");
					break;
				default:
					printf("Invalid sub-option.\n");
				}
				break;

			case 7:
				printToReportFile(myMachine);
				break;

			case 8:
				listByValuation(myMachine);
				break;

			default:
				printf("Invalid option. Please try again.\n");
			}

			// Show the menu again
			printf("\n1) Add machine\n");
			printf("2) Display all machines to screen\n");
			printf("3) Display machine details\n");
			printf("4) Update a machine's details\n");
			printf("5) Delete machine\n");
			printf("6) Generate statistics (a - e) based on the machinery type:\n");
			printf("7) Print all machine details into a report file\n");
			printf("8) List all the machinery in order of current valuation\n");
			printf("-1) Exit\n");

			scanf("%d", &option);
		}

	}
}


void addMachine(machineT * *head)
{
	machineT* newMachine = (machineT*)malloc(sizeof(machineT));
	if (!newMachine) {
		printf("Memory allocation failed.\n");
		return;
	}

	printf("Enter chassis number: ");
	scanf("%ld", &newMachine->chassisNum);

	// Check if chassis number is unique
	machineT* current = *head;
	while (current != NULL) {
		if (current->chassisNum == newMachine->chassisNum) {
			printf("Chassis number already exists. Cannot add duplicate.\n");
			free(newMachine);
			return;
		}
		current = current->next;
	}

	printf("Enter make: ");
	scanf("%s", newMachine->make);

	printf("Enter model: ");
	scanf("%s", newMachine->model);

	printf("Enter year of manufacture: ");
	scanf("%d", &newMachine->yearOfManufacture);

	printf("Enter cost: ");
	scanf("%lf", &newMachine->cost);

	printf("Enter current valuation: ");
	scanf("%lf", &newMachine->currentValuation);

	printf("Enter current mileage: ");
	scanf("%lf", &newMachine->currentMileage);

	printf("Enter next service mileage: ");
	scanf("%lf", &newMachine->nextServiceMileage);

	printf("Enter owner name: ");
	scanf(" %[^\n]", newMachine->ownerName);

	//email validation checker to check for @ symbol and .com
	do {
		printf("Enter owner email (must contain '@' and end with '.com'): ");
		scanf("%s", newMachine->ownerEmail);

		if (strchr(newMachine->ownerEmail, '@') == NULL ||
			strstr(newMachine->ownerEmail, ".com") == NULL ||
			//below checks the email ends with .com 
			strcmp(newMachine->ownerEmail + strlen(newMachine->ownerEmail) - 4, ".com") != 0) {
			printf("Invalid email format. Please try again.\n");
		}
		else {
			break;  
		}

	} while (1);

	printf("Enter owner phone: ");
	scanf("%s", newMachine->ownerPhone);

	printf("Enter machine type: ");
	scanf("%s", newMachine->machineType);

	printf("Enter breakdown frequency: ");
	scanf(" %[^\n]", newMachine->breakdownFrequency);

	newMachine->next = NULL;

	// Insert in sorted order by chassis number
	if (*head == NULL || newMachine->chassisNum < (*head)->chassisNum) {
		newMachine->next = *head;
		*head = newMachine;
	}
	else {
		machineT* prev = *head;
		while (prev->next != NULL && prev->next->chassisNum < newMachine->chassisNum) {
			prev = prev->next;
		}
		newMachine->next = prev->next;
		prev->next = newMachine;
	}

	printf("Machine added successfully.\n");
}

//Below is to show just the machine chassis number, for full specific machine details, use option 3
void displayAll(machineT * head)
{
	if (head == NULL) {
		printf("No machines to display.\n");
		return;
	}

	machineT* current = head;
	int count = 1;

	printf("\n--- Machine List ---\n");
	while (current != NULL) {
		printf("\nMachine #%d\n", count++);
		printf("Chassis Number       : %ld\n", current->chassisNum);
		current = current->next;
	}
}

// Function to display details of a specific machine based on chassis number
void displayMachineDetails(machineT * head) {
	if (head == NULL) {
		printf("No machines available.\n");
		return;
	}

	long chassisNum;
	printf("Enter chassis number to search for: ");
	scanf("%ld", &chassisNum);

	machineT* current = head;
	while (current != NULL) {
		if (current->chassisNum == chassisNum) {
			// Display details of the machine
			printf("\n--- Machine Details ---\n");
			printf("Chassis Number       : %ld\n", current->chassisNum);
			printf("Make                 : %s\n", current->make);
			printf("Model                : %s\n", current->model);
			printf("Year of Manufacture  : %d\n", current->yearOfManufacture);
			printf("Cost                 : %.2f\n", current->cost);
			printf("Current Valuation    : %.2f\n", current->currentValuation);
			printf("Current Mileage      : %.2f\n", current->currentMileage);
			printf("Next Service Mileage : %.2f\n", current->nextServiceMileage);
			printf("Owner Name           : %s\n", current->ownerName);
			printf("Owner Email          : %s\n", current->ownerEmail);
			printf("Owner Phone          : %s\n", current->ownerPhone);
			printf("Machine Type         : %s\n", current->machineType);
			printf("Breakdown Frequency  : %s\n", current->breakdownFrequency);
			return;  // Stop once we find and display the machine details
		}
		current = current->next;
	}

	// If the machine with the given chassis number is not found
	printf("Machine with chassis number %ld not found.\n", chassisNum);
}


void editMachine(machineT * *head) {
	if (*head == NULL) {
		printf("No machines available to edit.\n");
		return;
	}

	long chassisNum;
	printf("Enter chassis number of the machine you want to edit: ");
	scanf("%ld", &chassisNum);

	machineT* current = *head;
	while (current != NULL) {
		if (current->chassisNum == chassisNum) {
			printf("\nEditing machine with chassis number: %ld\n", chassisNum);

			printf("Enter new make (current: %s): ", current->make);
			scanf("%s", current->make);

			printf("Enter new model (current: %s): ", current->model);
			scanf("%s", current->model);

			printf("Enter new year of manufacture (current: %d): ", current->yearOfManufacture);
			scanf("%d", &current->yearOfManufacture);

			printf("Enter new cost (current: %.2f): ", current->cost);
			scanf("%lf", &current->cost);

			printf("Enter new current valuation (current: %.2f): ", current->currentValuation);
			scanf("%lf", &current->currentValuation);

			printf("Enter new current mileage (current: %.2f): ", current->currentMileage);
			scanf("%lf", &current->currentMileage);

			printf("Enter new next service mileage (current: %.2f): ", current->nextServiceMileage);
			scanf("%lf", &current->nextServiceMileage);

			printf("Enter new owner name (current: %s): ", current->ownerName);
			scanf(" %[^\n]", current->ownerName);

			printf("Enter new owner email (current: %s): ", current->ownerEmail);
			scanf("%s", current->ownerEmail);

			printf("Enter new owner phone (current: %s): ", current->ownerPhone);
			scanf("%s", current->ownerPhone);

			printf("Enter new machine type (current: %s): ", current->machineType);
			scanf("%s", current->machineType);

			printf("Enter new breakdown frequency (current: %s): ", current->breakdownFrequency);
			scanf(" %[^\n]", current->breakdownFrequency);

			printf("Machine details updated successfully.\n");
			return;
		}
		current = current->next;
	}

	printf("Machine with chassis number %ld not found.\n", chassisNum);
}



void deleteMachine(machineT * *head) {
	if (*head == NULL) {
		printf("No machines available to delete.\n");
		return;
	}

	long chassisNum;
	printf("Enter chassis number of the machine you want to delete: ");
	scanf("%ld", &chassisNum);

	machineT* current = *head;
	machineT* prev = NULL;

	while (current != NULL) {
		if (current->chassisNum == chassisNum) {
			// If the node to delete is the head
			if (prev == NULL) {
				*head = current->next;
			}
			else {
				prev->next = current->next;
			}

			free(current);
			printf("Machine with chassis number %ld deleted successfully.\n", chassisNum);
			return;
		}

		prev = current;
		current = current->next;
	}

	printf("Machine with chassis number %ld not found.\n", chassisNum);
}


void generateStat(machineT * head, const char* type) {
	int total = 0, noBreakdowns = 0;
	machineT* current = head;

	while (current != NULL) {
		//comparing the type to the actual machine and calling the function to ignore casing
		if (compareIgnoreCase(current->machineType, type)) {
			total++;


			// If user enters none for breakdowns or 0, they both will have no breakdowns put down
			if (compareIgnoreCase(current->breakdownFrequency, "None") || strcmp(current->breakdownFrequency, "0") == 0) {
				noBreakdowns++;
			}
		}
		current = current->next;
	}

	if (total == 0) {
		printf("No machines of type '%s' found.\n", type);
		return;
	}

	double percentage = (double)noBreakdowns / total * 100;
	printf("'%s': %.2f%% have no breakdowns (%d of %d machines)\n",
		type, percentage, noBreakdowns, total);
}



void printToReportFile(machineT* head) {
	if (head == NULL) {
		printf("No machines to write to file.\n");
		return;
	}

	//open fleet text file
	FILE* file = fopen("fleet.txt", "w");
	if (file == NULL) {
		printf("Error opening fleet.txt for writing.\n");
		return;
	}

	machineT* current = head;
	int count = 1;

	fprintf(file, "==== Fleet Machine Report ====\n");

	while (current != NULL) {
		fprintf(file, "\nMachine #%d\n", count++);
		fprintf(file, "Chassis Number       : %ld\n", current->chassisNum);
		fprintf(file, "Make                 : %s\n", current->make);
		fprintf(file, "Model                : %s\n", current->model);
		fprintf(file, "Year of Manufacture  : %d\n", current->yearOfManufacture);
		fprintf(file, "Cost                 : %.2f\n", current->cost);
		fprintf(file, "Current Valuation    : %.2f\n", current->currentValuation);
		fprintf(file, "Current Mileage      : %.2f\n", current->currentMileage);
		fprintf(file, "Next Service Mileage : %.2f\n", current->nextServiceMileage);
		fprintf(file, "Owner Name           : %s\n", current->ownerName);
		fprintf(file, "Owner Email          : %s\n", current->ownerEmail);
		fprintf(file, "Owner Phone          : %s\n", current->ownerPhone);
		fprintf(file, "Machine Type         : %s\n", current->machineType);
		fprintf(file, "Breakdown Frequency  : %s\n", current->breakdownFrequency);
		current = current->next;
	}

	// Adding machine performance statistics to the file
	fprintf(file, "\n==== Machine Performance Statistics ====\n");

	const char* types[] = { "Tractor", "Excavator", "Roller", "Crane", "Mixer" };
	for (int i = 0; i < 5; i++) {
		int total = 0, noBreakdowns = 0;
		current = head;

		while (current != NULL) {
			if (compareIgnoreCase(current->machineType, types[i])) {
				total++;
				if (compareIgnoreCase(current->breakdownFrequency, "None") || strcmp(current->breakdownFrequency, "0") == 0) {
					noBreakdowns++;
				}
			}
			current = current->next;
		}

		if (total > 0) {
			double percentage = (double)noBreakdowns / total * 100;
			fprintf(file, "%s: %.2f%% have no breakdowns (%d of %d machines)\n",
				types[i], percentage, noBreakdowns, total);
		}
		else {
			fprintf(file, "%s: No machines of this type found.\n", types[i]);
		}
	}

	fclose(file);
	printf("Machine details and performance statistics written to 'fleet.txt'.\n");
}




void listByValuation(machineT* head) {
	if (head == NULL) {
		printf("No machines to list.\n");
		return;
	}

	// Count number of machines
	int count = 0;
	machineT* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}

	// Copy to array for sorting
	machineT** machineArray = (machineT**)malloc(count * sizeof(machineT*));
	if (machineArray == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}

	current = head;
	for (int i = 0; i < count; i++) {
		machineArray[i] = current;
		current = current->next;
	}

	// Sort array in descending order by currentValuation
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (machineArray[i]->currentValuation < machineArray[j]->currentValuation) {
				machineT* temp = machineArray[i];
				machineArray[i] = machineArray[j];
				machineArray[j] = temp;
			}
		}
	}

	// Print sorted list
	printf("\n==== Machines Sorted by Current Valuation ====\n");
	for (int i = 0; i < count; i++) {
		printf("Chassis Number: %ld\tValuation: %.2f\n",
			machineArray[i]->chassisNum, machineArray[i]->currentValuation);
	}

	free(machineArray);
}
