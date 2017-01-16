#!/usr/bin/python3

import os, sys, re, os.path

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

#Check if an info file exists, if so add tags
if os.path.exists(infoFile):
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
				iList.append(line[2:])
			if line[0:1] == 'U':
				uList.append(line[2:])

		#Format the list in a way that can be read by re.compile for string replacement

		#If we have text to bold in our file, add bold tags
		if not len(bList) == 0:
			bFormatted = '|'.join('{0}'.format(i) for i in bList)
			bFormatted = "(" + bFormatted + ")"

			regex = re.compile(bFormatted)
			#Compare the regex against the stringList, add tags when we have a match
			bAdded = regex.sub(r'<b>\1</b>', stringList)

		#If we do not have test to bold in our file, do not add bold tags
		if len(bList) == 0:
			bAdded = stringList

		#If we have text to underline in our file, add underline tags
		if not len(uList) == 0:
			uFormatted = '|'.join('{0}'.format(i) for i in uList)
			uFormatted = "(" + uFormatted + ")"

			regex = re.compile(uFormatted)
			#Compare the regex against the updated stringList with the <b>'s added, add <u> tags when we have a match
			uAdded = regex.sub(r'<u>\1</u>', bAdded)

		#If we do not have text to underline in our file, do not add underline tags
		if len(uList) == 0:
			uAdded = bAdded

		#If we have text to italicize in our file, add italic tags
		if not len(iList) == 0:
			iFormatted = '|'.join('{0}'.format(w) for w in iList)
			iFormatted = "(" + iFormatted + ")"

			regex = re.compile(iFormatted)
			uFormatted = regex.sub(r'<i>\1</i>', uAdded)

		#If we do not have text to italicize in our file, do not add italic tags
		if len(iList) == 0:
			uFormatted = uAdded

#If there is no .info file, do not add any tags just add text passed in
else:
	uFormatted = stringList


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
