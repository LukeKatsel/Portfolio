'''
WK-6 SCRIPT
CYBV 312
Luke Katsel
August 2023
'''

# Python Standard Libaries 
import os
import re
import logging
import platform
import socket
import uuid

import psutil  # pip install psutil

def getSystemInfo():
    try:
        info={}
        info['platform']=platform.system()
        info['platform-release']=platform.release()
        info['platform-version']=platform.version()
        info['architecture']=platform.machine()
        info['hostname']=socket.gethostname()
        info['ip-address']=socket.gethostbyname(socket.gethostname())
        info['mac-address']=':'.join(re.findall('..', '%012x' % uuid.getnode()))
        info['processor']=platform.processor()
        info['ram']=str(round(psutil.virtual_memory().total / (1024.0 **3)))+" GB"
        return info
    except Exception as e:
        logging.exception(e)
        return False


def main():
    
    # Remove any old logging script
    if os.path.isfile('Luke-ScriptLog.txt'):   # REPLACE YOURNAME with Your Name
        os.remove("Luke-ScriptLog.txt")
    
    # configure the python logger, Replace YOURNAME
    logging.basicConfig(filename='Luke-ScriptLog.txt', level=logging.DEBUG, format='%(process)d-%(levelname)s-%(asctime)s %(message)s')
    logging.info("Script Start\n")
    
    investigator = input("Investigator Name:  ")   # Enter Your Name at this prompt
    organization = input("Class Code  :       ")   # Enter the Class at this prompt i.e. CYBV-312 YOUR SECTION
    userFile = input('File:  ')
    
    sysInfo = getSystemInfo()
    
    if sysInfo:
        
        logging.info("Investigator:  " +investigator)
        logging.info("Organization:  " +organization)
        logging.info('===============================\n')
        logging.info("***** System Information *****")
        
        for key, value in sysInfo.items():
            keyValue = '   '+key+':  '+value
            logging.info(keyValue)
            
        logging.info('===============================\n')
        
        
        with open(userFile, 'r') as test:
            data = test.read()
            logging.info("User File:", userFile)    
            logging.info()
        
       
if __name__ == '__main__':
    
    print("\n\nWeek-6 Logging Starter Script - Luke \n")
    main()
    print("\nScript End")

