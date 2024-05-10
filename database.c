/****************************************************************************
//
//   NAME:       Lionel Derrick S. Roxas
//
//   HOMEWORK:   Project 1
//
//   CLASS:      ICS 212
//
//   INSTRUCTOR: Ravi Narayan
//
//   DATE:       March 22, 2024
//
//   FILE:       database.c
//
//   DESCRIPTION:
//               This file contains functions that allows for creating,
//               viewing, deleting, and modifying customer records.
//
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
extern int debugmode;

/******************************************************************************
//
//   Function name:    addRecord
//
//   Description:      Adds a new record into the database.
//
//   Parameters:       accNum (int*) : points to the account number
//                     name (char) : contains the name of the account owwner
//                     address (char) : contains the address 
//                     start (record **) : points to the record
//
//   Return values:    0 : success
// 
*******************************************************************************/

int addRecord(struct record **start, int* accNum, char name[], char address[])
{
    struct record *newRecord = NULL;
    struct record *prev = NULL;
    struct record *current = NULL;
    struct record *temp = NULL;
    struct record *temp1 = NULL;
    int success = 0;
    newRecord = (struct record*)malloc(sizeof(struct record));
    if (debugmode)
    {
        printf("\n[SUCCESS DEBUG] [addRecord]");
        printf("\nstart: %p, \nAccount Number: %d, ", (void*)start, *accNum);
        printf("\nName: %s, \nAddress:\n%s\n", name, address);
    }
    if (newRecord == NULL)
    {
        printf("Memory allocation failed\n");
        success = -1;
    }
    else
    {
        newRecord->accountno = *accNum;
        strcpy(newRecord->name, name);
        strcpy(newRecord->address, address);
        newRecord->next = NULL;
    }
    if (*start == NULL)
    {
        *start = newRecord;
        success = -1;
    }
    if (success == 0)
    {
        current = *start;
        while (current != NULL && current->accountno < *accNum)
        {
            temp = current;
            current = current->next;
            temp1 = temp;
            prev = temp1;
        }
        if (current != NULL && current->accountno == *accNum)
        {
            printf("Duplicate account number found\n");
            free(newRecord);
            success = -1;
        }
        if (success == 0)
        {
            if (prev == NULL)
            {
                newRecord->next = current;
                *start = newRecord;
            }
            else
            {
                prev->next = newRecord;
                newRecord->next = current;
            }
        }
    }
    return 0;
}

/******************************************************************************
//   
//   Function name:    printAllRecords
//
//   Description:      Prints all the records in the list.
//
//   Parameters:       start (record *) : Points to the start of record
//
//   Return values:    None
//
******************************************************************************/

void printAllRecords(struct record *start)
{
    struct record *current = start;
    if (debugmode)
    {
        printf("\n[SUCCESS DEBUG] [printAllRecords] \nstart: %p\n", (void*)start);
    }
    printf("Printing all records:\n");
    printf("--------------------\n");
    while (current != NULL)
    {
        printf("Account Number: %d\n", current->accountno);
        printf("Name: %s\n", current->name);
        printf("Address: \n%s\n", current->address);
        printf("--------------------\n");
        current = current->next;
    }
}

/*******************************************************************************
//    
//   Function name:    findRecord
//
//   Description:      Prints out the account information. 
//
//   Parameters:       accNum (int*) : points to the account number
//                     start (record *) : points to the start of record
//
//   Return values:    0 : success
//
*******************************************************************************/

int findRecord(struct record *start, int* accNum)
{
    struct record *current = start;
    int found = 0;
    if (debugmode)
    {
        printf("\n[SUCCESS DEBUG] [findRecord] \nstart: %p, ", (void*)start);
        printf("\nAccount Number: %d\n", *accNum);
    }
    if (start == NULL)
    {
        printf("List is empty.\n");
        found = -1;
    }
    while (current != NULL && found == 0)
    {
        if (current->accountno == *accNum)
        {
            found = 1;
        }
        else
        {
            current = current->next;
        }
    }
    if (found == 1)
    {
        printf("Record found:\n");
        printf("--------------------\n");
        printf("Account Number: %d\n", current->accountno);
        printf("Name: %s\n", current->name);
        printf("Address: \n%s\n", current->address);
        printf("--------------------\n");
    }
    else
    {
        printf("Record not found\n");
    }
    return 0;
}

/*****************************************************************************
// 
//   Function name:    deleteRecord
//
//   Description:      Deletes the record
//
//   Parameters:       accNum (int*) : points to the account number
//                     start (record **) : points to the start of record
// 
//   Return values:    0 : success
//
*****************************************************************************/

int deleteRecord(struct record **start, int* accNum)
{
    struct record *prev = NULL;
    struct record *current = *start;
    struct record *temp = NULL;
    struct record *temp1 = NULL;
    int success = 0;
    if (debugmode)
    {
        printf("\n[SUCCESS DEBUG] [deleteRecord] \nstart: %p, ", (void*)start);
        printf("\nAccount Number: %d\n", *accNum);
    }
    if (*start == NULL)
    {
        printf("List is empty. Nothing to delete\n");
        success = -1;
    }
    if (success == 0)
    {
        if (current != NULL && current->accountno == *accNum)
        {
            *start = current->next;
            free(current);
            printf("Record Deleted!\n");
            success = -1;
        }
    }
    if (success == 0)
    {
        while (current != NULL && current->accountno != *accNum)
        {
            temp = current;
            current = current->next;
            temp1 = temp;
            prev = temp1;
        }
        if (current == NULL)
        {
            printf("Record not found\n");
            success = -1;
        }
    }
    if (success == 0)
    {
        if (prev != NULL)
        {
            prev->next = current->next;
            free(current);
            printf("Record Deleted!\n");
            success = 0;
        }
    }
    return 0;
}

/******************************************************************************
//   
//   Function name:     writefile
//
//   Description:       Writes data to records.txt file.
//
//   Parameters:        start (struct record *): Start of linked list.
//                      filename (char): The name of the text file.
//
//   Return Values:     0 : success
//
******************************************************************************/

int writefile(struct record *start, char filename[])
{
    struct record *current;
    int success = 0;
    FILE *file = fopen(filename, "w");
    if (debugmode)
    {
        printf("[SUCCESS DEBUG] [writefile]\n");
        printf("******Passing in writeFile: '%s'\n", filename);
    }
    if (start == NULL)
    {
        printf("File %s is empty. . .\n", filename);
        success = -1;
    }
    if (success == 0)
    {
        if (file == NULL)
        {
            printf("Error opening file %s\n", filename);
            success = -1;
        }
    }
    if (success == 0)
    {
        current = start;
        while (current != NULL)
        {
            fprintf(file, "%d\n", current->accountno);
            fprintf(file, "%s\n", current->name);
            fprintf(file, "%s\n\n", current->address);
            current = current->next;
        }
        fclose(file);
        printf("Records written to %s successfully.\n", filename);
    }
    return 0;
}

/******************************************************************************
//    
//   Function name:     readfile
//
//   Description:       Reads the record files
//
//   Parameters:        start (struct record **): Pointer that points to the
//                      pointer of start.
//                      filename (char []): Name of the file being read.
//
//   Return values:     0 : success
//
*******************************************************************************/

int readfile(struct record **start, char filename[])
{
    int length = 0;
    int accountno;
    char name[100];
    char address[100];
    char line[100];
    int success = 0;
    FILE *file = fopen(filename, "r");
    if (debugmode)
    {
        printf("[SUCCESS DEBUG] [readfile]\n");
        printf("******Passing in readFile: '%s'\n", filename);
    }
    if (file == NULL)
    {
        printf("----------------------\n");
        printf("No file was found. . .\n");
        success = -1;
    }
    else if (fgetc(file) == EOF)
    {
        printf("---------------------------\n");
        printf("No records found in %s. . .\n", filename);
        fclose(file);
        success = -1;
    }
    if (success == 0)
    {
        rewind(file);
        printf("----------------------------------------------\n");
        printf("Records found in %s. Transferring to heap. . .\n", filename);
        while (fscanf(file, "%d\n", &accountno) != EOF)
        {
            success = 0;
            fgets(name, 100, file);
            length = strlen(name);
            if (name[length - 1] == '\n')
            {
                name[length -1] = '\0';
            }
            length = strlen(line);
            address[0] = '\0';
            while (success == 0 && fgets(line, 100, file) != NULL)
            {
                length = strlen(line);
                strcat(address, line);
                if (strstr(address, "\n\n") != NULL)
                {
                    success = 1;
                    length = strlen(address);
                    if (address[length - 1] == '\n')
                    {
                        address[length - 1] = '\0';
                    }
                    if (address[length - 2] == '\n')
                    {
                        address[length - 2] = '\0';
                    }
                }
            }
            addRecord(start, &accountno, name, address);
        }
        fclose(file);
    }
    return 0;
}

/***************************************************************************
//     
//     Function name:     cleanup
//
//     Description:       Releases all the heap space.
//
//     Parameters:        start (struct record **): start of the linked list.
//
//     Return values:     None.
//
****************************************************************************/

void cleanup(struct record **start)
{
    struct record *current = *start;
    struct record *next = NULL;
    if (debugmode)
    {
        printf("[SUCCESS DEBUG] [cleanup]\n");
    }
    while (current != NULL)
    {
        printf("-------------------------\n");
        printf("Record removed from heap!\n");
        printf("-------------------------\n");
        next = current->next;
        free(current);
        current = next;
    }
    if (start != NULL)
    {
        *start = NULL;
    }
}
