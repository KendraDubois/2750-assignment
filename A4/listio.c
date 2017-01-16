#include "listio.h"
#define SUCCESS 1
#define FAILURE 0
#define MAX_QUERY 512
#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "kdubois"
#define PASSWORD  "0890708"
#define DATABASE  "kdubois"

struct returnStruct *buildHeader()
{
	/*Malloc room for header and return struct*/
	struct returnStruct * returnStruct;

	returnStruct = malloc(sizeof(struct returnStruct));

	/*If malloc failed because it returned NULL, return*/
	if (returnStruct == NULL)
	{
		return returnStruct;
	}

	returnStruct->header = malloc(sizeof(struct dataHeader));

	if (returnStruct->header == NULL)
	{
		returnStruct->value = FAILURE;
		return returnStruct;
	}
	returnStruct->value = SUCCESS;
	/*Intialize starter values*/
	returnStruct->header->name = NULL;
	returnStruct->header->length = 0;
	returnStruct->header->next = NULL;

	return returnStruct;
}

int setName(struct dataHeader *header, char *name)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		return FAILURE;
	}
	if (name == NULL)
	{
		return FAILURE;
	}
	/*Malloc room for name, including our /0 character*/
	header->name = malloc((sizeof(char) * strlen(name) + 1));
	/*Check malloc succeeded*/
	if (header->name == NULL)
	{
		return FAILURE;
	}

	strcpy(header->name, name);
	return SUCCESS;
}

char * getName(struct dataHeader *header)
{
	/*Check for NULL pointer*/
	if (header == NULL)
	{
		return NULL;
	}
	if (header->name == NULL)
	{
		return NULL;
	}
	/*Check if string is empty*/
	if (strcmp(header->name, "") == 0)
	{
		return NULL;
	}
	return header->name;
}

int getLength(struct dataHeader *header)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		return FAILURE;
	}
	return header->length;
}

int addString(struct dataHeader *header, char *str)
{
	struct dataString * newDataString = NULL;
	struct dataString * tempDataString = NULL;

	/*Check for NULL pointers*/
	if (header == NULL)
	{
		return FAILURE;
	}
	if (str == NULL)
	{
		return FAILURE;
	}

	int lengthToAdd = strlen(str) + 1;

	newDataString = malloc(sizeof(struct dataString));
	/*Check if malloc fails*/
	if (newDataString == NULL)
	{
		return FAILURE;
	}
	newDataString->string = malloc(sizeof(char) * strlen(str) + 1);
	/*Check if malloc fails*/
	if (newDataString->string == NULL)
	{
		/*Free the above struct because we failed to malloc memory and will be returning*/
		free(newDataString);
		return FAILURE;
	}
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
	return SUCCESS;
}

int printString(struct dataHeader *header)
{
	struct dataString * stringList = NULL;

	/*Check for NULL pointers*/
	if (header == NULL)
	{
		return FAILURE;
	}

	stringList = header->next;

	/*Print out the list, printing each item until we reach the end of the list*/
	while (stringList != NULL)
	{
		struct dataString * tempNext = stringList->next;
		printf("%s\n", stringList->string);
		stringList = tempNext;
	}
	return SUCCESS;
}

int processStrings(struct dataHeader *header, int database)
{
	/*If header is null, return failure*/
	if (header == NULL)
	{
		return FAILURE;
	}
	if (header->name == NULL)
	{
		return FAILURE;
	}
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

	/*While we are not out of strings to process...*/
	while (stringList != NULL)
	{
		/*Make a new string which will be our formatted string, make it large so it can accomodate a bigger string size*/
		newString = malloc((strlen(stringList->string) * 5) + 1);
		if (newString == NULL)
		{
			return FAILURE;
		}
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
					while (stringList->string[i + addOne] == '\n' || stringList->string[i + addOne] == '\r'
					        || stringList->string[i + addOne] == ' ' || stringList->string[i + addOne] == '\t')
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
					while (stringList->string[i + addOne] == '\n' || stringList->string[i + addOne] == '\r' ||
					        stringList->string[i + addOne] == ' ' || stringList->string[i + addOne] == '\t')
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
	/*Update length*/
	header->length = totalStringLength;
	/*Deal with strings beside one another so we have proper formatting*/
	processAdjecent(header);
	/*Call python function that adds HTML tags*/
	pythonProcess(header, database);

	return SUCCESS;
}

int pythonProcess(struct dataHeader *header, int database)
{
	/*If header is null, return failure*/
	if (header == NULL)
	{
		return FAILURE;
	}
	if (header->name == NULL)
	{
		return FAILURE;
	}
	char newFile[25];
	char command1[25];
	char command2[25];
	int character = 0;
	struct dataString * stringList = NULL;
	FILE * queuePointer = NULL;
	FILE * filePointer = NULL;

	/*Start up python in terminal using two commands*/
	strcpy(command1, "chmod u+x a4.py");
	system(command1);
	strcpy(command2, "python a4.py &" );
	system(command2);

	strcpy(newFile, header->name);
	strcat(newFile, ".html");

	if ((filePointer = fopen(newFile, "w")) == NULL)
	{
		return FAILURE;
	}

	/*Make a fifo queue called q1 and open it for writing to python*/
	mkfifo("./q1", 0777);
	queuePointer = fopen("./q1", "w");

	stringList = header->next;

	/*Send python the filename, which will go into it's title*/
	fprintf(queuePointer, "%s\n", header->name);

	/*Write out the stringList to python*/
	while (stringList != NULL)
	{
		struct dataString * tempNext = stringList->next;
		fprintf(queuePointer, "%s\n", stringList->string);
		stringList = tempNext;
	}

	/*We are done writing, so close the queuePointer*/
	fclose(queuePointer);

	/*Wait 4 seconds for python to finish processing the strings*/
	sleep(4);
	/*Open the q2 fifo queue that Python has made*/
	queuePointer = fopen("./q2", "r");
	/*Read the strings python sends over, and put them into an HTML file*/

	if (queuePointer)
	{
		/*If database = 0, do not send to database, store the html file in files directory*/
		if (database == 0)
		{
			while ((character = getc(queuePointer)) != EOF)
			{
				fputc(character, filePointer);
				putchar(character);
			}
			fclose(filePointer);
		}
		/*If database = 1, send html file to the database*/
		else if (database == 1)
		{
			while ((character = getc(queuePointer)) != EOF)
			{
				fputc(character, filePointer);
				putchar(character);
			}
			fclose(filePointer);
			/*Call createDBFile - which sets up information to be sent to the database*/
			createDBFile(header, newFile);
		}

	}
	/*Close the queue and remove q2*/
	fclose(queuePointer);
	remove("./q2");

	return SUCCESS;
}

void createDBFile(struct dataHeader *header, char * newFile)
{
	char date[30];
	long long int fileSize = 0;
	FILE * filePointer = NULL;
	char buffer[3000];
	struct stat fileStat;
	time_t rawtime;
	struct tm * timeinfo;
	char * DBfileName;
	char txtFile[25];
	char * fullFile = NULL;

	/*Get information about file to send to database*/
	stat(newFile, &fileStat);
	fileSize = fileStat.st_size;
	/*Copy the textfile name into txtFile*/
	strcpy(txtFile, header->name);
	DBfileName = strtok(header->name, "/");
	DBfileName = strtok(NULL, ".");
	/*If DBfileName = NULL, get the name again... this handles the case where a file does not  have a .txt extension*/
	if (DBfileName == NULL)
	{
		DBfileName = strtok(header->name, "/");
	}
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	/*asctime will give us the current time, copy this into date*/
	strcpy(date, asctime(timeinfo));

	/*Malloc memory for file contents*/
	fullFile = malloc(sizeof (char) * (fileSize + 100));

	/*Read file put file contents into fullFile variable*/
	filePointer = fopen(newFile, "r");
	strcpy(fullFile, "");
	while (fgets(buffer, 3000, (FILE*)filePointer) != NULL)
	{
		strcat(fullFile, buffer);
	}
	/* Call databaseStore - function saves file information into database*/
	databaseStore(DBfileName, fileSize, date, fullFile, newFile);
	free(fullFile);
	fclose(filePointer);
}

void databaseStore(char * DBfileName, long long int fileSize, char *date, char * fullFile, char * txtFile)
{
	MYSQL mysql;
	char * query = NULL;
	/* Make room for ize of the file contents, plus date, plus instructions to mysql*/
	char * record = malloc(sizeof (char) * (fileSize + 300));
	query = malloc(sizeof(char) * (fileSize + 300));
	/*Format a query for mysql*/
	sprintf(record, "insert into html_files values('%s','%s','%lld','%s')", DBfileName, fullFile, fileSize, date);

	/* Connect to database server */
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
	{
		error("Could not connect to host.", &mysql);
	}

	clrstr(query);

	/*Create the html_files table with requred columns, make name primary key*/
	strcat(query, "create table html_files (file_name varchar(50)  not null ,");
	strcat(query, "html_text varchar(21844),");
	strcat(query, "byte_size varchar(21844),");
	strcat(query, "time_loaded varchar(50),");
	strcat(query, "primary key(file_name)   )");

	if (mysql_query(&mysql, query))
	{
		error("Could not create table.\n", &mysql);
	}

	clrstr(query);

	/*Insert a file*/
	if (mysql_query(&mysql, record ))
	{
		error("Could not insert record.\n", &mysql);
	}

	/*Close mysql*/
	mysql_close(&mysql);
	mysql_library_end();

	/*Free memory*/
	free(query);
	free(record);

	/*Remove html file from files directory*/
	char command1[25];
	sprintf(command1, "rm -f %s", txtFile);
	printf("%s", command1);
	system(command1);
}

int processAdjecent(struct dataHeader * header)
{
	/*Check for NULL pointers*/
	if (header == NULL)
	{
		return FAILURE;
	}
	struct dataString * stringList = NULL;
	stringList = header->next;
	int i = 1;

	/*While we are not at the end of the list, keep processing*/
	while (stringList != NULL)
	{
		struct dataString * tempNext = stringList->next;

		for (int i = 0; i <= strlen(stringList->string); i++)
		{
			/*If we find a <P>*/
			if (stringList->string[i] == '<' && stringList->string[i + 1] == 'P' && stringList->string[i + 2] == '>'
			        && stringList->string[i + 3] == '\0')
			{
				/*Check if we have a <P> at the beginning of the next line*/
				int j = 0;
				if (stringList->next != NULL && stringList->next->string[j] == '<' && stringList->next->string[j + 1] == 'P'
				        && stringList->next->string[j + 2] == '>')
				{
					/*If we have two <P>'s in a row, remove the <P> on the top line*/
					stringList->string[i] = '\0';
					stringList->string[i + 1] = '\0';
					stringList->string[i + 2] = '\0';
				}
				/*If we have a <BR> after <P>, remove repeat*/
				else if (stringList->next != NULL && stringList->next->string[j] == '<' && stringList->next->string[j + 1] == 'B'
				         && stringList->next->string[j + 2] == 'R' && stringList->next->string[j + 3] == '>')
				{
					stringList->string[i] = '\0';
					stringList->string[i + 1] = '\0';
					stringList->string[i + 2] = '\0';
					stringList->string[i + 3] = '\0';
				}
			}
			/*Else if we find a <BR>*/
			else if (stringList->string[i] == '<' && stringList->string[i + 1] == 'B' && stringList->string[i + 2] == 'R'
			         && stringList->string[i + 3] == '>' && stringList->string[i + 4] == '\0')
			{
				/*Check if we have a <P> at the beginning of the next line*/
				int j = 0;
				if (stringList->next != NULL && stringList->next->string[j] == '<' && stringList->next->string[j + 1] == 'P'
				        && stringList->next->string[j + 2] == '>')
				{
					/*If we have a <BR> then a <P>, make the <P> take over, remove <BR>*/
					stringList->string[i] = '\0';
					stringList->string[i + 1] = '\0';
					stringList->string[i + 2] = '\0';
					stringList->string[i + 3] = '\0';
				}
				/*If we have a <BR> and another <BR>, make this <P>*/
				else if (stringList->next != NULL && stringList->next->string[j] == '<' && stringList->next->string[j + 1] == 'B'
				         && stringList->next->string[j + 2] == 'R' && stringList->next->string[j + 3] == '>')
				{
					/*Set <BR> to <P> and second <BR> to nothing*/
					stringList->string[i] = '<';
					stringList->string[i + 1] = 'P';
					stringList->string[i + 2] = '>';
					stringList->string[i + 3] = '\0';
					stringList->string[i + 4] = '\0';

					stringList->next->string[j] = '\0';
					stringList->next->string[j + 1] = '\0';
					stringList->next->string[j + 2] = '\0';
					stringList->next->string[j + 3] = '\0';
					stringList->next->string[j + 4] = '\0';

					/*Set <BR> to <P> and second <BR> to nothing*/
					if (stringList->next->next != NULL && stringList->next->next->string[j] == '<'
					        && stringList->next->next->string[j + 1] == 'B' && stringList->next->next->string[j + 2] == 'R'
					        && stringList->next->next->string[j + 3] == '>')
					{
						stringList->next->next->string[j] = '\0';
						stringList->next->next->string[j + 1] = '\0';
						stringList->next->next->string[j + 2] = '\0';
						stringList->next->next->string[j + 3] = '\0';
					}
				}
			}
		}
		/*Keep loop going*/
		i++;
		/*Get next string*/
		stringList = tempNext;
	}
	return SUCCESS;
}

int freeStructure(struct dataHeader * header)
{
	if (header == NULL)
	{
		return FAILURE;
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
	return SUCCESS;
}

int freeList(struct dataString * toFree)
{
	if (toFree == NULL)
	{
		return FAILURE;
	}
	if (toFree->next != NULL)
	{
		freeList(toFree->next);
	}
	free(toFree->string);
	free(toFree->next);
	return SUCCESS;
}


int writeStrings(char *filename, struct dataHeader * header)
{
	/*Check if our parameters are NULL, if they are return failure*/
	if (filename == NULL)
	{
		return FAILURE;
	}
	if (header == NULL)
	{
		return FAILURE;
	}
	if (header->name == NULL)
	{
		return FAILURE;
	}

	FILE * filePointer = NULL;

	if ((filePointer = fopen(filename, "w")) == NULL)
	{
		return FAILURE;
	}

	struct dataString * stringList = NULL;
	stringList = header->next;
	int nameLength = 0;
	nameLength = (strlen(header->name) + 1);
	int stringLength = 0;

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
	return SUCCESS;
}

struct returnStruct *readStrings(char *filename)
{
	struct returnStruct *returnStruct = NULL;
	struct dataHeader * header = NULL;

	FILE * filePointer = NULL;
	int nameLength = 0;
	char * headerName = NULL;
	int totalStringLength = 0;
	int stringLength = 0;
	char * string = NULL;

	returnStruct = buildHeader();
	header = returnStruct->header;

	if (filename == NULL)
	{
		/*If file is null, we return a failure*/
		returnStruct->value = FAILURE;
		returnStruct->header = NULL;
		return returnStruct;
	}

	filePointer = fopen(filename, "r");

	/*If the file does not exist, fopen returns NULL*/
	if (filePointer == NULL)
	{
		returnStruct->value = FAILURE;
		returnStruct->header = NULL;
		return returnStruct;
	}

	/*Read the length of the header's name and then header's name to the file*/
	fread(&nameLength, sizeof(int), 1, filePointer);

	/*Malloc the space for the header's name*/
	headerName = malloc(sizeof(char) * (nameLength + 1));
	if (headerName == NULL)
	{
		returnStruct->value = FAILURE;
		returnStruct->header = NULL;
		return returnStruct;
	}

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
		if (string == NULL)
		{
			returnStruct->value = FAILURE;
			returnStruct->header = NULL;
			return returnStruct;
		}

		/*Read the string from the file*/
		fread(string, sizeof(char), stringLength, filePointer);
		/*Add the string we just read to the header*/
		addString(header, string);
		free(string);
	}
	fclose(filePointer);
	/*If we got to here, it is a success so we return the struct with a success value added*/
	returnStruct->value = SUCCESS;
	return returnStruct;
}

int printFile(FILE * filePointer)
{
	if (filePointer == NULL)
	{
		return FAILURE;
	}
	int character;
	/*Print out the file one character at a time*/
	while ((character = getc(filePointer)) != EOF)
	{
		putchar(character);
	}
	return SUCCESS;
}

/* Standard error clause from mysql - code from prof */
void error(char *msg, MYSQL *mysql)
{
	printf("%s\n%s\n", msg, mysql_error(mysql));
}

/* Clear the contents of an array of char's for queries- code from prof */
void clrstr(char *buf)
{
	buf[0] = '\0';
}

