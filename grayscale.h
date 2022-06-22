/*
* Gray-scale filter header file.
* This file contains the declarations of the gray-scale filter functions.
*/

#ifndef GRAYSCALEH
#define GRAYSCALEH

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "arrow_menu.h"


/*
* A function to get the selected option of the menu which "grayScaleFilter" created and execute the corresponding function
* input: pointer to the frame list's head, exit flag for the arrow menu and a pointer to the selected option
* output: none
*/
void grayScaleFilterHandler(FrameNode** list, int* exitFlag, void** selected);

/*
* A manager function for the gray scale filter.
* this function will create an arrow menu and then call the gray scale filter functions accordingly.
* input: a pointer to the frame list's head, exit flag for the arrow menu.
* output: none
*/
void grayScaleFilter(FrameNode** list, int* exitFlag);

/*
* A function to handle the gray scale filter for adding/removing this filter from a specific frame
* This function will create another menu with frames and allow the user to choose a frame to modify its color scale.
* input: the list's head, and whether to open a menu for adding the filter or for removing the filter.
* output: none
*/
void grayScaleFrameHandler(FrameNode** list, int toAdd);

/*
* A manager function for the gray scale filter to a specific frame.
* this function will add/remove the filter from a specific frame.
* input: the frame list's head, the frame's name, whether the filter should be added or removed from the frame and exit flag for the arrow menu.
* output: none
*/
void grayScaleFrame(FrameNode* list, char* frameName, int toAdd, int* exitFlag);

/*
* A function to add the gray scale filter to a specific frame.
* input: a pointer to the frame list's head, exit flag for the arrow menu, and a pointer to the selected option (which contains frame's name).
* output: none
*/
void grayScaleFrameAdd(FrameNode** list, int* exitFlag, void** selected);

/*
* A function to remove the gray scale filter from a specific frame.
* input: a pointer to the frame list's head, exit flag for the arrow menu, and a pointer to the selected option (which contains frame's name).
* output: none
*/
void grayScaleFrameRemove(FrameNode** list, int* exitFlag, void** selected);

/*
* A manager function for the gray scale filter for all of the frames.
* this function will add/remove the filter from all frames in the list.
* input: the frame list's head, and whether the filter should be added or removed from the input frame.
* output: none
*/
void grayScaleList(FrameNode* list, int toAdd);

/*
* A function used to exit the gray scale filter's arrow menu.
* input: a pointer to the frame list's head, exit flag for the arrow menu.
* output: none
*/
void grayScaleExit(FrameNode** list, int* exitFlag);

#endif