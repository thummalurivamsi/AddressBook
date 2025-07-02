/*
Documentation
Name        : Vamsi T
Date        : 16/6/25
Description : Address Book project
*/

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main()
{
	int choice;

	AddressBook addressBook;
	initialize(&addressBook); // Initialize the address book

	do
	{
		printf("\n**Address Book Menu**\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		// scanf() function returns the number of input items successfully matched and assigned
		if (scanf("%d", &choice) != 1)
		{
			printf("\nInvalid selection! Please select 1 to 6\n");

			// Clear the invalid characters from the input buffer
			while (getchar() != '\n')
				; // clear until newline
			continue;
		}

		switch (choice)
		{
		case 1:
			createContact(&addressBook);
			break;
		case 2:
			searchContact(&addressBook);
			break;
		case 3:
			editContact(&addressBook);
			break;
		case 4:
			deleteContact(&addressBook);
			break;
		case 5:
			listContacts(&addressBook);
			break;
		case 6:
			printf("Saving and Exiting...\n");
			// saveContactsToFile(&addressBook);
			saveAndExit(&addressBook);
			break;
		default:
			printf("Invalid choice. Please try again\n");
		}
	} while (choice != 6);

	// cleanup(); // Cleanup any resources before exiting
	return 0;
}
