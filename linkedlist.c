/*
* Linked list header's source file.
* This file contains the the definition of the function's prototypes declared in the header file.
*/

#include "dirent.h"
#include "linkedlist.h"
#include "arrow_menu.h"

FrameNode* findFrame(FrameNode* head, char* name)
{
	FrameNode* result = NULL;

	while (head != NULL && strcmp(head->frame->name, name) != STRINGS_EQUAL) // while the head is not NULL and the frame is yet to be found
	{
		head = head->next; // move to the next node
	}

	return head;
}

void insertFrame(FrameNode** head, FrameNode* newFrame, int index)
{
	FrameNode* cur = *head;
	FrameNode* prev = NULL;
	int i = 0;

	if (index == FIRST_NODE)
	{
		newFrame->next = cur;
		*head = newFrame;
	}
	else
	{
		while (i < index && cur != NULL)
		{
			prev = cur;
			cur = cur->next;
			i++;
		}

		if (prev == NULL)
		{
			*head = newFrame;
		}
		else
		{
			newFrame->next = prev->next;
			prev->next = newFrame;
		}
	}
}

void addFrameInput(FrameNode** list, int* exitFlag)
{
	char* frameName = NULL;
	char* framePath = NULL;
	int frameDuration = 0;
	int firstIteration = TRUE;

	printf("*** Creating new frame ***\n");
	inputString(&framePath, "Please insert frame path:\n");
	inputInt(&frameDuration, "Please insert frame duration(in miliseconds):\n");

	do
	{
		if (firstIteration == FALSE)
		{
			printf(COLOR_RED"Frame name cannot contain the character '"SEPERATOR_STRING"'\n"COLOR_RESET);
		}
		inputString(&frameName, "Please choose a name for this frame:\n");
		firstIteration = FALSE;
	} while (strstr(frameName, SEPERATOR_STRING) != NULL);

	if (addFrame(list, frameName, frameDuration, CV_LOAD_IMAGE_COLOR, framePath, TRUE) == FALSE)
	{
		printf("%sFrame will not be added because the provided path is invalid.%s\n", COLOR_RED, COLOR_RESET);
		free(frameName);
	}
	else
	{
		printf("%sFrame was successfully added.%s\n", COLOR_GREEN, COLOR_RESET);
	}
	free(framePath); // the frame's path is being cloned in the addFrame function, so we dont need to worry about it being freed here
}

FrameNode* frameExists(FrameNode* list, char* name)
{
	FrameNode* cur = list;
	FrameNode* lastNode = NULL;
	int found = FALSE;

	while (cur && found == FALSE)
	{
		//check if a frame with this name already exists
		if (strcmp(cur->frame->name, name) == STRINGS_EQUAL)
		{
			found = TRUE;
		}


		//if the frame doesnt exists, the loop will run until "cur" is NULL,
		//therfore we must save the last node into a variable
		if (cur->next == NULL)
		{
			lastNode = cur;
		}

		cur = cur->next;
	}

	return found == FALSE ? lastNode : NULL;
}

int addFrame(FrameNode** head, char* name, int duration, int imageColor, char* path, int cameFromInput)
{
	FrameNode* lastNode = NULL;
	FrameNode* newNode = NULL;
	int sepError = FALSE;
	char* fullFramePath = joinPaths(currentWorkingDirectory("GET", NULL), path);

	int result = checkIfFileExists(fullFramePath);

	if (result == TRUE)
	{
		if (cameFromInput == TRUE)
		{
			while (*head != NULL && ((sepError = MAKE_BOOL(strstr(name, SEPERATOR_STRING))) == TRUE || (lastNode = frameExists(*head, name)) == NULL))
			{
				free(name);
				inputString(&name, COLOR_RED"%s, please choose another name:\n"COLOR_RESET, sepError == TRUE ? "Frame name cannot contain the character '"SEPERATOR_STRING"'" : "This name is already taken");
				sepError = FALSE; // reset the error flag
			}
		}
		else
		{
			lastNode = frameExists(*head, name);
		}

		if (lastNode != NULL || (lastNode == NULL && *head == NULL))
		{

			//allocate the needed memory and insert the node at the end
			newNode = (FrameNode*)malloc(sizeof(FrameNode));
			Frame* frame = (Frame*)malloc(sizeof(Frame));
			frame->name = name;
			frame->duration = duration;
			frame->color_scale = imageColor;
			frame->path = fullFramePath;

			newNode->frame = frame;
			newNode->next = NULL;

			if (lastNode == NULL)
			{
				*head = newNode;
			}
			else
			{
				lastNode->next = newNode;
			}

			result = TRUE;
		}
		else
		{
			result = FALSE;
		}
	}
	else
	{
		free(fullFramePath);
	}

	return result;
}

void frameSelectMenu(FrameNode** head, functionType handler, char* title, char* emptyMenuMsg, char* exitOptionName)
{
	MenuOption* framesMenu = NULL;
	FrameNode* cur = *head;
	
	while (cur)
	{
		amAddOption(&framesMenu, cur->frame->name, handler);
		cur = cur->next;
	}

	if (framesMenu == NULL) // if the list is empty
	{
		printf(COLOR_RED"%s\n"COLOR_RESET, emptyMenuMsg);
	}
	else
	{
		amAddOption(&framesMenu, exitOptionName, handler);

		printf(COLOR_BOLD COLOR_CYAN"\n%s\n"COLOR_RESET, title);
		amPrintMenu(framesMenu, framesMenu, TRUE);

		amHandleMenu(framesMenu, framesMenu, head);
	}
}

void removeFrame(FrameNode** head, int* exitFlag, void** selected, void** menu)
{
	FrameNode* cur = *head;
	FrameNode* prev = NULL;
	char* frameName = (*(MenuOption**)selected)->option;
	
	if (strcmp(frameName, EXIT_MENU) != STRINGS_EQUAL)
	{
		
		while (cur != NULL && strcmp(cur->frame->name, frameName) != STRINGS_EQUAL)
		{
			prev = cur;
			cur = cur->next;
		}

		//no need to check if the frame exists, because it was checked in the menu
		
		if (prev == NULL) // if the node to remove is the head
		{
			*head = cur->next;
		}
		else
		{
			prev->next = cur->next;
		}

		//free allocated memory
		free(cur->frame->name);
		free(cur->frame->path);
		free(cur->frame);
		free(cur);

		printf("%sFrame was successfully removed.%s\n", COLOR_GREEN, COLOR_RESET);
		amRemoveOption(menu, frameName);
		*selected = NULL;
	}
	else
	{
		*exitFlag = TRUE;
	}
}
void removeFrameHandler(FrameNode** head, int* exitFlag)
{
	frameSelectMenu(head, removeFrame, "Please choose a frame to remove.", "There are no frames to remove.", EXIT_MENU);
}

void modifyIndex(FrameNode** head, int* exitFlag, void** selected)
{
	FrameNode* cur = *head;
	FrameNode* foundNodePrev = NULL;
	FrameNode* foundNode = NULL;
	int foundNodeIndex = 0;
	FrameNode* newIndexNode = NULL;
	FrameNode* newIndexNodePrev = NULL;
	int i = 0;
	int newIndex = 0;
	int result = FALSE;
	char* frameName = (*(MenuOption**)selected)->option;
	
	if (strcmp(frameName, MODIFY_INDEX_EXIT) != STRINGS_EQUAL)
	{
		inputInt(&newIndex, "Enter new index for %s:\n", frameName);

		newIndex -= 1; // the index starts at 0, but the user wants it to count from 1

		//go through the list until both the found node and the new index node are found
		while (cur != NULL && (foundNode == NULL || newIndexNode == NULL))
		{
			//this block will be in "if-else" and not 2 different "if" because if the indexes are the same
			//only the first block will be executed, and then the other will be NULL, therfore the function will return FALSE as it should

			if (strcmp(cur->frame->name, frameName) == STRINGS_EQUAL) // if the current node's name is the same as the searched one
			{
				foundNodeIndex = i;
				foundNode = cur;
			}
			else if (i == newIndex) // if the current node's index is the same as the new index
			{
				newIndexNode = cur;
			}

			//modify the previous nodes only if the nodes arent found yet
			if (foundNode == NULL)
			{
				foundNodePrev = cur;
			}

			if (newIndexNode == NULL)
			{
				newIndexNodePrev = cur;
			}

			//go to the next node
			cur = cur->next;
			i++;
		}

		if (newIndexNode) // only if the new index node was found (no need to check if the "foundNode" was found, because it was already checked in the menu)
		{
			if (foundNodePrev == NULL) // if the found node is the head
			{
				*head = (*head)->next;
				foundNode->next = newIndexNode->next;
				newIndexNode->next = foundNode;
			}
			else if (newIndexNodePrev == NULL) // if the new index node is the head
			{
				foundNodePrev->next = foundNode->next;
				foundNode->next = newIndexNode;
				*head = foundNode;
			}
			else
			{
				foundNodePrev->next = foundNode->next; // remove the found node from the list

				if (newIndex < foundNodeIndex) // if the new index is before the found node (meaning we need to move the node to the left)
				{
					foundNode->next = newIndexNode;
					newIndexNodePrev->next = foundNode;
				}
				else // if the new index is after the found node (meaning we need to move the node to the right)
				{
					foundNode->next = newIndexNode->next;
					newIndexNode->next = foundNode;
				}
			}

			result = TRUE;
		}

		if (result == FALSE)
		{
			printf("%sAn error occurred, it could be one of the following:\n", COLOR_RED);
			printf("\t - The new index is out of the valid range.\n");
			printf("\t - The frame is already in this index.%s\n", COLOR_RESET);
		}
		else
		{
			printf("%sFrame's index has been successfully modified.%s\n", COLOR_GREEN, COLOR_RESET);
		}
	}
	
	*exitFlag = TRUE;
}
void modifyIndexHandler(FrameNode** head, int* exitFlag)
{
	frameSelectMenu(head, modifyIndex, "Please choose a frame to modify its index.", "There are no frames to modify.", MODIFY_INDEX_EXIT);
}

void modifyDuration(FrameNode** head, int* exitFlag, void** selected)
{
	FrameNode* toModify = NULL;;
	int newDuration = 0;

	if (strcmp((*(MenuOption**)selected)->option, EXIT_MENU) != STRINGS_EQUAL)
	{
		inputInt(&newDuration, "Enter new duration for %s:\n", (*(MenuOption**)selected)->option);

		toModify = findFrame(*head, (*(MenuOption**)selected)->option);

		//no need to check if the frame exists, because it was checked in the menu
		toModify->frame->duration = newDuration;
		printf("%sFrame's duration has been successfully modified.%s\n", COLOR_GREEN, COLOR_RESET);
	}
	else
	{
		*exitFlag = TRUE;
	}
}
void modifyDurationHandler(FrameNode** head, int* exitFlag)
{
	frameSelectMenu(head, modifyDuration, "Please choose a frame to modify its duration.", "There are no frames to modify.", EXIT_MENU);
}

void modifyAllDuration(FrameNode** head, int* exitFlag)
{
	int newDuration = 0;
	FrameNode* cur = *head;

	if (cur == NULL)
	{
		printf(COLOR_RED"There are no frames to modify.\n"COLOR_RESET);
	}
	else
	{		
		inputInt(&newDuration, "Enter new duration:\n");

		while (cur != NULL)
		{
			cur->frame->duration = newDuration;
			cur = cur->next;
		}

		printf(COLOR_GREEN"All frames's durations were successfully modified.\n"COLOR_RESET);
	}
}

void printList(FrameNode** head, int* exitFlag)
{
	FrameNode* cur = *head;
	char hasFilter[][4] = { "No", "Yes" };

	if (cur == NULL)
	{
		printf(COLOR_RED"There are no frames to display.\n"COLOR_RESET);
	}
	else
	{
		printf("\t\tName\t\tDuration\tGray Scale\tPath\n");
		while (cur)
		{
			printf("\t\t%s\t\t%d ms\t\t%s\t\t%s\n",
				cur->frame->name, cur->frame->duration, hasFilter[cur->frame->color_scale == CV_LOAD_IMAGE_GRAYSCALE], cur->frame->path);
			cur = cur->next;
		}
	}
}

void freeList(FrameNode* head)
{
	FrameNode* cur = head;
	FrameNode* next = NULL;

	while (cur)
	{
		next = cur->next;
		free(cur->frame->name);
		free(cur->frame->path);
		free(cur->frame);
		free(cur);
		cur = next;
	}
}

void reverseList(FrameNode** head)
{
	FrameNode* cur = *head;
	FrameNode* reversedList = NULL;
	FrameNode* temp = NULL;

	while (cur != NULL)
	{
		temp = cur->next;
		cur->next = reversedList;
		reversedList = cur;
		cur = temp;
	}

	*head = reversedList;
}