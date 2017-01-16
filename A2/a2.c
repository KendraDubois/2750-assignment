#include "listio.h"

int main(int argc, char * argv[])
{
	FILE * filePointer = NULL;
	char * fileName = argv[1];
	struct returnStruct * structure;
	structure = buildHeader();
	char buffer[3000];

	/*Checks that user enters more than one command line arg*/
	argValidate(argc, argv);
    
    /*Save the information after the . into a string called extension*/
	char *extension = strrchr(argv[1], '.');

	if ((filePointer = fopen(fileName, "r")) == NULL)
	{
		/*If the file doesn't open we must return or else the program will segfault*/
		return 1;
	}
	/*If we have no extension*/
	if (extension == NULL)
	{
		extension = "";
	}
	/*If our file is a .html file, print it out*/
	if (strcmp(extension, ".html") == 0)
	{
		printFile(filePointer);
	}
	/*If our file has no extension, make an HTML file*/
	else if (strcmp(extension, "") == 0)
	{
		char newHTMLFile[25];
		strcpy(newHTMLFile, fileName);
		strcat(newHTMLFile, ".html");

		int character;
		setName(structure->header, fileName);
		/*Add strings to the structure, reading two lines at a time*/
		while (fgets(buffer, 3000, (FILE*)filePointer) != NULL)
		{
			addString(structure->header, buffer);
		}
		/*processStrings adds all of our tags and calls a function that makes an HTML file*/
		processStrings(structure->header);

	}

	fclose(filePointer);
	freeStructure(structure->header);
	free(structure);

	return 0;
}
