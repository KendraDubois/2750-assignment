#include "listio.h"

#define MAX_QUERY 512
#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "kdubois"
#define PASSWORD  "0890708"
#define DATABASE  "kdubois"

/*Displays an error when there is an issue with queries or setting up the database/tables - code from prof*/
void error(char *msg, MYSQL *mysql)
{
	printf("%s\n%s\n", msg, mysql_error(mysql));
	exit(1);
}

/*Clear the contents of an array of char's, this is done when we create a new query - code from prof*/
void clrstr(char *buf)
{
	buf[0] = '\0';
}

int main(int argc, char *argv[])
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY];
	int i = 0;

	/*Connect to database server*/
	printf("Connecting...\n");

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD, DATABASE, 0, NULL, 0))
	{
		error("Could not connect to host.", &mysql);
	}
	/*Check the user has used two arguments, the required ammount for this program*/
	if (argc == 2)
	{

		/*Save flag user inputs through commandline*/
		char * flag = argv[1];

		clrstr(query);

		/*if user uses - clear flag, remove all rows from the table in the database*/
		if (strcmp(flag, "-clear") == 0)
		{
			strcat(query, "delete from html_files;");
			if (mysql_query(&mysql, query))
			{
				error("Could not remove all rows.", &mysql);
			}
			else
			{
				printf("Rows removed.\n");
			}
		}
		/* if user uses -reset flag, remove all tables from the database*/
		else if (strcmp(flag, "-reset") == 0)
		{
			strcat(query, "drop table html_files;");
			if (mysql_query(&mysql, query))
			{
				error("Could not remove the table.", &mysql);
			}
			else
			{
				printf("Tables removed.\n");
			}
		}
		/* if user used -show flag, show the name of the file, the length, and the time it was loaded*/
		else if (strcmp(flag, "-show") == 0)
		{
			strcpy(query, "select file_name, byte_size, time_loaded from html_files");

			if (mysql_query(&mysql, query))
			{
				error("Selection query failed.", &mysql);
			}
			/*Store results from query into result structure*/
			if (!(res = mysql_store_result(&mysql)))
			{
				error("Storing to results structure failed.", &mysql);
			}

			/*Print out the name, length and date for all files stored on the database*/
			while ((row = mysql_fetch_row(res)))
			{
				for (i = 0; i < mysql_num_fields(res); i++)
				{
					printf("%s ", row[i]);
				}
			}

			/*Free results*/
			mysql_free_result(res);
		}
		/*if the user uses the -help flag, give them instructions on how to use program*/
		else if (strcmp(flag, "-help") == 0)
		{
			printf("= = = = = = = HELP = = = = = = =\n");
			printf("\nThis is a utility program to view and manage the database.\n\n");
			printf("= = = = = = = USE = = = = = = = =\n");
			printf("\nTo use the program, type:\n./db -desiredflag\nWhere '-desiredflag' is to be replaced with one of these options:\n");
			printf("-clear\n    This flag will remove all rows from the table in the database.\n");
			printf("-reset\n    This flag will delete the table from the database.\n");
			printf("-show\n     This flag will print out the name, length and date for all files stored in the database. If the rows are empty, no rows will be outputted.\n");
			printf("-help\n     This flag will display this menu, which describes how to use the program.\n");
		}
		/*if the user did not use a valid flag, instruct them to do so*/
		else
		{
			printf("Please use flags described in assignment. (-clear, -reset, -show, -help) Use './db -help' for more detailed instructions.\n");
		}

		clrstr(query);
		/*Close mysql*/
		mysql_close(&mysql);
		mysql_library_end();
	}
	/*If user did not input 2 command line arugments, prompt them to do so*/
	else
	{
		printf("Please input 2 arguements. Use './db -help' for more detailed instructions.\n");
	}

	return 0;
}
