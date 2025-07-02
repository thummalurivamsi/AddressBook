#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>

#define MAX_CONTACTS 100
#define SEARCH 0
#define EDIT 1
#define DELETE 2

typedef struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// Core operations
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
// Menu display
void print_menu();
// Validation
int is_validnumber(AddressBook *addressBook, char *number);
int is_validemail(AddressBook *addressBook, char *mail);
int is_duplicate_number(AddressBook *addressBook, char *number);
int is_duplicate_email(AddressBook *addressBook, char *mail);
// Search operations
void search_by_name(AddressBook *addressBook, int f);
void search_by_number(AddressBook *addressBook, int f);
void search_by_email(AddressBook *addressBook, int f);
// Edit / Delete operations
void edit_contact(AddressBook *addressBook, int *index, int count);
void delete_contact(AddressBook *addressBook, int *index, int count);
// Save contact
int askToSaveContact();

#endif
