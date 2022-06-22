/*
* Arrow Menu header's source file.
* This file contains the the definition of the function's prototypes declared in the header file.
*/

#include <windows.h>
#include "arrow_menu.h"

#pragma warning(disable:4996)

void amEnableVirtualTerminalProcessing()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

void amAddOption(MenuOption** options, char* option, functionType handler)
{
	MenuOption* cur = *options;
	MenuOption* newOption = (MenuOption*)malloc(sizeof(MenuOption));
	newOption->option = (char*)malloc(sizeof(char) * (strlen(option) + 1));
	strcpy(newOption->option, option);
	newOption->prev = NULL;
	newOption->next = NULL;
	newOption->handler = handler;
	if (*options == NULL)
	{
		*options = newOption;
	}
	else
	{
		while (cur->next != NULL)
		{
			cur->last = newOption;
			cur = cur->next;
		}
		cur->last = newOption;
		cur->next = newOption;
		newOption->prev = cur;
	}
}

void amRemoveOption(MenuOption** head, char* optionName)
{
	MenuOption* cur = *head;

	while (cur != NULL && strcmp(cur->option, optionName) != STRINGS_EQUAL)
	{
		cur = cur->next;
	}

	if (cur != NULL)
	{
		if (cur->next)
		{
			cur->next->prev = cur->prev;
		}

		if (cur->prev == NULL) // if the node to remove is the head
		{
			*head = cur->next;
		}
		else
		{
			cur->prev->next = cur->next;
		}
		//free allocated memory
		free(cur->option);
		free(cur);
	}
}

void amPrintMenu(MenuOption* menu, MenuOption* selected, int firstRun)
{
	int i = 0;
	int menuSize = amGetMenuSize(menu);
	
	if (!firstRun)
	{
		//delete the previously printed menu
		printf("\x1b[%dF", menuSize + ADDITIONAL_PRINTED_LINES); // ADDITIONAL_PRINTED_LINES are printed in line #88
		printf("\x1b[2K");
	}

	printf("\nUse arrow keys to navigate:\n");
	for (i = 0; i < menuSize; i++)
	{
		if (menu == selected)
		{
			printf("%s> ", COLOR_DARK_GREEN);
		}
		else
		{
			printf("  ");
		}

		printf("%s%s\n", menu->option, COLOR_RESET);
		menu = menu->next;
	}
}

int amGetMenuSize(MenuOption* menu)
{
	return menu ? 1 + amGetMenuSize(menu->next) : 0;
}

void amFreeMenu(MenuOption* menu)
{
	MenuOption* next = NULL;
	while (menu)
	{
		next = menu->next;
		free(menu->option);		
		free(menu);
		menu = next;
	}
}

void amHandleMenu(MenuOption* menu, MenuOption* selected, FrameNode** list)
{
	int key = 0;
	int exitFlag = FALSE;
	MenuOption* cur = selected;

	while (exitFlag == FALSE)
	{
		key = getch();

		if (key == SCROLL_KEY)
		{
			//we must call the getch function twice since the buffer holds 2 values in it:
			//constant SCROLL_KEY, and the actual key code
			key = getch();


			if (menu->next != NULL) // if theres more than 1 option in the menu.
			{
				cur = key == UP_KEY ? cur && cur->prev ? cur->prev : menu->last : \
					key == DOWN_KEY ? cur && cur->next ? cur->next : menu : cur;

				if (key == UP_KEY || key == DOWN_KEY) {
					amPrintMenu(menu, cur, FALSE);
				}
			}
		}
		else if (key == ENTER_KEY)
		{
			//execute action
			if (cur)
			{
				cur->handler(list, &exitFlag, &cur, &menu);
				if (cur == NULL)
				{
					cur = menu; //cur is null? meaning it was deleted, therfore set the first option into the selected one
				}
			}


			// we will print the menu again with firstRun set to TRUE
			// in order to keep whatever printed during the current action in the console
			if (exitFlag == FALSE)
			{
				amPrintMenu(menu, cur, TRUE);
			}
		}
	}

	amFreeMenu(menu);
}