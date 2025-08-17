'''
Luke Katsel
Assignment 9
10/4/23
'''

# Python Standard Libaries
import requests                                 # Python Standard Library for url requests
import os
import re

# Python 3rd Party Libraries
from bs4 import BeautifulSoup                   # 3rd Party BeautifulSoup Library - pip install Beautifulsoup4

street_address_pattern = re.compile(r'\d{1,4} [\w\s]{1,20}(?:street|st|avenue|ave|road|rd|highway|hwy|square|sq|trail|trl|drive|dr|court|ct|parkway|pkwy|circle|cir)\W?(?=\s|$)', re.IGNORECASE)
po_box_pattern =  re.compile(r'\b(?:P\.?O\.?|P(?:ost)?[-. ]?O\.?(?:ffice)?)?[-. ]?Box\b(?:\s\d+)?\b', re.IGNORECASE)
zip_code_pattern = r'\b\d{5}(?:-\d{4})?\b'

urls = ['https://www.aamu.edu/index.html', 'http://www.tuskegee.edu/', 'http://www.ua.edu/', 'http://www.uab.edu/home/', 
        'http://www.uah.edu/', 'http://www.southalabama.edu/', 'http://www.uaf.edu/', 'http://www.amsamoa.edu/', 'https://www.asu.edu/',
        'http://nau.edu/', 'https://www.arizona.edu/', 'https://www.astate.edu/', 'http://www.uark.edu/', 'http://www.uapb.edu/',
        'http://www.calpoly.edu/', 'https://csun.edu/', 'http://www.sdsu.edu/', 'http://www.sjsu.edu/discover/index.html', 'http://www.berkeley.edu/index.html',
        'http://ucdavis.edu/index.html', 'http://www.uci.edu/', 'http://www.ucla.edu/', 'http://www.ucmerced.edu/', 'http://www.ucr.edu/',
        'http://www.ucsd.edu/', 'http://www.ucsb.edu/', 'http://www.ucsc.edu/', 'http://www.mines.edu/']

with open("webData.txt", 'a') as outFile:
    for eachUrl in urls:
        page = requests.get(eachUrl)                        # retrieve a page from your favorite website
        soup = BeautifulSoup(page.text, 'html.parser')  # convert the page into soup
        
        po_boxes = re.findall(po_box_pattern, page.text)
        street_addresses = re.findall(street_address_pattern, page.text)
        zip_codes = re.findall(zip_code_pattern, page.text)
        
        for street_address in street_addresses:
            print(street_address)
            print("\n\n")
            
        for zip_code in zip_codes:
            print(zip_code)
            print("\n\n") 
            
        for po_box in po_boxes:
            print(po_box)
            print("\n\n")    
    
        outFile.write("------------------------")
        outFile.write(eachUrl)
        outFile.write("------------------------\n\n")
        
        for street_address in street_addresses:
            outFile.write(street_address)
            outFile.write("\n\n")
            
        for zip_code in zip_codes:
            outFile.write(zip_code)
            outFile.write("\n\n") 
            
        for po_box in po_boxes:
            outFile.write(po_box)
            outFile.write("\n\n")            

print('\n\nScript Complete')
