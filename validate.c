#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "validate.h"
#include "file.h"
#include <ctype.h>
#include "populate.h"

// Checks a given email is already exists in the address book
int unix_mail(AddressBook *addressBook,char *mail,int res)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Compare the given email with the current contact's email
        if(strcmp(addressBook->contacts[i].email,mail) == 0)
        {
            return 0;  // Email already exists
        }
    }
    return 1;  // Email does not exist
}
// Checks a given phone is already exists in the address book
int unix_phone(AddressBook *addressBook,char *phone,int res)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Compare the given phone no. with the current contact's phone no.
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)
        {
            return 0;  // phone no. already exists
        }
    }
    return 1;  // phone no. does not exist
}
// Validates an email address 
int valid_email(char *mail)
{
    // First character must not be a digit
    if(isdigit(mail[0]))
    {
        printf("\033[31mDigit should not start first\033[0m\n");
        return 0; // Invalid email
    }
    char *at=strstr(mail, "@");
    // Email must have a '@' symbol
    if(at == NULL)
    {
        printf("\033[31mEmail should contain @ character\033[0m\n");
        return 0; // Invalid email
    }
    // Character before '@' must be an alphabet
    if(at == mail || !isalpha(*(at-1)))
    {
        printf("\033[31mBefore @ must be one alphabet\033[0m\n");
        return 0; // Invalid email
    }
    char *dot=strstr(mail, ".com");
    // Email must have a '.com' at the end
    if(dot == NULL)
    {
        printf("\033[31mEmail should end with .com\033[0m\n");
        return 0;  // Invalid email
    }
    int found=0;
    // Between '@' and ".com" must have at least one alphabet
    for(char *at_dot=at+1;at_dot < dot;at_dot++)
    {
        if(isalpha(*at_dot))
        {
            found++; 
        }
    }
    if(found < 1)
    {
        printf("\033[31mBetween @ and . should have alphabet\033[0m\n");
        return 0; // Invalid email
    }
    return 1; // Valid email
}
// Validates phone number 
int valid_phone(char *phone)
{
    int count=0;
    for(int i=0;phone[i]!='\0';i++)
    {
        // Check that all characters are digits
        if(!isdigit(phone[i]))
        {
            return 0;
        }
        count++;
    }
    // Check if the phone number contains 10 digits
    if(count == 10)
        return 1;
    else
        return 0;
}
// Validates a name
int valid_name(char *name)
{
    for(int i=0;name[i] != '\0';i++)
    {
        // Check that all characters are alphabets
        if(!isalpha(name[i]) && (name[i] != ' '))
        {
            return 0;
        }
    }
    return 1;
}
// Function to search a contact in the AddressBook 
int searchcontact(AddressBook *addressBook) 
{
    int choice;
    int found;
    char temp[50];
    do{
        printf("Serach by contact\n");
        printf("1.Search by Name\n");
        printf("2.Search by Phone\n");
        printf("3.Search by email\n");
        printf("4.Exit\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                while(1)
                {
                    printf("Enter the name: ");
                    scanf(" %[^\n]",temp);
                    // Check if name contains only alphabets
                    if(!valid_name(temp))
                    {
                        printf("\033[31mInvalid...Enter only Alphabet character\033[0m\n");
                    }
                    else 
                    {
                        break;
                    }
                }
                found=0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcasecmp(addressBook->contacts[i].name,temp) == 0)
                    {
                        printf("\nContact[%d]\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        return i; // Return the index of the contact
                    }   
                }
                if(found == 0)
                {
                    printf("\033[31mContact not found\033[0m\n");
                }
                break;
            case 2:
                while(1)
                {
                     printf("Enter phone number: ");
                    scanf(" %[^\n]",temp);
                    // Check if phone number contains only digits
                    if(!valid_phone(temp))
                    {
                        printf("\033[31mInvalid...Enter only numbers\033[0m\n");
                    }
                    else
                    {
                        break;
                    }
                }
                found=0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].phone,temp) == 0)
                    {
                        printf("\nContact[%d]\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        return i; // Return the index of the contact
                    }  
                }
                if(found == 0) 
                {
                    printf("\033[31mContact not found\033[0m\n");
                }
                break;
            case 3:
                while(1)
                {
                    printf("Enter email id: ");
                    scanf(" %[^\n]",temp);
                    // Check if email id is valid
                    if(!valid_email(temp)) 
                    {
                        printf("\033[31mInvalid...Enter valid mail id\033[0m\n");
                    }
                    else
                    {
                        break;
                    }
                }
                found=0;
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].email,temp) == 0)
                    {
                        printf("\nContact[%d]\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        return i; // Return the index of the contact
                    }  
                }
                if(found == 0)
                {
                    printf("\033[31mContact not found\033[0m\n");
                }
                break;
            case 4:
                {
                    printf("Exiting search\n");
                    break;
                }
            default:
                printf("\033[31mInvalid choice. Please try again.\033[0m\n");
                break;
        }      
    }while(choice != 4);

    return -1;
}