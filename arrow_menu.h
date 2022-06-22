/*
* Arrow Menu header file.
* This file contains the declarations of the arrow menu functions.
*/

#ifndef ARROW_MENUH
#define ARROW_MENUH

#define ENTER_KEY 0x0D
#define SCROLL_KEY 0xe0
#define UP_KEY 72
#define DOWN_KEY 80

#define COLOR_DARK_GREEN "\033[38;5;30m"
#define COLOR_RESET "\033[0m"

#define FALSE 0
#define TRUE !FALSE

#define ADDITIONAL_PRINTED_LINES 2

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "linkedList.h"
#include "helper.h"

typedef struct MenuOption
{
	char* option;
	functionType handler;
	struct MenuOption* last;
	struct MenuOption* prev;
	struct MenuOption* next;
} MenuOption;


/*
* A function to set the windows terminal into accepting special characters like ANSI colors
* credit: https://superuser.com/a/1529908
* input: none
* output: none
*/
void amEnableVirtualTerminalProcessing();

/*
* A function to add an option into the menu
* input: a pointer to the menu's head, the option which will be displayed to the user and the function of that option
* output: none
*/
void amAddOption(MenuOption** options, char* option, functionType handler);

/*
* A function to remove an option from the menu
* input: a pointer to the menu's head and the option to remove
* output: none
*/
void amRemoveOption(MenuOption** head, char* optionName);

/*
* A function to print a menu.
* input: menu to print, the selected option and whether its the first run or not
* output: none
*/
void amPrintMenu(MenuOption* menu, MenuOption* selected, int firstRun);

/*
* A function to handle the menu,
* It will handle the arrow keys which the user will press,
* and will execute the needed function when the user presses Enter
* input: the menu to handle, the selected option to choose (aka default choice)
* output: none
*/
void amHandleMenu(MenuOption* menu, MenuOption* selected, FrameNode** list);

/*
* A function to get a menu's size (amount of options in it)
* input: the menu to check his size
* output: amount of options in the menu (int)
*/
int amGetMenuSize(MenuOption* menu);

/*
* A function to free a menu,
* input: the menu to free
* output: none
*/
void amFreeMenu(MenuOption* menu);

#endif