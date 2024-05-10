/*****************************************************************
//
//  NAME:        Lionel Derrick Roxas
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//  
//  DATE:        February 11, 2024
//  
//  FILE:        user_interface.c
//  
//  DESCRIPTION: This file contains the main function and other supporting functions
//               for user interface. It implements a simple interactive program to manage
//               a database of records.
//  
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"

void introDisplay();
struct record* getInput(char*, int, struct record*, int);
void getAccNum(int*);
void getName(char*, int, int*);
void getAddress(char*, int, char*);

int debugmode = 0;

/********************************************************************
//
//  Function name: main
//  
//  Description:   Entry point of the program. Loops back to menu.
//                 
//  
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return value:  0 : success
//                   
*********************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    char user_input[50];
    int accNum = 0;
    int loop = 0;
    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
    }
    else if (argc > 1)
    {
        printf("ErrorMessage: Invalid usage. Use './project' or './project debug' ONLY.\n");
    }
    readfile(&start, "records.txt");
    while (loop == 0)
    {
        introDisplay();
        memset(user_input, 0, 50);
        start = getInput(user_input, 50, start, accNum);
        if (strcmp(user_input, "q") == 0)
        {
            loop = 1;
        }
        else if (strcmp(user_input, "qu") == 0)
        {
            loop = 1;
        }
        else if (strcmp(user_input, "qui") == 0)
        {
            loop = 1;
        }
        else if (strcmp(user_input, "quit") == 0)
        {
            loop = 1;
        }
    }
    return 0;
}

/*********************************************************************
//
//  Function name: introDisplay
//
//  Description:   Displays an introductory message.
//
//  Parameters:    None
//
//  Return value:  None
//
********************************************************************/

void introDisplay()
{
    printf("********************************************************************************\n");
    printf("Welcome to ICE, the software that stores the company records for 'ReZero'!\n\n");
    printf("Choose from the MENU OPTIONS below:\n");
    printf("\"add\":          Add a new record in the database\n");
    printf("\"printall\":     Print all records in the database\n");
    printf("\"find\":         Find the record(s) with a specified account #\n");
    printf("\"delete\":       Delete existing record(s) from the database using the account #\n");
    printf("\"quit\":         Quit the program\n");
    printf("********************************************************************************\n");
}

/*********************************************************************
//
//  Function name: getInput
//
//  Description:   Gets input from the user based on the selected command.
//
//  Parameters:    user_input (char*): Buffer to store user input
//                 size (int): Size of the user_input buffer
//                 start (struct record*): Pointer to the start of the record list
//
//  Return value:  None
//
********************************************************************/

struct record* getInput(char* user_input, int size, struct record *start, int accNum)
{
    char* add[] = {"a", "ad", "add"};
    char* printall[] = {"p" , "pr" , "pri", "prin", "print", "printa", "printal", "printall"};
    char* find[] = {"f", "fi", "fin", "find"};
    char* delete[] = {"d", "de", "del", "dele", "delet", "delete"};
    char* quit[] = {"q", "qu", "qui", "quit"};
    int p = 0;
    int f = 0;
    int d = 0;
    int q = 0;
    int a = 0;
    int addMenu = 0;
    int printallMenu = 0;
    int findMenu = 0;
    int deleteMenu = 0;
    int quitMenu = 0;
    char name[50];
    char address[100];
    char filename[] = "records.txt";
    printf("Type your command here: ");
    fgets(user_input, size, stdin);
    user_input[strlen(user_input) - 1] = '\0';
    while (a < 3 && !addMenu)
    {
        if (strcmp(user_input, add[a]) == 0)
        {
            addMenu = 1;
        }
        a++;
    }
    while (p < 8 && !printallMenu)
    {
        if (strcmp(user_input, printall[p]) == 0)
        {
            printallMenu = 1;
        }
        p++;
    }
    while (f < 4 && !findMenu)
    {
        if (strcmp(user_input, find[f]) == 0)
        {
            findMenu = 1;
        }
        f++;
    }
    while (d < 6 && !deleteMenu)
    {
        if (strcmp(user_input, delete[d]) == 0)
        {
            deleteMenu = 1;
        }
        d++;
    }
    while (q < 4 && !quitMenu)
    {
        if (strcmp(user_input, quit[q]) == 0)
        {
            quitMenu = 1;
        }
        q++;
    }
    if (addMenu == 1)
    {
        printf("SUCCESS! You have chosen to add a new record.\n\n");
        addMenu = '\0';
        getAccNum(&accNum);
        getName(name, 50, &accNum);
        getAddress(address, 100, name);
        addRecord(&start, &accNum, name, address);
    }
    else if (printallMenu == 1)
    {
        printf("SUCCESS! You have chosen to print all records.\n\n");
        printallMenu = '\0';
        printAllRecords(start);
    }
    else if (findMenu == 1)
    {
        printf("SUCCESS! You have chosen to find records.\n\n");
        findMenu = '\0';
        getAccNum(&accNum);
        findRecord(start, &accNum);
    }
    else if (deleteMenu == 1)
    {
        printf("SUCCESS! You have chosen to delete records.\n\n");
        deleteMenu = '\0';
        getAccNum(&accNum);
        deleteRecord(&start, &accNum);
    }
    else if (quitMenu == 1)
    {
        writefile(start, filename);
        cleanup(&start);
        printf("Quitting program . . .\n");
        printf("Thank you for using my program!\n");
        quitMenu = '\0';
    }
    else
    {
        printf("ErrorMessage: Please type the options exactly as they are shown.\n\n");
    }
    return start;
}

/*********************************************************************
//
//  Function name: getAccNum
//
//  Description:   Gets the account number from the user.
//
//  Parameters:    accNum (int*): Pointer to store the account number
//
//  Return value:  None
//
********************************************************************/

void getAccNum(int* accNum)
{
    char temp[50];
    int validInput;
    printf("Please enter a positive number (> 0) for the account number.");
    do
    {
        printf("\nEnter account number: ");
        validInput = scanf("%d", accNum);
        if (validInput == 1 && *accNum > 0)
        {
            printf("SUCCESS!\n/********************\n");
            printf("Account Number: %d\n", *accNum);
            printf("********************/\n");
            fgets(temp, 50, stdin);
            return;
        }

        else
        {
            printf("ErrorMessage: Please enter a positive whole number greater than 0.");
            fgets(temp, 50, stdin);
        }
    }
    while (validInput == 0 || *accNum <= 0);
}

/*********************************************************************
//
//  Function name: getName
//
//  Description:   Gets the name from the user.
//
//  Parameters:    name (char*): Buffer to store the name
//                 size (int): Size of the name buffer
//                 accNum (int*): Pointer to the account number
//
//  Return value:  None
//
********************************************************************/

void getName(char* name, int size, int* accNum)
{
    size_t len;
    int hasDigit;
    int i;
    int loop;
    loop = 0;
    printf("\nPlease enter a name to designate \"%d\" to.", *accNum);
    while (loop == 0)
    {
        printf("\nEnter name: ");
        hasDigit = 0;
        fgets(name, size, stdin);
        for (i = 0; name[i] != '\0' && !hasDigit; i++)
        {
            if (name[i] >= '0' && name[i] <= '9')
            {
                hasDigit = 1;
            }
        }
        if (name[0] == '\n'|| name[0] == ' ')
        {
            printf("ErrorMessage: Name must not be empty.");
        }
        else if (hasDigit == 1)
        {
            printf("ErrorMessage: Name must not contain integers.");
        }

        else
        {
            len = strlen(name);
            if (len > 0 && name[len - 1] == '\n')
            {
                name[len - 1] = '\0';
            }
            printf("SUCCESS!\n/********************\n");
            printf("Name: %s\n", name);
            printf("********************/\n");
            loop = 1;
        }
    }
}

/*********************************************************************
//
//  Function name: getAddress
//
//  Description:   Gets the address from the user.
//
//  Parameters:    address (char*): Buffer to store the address
//                 size (int): Size of the address buffer
//                 name (char*): Name associated with the address
//
//  Return value:  None
//
********************************************************************/

void getAddress(char* address, int size, char* name)
{
    size_t len;
    char line[100];
    int loop;
    loop = 0;
    printf("\nEnter the address for \"%s\". ", name);
    printf("Press \"enter\" once for new line. Press \"enter\" twice to end:\n");
    memset(address, 0, size);
    while (loop == 0)
    {
        fgets(line, size, stdin);
        if (line[0] == '\n' || line[0] == ' ')
        {
            if (strlen(address) == 0 || strcmp(address, "\n") == 0 || strcmp(address, " ") == 0)
            {
                printf("ErrorMessage: Address cannot be empty. ");
                printf("Enter valid address:\n");
                line[strcspn(line, "\n")] = '\0';
                line[strcspn(line, " ")] = '\0';
            }

            else
            {
                loop = 1;
            }
        }
        strcat(address, line);
    }
    len = strlen(address);
    if (len > 0 && address[len - 1] == '\n')
    {
        address[len - 1] = '\0';
    }
    printf("SUCCESS!\n/********************\n");
    printf("Address:\n%s", address);
    printf("********************/\n");
}
