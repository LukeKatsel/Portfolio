'''
Luke Katsel
Week 3 script
September 11 2023
'''
from __future__ import print_function
import os
import time


'''
Assignment 4 - File Processing Object

Complete the script below to do the following:
1) Add your name, date, assignment number to the top of this script
2) Create a class named FileProcessor
   a) The Init method shall:
      i) verify the file exists
      ii) Extract key file system metadata from the file
          and store them as instance attribute
          i.e. FilePath, FileSize, MAC Times, Owner, Mode etc.
   b) Create a GetFileHeader Method which will
      i) Extract the first 20 bytes of the header
         and store them in an instance attribute
   c) Create a PrintFileDetails Method which will
      i) Print the metadata
      ii) Print the hex representation of the header
      
3) Demonstrate the use of the new class
   a) prompt the user for a directory path
   b) using the os.listdir() method extract the filenames from the directory path
   c) Loop through each filename and instantiate and object using the FileProcessor Class
   d) Using the object
      i) invoke the GetFileHeader Method
      ii) invoke the PrintFileDetails Method
      
4) Submit
   NamingConvention: lastNameFirstInitial_Assignment_.ext
   for example:  alharthiD_WK3_script.py
                 alharthiD_WK3_screenshot.jpg
   A) Screenshot of the results in WingIDE
   B) Your Script
'''



class FileProcessor:
    def __init__(self, filePath):
        if os.path.isfile(filePath):
            if os.access(filePath, os.R_OK):
                self.filePath = filePath
                self.fileSize = os.path.getsize(self.filePath)
                stats = os.stat(self.filePath)
                self.accessTime = time.ctime(stats.st_atime)
                self.modifiedTime = time.ctime(stats.st_mtime)
                self.createdTime = time.ctime(stats.st_ctime) 
                self.fileOwner = stats.st_uid
                self.header = None
                
    def GetFileHeader(self):
        with open(self.filePath, 'rb') as file:
            self.header = file.read(20)
        
    def PrintFileDetails(self):
        print (f"\nFile Path: {self.filePath}")
        print (f"File Size: {self.fileSize}")
        print (f"Access Time: {self.accessTime}")
        print (f"Modified Time: {self.modifiedTime}")
        print (f"Created Time: {self.createdTime}")
        print (f"Owner: {self.fileOwner}") 
        print(f"Header: {self.header.hex()}")
        
def ProcessDirectory (directoryPath):
    fileList = os.listdir(directoryPath)
    for fileName in fileList:
        filePath = os.path.join(directoryPath,fileName)
        if os.path.isfile(filePath):
            processor = FileProcessor(filePath)
            processor.GetFileHeader()
            processor.PrintFileDetails()            
        
directoryPath = input("Enter a Directory: ")
        
ProcessDirectory(directoryPath)
