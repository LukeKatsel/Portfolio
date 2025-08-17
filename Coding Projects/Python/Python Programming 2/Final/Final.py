'''
Luke Katsel
Final Project
12/6/23
'''

# Python Standard Libaries
import requests                              
import nltk
from nltk import pos_tag
import os
import re

# Python 3rd Party Libraries
from prettytable import PrettyTable
from bs4 import BeautifulSoup

class classNLTK:                                # class to perform natural language processing
      def __init__(self):
            self.tokens = []                    # variable to hold the individual words
            self.posTags = []                   # variable to hold the position tags

      def GetTokens(self, RawString):           # function to get the individual words and tags
            
            self.tokens = nltk.word_tokenize(RawString.lower())   # convert all words to lowercase and tokenize them
            self.posTags = pos_tag(self.tokens)                   # tag the word positions
                  
      def printVocabulary(self):                # function to print unique words
            
            print("\n\n---------------------Unique Words------------------------\n\n")
            
            vocabFreq = nltk.FreqDist(self.tokens)                # Compute frequency distribution
      
            tbl = PrettyTable(["Unique Word", "Occurs"])          # create pretty table
            for word, freq in vocabFreq.items():
                  tbl.add_row([word, freq])                       # add row for each unique word and occurance
      
            tbl.sortby = "Occurs"
            tbl.reversesort = True
      
            print(tbl)                                            # print the pretty table
      
      def printVerbs(self):                                       # function to print the unique verbs
            
            print("\n\n---------------------Unique Verbs--------------------------\n\n")
            verbs = []                                            # variable to hold verbs
            for word, tag in self.posTags:
                  if tag.startswith('VB'):
                        verbs.append(word)                        # add the words identified as possible verbs to verbs variable
                        
            uniqueVerbs = list(set(verbs))                        # from the list of verbs create a set of unique verbs
            for verb in uniqueVerbs:
                  print(verb)                                     # print them
                        
      def printNouns(self):                                       # function to print unique nouns
            
            print("\n\n---------------------Unique Nouns--------------------------\n\n")
            nouns = []                                            # variable to hold nouns
            for word, tag in self.posTags:
                  if tag.startswith('NN'):      
                        nouns.append(word)                        # add the words identified as possible nouns to nouns variable
                        
            uniqueNouns = list(set(nouns))                        # create a set of unique nouns
            for noun in uniqueNouns:
                  print(noun)                                     # print the nouns

zipPatt = re.compile(r'\d{5}(?:-\d{4})?')
phonePatt = re.compile(r'\(?\d{3}\)?-? *\d{3}-? *-?\d{4}')        # regex patterns for zipcodes and phone numbers

url = 'https://casl.website/'                                     # url for site to crawl

page = requests.get(url)                                          # request the page
soup = BeautifulSoup(page.text, 'html.parser')                    # convert the page into soup

textContent = ""                                                  # create a string variable to hold all the raw text
    
print("\n------------------------Links------------------------\n\n")      
links = soup.findAll('a')                                         # get all the links and store in links variable

for eachLink in links:                                            # loop to get the links and print to screen
      try:
            newLink = eachLink.get('href')
            if newLink is not None:
                  print(newLink, "\n") 
                  
      except Exception as err:
            print(newLink, err)
            continue
    
print("\n\n------------------------Images------------------------\n\n")
images = soup.findAll('img')                                      # Find the image tags
    
for eachImage in images:                                          # loop to process and display each image
      try:
            imgURL = eachImage['src']
            if imgURL[0:4] != 'http':                             # If URL path is relative
                  imgURL = url+imgURL                             # try prepending the base url

            print(imgURL, "\n")                                   # print image url
                 
      except Exception as err:
            print(imgURL, err)
            continue   
    
print("\n\n---------------------Phone Numbers--------------------\n\n")
phoneNumbers = re.findall(phonePatt, page.text)                   # find all of the phone numbers in the website

for eachNumber in phoneNumbers:                                   # loop to print each phone number
      print(eachNumber, "\n")                                       
    
print("\n\n---------------------Zip Codes------------------------\n\n")
zipCodes = re.findall(zipPatt, page.text) 

for eachZipCode in zipCodes:                                      # loop to print each zip code
      print(eachZipCode, "\n")            
      

for eachLink in links:                                            # loop to process each link for crawling
      linkUrl = eachLink.get('href')
      if linkUrl is not None:                                     
            if linkUrl.startswith('http'):                        # Check if the link is relative
                  continue                                        # if it is (outside link) -> skip it
            else:
                  linkUrl = url + linkUrl                         # if its not -> make it an absolute URL
        
                  linkPage = requests.get(linkUrl)                # request the site
                  linkSoup = BeautifulSoup(linkPage.text, 'html.parser')      # make it into soup
              
                  linkText = linkSoup.get_text(separator=' ')     # Get text content of the page
                  textContent += linkText + "\n\n"                # Append text content to the variable

nltkObj = classNLTK()                                             # create a classNLTK variable
nltkObj.GetTokens(textContent)                                    # call the tokenizer function
nltkObj.printVocabulary()                                         # call the unique vocab function
nltkObj.printVerbs()                                              # call the unique verb function
nltkObj.printNouns()                                              # call the unique noun function

print('\n\nScript Complete')
