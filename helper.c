/*
* Helper header's source file.
* This file contains the the definition of the function's prototypes declared in the header file.
*/

#include "helper.h"
#include "linkedList.h"

int inputInt(int* userInput, const char* format, ...)
{
	if (format)
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
	scanf("%d", userInput);
	getchar(); //clean buffer after getting an input
	
	return *userInput;
}

char* myFgets(FILE* stream)
{
	char tmpStr[MAX_STR_LEN] = { 0 };
	char* str = NULL;
	fgets(tmpStr, MAX_STR_LEN, stream);
	tmpStr[strcspn(tmpStr, "\n")] = 0;
	str = (char*)malloc(sizeof(char) * strlen(tmpStr) + 1); // + 1 for null terminator
	strcpy(str, tmpStr);
	return str;
}

char* inputString(char** userInput, const char* format, ...)
{
	if (format)
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
	*userInput = myFgets(stdin);

	return *userInput;
}

int checkIfFileExists(char* path)
{
	FILE* file = fopen(path, "r");
	int result = FALSE;

	if (file)
	{
		result = TRUE;
		fclose(file);
	}

	return result;
}

char* joinPaths(char* folder, char* path)
{
	char* fullPath = NULL;
	int slashChar = 0;
	
	if (folder == NULL)
	{
		folder = "";
	}

	if (strlen(folder) > 0 && folder[strlen(folder) - 1] != '/') // -1 since its zero-based index
	{
		//the folder's name doesnt ends with the slash, therefore allocate memory for that aswell 
		slashChar = 1;
	}

	fullPath = (char*)malloc(sizeof(char) * (strlen(folder) + strlen(path) + NULL_CHAR_LEN + slashChar));
	strcpy(fullPath, folder);

	if (slashChar)
	{
		strncat(fullPath, "/", 1);
	}
	strncat(fullPath, path, strlen(path));

	return fullPath;
}

void selectionSort(char** arr, int n)
{
	int i = 0, j = 0, min_idx = 0;
	char* tmp = NULL;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(arr[j], arr[min_idx]) < 0)
			{
				min_idx = j;
			}
		}
		//swap the minimum with the current index
		tmp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = tmp;
	}
}

char* currentWorkingDirectory(char* action, char* newWorkingDirectory)
{
	static char* workingDirectory = NULL;
	char* newPath = NULL;

	if (strcmp(action, "SET") == STRINGS_EQUAL)
	{
		free(workingDirectory); // free the old working directory
		workingDirectory = (char*)malloc(sizeof(char) * (strlen(newWorkingDirectory) + 1));
		strcpy(workingDirectory, newWorkingDirectory);
	}
	else if(strcmp(action, "FREE") == STRINGS_EQUAL)
	{
		free(workingDirectory);
		workingDirectory = NULL;
	}
	
	return workingDirectory;
}

void setWorkingDirectory()
{
	char* newWorkingDirectory = NULL;

	inputString(&newWorkingDirectory, "Enter the new working directory:\n");
	currentWorkingDirectory("SET", newWorkingDirectory);
	free(newWorkingDirectory);

	printf(COLOR_GREEN "Successfully changed the current working directory.\n"COLOR_RESET);
}