#!/usr/bin/python3

import os, sys, re

#Open the fifo queue that our C program has made for reading
queueName = "./q1"
pipe = open(queueName, "r")

#First read the titlename/original filename, it is the first item sent
titleName = pipe.readline().strip()

#Save all the strings from the C program in stringList
stringList = ""
for line in pipe:
	stringList += line

#Take the filename and add .info so we can open the info file
infoFile = titleName + ".info"

with open(infoFile) as f:
	infodata = f.read().splitlines()

#Make 3 lists, 1 for each formatting style(B,I,U)
bList = []
iList = []
uList = []

#Looking at the first character, each string in the proper list
for line in infodata:
	if line[0:1] == 'B':
		bList.append(line[2:])
	if line[0:1] == 'I':
		uList.append(line[2:])
	if line[0:1] == 'U':
		iList.append(line[2:])

#Format the list in a way that can be read by re.compile for string replacement
bFormatted = '|'.join('{0}'.format(i) for i in bList)
bFormatted = "(" + bFormatted + ")"

regex = re.compile(bFormatted)
#Compare the regex against the stringList, add tags when we have a match
bAdded = regex.sub(r'<b>\1</b>', stringList)

uFormatted = '|'.join('{0}'.format(i) for i in uList)
uFormatted = "(" + uFormatted + ")"

regex = re.compile(uFormatted)
#Compare the regex against the updated stringList with the <b>'s added, add <u> tags when we have a match
uAdded = regex.sub(r'<u>\1</u>', bAdded)

iFormatted = '|'.join('{0}'.format(w) for w in iList)
iFormatted = "(" + iFormatted + ")"

regex = re.compile(iFormatted)
uFormatted = regex.sub(r'<i>\1</i>', uAdded)

finalFormatted = ""

finalFormatted = "<html>" + "<head>" + "<title>" + titleName + "</title>" \
+ "</head>" + "<body>" + uFormatted + "</body>" + "</html>"

os.remove(queueName)

#Open a new fifo queue called q2
queueName = "./q2"
os.mkfifo(queueName)
pipe = os.open(queueName, os.O_WRONLY)

#Write the formatted input back to C
os.write(pipe,finalFormatted)

os.close(pipe)
