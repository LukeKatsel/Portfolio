'''
Searching through a chunked file
Luke Katsel
4/9/2023
'''

import sys
import os
import re       # Python regular expression Library
from prettytable import PrettyTable   # 3rd Party Table Library
                              # pip install prettytable

print("\nPossible Word List\n")

urlPattern = re.compile(b'\w+:\/\/[\w@][\w.:@]+\/?[\w\.?=%&=\-@/$,]*')

try:
    # Prompt user for a file and Chunk Size    
    largeFile = input("Enter the name of a large File: ")

    wordDict = {}  # Create an empty dictionary

    if os.path.isfile(largeFile):  # Verify file is real
        with open(largeFile, 'rb') as targetFile:
            while True:          
                fileChunk = targetFile.read(65535)

                if fileChunk:  # if we still have data         
                    wordList = urlPattern.findall(fileChunk)

                    for eachWord in wordList:
                        try:
                            cnt = wordDict[eachWord]  # obtain the value if key exists
                            cnt += 1                  # Increment the count
                            wordDict[eachWord] = cnt  # Update the dictionary entry
                        except:
                            wordDict[eachWord] = 1    # otherwise, key doesn't exist, create it
                else:
                    # File has been processed
                    tbl = PrettyTable(["OCCURS", "URL"])
                    for word, cnt in wordDict.items():
                        tbl.add_row([cnt, word.decode('utf-8')])
                    tbl.align = 'l'
                    print(tbl.get_string(sortby="OCCURS", reversesort=True))
                    break
    else:
        print(largeFile, "is not a valid file")
        sys.exit("Script Aborted")

except Exception as err:
    sys.exit("\nException: "+str(err)+ "Script Aborted")

print("\nFile Processed ... Script End")