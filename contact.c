#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "validate.h"
#include "file.h"
#include <ctype.h>
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    printf("\033[35m<-----CONTACTS LISTS----->\033[0m\n");
    // Bubble sort the contacts based on the sort criteria
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            int cmp=0;
            switch (sortCriteria)
            {
                case 1:
                {
                    // Compare by name
                    cmp=strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                    break;
                }
                case 2:
                {
                    // Compare by phone number
                    cmp=strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                    break;
                }
                case 3:
                {
                    // Compare by email
                    cmp=strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                    break;
                }
                default:
                {
                    cmp=0;
                    break;
                }
            }
            if(cmp > 0)  // Swap contacts if they are in the wrong order
            {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }  
        }
    }
    // Print the sorted contacts
    printf("\033[34m\nContact\n\033[0m\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {

        printf("%-20s",addressBook->contacts[i].name);
        printf("%-15s",addressBook->contacts[i].phone);
        printf("%-20s\n",addressBook->contacts[i].email);
    }
    printf("\n");
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0; // Reset contactcount before using it to 0
    loadContactsFromFile(addressBook); // Load contacts from file
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    int res;
    // Check if maximum contacts reached
    if(addressBook->contactCount==MAX_CONTACTS)
    {
        printf("\033[31mContact is full\033[0m\n");
        return ;
    }
    
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];
    printf("\n\033[35mContacts Exists ---> [%d]\033[0m\n", addressBook->contactCount);

    while(1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",temp_name);
        if(!valid_name(temp_name)) // check if name is valid
        {
            printf("\033[31mInvalid...Enter only Alphabet character\033[0m\n");
        }
        else 
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp_name);

    while(1)
    {
        printf("Enter phone number: ");
        scanf(" %[^\n]",temp_phone);
        if(!valid_phone(temp_phone)) // check if phone number is valid
        {
            printf("\033[31mInvalid...Enter only numbers\033[0m\n");
        }
        else if(!unix_phone(addressBook,temp_phone,res)) // chech if phone number is unique 
        {
            printf("\033[31mAlready exists...Enter unique number\033[0m\n");
        }
        else
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].phone,temp_phone);

    while(1)
    {
        printf("Enter email id: ");
        scanf(" %[^\n]",temp_email);
        if(!valid_email(temp_email)) // check if email id is valid
        {
            printf("\033[31mInvalid...Enter valid mail id\033[0m\n");
        }
        else if(!unix_mail(addressBook,temp_email,res)) // check if email id is unique
        {
            printf("\033[31mAlready exists...Enter unique mail\033[0m\n");
        }
        else
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp_email);
    printf("\033[32m<------Contact created successfully✅------>\033[0m\n");
    addressBook->contactCount++; // increment contactcount
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    int found;
    char temp[50];
    do{
        printf("Serach by contact:\n");
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
                    if(!valid_name(temp)) // check if name is valid
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
                    if(strcasestr(addressBook->contacts[i].name,temp) != NULL)
                    {
                        printf("\n\033[34mContact[%d]\033[0m\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        found =1;
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
                    if(!valid_phone(temp)) // check if phone number is valid
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
                    if(strstr(addressBook->contacts[i].phone,temp) != NULL)
                    {
                        printf("\n\033[34mContact[%d]\033[0m\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        found =1;
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
                    if(!valid_email(temp)) // check if email is valid
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
                    if(strstr(addressBook->contacts[i].email,temp) != NULL)
                    {
                        printf("\n\033[34mContact[%d]\033[0m\n", i + 1);
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        found=1; 
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
                printf("\033[31mInvalid choice...Please try again.\033[0m\n");
                break;
        }      
    }while(choice != 4);

}

void editContact(AddressBook *addressBook)
{
    int res=searchcontact(addressBook); // contact index from searchcontact function
    if(res == -1)
    {
        printf("\033[31mContact not found\033[0m\n");
        return;
    }
    char new[100];
    int choice;
    do{
        printf("Edit the contact Menu:\n");
        printf("1.Edit the Name\n");
        printf("2.Edit the phone\n");
        printf("3.Edit the email\n");
        printf("4.Exit\n");
        printf("Enter the choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            while(1)
            {
                printf("Enter the new_name: ");
                scanf(" %[^\n]",new);
                if(!valid_name(new)) // check if name is valid
                {
                    printf("\033[31mInvalid...Enter only Alphabet character\033[0m\n");
                }
                else 
                {
                    printf("\033[32m<-----Successfully edited✅----->\033[0m\n");
                    break;
                }
            }
            strcpy(addressBook->contacts[res].name,new);
            break;
        case 2:
            while (1)
            {
                printf("Enter the new_phone number: ");
                scanf(" %[^\n]",new);
                if(!valid_phone(new)) // check if phone number is valid
                {
                    printf("\033[31mInvalid...Enter only Numbers\033[0m\n");
                }
                else if(!unix_phone(addressBook,new,res)) // check if phone number is unique
                {
                    printf("\033[31mAlready exists...Enter unique number\033[0m\n");
                }
                else 
                {
                    printf("\033[32m<-----Successfully edited✅----->\033[0m\n");
                    break;
                }
            }
            strcpy(addressBook->contacts[res].phone,new);
            break;
        case 3:
            while (1)
            {
                printf("Enter the new_email: ");
                scanf(" %[^\n]",new);
                if(!valid_email(new)) // check if email is valid
                {
                    printf("\033[31mInvalid...Enter valid mail id\033[0m\n");
                }
                else if(!unix_mail(addressBook,new,res)) // check if email is unique
                {
                    printf("\033[31mAlready exists...Enter unique mail\033[0m\n");
                }
                else 
                {
                    printf("\033[32m<-----Successfully edited✅----->\033[0m\n");
                    break;
                }
            }
            strcpy(addressBook->contacts[res].email,new);  
            break;  
        case 4:
            {
                printf("Exiting editing\n");
                break;
            }      
        
        default:
            printf("\033[31mInvalid choice...Please try again.\033[0m\n");
            break;
        }
    }while(choice != 4);
}

void deleteContact(AddressBook *addressBook)
{
    int res=searchcontact(addressBook); //contact index from searchcontact function
    if(res == -1)
    {
        printf("\033[31mContact not found\033[0m\n");
        return;
    }
    // shift all contacts after the deleted contact 
    for(int i=res;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--; // decrement contactcount
    printf("\033[32m<-----Contact successfully Deleted✅----->\033[0m\n");
}
