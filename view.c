/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/

#include "view.h"

/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode** list, int* exitFlag)
{
	FrameNode* cur = *list;
	FrameNode* head = *list;
	int imgNum = 1, playCount = 0;
	IplImage* image;
	int userKeyInput = NO_KEY_ENTERED;
	
	if (cur == NULL)
	{
		printf(COLOR_RED"There are no frames to play.\n"COLOR_RESET);
	}
	else
	{	
		cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
		while (userKeyInput == NO_KEY_ENTERED)
		{
			while (cur != NULL && userKeyInput == NO_KEY_ENTERED)
			{
				image = cvLoadImage(cur->frame->path, cur->frame->color_scale);
				if (!image) //The image is empty - shouldn't happen since we checked already.
				{
					printf("%sCould not open or find image number %d%s\n", COLOR_RED, imgNum, COLOR_RESET);
				}
				else
				{
					cvShowImage("Display window", image); //display the image
					userKeyInput = cvWaitKey(cur->frame->duration); //wait
					cur = cur->next;
					cvReleaseImage(&image);
				}
				imgNum++;
			}
			cur = head; // rewind
			playCount++;
		}
		cvDestroyWindow("Display window");
	}
	return;
}

void reversePlay(FrameNode** list, int* exitFlag)
{
	reverseList(list);
	play(list, exitFlag);
	reverseList(list);
}