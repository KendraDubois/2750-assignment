#include "listio.h"

struct dataHeader *buildHeader()
{
	struct dataHeader * header = NULL;
	/*Malloc room for header*/
	header = malloc(sizeof(struct dataHeader));
	/*Intialize starter values*/
	header->name = NULL;
	header->length = 0;
	header->next = NULL;

	return header;
}

void setName(struct dataHeader *header, char *name)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		printf("Null pointer was entered for header in setName function.\n");
		return;
	}
	if (name == NULL)
	{
		printf("Null pointer was entered for name in setName function.\n");
		return;
	}
	/*Malloc room for name, including our /0 character*/
	header->name = malloc((sizeof(char) * strlen(name) + 1));
	strcpy(header->name, name);
}

char * getName(struct dataHeader *header)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		printf("Null pointer was entered for header in getName function.\n");
		return NULL;
	}

	return header->name;
}

int getLength(struct dataHeader *header)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		printf("Null pointer was entered for header in getLength function.\n");
		return 0;
	}

	return header->length;
}

void addString(struct dataHeader *header, char *str)
{
	struct dataString * newDataString = NULL;
	struct dataString * tempDataString = NULL;
	int lengthToAdd = strlen(str) + 1;

	/*Check for NULL pointers*/
	if (header == NULL)
	{
		printf("Null pointer was entered for header in addString function.\n");
		return;
	}
	if (str == NULL)
	{
		printf("Null pointer was entered for str in addString function.\n");
		return;
	}

	newDataString = malloc(sizeof(struct dataString));
	newDataString->string = malloc(sizeof(char) * strlen(str) + 1);
	newDataString->next = NULL;
	/*Add string to string struct*/
	strcpy(newDataString->string, str);

	/*If this is the first data string in the list, set up the header*/
	if (header->next == NULL)
	{
		header->next = newDataString;
		newDataString->next = NULL;
	}
	/*Else this is not the first item in the list so we must traverse to the end to add to end*/
	else
	{
		tempDataString = header->next;
		while (tempDataString->next != NULL)
		{
			tempDataString = tempDataString->next;
		}
		tempDataString->next = newDataString;
	}
	header->length = lengthToAdd + getLength(header);
}

void printString(struct dataHeader *header)
{
	struct dataString * stringList = NULL;

	/*Check for NULL pointers*/
	if (header == NULL)
	{
		printf("Null pointer was entered for header in addString funtion.\n");
		return;
	}

	stringList = header->next;

	/*Print out the list, printing each item until we reach the end of the list*/
	while (stringList != NULL)
	{
		struct dataString * tempNext = stringList->next;
		printf("%s\n", stringList->string);
		stringList = tempNext;
	}
}

void processStrings(struct dataHeader *header)
{
	struct dataString * stringList = NULL;
	stringList = header->next;
	int moveAhead = 0;	/*Number we add to move ahead past our original string to write
	to the correct place in the formatted the string*/
	int addOne = 1;
	char * newString = NULL;
	char * br = "<BR>";
	char * paragraph = "<P>";
	int totalStringLength = 0;
	/*Iterators*/
	int i = 0;
	int j = 0;
	int counter = 0;

	if (header == NULL)
	{
		printf("Null pointer sent to processStrings\n");
		return;
	}

	/*While we are not out of strings to process...*/
	while (stringList != NULL)
	{
		/*Make a new string which will be our formatted string, make it large so it can accomodate a bigger string size*/
		newString = malloc((strlen(stringList->string) * 5) + 1);
		struct dataString * tempNext = stringList->next;

		for (j = i = 0; i <= strlen(stringList->string); i++)
		{

			/*Check if we hit a space, tab, new line or carriage return*/
			switch (stringList->string[i])
			{
			case ' ':
				/*Loop until next char is not a space*/
				while (stringList->string[i + addOne] == ' ')
				{
					addOne++;
					moveAhead++;
				}
				/*Reset addOne for future use*/
				addOne = 1;
				i = i + moveAhead;
				/*We should now be in the appropriate spot in the i string to test the next char*/
				break;

			case '\t':
				/*While next char is a tab*/
				while (stringList->string[i + addOne] == '\t')
				{
					addOne++;
					moveAhead++;
				}
				addOne = 1;
				i = i + moveAhead;
				/*We should now be in the appropriate spot in the string to test the next char*/
				break;

			case '\n':
				/*If next char is not a new line and not a carriage return, replace with <BR>*/
				if (stringList->string[i + addOne] != '\n' && stringList->string[i + addOne] != '\r')
				{
					/*Add "<BR>" to reformatted string*/
					for (counter = 0; counter < 4; counter++)
					{
						newString[j] = br[counter];
						j++;
					}
					/*Add one to i so that we get rid of the new line by overwriting it*/
					i = i + addOne;
				}
				else
				{
					/*While we have 2 or more new lines/carriage returns in a row we remove all new lines*/
					while (stringList->string[i + addOne] == '\n' || stringList->string[i + addOne] == '\r')
					{
						addOne++;
						moveAhead++;
					}
					addOne = 1;
					i = i + moveAhead;

					/*Add "<P>" to reformatted string*/
					for (counter = 0; counter < 3; counter++)
					{
						newString[j] = paragraph[counter];
						j++;
					}
					i = i + 1;
				}
				break;
			/*The cases below are very similar to the above cases, see comments for details*/
			case '\r':
				if (stringList->string[i + addOne] != '\n' && stringList->string[i + addOne] != '\r')
				{
					for (counter = 0; counter < 4; counter++)
					{
						newString[j] = br[counter];
						j++;
					}
					i = i + addOne;
				}
				else
				{
					while (stringList->string[i + addOne] == '\n' || stringList->string[i + addOne] == '\r')
					{
						addOne++;
						moveAhead++;
					}
					addOne = 1;
					i = i + moveAhead;

					for (counter = 0; counter < 3; counter++)
					{
						newString[j] = paragraph[counter];
						j++;
					}
					i = i + 1;

				}
				break;
			}
			/*Copy character to new string*/
			newString[j] = stringList->string[i];

			j++;
			/*Reset moveAhead for next loop*/
			moveAhead = 0;

		}
		newString[j] = '\0';

		/*Get the total length of all hte strings together*/
		for (counter = 0; newString[counter] != '\0'; counter++)
		{
			totalStringLength++;
		}
		/*add 1 for the \0 character*/
		totalStringLength = totalStringLength + 1;

		/*Free current string in dataStruct*/
		free(stringList->string);
		/*Copy new formatted string into the string structure*/
		stringList->string = newString;
		/*Move onto next string*/
		stringList = tempNext;
	}
	header->length = totalStringLength;
}

void freeStructure(struct dataHeader *header)
{
	if (header == NULL)
	{
		printf("Header is equal to null, returning. \n");
		return;
	}
	if (header->next != NULL)
	{
		/*Recursively call freeList to free the dataStrings*/
		freeList(header->next);
		free(header->next);
	}
	if (header->name != NULL)
	{
		free(header->name);
	}
	/*Free the header at the end*/
	if (header != NULL)
	{
		free(header);
	}
}

void freeList(struct dataString * toFree)
{
	if (toFree->next != NULL)
	{
		freeList(toFree->next);
	}
	free(toFree->string);
	free(toFree->next);
}


void writeStrings(char *filename, struct dataHeader * header)
{
	FILE * filePointer = NULL;
	filePointer = fopen(filename, "w");
	struct dataString * stringList = NULL;
	stringList = header->next;
	int nameLength = 0;
	nameLength = (strlen(header->name) + 1);
	int stringLength = 0;

	if (filename == NULL)
	{
		printf("File name is equal to null in writeStrings.");
	}
	if (header == NULL)
	{
		printf("Header is equal to null in writeStrings.");
	}

	/*Write the length of the header's name to the file and then the header's name to the file*/
	fwrite(&nameLength, sizeof(int), 1, filePointer);
	fwrite(header->name, sizeof(char), (strlen(header->name) + 1), filePointer);

	/*Write length of all strings together to file*/
	fwrite(&header->length, sizeof(int), 1, filePointer);

	/*While we are not out of strings...*/
	while (stringList != NULL)
	{
		struct dataString * tempNext = stringList->next;

		/*Write length of the current string to the file*/
		stringLength = (strlen(stringList->string) + 1);
		fwrite(&stringLength, sizeof(int), 1, filePointer);
		/*Write the current string to the file*/
		fwrite(stringList->string, sizeof(char), (strlen(stringList->string) + 1), filePointer);

		stringList = tempNext;
	}
	fclose(filePointer);
}

struct dataHeader *readStrings(char *filename)
{
	struct dataHeader * header = NULL;

	FILE * filePointer = NULL;
	filePointer = fopen(filename, "r");
	int nameLength = 0;
	char * headerName = NULL;
	int totalStringLength = 0;
	int stringLength = 0;
	char * string = NULL;

	if (filename == NULL)
	{
		/*If file is null, we can return a blank header*/
		return header;
	}

	header = buildHeader();

	/*Read the length of the header's name and then header's name to the file*/
	fread(&nameLength, sizeof(int), 1, filePointer);
	/*Malloc the space for the header's name*/
	headerName = malloc(sizeof(char) * (nameLength + 1));

	fread(headerName, sizeof(char), (nameLength), filePointer);

	setName(header, headerName);
	free(headerName);

	fread(&totalStringLength, sizeof(int), 1, filePointer);

	/*While we have not reached the end of the file*/
	while (!feof(filePointer))
	{

		/*Read the string length from the file*/
		fread(&stringLength, sizeof(int), 1, filePointer);

		if (feof(filePointer))
		{
			break;
		}

		/*Malloc room for this new string we are reading in, plus one for the new line*/
		string = malloc(sizeof(char) * (stringLength + 1));

		/*Read the string from the file*/
		fread(string, sizeof(char), stringLength, filePointer);
		/*Add the string we just read to the header*/
		addString(header, string);
		free(string);
	}
	fclose(filePointer);

	return header;
}
