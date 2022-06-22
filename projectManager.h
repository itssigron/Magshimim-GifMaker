#ifndef PROJECT_MANAGERH
#define PROJECT_MANAGERH

#include "linkedList.h"
#include "dirent.h"

/*
* A function to load a project from a file.
* input: a pointer to the list of frames, exit flag for the arrow menu
* output: none
*/
void loadProject(FrameNode** list, int* exitFlag);

/*
* A function to load a project from a file using function parameter instead of asking an input from the user inside the function.
* input: a pointer to the list of frames, and the path to the file
* output: none
*/
void loadProjectFile(FrameNode** list, char* projectPath);

/*
* A function to load a project from a folder (containing image files).
* input: a pointer to the list of frames, exit flag for the arrow menu
* output: none
*/
void loadFolder(FrameNode** list, int* exitFlag);

/*
* A function to create an empty frame list (well, this function actually does nothing.. since the list is already empty),
* but it was designed in order to allow the arrow menu to simply continue after the user chose to create a project
* input: a pointer to the list of frames, exit flag for the arrow menu
* output: none
*/
void createProject(FrameNode** list, int* exitFlag);

/*
* A function to save a project into a file.
* input: a pointer to the list of frames, exit flag for the arrow menu
* output: none
*/
void saveProject(FrameNode** list, int* exitFlag);
#endif
