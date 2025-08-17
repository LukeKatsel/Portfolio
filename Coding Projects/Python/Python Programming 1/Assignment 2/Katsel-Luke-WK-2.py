'''
Script:  First Script
Author:  Luke Katsel
Date:    3/26/2023
Version: 1
Purpose: ENTER PURPOSE

'''

''' IMPORT STANDARD LIBRARIES '''
import os       # File System Methods
import sys      # System Methods
import time     # Time Conversion Methods

''' IMPORT 3RD PARTY LIBRARIES '''
# NONE

''' DEFINE PSEUDO CONSTANTS '''

# NONE

''' LOCAL FUNCTIONS '''

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
        
        utcMod = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(timeLastModified))        
            
        utcAccess = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(timeLastAccess))
                
        utcCreated = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(timeCreated))                
        
        macTimeList = [utcMod, utcAccess, utcCreated] # Group the MAC Times in a List
        return True, None, fileSize, macTimeList
    
    except Exception as err:
        return False, str(err), None, None

''' LOCAL CLASSES '''
# NONE

''' MAIN ENTRY POINT '''

if __name__ == '__main__':
    
    print("\nWK-2 Solution: Luke Katsel - Version One\n")

    targetDIR = input('Enter a Directory Path i.e. c:/ >>> ')
    print()
    
    try:
        fileList = os.listdir(targetDIR)
        for eachFile in fileList:
            print(eachFile)
            path = os.path.join(targetDIR, eachFile)
            print(path)

            success, errInfo, fileSize, macList = GetFileMetaData(path)
            
            print(success)
            print(errInfo)
            print(fileSize)
            print(macList)
            
            print("="*50)
            
            # Your additional script code here
            
    except Exception as err:
        print("\n\nScript Aborted     ", "Exception =     ", err)        