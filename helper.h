/*
* Helper header file.
* This file contains the declarations of the helper functions.
*/

#ifndef HELPERH
#define HELPERH

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define FALSE 0
#define TRUE !FALSE

#define STRINGS_EQUAL 0
#define MAX_STR_LEN 1024

#define SEPERATOR_CHAR '|'
#define SEPERATOR_STRING "|"

#define NULL_CHAR_LEN 1

#define COLOR_GREEN "\x1b[32m"
#define COLOR_DARK_YELLOW "\x1b[38;5;144m"
#define COLOR_BRIGHT_PURPLE "\x1b[38;5;111m"
#define COLOR_RED "\x1b[38;5;88m"
#define COLOR_CYAN "\x1b[38;5;14m"
#define COLOR_BOLD "\x1b[1m"
#define COLOR_RESET "\x1b[0m"

#define MAKE_BOOL(x) !!x

#define ONE_CHAR_STRING 2

typedef void (*functionType)(void**, int*, void**, void**); //shortcut for function type

/*
* A function to scan for an integer input from the user.
* input: the pointer to which location the value will be stored, the message to print to the user and values to format the message.
* output: the entered number
*/
int inputInt(int* userInput, const char* format, ...);

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
This function will allocate dynamic amount of memory (depends on string's size) and must be freed after use.
input: stream to read data from
output: a pointer to the newly allocted string that was entered without the new line at the end.
*/
char* myFgets(FILE* stream);

/*
* A function to scan for a string input from the user.
* input: the pointer to which location the value will be stored, the message to print to the user and values to format the message.
* output: the entered string
*/
char* inputString(char** userInput, const char* format, ...);

/*
* A function to check if a specific file exists.
* input: the path of the file.
* output: TRUE if the file exists, FALSE otherwise.
*/
int checkIfFileExists(char* path);

/*
* A function which allows you to geneate a full path from dir and file paths
* input: folder path, file/folder path
* output: a dynamically allocated string in the format "{folderPath}/{path}"
*/
char* joinPaths(char* folder, char* path);

/**
* A function to implement the selection sort algorithm in ascending order (by alphabet).
* this will be used to sort an array of strings.
* input: an array of strings and the number of strings in the array.
* output: none.
*/
void selectionSort(char** arr, int n);

/*
* A function to get/set/free the project's current working directory.
* input: the action (GET/SET/FREE) and the path to the directory (NULL if GET/FREE).
* output: the current/updated working directory.
*/
char* currentWorkingDirectory(char* action, char* newWorkingDirectory);

/*
* An handler function for the "Change the current working directory" option in the main arrow menu.
* input: none
* output: none
*/
void setWorkingDirectory();
#endif