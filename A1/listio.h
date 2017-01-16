#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dataHeader
{
	/*Name of the book/journal/story... refers to what the text is*/
	char *name;
	/*Length of TOTAL text, all chars added up from every added string*/
	int length;
	/*Pointer to the data string*/
	struct dataString *next;
};

struct dataString
{
	char *string;
	/*Pointing to the next string in the linked list*/
	struct dataString *next;
};

/*********************************************************************
 * NAME: buildHeader
 * PURPOSE: This creates the header, which we use to access the data
 * strings
 * ARGUMENTS: None.
 * PRECONDITIONS: None.
 * POSTCONDITIONS: A header is created.
 *********************************************************************/
struct dataHeader *buildHeader();

/*********************************************************************
 * NAME: setName
 * PURPOSE: This sets the name of the header.
 * ARGUMENTS: The header and the name that will go inside header (header->name)
 * PRECONDITIONS: Name should be valid, header should be created.
 * POSTCONDITIONS: A name is set for header.
 *********************************************************************/
void setName(struct dataHeader *header, char *name);

/*********************************************************************
 * NAME: getName
 * PURPOSE: This gets the name of the header, and returns it.
 * ARGUMENTS: The header.
 * PRECONDITIONS: The header should be created.
 * POSTCONDITIONS: A name is set for header.
 *********************************************************************/
char * getName(struct dataHeader *header);

/*********************************************************************
 * NAME: getLength
 * PURPOSE: This gets the length that is contained in the header, and
 * returns it as an int.
 * ARGUMENTS: The header.
 * PRECONDITIONS: The header should be created and the length has been set.
 * Otherwise it will return 0, the default number.
 * POSTCONDITIONS: The length within header will be returned.
 *********************************************************************/
int getLength(struct dataHeader *header);

/*********************************************************************
 * NAME: addString
 * PURPOSE: addString creats a new dataString and adds that string to
 * the linked list of dataString structs.
 * ARGUMENTS: It takes in the header, and the string to be added to the
 * linked list of dataString structs. The header is used to access the list.
 * PRECONDITIONS: The header should be created and the string should be valid.
 * POSTCONDITIONS: The linked list is updated, with a new dataString that
 * is filled out.
 *********************************************************************/
void addString(struct dataHeader *header, char *str);

/*********************************************************************
* NAME: printString
* PURPOSE: This prints out all the strings saved to the screen that are
* contained in the dataStrings
* ARGUMENTS: The header which contains the head of our linked list of
* dataString structs
* PRECONDITIONS: The list is not empty.
* POSTCONDITIONS: The full list of strings will be printed out to the screen.
*********************************************************************/
void printString(struct dataHeader *header);

/*********************************************************************
* NAME: processStrings
* PURPOSE: Modifies the characters space, tab, newline and carriage returns
* contained in the strings in the dataStrings. This is done by looking at the
* the original string char by char. When we encounter any of the characters
* mentioned above we modify the string based on a number of rules. A new
* reformatted string is made and the original string is freed.
* ARGUMENTS: The header which contains the head of our linked list of
* dataString structs.
* PRECONDITIONS: The dataString list is not empty.
* POSTCONDITIONS: The strings will be modified in their respective dataString
* structs according to the specification.
*********************************************************************/
void processStrings(struct dataHeader *header);

/*********************************************************************
* NAME: freeStructure
* PURPOSE: Free the allocated memory in the structures made
* ARGUMENTS: The header which contains the head of the list
* PRECONDITIONS: The list is not empty
* POSTCONDITIONS: The allocated memory will be freed
*********************************************************************/
void freeStructure(struct dataHeader *header);

/*********************************************************************
* NAME: freeList
* PURPOSE: Free the allocated memory of the strings and dataStrings
* ARGUMENTS: The dataString that is to be freed
* PRECONDITIONS: The list is not empty
* POSTCONDITIONS: The allocated memory will be freed
*********************************************************************/
void freeList(struct dataString * toFree);

/*********************************************************************
* NAME: writeStrings
* PURPOSE: Write strings and ints from our list into a binary file.
* It is to be written in such a way that the file can be read from later to
* fill in a new list (with header and dataString structs).
* ARGUMENTS: A filename, and the he header which contains the head of the list.
* PRECONDITIONS: The list is not empty, and a valid filename
* POSTCONDITIONS: A binary file will be created and wrote to with the specified
* data
*********************************************************************/
void writeStrings(char *filename, struct dataHeader * header);

/*********************************************************************
* NAME: readStrings
* PURPOSE: Reads strings and ints from a binary file, and takes that information
* and puts it into a new list with header and dataString structs
* ARGUMENTS: A filename
* PRECONDITIONS: A valid filename is sent in
* POSTCONDITIONS: A binary file will be successesfully read from. The information
* from that binary file has been used to create a new list of dataStrings with the header
* filled out as described in the specification
*********************************************************************/
struct dataHeader *readStrings(char *filename);
