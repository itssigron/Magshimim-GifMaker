#include "projectManager.h"

void createProject(FrameNode** list, int* exitFlag)
{
	//simply do nothing and exit the menu in order to continue with an empty list
	*exitFlag = TRUE;
}

void loadProject(FrameNode** list, int* exitFlag)
{
	char* projectPath = NULL;
	inputString(&projectPath, "Enter the path of the project (including project name):\n");
	loadProjectFile(list, projectPath);
	free(projectPath);

	*exitFlag = TRUE;
}

void loadProjectFile(FrameNode** list, char* projectPath)
{
	FILE* projectFile = NULL;
	int bufferLength = 0;
	char buffer[MAX_STR_LEN] = { 0 };
	char* path = NULL;
	int duration = 0;
	int imageColor = 0;
	char* name = NULL;
	int i = 0;
	int currentParameterName = 0;
	char currentParameterValue[MAX_STR_LEN] = { 0 };


	projectFile = fopen(projectPath, "r");
	if (projectFile == NULL)
	{
		printf("%sError! - cant open file, creating a new project.%s\n", COLOR_RED, COLOR_RESET);
	}
	else
	{
		fgets(buffer, MAX_STR_LEN, projectFile); //the first line is the project's current working directory.
		buffer[strcspn(buffer, "\n")] = 0; // remove the new line character
		currentWorkingDirectory("SET", buffer);
		
		while (fgets(buffer, MAX_STR_LEN, projectFile) != NULL)
		{
			buffer[strcspn(buffer, "\n")] = 0;
			bufferLength = strlen(buffer);

			for (i = 0; i < bufferLength && currentParameterName <= Name; i++) //we only want to allow |a|b|c|d to be read ("Name" is the last parameter)
			{
				if (buffer[i] == SEPERATOR_CHAR || i == bufferLength - 1)
				{
					if (i == bufferLength - 1) // if we are at the end of the line, then add that token (consider it as the separator)
					{
						currentParameterValue[strlen(currentParameterValue)] = buffer[i];
					}

					if (currentParameterName == Path)
					{
						path = (char*)malloc(sizeof(char) * (strlen(currentParameterValue) + 1));
						strcpy(path, currentParameterValue);
					}
					else if (currentParameterName == Duration)
					{
						duration = atoi(currentParameterValue);
					}
					else if (currentParameterName == ImageColor)
					{
						imageColor = atoi(currentParameterValue);
					}
					else if (currentParameterName == Name)
					{
						name = (char*)malloc(sizeof(char) * (strlen(currentParameterValue) + 1));
						strcpy(name, currentParameterValue);
					}
					currentParameterName++;
					memset(currentParameterValue, 0, strlen(currentParameterValue)); //reset the value for next iteration
				}
				else
				{
					currentParameterValue[strlen(currentParameterValue)] = buffer[i];
				}
			}

			currentParameterName = 0; //reset for next iteration

			if (addFrame(list, name, duration, imageColor, path, FALSE) == FALSE)
			{
				printf("%sThe frame with the name %s was not added either because the name of the frame was already taken or the path is invalid.%s\n", COLOR_RED, name, COLOR_RESET);
				free(name);
			}
			else
			{
				printf("%sFrame %s has been successfully added.%s\n", COLOR_DARK_YELLOW, name, COLOR_RESET);
			}
			free(path); // free the path after we have used it (its being handled by the addFrame function, so we dont need to worry about it)
		}

		printf("%sProject loaded successfully.%s\n", COLOR_GREEN, COLOR_RESET);
		fclose(projectFile);
	}
}

void loadFolder(FrameNode** list, int* exitFlag)
{
	struct dirent* dirEntry = NULL;
	DIR* projectDir = NULL;
	FILE* currentFile = NULL;
	char* folderPath = NULL;

	char* framePath = NULL;
	char* frameName = NULL;
	int succeeded = 0;
	int failed = 0;
	int frameDuration = 0;

	inputString(&folderPath, "Enter folder's path:\n");
	inputInt(&frameDuration, "Enter default frame's duration: ");

	projectDir = opendir(folderPath);
	if (projectDir == NULL)
	{
		printf("%sError! - cant open folder, creating a new project.%s\n", COLOR_RED, COLOR_RESET);
	}
	else
	{
		currentWorkingDirectory("SET", folderPath);
		while ((dirEntry = readdir(projectDir)) != NULL)
		{
			if (!(strcmp(dirEntry->d_name, "..") == STRINGS_EQUAL || strcmp(dirEntry->d_name, ".") == STRINGS_EQUAL || dirEntry->d_type == DT_DIR))
			{
				framePath = joinPaths(folderPath, dirEntry->d_name);
				currentFile = fopen(framePath, "r");

				if (currentFile == NULL)
				{
					printf("%sError! - cant open the file %s | Skipping to the next one.%s\n", COLOR_RED, dirEntry->d_name, COLOR_RESET);
					failed++;
				}
				else
				{
					//values must be in heap, therfore we need to allocate memory for them
					frameName = (char*)malloc(sizeof(char) * (strlen(dirEntry->d_name) + 1));
					strcpy(frameName, dirEntry->d_name);

					addFrame(list, frameName, frameDuration, CV_LOAD_IMAGE_COLOR, dirEntry->d_name, FALSE);
					printf("%sFrame %s has been successfully added.%s\n", COLOR_DARK_YELLOW, frameName, COLOR_RESET);
					succeeded++;
					fclose(currentFile);
				}
				free(framePath);
			}
		}

		printf("%s%d frames succeeded and %d frames failed.%s\n", COLOR_BRIGHT_PURPLE, succeeded, failed, COLOR_RESET);
		closedir(projectDir);
	}

	free(folderPath);
	*exitFlag = TRUE;
}

void saveProject(FrameNode** list, int* exitFlag)
{
	FILE* savedOutput = NULL;
	char* projectPath = NULL;
	char* cwd = NULL;
	FrameNode* cur = *list;

	if (cur == NULL)
	{
		printf(COLOR_RED"This project is empty.\n"COLOR_RESET);
	}
	else
	{
		inputString(&projectPath, "Where to save the project? enter a full path and file name\n");
		savedOutput = fopen(projectPath, "w");
		
		cwd = currentWorkingDirectory("GET", NULL);
		fprintf(savedOutput, "%s\n", cwd ? cwd : ""); // save the project's current working directory
		
		while (cur)
		{
			fprintf(savedOutput, "%s|%d|%d|%s", cur->frame->path, cur->frame->duration, cur->frame->color_scale, cur->frame->name);
			
			cur = cur->next;
			if (cur)
			{
				fprintf(savedOutput, "\n"); //print new line if there's going to be a new frame
			}
		}

		printf("%sProject saved successfully.%s\n", COLOR_GREEN, COLOR_RESET);
		free(projectPath);
		fclose(savedOutput);
	}
}