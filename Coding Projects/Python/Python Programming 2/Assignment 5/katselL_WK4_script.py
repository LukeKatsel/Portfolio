'''
Luke Katsel 
Assignment 5
9/18/2023
'''

import os
import sys

from prettytable import PrettyTable
from PIL import Image


tbl = PrettyTable(['Image?', 'File', 'FileSize', 'Ext', 'Format', 'Width', 'Height', 'Type'])

directory = input("Enter a directory to scan: ")

try:
    
    fileList = os.listdir(directory)                        # Make sure user entered Directory
except Exception as err:
    sys.exit("Err: "+str(err))
    
try:
    
    for eachFile in fileList:                               # Itterate through files in diresctory
        path = os.path.join(directory, eachFile)
        
        img = Image.open(path)                              #open file as image
        split = os.path.splitext(path)
        
        try:                                                #if it is an image do these things
            img.verify()
            isImage = ("Yes")
        except Exception:
            isImage = ("No")
        absPath = path
        size = os.path.getsize(path)
        ext = split[1]
        imageFormat = img.format
        width = img.width
        height = img.height
        Imagetype = img.mode
    
        tbl.add_row([isImage, absPath, size, ext, imageFormat, width, height, Imagetype])
        
except Exception as err:
    sys.exit("Err: "+str(err))


tbl.align='l'
tbl.hrules=1
output = tbl.get_string()
#output = tbl.get_string(sortby='Type')

print(output)
