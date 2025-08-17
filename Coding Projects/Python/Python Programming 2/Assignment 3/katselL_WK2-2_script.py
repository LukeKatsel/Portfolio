
'''
Luke Katsel
Week Two Assignment 2 - File Hashing
Sep 6 2023
'''

'''
Complete the script below to do the following:
1) Add your name, date, assignment number to the top of this script
2) Using the os library and the os.walk() method 
   a) Create a list of all files
   b) Create an empty dictionary named fileHashes 
   c) Iterate through the list of files and
      - calculate the md5 hash of each file
      - create a dictionary entry where:
        key   = md5 hash
        value = filepath
    d) Tterate through the dictionary
       - print out each key, value pair
    
3) Submit
   NamingConvention: lastNameFirstInitial_Assignment_.ext
   for example:  alharthiD_WK1_script.py
                 alharthiD_WK1_screenshot.jpg
   A) Screenshot of the results in WingIDE
   B) Your Script
'''

import os
import hashlib
from prettytable import PrettyTable



directory = input("Enter a directory: ")

fileList   = []
fileHashes = {}

tbl = PrettyTable(['FilePath','Hash'])

for root, dirs, files in os.walk(directory):

    # Walk the path from top to bottom.
    # For each file obtain the filename 
    
    for fileName in files:
        path = os.path.join(root, fileName)
        fullPath = os.path.abspath(path)
        fileList.append(fullPath)
for fullPath in fileList:
    with open(fullPath, 'rb') as fileObj:
        fileContent = fileObj.read()
        sha256Obj = hashlib.sha256()
        sha256Obj.update(fileContent)
        hexDigest = sha256Obj.hexdigest()
        fileHashes[hexDigest] = fullPath
            
for key, value in fileHashes.items():
        tbl.add_row( [ value, key] )                    
        
tbl.align = "l" 
hashTable = tbl.get_string(sortby="FilePath", reversesort=False)
print(hashTable)