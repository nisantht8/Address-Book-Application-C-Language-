#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook); // Create a new contact
                break;
            case 2:
                searchContact(&addressBook); // Search for a contact by name, phone number, or email
                break;
            case 3:
                editContact(&addressBook); // Edit an existing contact by name, phone number, or email
                break;
            case 4:
                deleteContact(&addressBook); // Delete a contact by name, phone number, or email
                break;
            case 5:
                printf("Select sort criteria:\n"); // List all contacts in the address book
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n"); // Save the address book and exit the program
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("\033[31mInvalid choice...Please try again.\033[0m\n");
        }
    } while (choice != 6);
    
       return 0; // Exit the program
}
