/*
Documentation
Name        : Vamsi T
Date        : 16/6/25
Description : Address Book project
*/

#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressBook.csv", "w"); // Overwrite mode
    if (fptr == NULL)
    {
        fprintf(stderr, "Cannot open the file for writing\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressBook.csv", "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "Cannot open the file for reading\n");
        addressBook->contactCount = 0; // no contacts loaded
        return;
    }

    int i = 0;
    while (i < MAX_CONTACTS &&
           fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 3)
    {
        i++;
    }

    addressBook->contactCount = i;
    fclose(fptr);
}

/*
#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressBook.csv", "w"); // overwrite to save permanently
    if (fptr == NULL)
    {
        fprintf(stderr, "Cannot open the file for writing\n");
        return;
    }

    fprintf(fptr, "#%d\n", addressBook->contactCount); // Save contact count

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressBook.csv", "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "Cannot open the file for reading\n");
        return;
    }

    if (fscanf(fptr, "#%d\n", &addressBook->contactCount) != 1)
    {
        fprintf(stderr, "Failed to read contact count\n");
        addressBook->contactCount = 0;
        fclose(fptr);
        return;
    }

    int i = 0;
    while (i < MAX_CONTACTS && fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                                      addressBook->contacts[i].name,
                                      addressBook->contacts[i].phone,
                                      addressBook->contacts[i].email) == 3)
    {
        i++;
    }

    addressBook->contactCount = i;
    fclose(fptr);
}

*/