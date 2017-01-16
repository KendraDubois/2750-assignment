****************************************************
Kendra Dubois		0890708
CIS*2750		Assignment 1
September 25th, 2016
**************************************************** 

************
Compilation
************
To compile, while in the main folder(A1) type:
make

***********************
Running the program(s)
***********************
For running the program type, while in the main folder(A1) type:
gcc -o programname yourmain.c liblistio.a

For running tests type:
./programname

******************************
What Works
******************************
The program works as specified in the assignment. I have also checked for memory leaks and errors in valgrind, any errors found were fixed and leaks have been dealt with. 

*****************
Known Limitations
*****************
Sending in NULL pointers to functions can lead to irregular behaviour of the program and segfaulting. There is some checking done for this but it is not especially robust. 


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

