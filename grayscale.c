/*
* Gray-scale header's source file.
* This file contains the the definition of the function's prototypes declared in the header file.
*/

#include "grayscale.h"

void grayScaleFrameHandler(FrameNode** list, int toAdd)
{
	char* title = toAdd ? "Please choose a frame to add grayscale to" : "Please choose a frame to remove grayscale from";
	functionType handler = toAdd ? grayScaleFrameAdd : grayScaleFrameRemove;

	frameSelectMenu(list, handler, title, "There are no frames to modify.", EXIT_MENU);
}

void grayScaleFrame(FrameNode* list, char* frameName, int toAdd, int* exitFlag)
{
	FrameNode* toModify = NULL;
	
	if (strcmp(frameName, EXIT_MENU) != STRINGS_EQUAL)
	{
		toModify = findFrame(list, frameName);
		toModify->frame->color_scale = toAdd ? CV_LOAD_IMAGE_GRAYSCALE : CV_LOAD_IMAGE_COLOR;
		printf("%sFrame's color scale has been successfully modified.%s\n", COLOR_GREEN, COLOR_RESET);
	}
	else
	{
		*exitFlag = TRUE;
	}
}

void grayScaleFrameAdd(FrameNode** list, int* exitFlag, void** selected)
{
	grayScaleFrame(*list, (*(MenuOption**)selected)->option, TRUE, exitFlag);
}

void grayScaleFrameRemove(FrameNode** list, int* exitFlag, void** selected)
{
	grayScaleFrame(*list, (*(MenuOption**)selected)->option, FALSE, exitFlag);
}

void grayScaleList(FrameNode* list, int toAdd)
{
	int val = toAdd ? CV_LOAD_IMAGE_GRAYSCALE : CV_LOAD_IMAGE_COLOR;
	
	while (list)
	{
		list->frame->color_scale = val;
		list = list->next;
	}

	printf("%sSuccessfully %s%s\n", COLOR_GREEN, toAdd ? "added gray-scale to all frames." : "removed gray-scale from all frames.", COLOR_RESET);
}

void grayScaleExit(FrameNode** list, int* exitFlag)
{
	*exitFlag = TRUE;
}

void grayScaleFilterHandler(FrameNode** list, int* exitFlag, void** selected)
{
	char* option = (*(MenuOption**)selected)->option;
	
	if(strstr(option, "specific"))
	{
		grayScaleFrameHandler(list, MAKE_BOOL(strstr(option, "Apply")));
	}
	else if(strstr(option, "all"))
	{
		grayScaleList(*list, MAKE_BOOL(strstr(option, "Apply")));
	}
}

void grayScaleFilter(FrameNode** list, int* exitFlag)
{
	MenuOption* menu = NULL;

	if (*list == NULL)
	{
		printf(COLOR_RED"There are no frames to modify.\n"COLOR_RESET);
	}
	else
	{
		amAddOption(&menu, "Apply filter to a specific frame.", grayScaleFilterHandler);
		amAddOption(&menu, "Remove filter from a specific frame.", grayScaleFilterHandler);
		amAddOption(&menu, "Apply filter to all frames.", grayScaleFilterHandler);
		amAddOption(&menu, "Remove filter from all frames.", grayScaleFilterHandler);
		amAddOption(&menu, "Exit gray scale filter menu.", grayScaleExit);

		amPrintMenu(menu, menu, TRUE);

		amHandleMenu(menu, menu, list);
	}
}