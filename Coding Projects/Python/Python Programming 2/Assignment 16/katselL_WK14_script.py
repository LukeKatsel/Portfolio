'''
Luke Katsel
Week 14
11/29/23
'''

import json
import os
import hashlib
from virus_total_apis import PublicApi as VirusTotalPublicApi

# You will need to obtain an API Key from Virus Total
API_KEY = '2d3591885e21c7b31b4bb9e91082aa949d96fed09045a317e3739ec20f7a8ce9'

path = "TARGET"                                     # Target directory to traverse

vt = VirusTotalPublicApi(API_KEY)

report = {}

for (dirpath, dirnames, filenames) in os.walk(path):
    for files in filenames:
        file_path = os.path.join(dirpath, files)    # traverse directory
        
        with open(file_path, "rb") as file:         # open files found
    
            SAMPLE = file.read()
            SAMPLE_MD5 = hashlib.md5(SAMPLE).hexdigest()

            response =  vt.get_file_report(SAMPLE_MD5)
            report[files] = response

            print (json.dumps(response, sort_keys=False, indent=4)) # print reports

with open('virus_total_report.json', 'w') as report_file:
    json.dump(report, report_file, indent=4)        # write reports to json file
    
print("Script done")