#include <stdio.h>
#include <string.h>
#include "file.h"
// Function to save contacts to a file 
void saveContactsToFile(AddressBook *addressBook) 
{
    // Open the file in write mode
    FILE *file=fopen("contacts.txt","w");
    if(file == NULL)
    {
        printf("\033[31mFile is not created\033[0m\n"); // Print error message
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Write the contact details to the file
       fprintf(file,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); 
    }
    fclose(file); // Close the file after writing
  
}
// Function to load contacts from a file
void loadContactsFromFile(AddressBook *addressBook) 
{
    // Open the file in read mode
    FILE *file=fopen("contacts.txt","r");
    if(file == NULL)
    {
        printf("\033[31mFile is not created\033[0m\n");  // Print error message
        return;
    }
    addressBook->contactCount=0; // Reset contactcount before using it to 0
    char name[50];
    char phone[20];
    char email[50];
    int i=0;
    while (!feof(file)) // Loop until the end of the file is reached
    {
        fscanf(file,"%50[^,],%10[^,],%s\n",name,phone,email);
        strcpy(addressBook->contacts[i].name,name);
        strcpy(addressBook->contacts[i].phone,phone);
        strcpy(addressBook->contacts[i].email,email);
        i++;
    }
    addressBook->contactCount=i;  // Update contactcount every time a contact is stored 
    fclose(file); // Close the file after reading
}
