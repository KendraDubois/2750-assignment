#include "listio.h"

int main(int argc, char * argv[])
{
	FILE * filePointer = NULL;
	char * fileName = argv[1];
	struct returnStruct * structure;
	structure = buildHeader();
	char buffer[3000];
	int database = 0;
	/*Database is used to see if the user wants to save on the database:
	1 is set to use database, 0 to put on the server*/

	/*Checks user uses appropriate ammount of arguments*/
	if (argc < 2 || argc > 3)
	{
		printf("Invalid arguement count.\n");
		return 1;
	}
	/*If arguement count is 2, do not send to database*/
	if (argc == 2)
	{
		database = 0;
	}
	/*If arguement count is 3 program acts as if .php button was pressed*/
	else if (argc == 3)
	{	;
		/*-c flag represents the convert button from .php program*/
		if (strcmp(argv[2], "-c") == 0)
		{
			database = 0;
		}
		/*-db flag means dbStore buttonw as pressed from .php program*/
		else if (strcmp(argv[2], "-db") == 0)
		{
			database = 1;
		}
	}

	/*Save the information after the . into a string called extension*/
	char *extension = strrchr(argv[1], '.');
	if ((filePointer = fopen(fileName, "r")) == NULL)
	{
		/*If the file doesn't open we must return or else the program will segfault*/
		freeStructure(structure->header);
		free(structure);
		return 1;
	}
	/*If our extension is nonexistent, set extension to empty*/
	if (extension == NULL)
	{
		extension = "";
	}
	/*If our file is a .html file, print it out*/
	if (strcmp(extension, ".html") == 0)
	{
		printFile(filePointer);
	}
	else
	{
		setName(structure->header, fileName);
		/*Add strings to the structure*/
		while (fgets(buffer, 3000, (FILE*)filePointer) != NULL)
		{
			addString(structure->header, buffer);
		}
		/*processStrings adds all of our tags and calls a function that makes an HTML file*/
		processStrings(structure->header, database);

	}

	fclose(filePointer);
	freeStructure(structure->header);
	free(structure);

	return 0;
}
