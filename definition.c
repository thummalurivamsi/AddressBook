/*
Documentation
Name        : Vamsi T
Date        : 16/6/25
Description : Address Book project
*/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void print_menu()
{
    printf("\nSelect one to search\n");
    printf("1. Name\n");
    printf("2. Number\n");
    printf("3. Email\n");
    printf("4. Back to Main Menu\n");
}

int is_validnumber(AddressBook *addressBook, char *number)
{
    int i = 0;

    // Check if the number has exactly 10 digits
    while (number[i])
    {
        if (number[i] < '0' || number[i] > '9') // Check if each char is digit
            return 0;
        i++;
    }

    if (i != 10) // Not 10 digits
        return 0;

    return 1;
}
int is_validemail(AddressBook *addressBook, char *mail)
{
    int i, len = strlen(mail);
    char *ret;
    if (mail == NULL || len < 7) // Minimum valid format is : a@b.com
        return 0;

    // Find '@' and check only one '@'
    char *at = strchr(mail, '@');
    if (at == NULL || strchr(at + 1, '@') != NULL)
        return 0;

    // Check if .com is at the end
    // Count how many times .com appears
    int com_count = 0;
    char *ptr = mail;
    while ((ptr = strstr(ptr, ".com")) != NULL)
    {
        com_count++;
        ptr += 4; // Move forward to search for next
    }

    // Must appear only once, and at the end
    if (com_count != 1 || strcmp(&mail[len - 4], ".com") != 0)
        return 0;

    // check characters before and after '@' are alphanumeric
    int index = at - mail;
    if (index == 0 || index == len - 1 || !isalnum(mail[index - 1]) || !isalnum(mail[index + 1]))
        return 0;

    // Check that the email only contains lowercase letters, digits, '.', '@'
    for (i = 0; i < len; i++)
    {
        // No uppercase letters or spaces
        if (isupper(mail[i]) || mail[i] == ' ')
            return 0;

        if (mail[i] == '.')
        {
            // Dot cannot be at the start or end
            if (i == 0 || i == len - 1)
                return 0;

            // No consecutive dots
            if (mail[i + 1] == '.')
                return 0;

            // Dot must be surrounded by alphanumeric characters
            if (!isalnum(mail[i - 1]) || !isalnum(mail[i + 1]))
                return 0;
        }

        // Only allow lowercase, digits, '@', '.'
        if (!islower(mail[i]) && !isdigit(mail[i]) && mail[i] != '@' && mail[i] != '.')
            return 0;
    }

    return 1; // All checks passed
}
// Duplicate funtion
int is_duplicate_number(AddressBook *addressBook, char *number)
{
    int i;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, number) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int is_duplicate_email(AddressBook *addressBook, char *mail)
{
    int i;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, mail) == 0)
        {
            return 1;
        }
    }
    return 0;
}
// Function to ask the user if they want to save the contact
int askToSaveContact()
{
    char choice;
    while (1)
    {
        printf("Do you want to save this contact? (y/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ; // Clear buffer

        if (choice == 'y' || choice == 'Y')
            return 1;
        else if (choice == 'n' || choice == 'N')
            return 0;
        else
            printf("❌ Invalid input! Please enter 'y' or 'n'.\n");
    }
}

//  Search contact
void search_by_name(AddressBook *addressBook, int mode)
{
    int i, count = 0;
    char new_name[50];
    int name_index[MAX_CONTACTS];

    while (1)
    {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", new_name);

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, new_name) == 0)
            {
                if (!count)
                    printf("\nThese are the matched contacts of you entered details\n");
                printf("\nContact %d:\n", count + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                name_index[count++] = i;
            }
        }

        if (count == 0)
        {
            printf("Invalid Name! or Contact name not found.\n");
            continue; // ask again
        }
        // Operation selection
        if (mode == EDIT)
        {
            edit_contact(addressBook, name_index, count);
        }
        else if (mode == DELETE)
        {
            delete_contact(addressBook, name_index, count);
        }
        // if mode == SEARCH, just proceed without calling edit/delete

        break; // Exit the loop after valid processing
    }
}

void search_by_number(AddressBook *addressBook, int mode)
{
    int i, count = 0;
    char new_number[20];
    int number_index;

    while (1)
    {
        printf("Enter the contact number: ");
        scanf(" %[^\n]", new_number);

        // Basic validation function
        if (!is_validnumber(addressBook, new_number))
        {
            printf("Invalid number format!\n");
            continue;
        }

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, new_number) == 0)
            {
                if (!count)
                    printf("\nThese are the matched contacts of you entered details\n");
                printf("\nContact %d:\n", count + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                number_index = i;
                count++;
                break;
            }
        }
        if (count == 0)
        {
            printf("Contact number not found\n");
            continue; // // ask again
        }
        // Operation selection
        if (mode == EDIT)
        {
            edit_contact(addressBook, &number_index, count);
        }
        else if (mode == DELETE)
        {
            delete_contact(addressBook, &number_index, count);
        }
        // if mode == SEARCH, just proceed without calling edit/delete

        break; // Exit the loop after valid processing
    }
}

void search_by_email(AddressBook *addressBook, int mode)
{
    int i, count = 0;
    char new_email[50];
    int email_index;

    while (1)
    {
        printf("Enter the contact email: ");
        scanf(" %[^\n]", new_email);

        // Basic validation function
        if (!is_validemail(addressBook, new_email))
        {
            printf("Invalid email format!\n");
            continue;
        }

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, new_email) == 0)
            {
                if (!count)
                    printf("\nThese are the matched contacts of you entered details\n");
                printf("\nContact %d:\n", count + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                email_index = i;
                count++;
                break;
            }
        }

        if (count == 0)
        {
            printf("Contact Email-ID not found\n");
            continue; // ask again
        }
        // Operation selection
        if (mode == EDIT)
        {
            edit_contact(addressBook, &email_index, count);
        }
        else if (mode == DELETE)
        {
            delete_contact(addressBook, &email_index, count);
        }
        // if mode == SEARCH, just proceed without calling edit/delete

        break; // Exit the loop after valid processing
    }
}

// Function to edit a contact based on user's field selection
void edit_contact(AddressBook *addressBook, int *index, int count)
{
    int choice = 0, select = 1, selected_index = 0;
    char edit_name[50], edit_number[20], edit_email[50];
    char again = 'y';
    int is_modified = 0; // Flag to indicate whether changes were made

    // If multiple matching contacts found, prompt user to select one
    if (count > 1)
    {
        while (1)
        {
            printf("\nSelect one contact to edit (1 to %d): ", count);
            if (scanf("%d", &select) != 1 || select < 1 || select > count)
            {
                printf("\n❌ Invalid selection!\n");
                while (getchar() != '\n')
                    ; // Clear invalid input
                continue;
            }
            break; // Valid selection received
        }
    }

    // Get the actual index of the contact to edit from the matched index list
    selected_index = index[select - 1];

    // Loop to allow multiple fields to be edited in one session
    while (again == 'y' || again == 'Y')
    {
        // Prompt user to select field to edit
        printf("\nSelect what to edit:\n");
        printf("1. Name\n2. Number\n3. Email\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("❌ Invalid input! Please enter a number (1 to 3).\n");
            while (getchar() != '\n')
                ; // Clear buffer
            continue;
        }

        switch (choice)
        {
        case 1:
            // Edit contact name
            printf("Enter the new name: ");
            scanf(" %[^\n]", edit_name);
            strcpy(addressBook->contacts[selected_index].name, edit_name);
            is_modified = 1;
            break;

        case 2:
            // Edit contact number with validation
            while (1)
            {
                printf("Enter the new contact number: ");
                scanf(" %[^\n]", edit_number);

                if (!is_validnumber(addressBook, edit_number))
                {
                    printf("❌ Invalid number format! Must be 10 digits.\n");
                    continue;
                }

                if (!is_duplicate_number(addressBook, edit_number))
                {
                    strcpy(addressBook->contacts[selected_index].phone, edit_number);
                    is_modified = 1;
                    break;
                }
                else
                {
                    printf("⚠️ Number already exists!\n");
                }
            }
            break;

        case 3:
            // Edit email ID with validation
            while (1)
            {
                printf("Enter the new Email-ID: ");
                scanf(" %[^\n]", edit_email);

                if (!is_validemail(addressBook, edit_email))
                {
                    printf("❌ Invalid email format!\n");
                    continue;
                }

                if (!is_duplicate_email(addressBook, edit_email))
                {
                    strcpy(addressBook->contacts[selected_index].email, edit_email);
                    is_modified = 1;
                    break;
                }
                else
                {
                    printf("⚠️ Email-ID already exists!\n");
                }
            }
            break;

        default:
            printf("⚠️ Invalid choice! Please select between 1 and 3.\n");
            continue;
        }

        // Display updated contact info after modification
        printf("\n✅ Contact updated:\n");
        printf("Name     : %s\n", addressBook->contacts[selected_index].name);
        printf("Contact  : %s\n", addressBook->contacts[selected_index].phone);
        printf("Email-ID : %s\n", addressBook->contacts[selected_index].email);

        // Ask user if they want to edit another field for the same contact
        while (1)
        {
            printf("\nWould you like to edit another field? (y/n): ");
            scanf(" %c", &again);
            while (getchar() != '\n')
                ; // Clear input buffer

            if (again == 'y' || again == 'Y' || again == 'n' || again == 'N')
                break;
            else
                printf("❌ Invalid input! Please enter 'y' or 'n'.\n");
        }
    }

    // If any modifications were made, ask if changes should be saved permanently
    if (is_modified && askToSaveContact())
    {
        saveContactsToFile(addressBook);
        printf("\n💾 Changes saved to file\n");
    }
    else if (is_modified)
    {
        printf("\n⚠️ Changes were made but not saved to file\n");
    }
}

// Function to delete a contact from the address book
void delete_contact(AddressBook *addressBook, int *index, int count)
{
    int i, select = 1, selected_index = 0;
    char confirm;

    // If multiple matching contacts, ask the user to select one
    if (count > 1)
    {
        while (1)
        {
            printf("\nSelect one contact to delete (1 to %d): ", count);
            if (scanf("%d", &select) != 1 || select < 1 || select > count)
            {
                printf("❌ Invalid selection! Please try again.\n");
                while (getchar() != '\n')
                    ; // Clear invalid input
                continue;
            }
            break; // Valid selection
        }
    }

    // Get the actual index of the contact to delete
    selected_index = index[select - 1];

    // Ask for deletion confirmation
    while (1)
    {
        printf("\nAre you sure you want to delete this contact\nPress (y/n): ");
        scanf(" %c", &confirm);
        while (getchar() != '\n')
            ; // Clear buffer

        if (confirm == 'y' || confirm == 'Y')
        {
            // Shift contacts left to overwrite the deleted contact
            for (i = selected_index; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            // Reduce contact count
            addressBook->contactCount--;

            // Save updated contact list to file immediately
            saveContactsToFile(addressBook);

            // Notify the user
            printf("\n✅ Contact deleted and changes saved to file\n");
            return;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            printf("\n⚠️ Deletion cancelled\n");
            return;
        }
        else
        {
            printf("❌ Invalid input! Please enter 'y' or 'n'\n");
        }
    }
}
