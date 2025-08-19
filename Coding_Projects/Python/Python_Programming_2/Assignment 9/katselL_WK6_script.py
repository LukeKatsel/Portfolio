'''
Luke Katsel
Assignment 9
10/4/23
'''

# Python Standard Libaries
import requests                                # Python Standard Library for url requests
import os

# Python 3rd Party Libraries
from bs4 import BeautifulSoup                   # 3rd Party BeautifulSoup Library - pip install Beautifulsoup4

url = 'https://casl.website/'

page = requests.get(url)                        # retrieve a page from your favorite website
soup = BeautifulSoup(page.text, 'html.parser')  # convert the page into soup

images = soup.findAll('img')  # Find the image tags

title = soup.title.string

links = soup.findAll('a')                       # get all the links stored in links variable

with open("webData", 'w') as outFile:
    outFile.write("------------------------Title------------------------\n\n")
    outFile.write(title)                        
    outFile.write("\n\n")
    
    outFile.write("------------------------Links------------------------\n\n")      
    for eachLink in links:
        try:
            newLink = eachLink.get('href')
            outFile.write(newLink)              # write all the links to the file
            outFile.write("\n")  
        except Exception as err:
            print(err)
            continue   
    
    outFile.write("\n\n------------------------Images------------------------\n\n")
    
    for eachImage in images:                    # Process and display each image
        try:
            imgURL = eachImage['src']
            if imgURL[0:4] != 'http':           # If URL path is relative
                imgURL = url+imgURL             # try prepending the base url

            outFile.write(imgURL)               # write image url to file
            outFile.write("\n")
                 
        except Exception as err:
            print(imgURL, err)
            continue    
    print('\n\nScript Complete')
