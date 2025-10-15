#ifndef VALIDATE_H
#define VALIDATE_H

#include "contact.h"

// Function to validate the unique contact  
int unix_mail(AddressBook *,char *,int);
int unix_phone(AddressBook *,char *,int);

// Function to validate the contact
int valid_email(char *);
int valid_phone(char *);
int valid_name(char *);

// Function to validate the searchcontact 
int searchcontact(AddressBook *);

#endif