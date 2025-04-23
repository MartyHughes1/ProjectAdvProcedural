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
	int user;
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
		printf("6) Generate statistics (a – d) based on the machinery type:\n");
		printf("   A. %% of machines with no breakdowns\n");
		printf("   B. %% of machines with no breakdowns\n");
		printf("   C. %% of machines with no breakdowns\n");
		printf("   D. %% of machines with no breakdowns\n");
		printf("7) Print all machine details into a report file\n");
		printf("8) List all the machinery in order of current valuation\n");
		printf("-1) Exit\n");

		scanf("%d", &option);

		while (option != -1)
		{
			switch (option)
			{
			case 1:
				addMachine();
				break;
			case 2:
				displayMachines();
				break;
			case 3:
				displayMachineDetails();
				break;
			case 4:
				updateMachine();
				break;
			case 5:
				deleteMachine();
				break;
			case 6:
				printf("Enter sub-option (A-D): ");
				scanf(" %c", &subOption);  
				switch (subOption)
				{
				case 'A':
				case 'a':
					generateStatA();
					break;
				case 'B':
				case 'b':
					generateStatB();
					break;
				case 'C':
				case 'c':
					generateStatC();
					break;
				case 'D':
				case 'd':
					generateStatD();
					break;
				default:
					printf("Invalid sub-option.\n");
				}
				break;
			case 7:
				printToReportFile();
				break;
			case 8:
				listByValuation();
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
			printf("6) Generate statistics (a – d) based on the machinery type:\n");
			printf("   A. %% of machines with no breakdowns\n");
			printf("   B. %% of machines with no breakdowns\n");
			printf("   C. %% of machines with no breakdowns\n");
			printf("   D. %% of machines with no breakdowns\n");
			printf("7) Print all machine details into a report file\n");
			printf("8) List all the machinery in order of current valuation\n");
			printf("-1) Exit\n");

			scanf("%d", &option);
		}

	}
}







			/*
			//Compare the password
			if (strcmp(sysPassword, password) == 0)
			{
				mode = 1;

				do
				{
					printf("Please enter the 1 to create a new database or 2 to load the previous library\n");
					scanf("%d", &option2);
				} while (option != 1 && option != 2);

				if (option == 1)
				{
					printf("Please enter the number of books in the library\n");
					scanf("%d", &numBooks);

					myLib = (bookT*)malloc(numBooks * sizeof(bookT));

					for (i = 0; i < numBooks; i++)
					{
						(myLib + i)->bookNum = 0;
						(myLib + i)->price = 0;
						strcpy((myLib + i)->author, "Empty");
						strcpy((myLib + i)->title, "Empty");
					}
				}
				else
				{
					loadBook(&myLib, &numBooks);
				}
			}
			else
			{

				loadBook(&myLib, &numBooks);
			}

		}
	}

	else
	{
		//The guest only gets to load a previous backup library
		loadBook(&myLib, &numBooks);
	}




	//Menu for interacting with the library array.....
	printf("Please enter 1 to Search for a book\n");
	printf("Please enter 2 to Add One book\n");
	printf("Please enter 3 to Save the Library to file\n");
	if (mode == 1)
	{
		printf("Please enter 4 to Edit a book\n");
	}
	printf("Please enter -1 to Exit\n");
	scanf("%d", &option);

	while (option != -1)
	{
		if (option == 1)
		{
			searchBook(myLib, numBooks);
		}

		else if (option == 2)
		{
			addBook(myLib, numBooks);
		}

		else if (option == 3)
		{
			saveBook(myLib, numBooks);
		}
		else if (option == 4 && mode == 1)
		{
			editBook(myLib, numBooks);
		}
		else if (option == 4 && mode == 0)
		{
			printf("The guest can not complete the edit option\n");
		}




		printf("Please enter 1 to Search for a book\n");
		printf("Please enter 2 to Add One book\n");
		printf("Please enter 3 to Save the Library to file\n");
		if (mode == 1)
		{
			printf("Please enter 4 to Edit a book\n");
		}
		scanf("%d", &option);
	}

	saveBook(myLib, numBooks);
	free(myLib);
}


void displayAll(bookT* dB, int size)
{
	int i;


	printf("dB is %d and size is %d\n", dB, size);
	for (i = 0; i < size; i++)
	{
		printf("%ld %s %s %lf\n", (dB + i)->bookNum, (dB + i)->title, (dB + i)->author, (dB + i)->price);
	}
}

void searchBook(bookT* dB, int size)
{
	int i;
	long searchNum;
	int found = 0;

	printf("Please enter the book number you are looking for\n");
	scanf("%ld", &searchNum);

	for (i = 0; i < size; i++)
	{
		if ((dB + i)->bookNum == searchNum)
		{
			printf("Book Number %ld\n", (dB + i)->bookNum);
			printf("Title %s\n", (dB + i)->title);
			printf("Author %s\n", (dB + i)->author);
			printf("The price is %lf\n", (dB + i)->price);
			i = size;
			found = 1;

		}

	}


	if (found == 0)
		printf("The book can not be found\n");


}


void addBook(bookT* dB, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if ((dB + i)->bookNum == 0)
		{
			printf("Please enter the book number, title, author and price\n");

			scanf("%ld %s %s %lf", &(dB + i)->bookNum, (dB + i)->title, (dB + i)->author, &(dB + i)->price);
			return;
		}
	}

	printf("Can not add another book as the array is full\n");

}


void editBook(bookT* dB, int size)
{
	int i;
	long searchNum;
	int found = 0;

	printf("Please enter the book number you are looking to edit\n");
	scanf("%ld", &searchNum);

	for (i = 0; i < size; i++)
	{
		if ((dB + i)->bookNum == searchNum)
		{
			printf("Enter the new price\n");
			scanf("%lf", &(dB + i)->price);

			i = size;
			found = 1;

		}

	}

	if (found == 0)
		printf("The book can not be found\n");

}

void saveBook(bookT* dB, int size)
{
	FILE* fp;
	int i;

	fp = fopen("backUp.txt", "w");

	if (fp == NULL)
	{
		printf("The back up file could not be opened\n");
	}

	else
	{
		fprintf(fp, "%d\n", size);


		for (i = 0; i < size; i++)
		{
			fprintf(fp, "%ld %s %s %lf\n", (dB + i)->bookNum, (dB + i)->title, (dB + i)->author, (dB + i)->price);
		}

		fclose(fp);

	}

}


void loadBook(bookT** dB, int* size)
{
	FILE* fp;
	int i;

	fp = fopen("backUp.txt", "r");

	if (fp == NULL)
	{
		printf("The file could not be opened\n");

	}

	else
	{
		fscanf(fp, "%d", size);

		*dB = (bookT*)malloc(*size * sizeof(bookT));

		for (i = 0; i < *size; i++)
		{
			fscanf(fp, "%ld %s %s %lf", &(*dB + i)->bookNum, (*dB + i)->title, (*dB + i)->author, &(*dB + i)->price);
		}


	}*/