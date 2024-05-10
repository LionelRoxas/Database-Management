/**********************************************************
// 
//   Name:        Lionel Derrick S. Roxas
//
//   Homework:    Project 1
//
//   Class:       ICS 212
//
//   Instructor:  Ravi Narayan
//
//   Date:        March 22, 2024
//
//   File:        database.h
//
//   Description:
//              This file contains the function prototype for 
//              'database.c'
//
**********************************************************/

#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"

int addRecord(struct record **, int*, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int*);
int deleteRecord(struct record **start, int*);
int writefile(struct record *, char[]);
int readfile(struct record **, char[]);
void cleanup(struct record **);

#endif
