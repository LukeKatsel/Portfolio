'''
Script:  First Script
Author:  Luke Katsel
Date:    July 2023
Version: 2
Purpose:

ASSIGNMENT DETAILS
After experimenting with the First.py script and attending this weeks lecture, you are to modify/extend the First.py script as follows:

1) Allow the user to specify a directory to process using the built-in Python input() function
2) Process each entry in that directory and report:
    Full-Filepath, FileSize, MAC Times for each directory entry
    Converting each MAC epoch value into human readable form
3) Catch any errors when attempting to process files and report them

LECTURE HINTS

    PROMPT USER FOR ENTRY
        directory = input("Enter a Directory to Process: ")
    
    CONVERT EPOCH VALUES TO HUMAN READABLE UTC TIME
        Epoch= macTimes[0]
        utcTime= time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(modEpoch))
        print(utcTime)
    
'''

''' IMPORT STANDARD LIBRARIES '''
import os       # File System Methods
import sys      # System Methods
import time     # Time Conversion Methods

''' IMPORT 3RD PARTY LIBRARIES '''
from prettytable import PrettyTable

''' DEFINE PSEUDO CONSTANTS '''

# NONE

''' LOCAL FUNCTIONS '''

def EpochToUTC(epochTime):
    
    utcTime= time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(epochTime))
    return utcTime    


def GetFileMetaData(fileName):
    ''' 
        obtain filesystem metadata
        from the specified file
        specifically, fileSize and MAC Times
        
        return True, None, fileSize and MacTimeList
    '''
    try:
        
        metaData         = os.stat(fileName)       # Use the stat method to obtain meta data
        fileSize         = metaData.st_size         # Extract fileSize and MAC Times
        timeLastAccess   = metaData.st_atime
        timeLastModified = metaData.st_mtime
        timeCreated      = metaData.st_ctime
        
        timeLastAccess   =  EpochToUTC(timeLastAccess)
        timeLastModified = EpochToUTC(timeLastModified)
        timeCreated = EpochToUTC(timeCreated)
        
       
        return True, None, fileSize, timeLastModified, timeLastAccess, timeCreated
    
    except Exception as err:
        return False, str(err), None, None, None, None
    
    

''' LOCAL CLASSES '''
# NONE

''' MAIN ENTRY POINT '''

tbl = PrettyTable(['File','Success','Error','File Size','Last Modified','Last Accessed', 'Time Created'])


if __name__ == '__main__':
    
    print("\nWK-2 Solution: Luke Katsel - Version Two\n")

    targetDIR = input('Enter a Directory Path i.e. c:/ >>> ')
    print()
    
    try:
        fileList = os.listdir(targetDIR)
        for eachFile in fileList:
            #print(eachFile)
            path = os.path.join(targetDIR, eachFile)
            #print(path)

            success, errInfo, fileSize, lastMod, lastAccessed, timeCreated = GetFileMetaData(path)
            
            tbl.add_row( [ eachFile,success, errInfo, fileSize, lastMod, lastAccessed, timeCreated ] )
            
        tbl.align = "l" 
        resultString = tbl.get_string(sortby="File", reversesort=True)
        print(resultString)            
          
    except Exception as err:
        print("\n\nScript Aborted     ", "Exception =     ", err)        