/******************************************************************
//
//  Name:          Lionel Derrick S. Roxas
//
//  Homework:      Project 1
//
//  Class:         ICS 212
//
//  Instructor:    Ravi Narayan
//
//  Date:          March 22, 2024
//
//  File:          record.h
//
//  Description:   This file contains the structure for record.
// 
*******************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[45];
    struct record*     next;
};

#endif
