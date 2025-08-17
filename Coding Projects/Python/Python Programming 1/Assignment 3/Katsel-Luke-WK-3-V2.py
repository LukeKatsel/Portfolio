'''
WK-3 SCRIPT
Luke Katsel
July 2023
Version 2
'''

# Python Standard Libaries 
import os
import haihfhshlib
import time

# Python 3rd Party Libraries
from prettytable import PrettyTable     # pip install prettytable

# Psuedo Constants

# Local Functions 

def EpochToUTC(epochTime):
    
    utcTime= time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(epochTime))
    return utcTime    


def GetFileMetaData(fileName):
    ''' 
        obtain filesystem metadata
        from the specified file
        specifically, MAC Times and HASH
        
    '''
    #MAC Times
    
    try:
        
        metaData         = os.stat(fileName)       # Use the stat method to obtain meta data
        timeLastAccess   = metaData.st_atime
        timeLastModified = metaData.st_mtime
        timeCreated      = metaData.st_ctime
        
        timeLastAccess   =  EpochToUTC(timeLastAccess)
        timeLastModified = EpochToUTC(timeLastModified)
        timeCreated = EpochToUTC(timeCreated)
        
        #HASH
        
        with open(fileName, 'rb') as target:
            
            fileContents = target.read()
            
            sha512Obj = hashlib.sha512()
            sha512Obj.update(fileContents)
            hexDigest = sha512Obj.hexdigest()        
        
       
        return timeLastModified, timeLastAccess, timeCreated, hexDigest
    
    except Exception as err:
        return str(err), err, err, err

# Local Classes

# Main

targetFolder = input("Enter Target Folder: ")

print("Walking: ", targetFolder, "\n")

tbl = PrettyTable(['AbsPath','FileSize','LastModified','LastAccess','CreatedTime','SHA-256 HASH'])  

for currentRoot, dirList, fileList in os.walk(targetFolder):

    for nextFile in fileList:
        
        fullPath = os.path.join(currentRoot, nextFile)
        absPath  = os.path.abspath(fullPath)
        fileSize = os.path.getsize(absPath)
        
        lastMod, lastAccess, timeCreated, sha256Hash = GetFileMetaData(absPath)
        
        tbl.add_row( [ absPath, fileSize, lastMod, lastAccess, timeCreated, sha256Hash] ) 

tbl.align = "l" # align the columns left justified
# display the table
print (tbl.get_string(sortby="FileSize", reversesort=True))


print("\nScript-End\n")