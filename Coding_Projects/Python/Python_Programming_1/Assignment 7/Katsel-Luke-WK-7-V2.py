'''
Searching for Images with PIL
Luke Katsel
August 2023
Version 2
'''

import sys
import os
from PIL import Image
from prettytable import PrettyTable


tbl = PrettyTable(['File', 'Ext', 'Format', 'Width', 'Height', 'Mode']) 

print("\nWeek 7 Script\n")
path = input("\nFolder to Examine: ")

try:
    
  for currentRoot, dirList, fileList in os.walk(path):
    for nextFile in fileList:
        
          fullPath = os.path.join(currentRoot, nextFile)
          absPath  = os.path.abspath(fullPath)   
          ext = os.path.splitext(nextFile)[1]
          try:
        
              with Image.open(absPath) as im:
                  tbl.add_row( [fullPath, ext, im.format, im.width, im.height, im.mode] )
                   
          except:
            print('test')
            tbl.add_row( [fullPath, ext, 'N/A', 'N/A', 'N/A', 'N/A'] )  
                
except Exception as err: 
                print('Cannot process  ', err)
        
tbl.align = "l" 
print (tbl.get_string(sortby="Format", reversesort=False))         

print("Script Done")
