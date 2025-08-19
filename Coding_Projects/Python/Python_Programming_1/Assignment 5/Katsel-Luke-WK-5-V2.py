'''
Assignment 5
Luke Katsel
Version: 2
'''
import itertools
import hashlib
import pickle
import os
from prettytable import PrettyTable

pickleFileWrite = open('rainbow.db', 'wb')

rainbowTable = {}

print("Creating Rainbow Table")
for variations in range(4,8):
    for pwTuple in itertools.product("abc123&", repeat=variations):
        pw = ""
        md5Hash = hashlib.md5()
        for eachChr in pwTuple:
            pw = pw+"".join(eachChr)
        pw = bytes(pw, 'ascii')
        md5Hash.update(pw)
        md5Digest = md5Hash.hexdigest()
        rainbowTable[md5Digest] = pw

print("Rainbow Size: ", len(rainbowTable), "\n")

pickle.dump(rainbowTable, pickleFileWrite)                      
pickleFileWrite.close() 

pickleFileRead = open('rainbow.db', 'rb')

retrievedList = pickle.load(pickleFileRead)

listList = list(retrievedList.items())

tbl = PrettyTable(['HASH', 'Password']) 

for md5Hash, password in listList[:5]:
    tbl.add_row( [md5Hash, password] )
    
for md5Hash, password in listList[-5:]:
    tbl.add_row( [md5Hash, password] )    

tbl.align = "l" 
print (tbl)

pickleFileRead.close()



            
            
