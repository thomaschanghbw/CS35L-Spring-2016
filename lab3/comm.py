#!/usr/local/cs/bin/python

import sys, locale
from optparse import OptionParser

locale.setlocale(locale.LC_ALL, 'C')

#This class contains the long string of a file's contents
class readLine:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()
def main():
    parser = OptionParser()
    parser.add_option("-1", action="store_true", dest="numOne", default=False, help="Do not output first column")
    parser.add_option("-2", action="store_true", dest="numTwo", default=False, help="Do not output second column")
    parser.add_option("-3", action="store_true", dest="numThree", default=False, help="Do not output third column")
    parser.add_option("-u", action="store_true", dest="unsorted", default=False, help="File is unsorted")
    options, args = parser.parse_args()

    listOne = []
    listTwo = []
    listThree = []
    helperList = []

    if len(args)>2:
        parser.error("Too many arguments!")


    
    try:
        testing = args[1]
        testing = args[0]
    except:
        parser.error("Invalid number of files inputted")
    
    #Read the files, first checking if the filename is -
    if args[0] == "-":
        firstFile = sys.stdin.readlines()
    else:
        try:
            firstFile = readLine(args[0])
        except:
            parser.error("There was an error reading file. Please Try again.")
    if args[1] == "-":
        secondFile = sys.stdin.readlines()
    else:
        try:
            secondFile = readLine(args[1])
        except:
            parser.error("There was an error reading file. Please Try again.")

        
    if options.unsorted == False:
        for A in firstFile.lines:
            added = False
            for B in secondFile.lines:
                if (locale.strcoll(A, B) > 0):
                    if not(B in helperList):
                        listOne.append(" ")
                        listThree.append(" ")
                        listTwo.append(B)
                        helperList.append(B)
                        added = True
                else:
                    if A == B:
                        if not(A in helperList):
                            listOne.append(" ")
                            listTwo.append(" ")
                            listThree.append(A)
                            helperList.append(A)
                            added = True
            if added == False:
                listOne.append(A)
                helperList.append(A)
                listTwo.append(" ")
                listThree.append(" ")
    else:
        for A in firstFile.lines:
            if not(A in secondFile.lines):
                listOne.append(A)
                listTwo.append(" ")
                listThree.append(" ")
                helperList.append(A)
            else:
                listOne.append(" ")
                listTwo.append(" ")
                listThree.append(A)
                helperList.append(A)
        for B in secondFile.lines:
            if not(B in helperList):
                listOne.append(" ")
                listTwo.append(B)
                listThree.append(" ")
                helperList.append(B)
    for x in range(0, len(listOne)):
        if (listOne[x] != " "):
            if options.numOne == False:
                if (listOne[x][-1:] == '\n'):
                    print(listOne[x][:-1])
                else:
                    print(listOne[x])
            else:
                continue
        if (listTwo[x] != " "):
            if options.numTwo == False:
                if (listTwo[x][-1:] == '\n'):
                    if (options.numOne == True):
                        print(listTwo[x][:-1])
                    else:
                        print('\t' + listTwo[x][:-1])
                else:
                    if (options.numOne == True):
                        print(listTwo[x])
                    else:
                        print('\t' + listTwo[x])
                continue
            else:
                continue
        if (listThree[x] != " "):
            if options.numThree == False:
                if (listThree[x][-1:] == '\n'):
                    if ((options.numOne == False and options.numTwo == True) or (options.numOne == True and options.numTwo == False)):
                        print('\t' + listThree[x][:-1])
                    else:
                        if (options.numOne == True and options.numTwo == True):
                            print(listThree[x][:-1])
                        else:
                            print('\t' + '\t' + listThree[x][:-1])
                else:
                    if ((options.numOne == False and options.numTwo == True) or (options.numOne == True and options.numTwo == False)):
                        print('\t' + listThree[x])
                    else:
                        if (options.numOne == True and options.numTwo == True):
                            print(listThree[x])
                        else:
                            print('\t' + '\t' + listThree[x])
                continue
            else:
                continue 


if __name__ == "__main__":
    main()
