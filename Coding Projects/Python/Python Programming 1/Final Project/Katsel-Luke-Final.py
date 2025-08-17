'''
Luke Katsel
Final Script
May 2023
'''
import re

print("Final Script")
with open("mem.raw", 'rb') as target:  # assumes that mem.raw is in the same folder as script
    
    contents = target.read() # read the entire contents of the file
    
    txt = re.sub(b"[^A-Za-z']", b' ', contents)  # strip all non alpha characters
    txt = txt.lower()                            # convert all to lower case
    txt = txt.decode("utf-8")                    # convert to simple ASCII
    
    wordList = txt.split()  # Create a list of possible words
    print(len(wordList))
    
    kernelCount = wordList.count("kernel")
    encryptCount = wordList.count("encrypt")
    fairwitnessCount = wordList.count("fairwitness")    
    
    print("kernelCount: ",      kernelCount)
    print("encryptCount:",      encryptCount)
    print("fairwitnessCount: ", fairwitnessCount)
    
