/*
Documentation
Name        : Vamsi T
Date        : 16/6/25
Description : Address Book project
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{
    int i;

    printf("\nThere are %d contacts :\n", addressBook->contactCount);
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nContact %d:\n", i + 1);
        printf("Name     : %s\n", addressBook->contacts[i].name);
        printf("Contact  : %s\n", addressBook->contacts[i].phone);
        printf("Email-ID : %s\n", addressBook->contacts[i].email);
    }
    // printf("%s\n", addressBook->contacts[addressBook->contactCount].name);
}

void initialize(AddressBook *addressBook)
{
    // addressBook->contactCount = 0;
    //  populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
    // saveContactsToFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    // Check if maximum contact limit is reached
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress book is full\n");
        return;
    }

    // Temporary contact to hold user input
    Contact newContact;

    // Read name
    printf("Enter the contact name: ");
    scanf(" %[^\n]", newContact.name);
    while (getchar() != '\n')
        ;

    char number[20];
    int ret = 0;
    while (!ret)
    {
        // Get and validate the mobile number
        printf("Enter the contact number: ");
        scanf(" %19s", number);
        while (getchar() != '\n')
            ;

        // Check format and duplication
        if (is_validnumber(addressBook, number))
        {
            if (!is_duplicate_number(addressBook, number))
            {
                ret = 1; // Valid and unique number
            }
            else
            {
                printf("Mobile number already exists!\n");
            }
        }
        else
        {
            printf("Invalid mobile number! Must be exactly 10 digits\n");
        }
    }
    // Store validated number
    strcpy(newContact.phone, number);

    char mail[50];
    ret = 0;
    while (!ret)
    {
        // Get and validate the email ID
        printf("Enter the Email-ID: ");
        scanf(" %[^\n]", mail);
        while (getchar() != '\n')
            ;

        // Check format and duplication
        if (is_validemail(addressBook, mail))
        {
            if (!is_duplicate_email(addressBook, mail))
            {
                ret = 1; // Valid and unique email
            }
            else
            {
                printf("Email-ID already exists!\n");
            }
        }
        else
        {
            printf("Invalid Email-ID!\n");
        }
    }

    // Store validated email
    strcpy(newContact.email, mail);

    printf("\n✅ Contact created successfully\n");

    // Ask the user whether to save the contact permanently
    if (askToSaveContact())
    {
        // Save to address book and file
        addressBook->contacts[addressBook->contactCount++] = newContact;
        saveContactsToFile(addressBook);
        printf("📁 Contact saved to file\n");
    }
    else
    {
        printf("⚠️ Contact not saved\n");
    }
}

void searchContact(AddressBook *addressBook)
{
    int choice = 0;
    print_menu(); // menu display

    while (1)
    {
        printf("Enter your choice: ");
        // scanf() function returns the number of input items successfully matched and assigned
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number from 1 to 4\n");
            while (getchar() != '\n') // Clear the invalid characters from the input buffer
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            search_by_name(addressBook, SEARCH);
            return;
        case 2:
            search_by_number(addressBook, SEARCH);
            return;
        case 3:
            search_by_email(addressBook, SEARCH);
            return;
        case 4:
            printf("Returning to main menu...\n");
            return;
        default:
            printf("Invalid choice! Please try again\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int choice = 0;
    print_menu(); // menu display

    while (1)
    {
        printf("Enter your choice: ");
        // scanf() function returns the number of input items successfully matched and assigned
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number from 1 to 4\n");
            while (getchar() != '\n') // Clear the invalid characters from the input buffer
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            search_by_name(addressBook, EDIT);
            return;
        case 2:
            search_by_number(addressBook, EDIT);
            return;
        case 3:
            search_by_email(addressBook, EDIT);
            return;
        case 4:
            printf("Returning to main menu...\n");
            return;
        default:
            printf("Invalid choice! Please try again\n");
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice = 0;
    print_menu(); // menu display

    while (1)
    {
        printf("Enter your choice: ");
        // scanf() function returns the number of input items successfully matched and assigned
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number from 1 to 4\n");
            while (getchar() != '\n') // Clear the invalid characters from the input buffer
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            search_by_name(addressBook, DELETE);
            return;
        case 2:
            search_by_number(addressBook, DELETE);
            return;
        case 3:
            search_by_email(addressBook, DELETE);
            return;
        case 4:
            printf("Returning to main menu...\n");
            return;
        default:
            printf("Invalid choice! Please try again\n");
        }
    }
}
