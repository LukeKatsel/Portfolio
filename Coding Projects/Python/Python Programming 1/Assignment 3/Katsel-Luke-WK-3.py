'''
Script:  First Script
Author:  Chet Hosmer
Date:    July 2020
Version: .50
Purpose: script Description
'''

''' IMPORT STANDARD LIBRARIES '''
import os       # File System Methods
import sys      # System Methods
import time     # Time Conversion Methods
import hashlib   # Python standard library hashlib

''' IMPORT 3RD PARTY LIBRARIES '''
from prettytable import PrettyTable

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
        
        macTimeList = [timeLastModified, timeCreated, timeLastAccess]   # Group the MAC Times in a List
        return True, None, fileSize, macTimeList
    
    except Exception as err:
        return False, str(err), None, None

''' LOCAL CLASSES '''
# NONE

''' MAIN ENTRY POINT '''

def main():
    
    print("\nWK-2 Final Solution: Professor Hosmer\n")

    targetDIR = input('Enter a Directory Path i.e. c:/ >>> ')
    print()
    
    resultTable = PrettyTable(['AbsPath', 'FileSize', 'LastModified', 'LastAccessed', 'LastCreated', 'SHA-256HASH'])
    
    resultList = []
    
    try:
        fileList = os.walk(targetDIR)
        for eachFile in fileList:

            path = os.path.join(targetDIR, eachFile)
            path = os.path.abspath(path)

            success, errInfo, fileSize, macList = GetFileMetaData(path)     
            
            if success:
                
                modTime = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(macList[0]))
                accTime = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(macList[1]))               
                creTime = time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(macList[2]))  
                
                with open(eachFile, 'rb') as target:
                    
                    fileContents = target.read()
                    
                    sha512Obj = hashlib.sha512()
                    sha512Obj.update(fileContents)
                    sha256Hash = sha512Obj.hexdigest()
                

                resultTable.add_row( [ path, fileSize, modTime, accTime, creTime, sha256Hash] )                    
                
            else:
                print("Fail:      ", path, "Exception =     ", errInfo)

        resultTable.align = "l" 
        print(resultTable.get_string(sortby="Size", reversesort=True))        
              
    except Exception as err:
        print("\n\nScript Aborted     ", "Exception =     ", err)        
        
        
if __name__ == '__main__':
    
    main()
    print("Script End")
    
