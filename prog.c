/*********************************
* Class: MAGSHIMIM C2			 *
* Final Project  - Harel Sigron  *
**********************************/


#pragma warning(disable:4996)

#include <Windows.h>
#include <stdlib.h>
#include "arrow_menu.h"
#include "linkedList.h"
#include "grayscale.h"
#include "helper.h"
#include "projectManager.h"
#include "view.h"

#define ARGS_AMOUNT 2

enum initialOptions { CreateProject, LoadProject };
enum options { Exit, AddFrame, RemoveFrame, ChangeFrameIndex, ChangeFrameDuration, ChangeAllDurations, ListFrames, MakeFrameGrayScale, MakeEntireMovieGrayScale, PlayMovie, ReversePlayMovie, SaveProject };

void exitProgram(FrameNode** list, int* exitFlag);

/*
* A program to handle a linked list of frames.
* The user can add, remove, change the index of a frame, and change the duration of a specific/all frames.
* The user can also list the frames in the list, and play the movie (both regular and reverse)
* + He also have the option to apply the gray scale filter to the entire movie, or just a specific frame.
* This program has a project management system, you can save projects, and load them later either using the menu or by providing the path as an argument to the program.
* input: none
* output: 0 on success
*/
int main(int argc, char** argv)
{
	MenuOption* initialMenu = NULL; //initial menu used for creating or opening a project.
	MenuOption* actionsMenu = NULL; //menu used in order to allow the user to execute actions on the project's frames
	FrameNode* list = NULL;
	int choice = NULL;
	
	amEnableVirtualTerminalProcessing(); //required to enable the use of the VT100 escape sequences in windows cmd.
	
	
	if(argc == ARGS_AMOUNT) //allow the user to load a project directly as an argument to the program.
	{
		loadProjectFile(&list, argv[1]);
	}
	else
	{		
		//--------------------------------- Initial Menu ----------------------------//
		printf("%s%sWelcome to Magshimim Movie Maker! what would you like to do?%s\n", COLOR_BOLD, COLOR_GREEN, COLOR_RESET);
		amAddOption(&initialMenu, "Create a new project", createProject);
		amAddOption(&initialMenu, "Load existing project from file", loadProject);
		amAddOption(&initialMenu, "Load project from folder filled with images", loadFolder);

		amPrintMenu(initialMenu, initialMenu, TRUE);
	
		amHandleMenu(initialMenu, initialMenu, &list);
		//---------------------------------------------------------------------------//
	}
	

	//--------------------------------- Actions Menu -----------------------------//
	amAddOption(&actionsMenu, "Exit", exitProgram);
	amAddOption(&actionsMenu, "Add new Frame", addFrameInput);
	amAddOption(&actionsMenu, "Remove a Frame", removeFrameHandler);
	amAddOption(&actionsMenu, "Change frame index", modifyIndexHandler);
	amAddOption(&actionsMenu, "Change frame duration", modifyDurationHandler);
	amAddOption(&actionsMenu, "Change duration of all frames", modifyAllDuration);
	amAddOption(&actionsMenu, "List frames", printList);
	amAddOption(&actionsMenu, "Gray scale filter", grayScaleFilter);
	amAddOption(&actionsMenu, "Play movie (press any key to stop)", play);
	amAddOption(&actionsMenu, "Play movie in reverse (press any key to stop)", reversePlay);
	amAddOption(&actionsMenu, "Change the current working directory", setWorkingDirectory);
	amAddOption(&actionsMenu, "Save project", saveProject);
	
	amPrintMenu(actionsMenu, actionsMenu, TRUE);
	
	amHandleMenu(actionsMenu, actionsMenu, &list);
	//----------------------------------------------------------------------------//
	
	system("pause"); // pause the program until the user presses a key.
	return 0;
}

/*
* An handler function to handle the exit option.
* input: a pointer to the list's head and exit flag for the arrow menu.
* output: none
*/
void exitProgram(FrameNode** list, int* exitFlag)
{
	freeList(*list);
	currentWorkingDirectory("FREE", NULL);
	printf("Bye!\n");
	*exitFlag = TRUE;
}