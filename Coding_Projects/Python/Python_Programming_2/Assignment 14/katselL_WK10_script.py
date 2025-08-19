'''
Luke Katsel
Week 10
11/1/23
'''

import sys
import os

''' 3rd Party Library '''
from PIL import Image               # pip install pillow

# Pixel tuple index
RED   = 0
GREEN = 1
BLUE  = 2

''' Obtain the Basic image information '''

'''
Image Orientation

         |
         |
y (rows) |
         |
         |     
         -----------------------------
                     x (columns)
'''
 
option = 0
optionDict = {
    0: 'Dead Drop @',
    1: 'Corner of Lexington Ave and E 48th Street',
    2: 'Corner of Madison Ave and E 34th Street',
    3: 'Drop Package in Potted Plant outside Wells Fargo',
    4: 'Drop Package in Gold Gargage Can',
    5: '12 PM Sharp',
    6: '7 AM Sharp',
    7: 'Abort if you see a Red Rose\n',
    88: 'Create New Image',
    99: 'Quit and discard message'
}
codeDict = {
    0: '000',
    1: '001',
    2: '010',
    3: '011',
    4: '100',
    5: '101',
    6: '110',
    7: '111',
}

pixDict = {}
messages = []
count = 0

# Pixel to Modify
r = 0  # Row
c = 0  # Col

img       = Image.open('monalisa.bmp')  

pix = img.load()  
width, height = img.size

print("Hide a Message\n")

while 1:

    for key, value in optionDict.items():
        print('[', key, ']', "\t", value)
        
    print("\n")
    
    option = input("Select Message to Hide: ")
    print("\n\n")
    
    try:
        option = int(option)
    except ValueError:
        print("Invalid input. Please enter a valid number.")    

    if(option == 88 or option == 99):
        break
    
    elif (option > 7 or option < 0):
        print("Invalid option\n")
        
    else:
        try:
            if (count == 0):
                count = 0
            else:
                # Pixel to Modify
                r += 1  # Row
                c += 1  # Col
            
            messageValue = codeDict[option]
            
            redCode = messageValue[0]
            greenCode = messageValue[1]
            blueCode = messageValue[2]
        
            # Read the Pixel
            pixel = pix[c, r]

            redPx = pixel[RED]      # Extract the RGB
            grnPx = pixel[GREEN]
            bluPx = pixel[BLUE]          
            
            
            while (redCode == redPx and greenCode == grnPx and blueCode == bluPx):
                
                if (r == width):
                    c += 1
                    r = 0
                elif (c == height):
                    print("Out of Pixels")
                    break
                else:
                    r += 1
                
                    pixel = pix[c, r]
                
                    redPx = pixel[RED]      # Extract the RGB
                    grnPx = pixel[GREEN]
                    bluPx = pixel[BLUE]    
                
            if messageValue[0] == 0:
                redPx = redPx & 0b11111110
            else:
                redPx = redPx | 0b00000001   
                
            if messageValue[1] == 0:
                grnPx = grnPx & 0b11111110
            else:
                grnPx = grnPx | 0b00000001       
                
            if messageValue[2] == 0:
                bluPx = bluPx & 0b11111110
            else:
                bluPx = bluPx | 0b00000001                           
            
            pixDict[count] = (c, r, redPx, grnPx, bluPx)
            messages.append(option)
            count += 1
            
        except Exception as err:
            print("Steg Failed: ", str(err))  
            break
        
    print("Current message: ")
    
    for eachMessage in messages:
        print('\t', optionDict[eachMessage])
    print('\n')

if (option == 88):
    
    for key, value in pixDict.items():
        pixel = (value[2], value[3], value[4])
        pix[value[0], value[1]] = pixel
    
    # create new image
    newName = input("Name of new Image:")
    
    # Save this as a new image
    img.save(newName)     
    
    print("\nSteganography Done")

elif (option == 99):
    print("Message Discarded")
