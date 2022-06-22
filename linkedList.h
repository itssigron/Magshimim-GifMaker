/*
* Linked list header file.
* This file contains the declarations of the linked list functions.
*/

#ifndef LINKEDLISTH
#define LINKEDLISTH

#pragma warning(disable:4996)

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE !FALSE

// constants for nodes locations, they are constants instead of "define",
// because we will need their memory address (read-only of course) for later use
#define LAST_NODE -1
#define FIRST_NODE 0

#define SPECIFIC_FRAME 0

#define EXIT_MENU "Done"
#define MODIFY_INDEX_EXIT "Exit without modifying index"

enum params{Path, Duration, ImageColor, Name};

// Frame struct
typedef struct Frame
{
	char*		 name;
	unsigned int duration;
	int          color_scale;
	char*	 	 path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

/*
* A function to find a frame by its name,
* input: the list's head and the name to search for
* output: the found node (or NULL if not found)
*/
FrameNode* findFrame(FrameNode* head, char* name);

/*
* A function to insert a frame's node in a given index.
* input: the head's pointer, the frame node and the index to put this frame in
* output: none
*/
void insertFrame(FrameNode** head, FrameNode* newFrame, int index);

/*
* A function for requesting input values for a frame in order to add one.
* input: a pointer to the list's head, exit flag for the arrow menu
* output: none
*/
void addFrameInput(FrameNode** list, int* exitFlag);

/*
* A function to create a new frame node by user's arguments and insert it to the end of the list.
* input: the list's head, the frame's name, duration, image color, path and whether "addFrameInput" called it or not
* output: TRUE if the frame was added (if the frame's name didnt existed before and path is correct) and FALSE otherwise
*/
int addFrame(FrameNode** head, char* name, int duration, int imageColor, char* path, int cameFromInput);


/*
* A function to remove a frame from the list,
* input: the list's head, exit flag for the arrow menu, a pointer to the selected option and a pointer to the used menu
* output: none
*/
void removeFrame(FrameNode** head, int* exitFlag, void** selected, void** menu);

/*
* A function to handle the remove frame option inside the main arrow menu.
* This function will create another menu with frames and allow the user to choose a frame to remove.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void removeFrameHandler(FrameNode** head, int* exitFlag);

/*
* A function to modify a frame's index
* input: the list's head, exit flag for the arrow menu, and a pointer to the selected option.
* output: none
*/
void modifyIndex(FrameNode** head, int* exitFlag, void** selected);

/*
* A function to handle the modify index option inside the main arrow menu.
* This function will create another menu with frames and allow the user to choose a frame to modify its index.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void modifyIndexHandler(FrameNode** head, int* exitFlag);

/*
* A function to change the duration of a specific frame.
* input: the list's head, exit flag for the arrow menu, and a pointer to the selected option.
* output: none
*/
void modifyDuration(FrameNode** head, int* exitFlag, void** selected);

/*
* A function to handle the modify duration option inside the main arrow menu.
* This function will create another menu with frames and allow the user to choose a frame to modify its duration.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void modifyDurationHandler(FrameNode** head, int* exitFlag);

/*
* A function to change the duration to every frame in a linked list.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void modifyAllDuration(FrameNode** head, int* exitFlag);

/*
* A function to print a linked list of frames.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void printList(FrameNode** head, int* exitFlag);

/*
* A function to free a linked list's memory.
* input: the list's head
* output: none
*/
void freeList(FrameNode* head);

/*
* A function to reverse a linked list.
* input: a pointer to the list's head.
* output: none
*/
void reverseList(FrameNode** head);

/*
* A function to check if a frame exists in a linked list.
* this function is used to check if the frame exists and then insert a new node after the last if it doesnt
* input: the list's head and the frame's name
* output: if the frame does not exists, it will return the last node of the list, NULL otherwise.
*/
FrameNode* frameExists(FrameNode* list, char* name);

/*
* A function to create a menu using the arrow menu library, the menu's options will be the frame's names.
* This function will display the menu and handle the selected option using the callback (handler parameter)
* input: the list's head, a function to call when the user selects an option, the title for the menu, a message to display when there are no frames in the list, and the name of the exit option
* output: none
*/
void frameSelectMenu(FrameNode** head, functionType handler, char* title, char* emptyMenuMsg, char* exitOptionName);
#endif