'''
WK-4 SCRIPT
Luke Katsel
July 2023
Version 2
'''

# Python Standard Libaries 
import os
import re
import sys

# Python 3rd Party Libraries
from prettytable import PrettyTable     # pip install prettytable

# Psuedo Constants

# Local Functions 

# Local Classes

# Main


try: 
    
    urlDictionary = {}
    
    urlPattern = re.compile(b'\w+:\/\/[\w@][\w.:@]+\/?[\w\.?=%&=\-@/$,]*')
    
    searchFile = input("Enter Target Folder: ")
    chunkSize = int(input("What size chunks?  "))

    if os.path.isfile(searchFile):  
        fileSize = os.path.getsize(searchFile)
        bytesProcessed = 0
        chunkCnt = 0
        with open(searchFile, 'rb') as targetFile:
            while True:
                fileChunk = targetFile.read(chunkSize)
                bytesProcessed += len(fileChunk)
                
                if fileChunk:  
                    urlMatches = urlPattern.findall(fileChunk)
                    chunkCnt += 1 
                    for eachUrl in urlMatches:
                        try:  
                            cnt = urlDictionary[eachUrl] 
                            cnt += 1
                            urlDictionary[eachUrl] = cnt
                        except:
                            urlDictionary[eachUrl] = 1   
                    for key, value in urlDictionary.items():
                        key = str(key)    
                else:
                    tbl = PrettyTable(['OCCURS','URL'])
                    tbl.title = 'Search Results'
                    for url, cnt in urlDictionary.items():
                        url = url.decode('ascii')
                        tbl.add_row([cnt, url])
                    tbl.align = 'l'
                    print(tbl.get_string(sortby="OCCURS", reversesort=True))                   
                    break
                                 
    else:
        print(searchFile, "is not a valid file")
        sys.exit("Script Aborted")
            
except Exception as err:
    sys.exit("\nException: "+str(err)+ " Script Aborted")

print("\nScript-End\n")