****************************************************
Kendra Dubois		0890708
CIS*2750		Assignment 2
Oct 10th, 2016
**************************************************** 

************
Compilation
************
To compile, while in the main folder(A2) type:
make

***********************
Running the program(s)
***********************
For running the main program, while in the main folder(A2) type:
./main <filename>

Side Note:
If you just want to run the library you can run:
make library (This only makes the library, nothing can be run from this)

**********************
File Descriptions
**********************
a2.c - is the name of my main that I created for this assignment
a2python.py - is the python program which adds the tags in the info file
listio.c - holds functions of the library from A1 and new helper functions
libstio.h - holds function descriptions and function explanations

******************************
What Works
******************************
The program works mostly as specified by the assignment. However, if a string is inside another string sometimes odd behaviour occurs (for example sometimes strings being bolded/italicized/underlined that maybe the user did not intend).

*****************
Known Limitations
*****************
If certain files are not present in the main folder this can lead to strange behaviour or the program will not function fully. For example if a ".info" file is left out, no tags will be added.

The program takes about 10 seconds to run, I called sleep for 10 seconds so that python could finish processing before C tried to read from the pipe. In this way the program is not super fast.


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

