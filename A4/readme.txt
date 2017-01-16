****************************************************
Kendra Dubois		0890708
CIS*2750		Assignment 4
Nov 23rd, 2016
**************************************************** 

******************************
What Works
******************************
The program functions as specified by the assignment. The only thing that doesn’t work is HTML files that are stored on the database do not show up in the HTML files section on the website. HTML files are listed alphabetically. However files are successfully saved the database. No valgrind errors/leaks. 

************
Compilation
************
To compile, unpack the compressed files and type:
make

***********************
Running the program(s)
***********************
To use the program as described in assignment 4, open "a4.php" from the main file directory into a web browser (chrome preferably).
This a4.php page has my assignment on it.

~!~Make sure all files have full/all permissions for program to work as expected~!~
Check for permissions with:
ls -l

If not all files have permissions, type:
"chmod -R 0777 <maindirectoryname>"

Or to give files permissions individually type:
“chmod 0777 <filename>”

Once all files have all permissions, the program should work as expected. If you run into trouble please read the “Important Notes (If Issues Occur)” section.

Uploading a File:
1. Press "Choose File"
2. Choose your file from the file browser that pops up, click open to select it.
3. Click the upload button.
4. Refresh the page to update it to see the file.

Using Convert:
1. Press the convert button.
2. Select the .txt file you want to convert.
3. Press OK.
...Wait about 3 seconds for conversion to take place...
4. Refresh the page to update it to see the .html file.

Using DB Store:
1. Press DB store button.
2. Select the .txt file you want to convert.
3. Press OK.
…Wait about 4 seconds for conversion to take place…
4. File will have been added to the database, to confirm this use db program.

For running the main program just in terminal like we did for a2, while in the current directory type:
./a4 <filename>.txt

To run valgrind do the same way as A3:
valgrind --leak-check=yes ./a4 filename.txt
**********************************
Important Notes (If Issues Occur)
**********************************
1. "Missing file(s)?/Convert won't work?" - PERMISSIONS. 
Permissions seemed to give some problems on the server, professor acknowledged this. Please give all the files full permissions. Especially for any new files added by the TA, a4, a4.py, a4.php, upload.php and the files directory. We can give these files all the permissions by typing "chmod 0777 <filename>" into the terminal. If many files need permissions, please give everything in a directory full permissions. You can do this by typing "chmod -R 0777 <directoryname>" command in terminal while outside the main directory.

2. "Blank page?" - WAIT TIME.  
After pressing convert, please wait about 4 seconds before refreshing the page to see the new .html file. The conversion takes a moment as C is told to wait for python so that python could finish processing before C tries to read from the pipe. If you try to access a page and did not wait 4 seconds it may show up blank at first. After waiting it will be as expected.

3. FILES.
My program can read .txt or text files with no extensions, however only .txt files, files with no extensions and .html files are displayed on the .php page as that is what is described on the assignment for A3.

4. BROWSER.
I tested mostly in Chrome with the window fully open, if there are any issues please try with these settings.

**********************
File Descriptions
**********************
a4.c - is the name of my main that I created for assignment 3, works on it's own
a4.py - is the python program which adds the tags in the info file
listio.c - holds functions of the library from A1 and new helper functions
libstio.h - holds function descriptions and function explanations
a4.php - the php that has my a3 on it, this is what is to be marked primarily
upload.php - a helper php program that a4.php calls, it uploads files to the server
(No files subdirectory was kept as it said it would be provided. (Removed my test one))
db.c - holds main for db program, this program is a utility program that lets us manage the database

***********************
Makefile Notes
***********************
If you just want to run the library you can type:
make library 
(This only makes the library, nothing can be run from this)

If you want to clean up the executables and compiled code type:
make clobber

******************************
Resources
******************************
For understanding CSS and javascript functions:
http://makecodeeasy.blogspot.ca/2012/07/popup-in-java-script-and-css.html
(Javascript functions used from site above)

For help with uploading files I followed these instructions and the profs from class:
http://www.w3schools.com/php/php_file_upload.asp

For general understanding, helped with lots of my program:
http://www.w3schools.com/

For how to get current computer time:
http://stackoverflow.com/questions/5141960/get-the-current-time-in-c

Profs code from class for database functionality

*******************************
Academic Integrity Pledge
*******************************

I have exclusive control over this submission via my password.
By including this file with my submitted files, I certify that:

1) I have read and understood the University policy on academic integrity;
2) I have completed the Computing with Integrity Tutorial on Moodle; and
3) I have achieved at least 80% in the Computing with Integrity Self Test.

I assert that this work is my own.

I have appropriately acknowledged any and all material (data, images, ideas or
words) that I have used, whether directly quoted or paraphrased.  Furthermore,
I certify that this assignment was prepared by me specifically for this course.
