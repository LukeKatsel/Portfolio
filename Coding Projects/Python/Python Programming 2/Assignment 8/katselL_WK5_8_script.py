'''
Luke Katsel 
Assignment 8
9/25/2023
'''


import os
import re
import sys

from prettytable import PrettyTable


try: 

    stringDictionary = {}
    
    wPatt = re.compile(b'[a-zA-Z]{5,15}')    
    
    searchFile = input("Enter Target File: ")
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
                    wordMatches = wPatt.findall(fileChunk)
                    chunkCnt += 1 
                    for eachWord in wordMatches:
                        try:  
                            cnt = stringDictionary[eachWord] 
                            cnt += 1
                            stringDictionary[eachWord] = cnt
                        except:
                            stringDictionary[eachWord] = 1 
                    for key, value in stringDictionary.items():
                                key = str(key)      
                else:          
                    tbl = PrettyTable(['OCCURS','Words'])
                    tbl.title = 'Search Results'
                    for word, cnt in stringDictionary.items():
                        word = word.decode('ascii')
                        tbl.add_row([cnt, word])
                    tbl.align = 'l'
                    print(tbl.get_string(sortby="OCCURS", reversesort=True))  
                    break
                        
    else:
        print(searchFile, "is not a valid file")
        sys.exit("Script Abor")
            
except Exception as err:
    sys.exit("\nException: "+str(err)+ " Script Aborted")

print("\nScript-End\n")                
        