#ifndef FILE_H
#define FILE_H

#include "contact.h"

// Function to add a contact to the file 
void saveContactsToFile(AddressBook *addressBook);

// Function to read contacts from the file
void loadContactsFromFile(AddressBook *addressBook);

#endif
