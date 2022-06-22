/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration	 	 *
**********************************/


#ifndef VIEWH
#define VIEWH

#pragma warning(disable:4996)

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include <stdio.h>
#include "LinkedList.h"

#define GIF_REPEAT 5 //no longer needed
#define NO_KEY_ENTERED -1 //opencv value 

/*
* A function to play a "moive" using a linked list of frames,
* the movie is played GIF_REPEAT times.
* input: the list's head and exit flag for the arrow menu
* output: none
*/
void play(FrameNode **list, int* exitFlag);

/*
* A function to play the movie in reverse
* input: a pointer to the linked list of frames to display
* output: none
*/
void reversePlay(FrameNode** list, int* exitFlag);
#endif