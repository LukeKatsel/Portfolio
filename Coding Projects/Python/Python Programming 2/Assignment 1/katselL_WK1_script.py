'''
Week One Assignment - Simple String Searching 
'''

'''
Given excerpt from the hacker manifesto 

Complete the script below to do the following:
1) Add your name, date, assignment number to the top of this script
2) Convert the string to all lower case
3) Count the number characters in the string
4) Count the number of words in the string
5) Sort the words in alphabetical order
6) Search the excerpt variable given below
   For the following and report how many occurances of each are found
   scandal
   arrested
   er
   good
   tomorrow
7) Submit
   NamingConvention: lastNameFirstInitial_Assignment_.ext
   for example:  alharthiD_WK1_script.py
                 alharthiD_WK1_screenshot.jpg
   A) Screenshot of the results in WingIDE
   B) Your Script
'''

excerpt = " Another one got caught today, it's all over the papers. Teenager Arrested in Computer Crime Scandal, Hacker Arrested after Bank Tampering kids. They're all alike"

''' Your work starts here '''
'''
Luke Katsel 
8/28/23 
Week 1 Assignment
'''

print("String:", excerpt)

print("Lower case String:", excerpt.lower())

print("Number of Characters:", len(excerpt))

words = excerpt.split()

print("Number of Words:", len(words))

wordsSorted = sorted(words)

print(wordsSorted)

excerptLower = excerpt.lower()

s = excerptLower.count("scandal")
a = excerptLower.count("arrested")
e = excerptLower.count("er")
g = excerptLower.count("good")
t = excerptLower.count("tomorrow")
    
print("scandal =", s, "times")

print("arrested =", a, "times")

print("er =", e, "times")

print("good found =", g, "times")

print("tomorrow =", t, "times")
