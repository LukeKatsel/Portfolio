
'''
Luke Katsel
Week Two Assignment 1 - File Processing
Sep. 5  2023
'''

'''
Complete the script below to do the following:
1) Add your name, date, and assignment number to the top of this script
2) Open the file redhat.txt 
   a) Iterate through each line of the file
   b) Split eachline into individual fields (hint str.split() method)
   c) Examine each field of the resulting field list
   d) If the word "worm" appears in the field then add the worm name to the set of worms
   e) Once you have processed all the lines in the file
      sort the set 
      iterate through the set of worm names
      print each unique worm name 
3) Submit
   NamingConvention: lastNameFirstInitial_Assignment_.ext
   for example:  alharthiD_WK2-1_script.py
                 alharthiD_WK2-2_screenshot.jpg
   A) Screenshot of the results in WingIDE
   B) Your Script
'''

import os

uniqueWorms = set()
word = "worm"
with open("redhat.txt", 'r') as logFile:
    for eachLine in logFile:
        for eachWord in eachLine.split():
            if word in eachWord.lower():
                uniqueWorms.add(eachWord)
    
sorted(uniqueWorms)
for eachItem in uniqueWorms:
    print(eachItem)
