'''
Luke Katsel 
Assignment 7
9/25/2023
'''

import os
import re
import sys


from prettytable import PrettyTable


try: 

    urlDictionary = {}
    emailDictionary = {}
    
    emailPattern = re.compile(b'[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}')
    urlPattern = re.compile(b'\w+:\/\/[\w@][\w.:@]+\/?[\w.\.?=%&=\-@$,]*')
    
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
                    emailMatches = emailPattern.findall(fileChunk)
                    chunkCnt += 1 
                    for eachUrl in urlMatches:
                        try:  
                            cnt = urlDictionary[eachUrl] 
                            cnt += 1
                            urlDictionary[eachUrl] = cnt
                        except:
                            urlDictionary[eachUrl] = 1  
                            
                    for eachEmail in emailMatches:
                        try:
                            cnt2 = emailDictionary[eachEmail]
                            cnt2 += 1
                            urlDictionary[eachEmail] = cnt
                        except:
                            emailDictionary[eachEmail] = 1
                            
                    for key, value in urlDictionary.items():
                        key = str(key)  
                    
                    for emailKey, emailValue in emailDictionary.items():
                        emailKey = str(emailKey)
                else:
                    tbl = PrettyTable(['OCCURS','URL'])
                    tbl.title = 'URL Search Results'
                    for url, cnt in urlDictionary.items():
                        url = url.decode('ascii')
                        tbl.add_row([cnt, url])
                    tbl.align = 'l'
                    print(tbl.get_string(sortby="OCCURS", reversesort=True))                   
                
                    tbl2 = PrettyTable(['OCCURS','EMAIL'])
                    tbl2.title = 'Email Search Results'
                    for email, cnt2 in emailDictionary.items():
                        email = email.decode('ascii')
                        tbl2.add_row([cnt2, email])
                    tbl2.align = 'l'
                    print(tbl2.get_string(sortby="OCCURS", reversesort=True))                   
                    break                
                                 
    else:
        print(searchFile, "is not a valid file")
        sys.exit("Script Aborted")
            
except Exception as err:
    sys.exit("\nException: "+str(err)+ " Script Aborted")

print("\nScript-End\n")