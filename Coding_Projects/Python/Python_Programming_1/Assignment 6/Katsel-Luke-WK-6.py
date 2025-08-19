# Python Standard Libraries 
import os
import re
import logging
import platform
import socket
import uuid
import hashlib

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
    if os.path.isfile('Luke-ScriptLog.txt'):   
        os.remove("Luke-ScriptLog.txt")
    
    # configure the python logger, Replace YOURNAME
    logging.basicConfig(filename='Luke-ScriptLog.txt', level=logging.DEBUG, format='%(process)d-%(levelname)s-%(asctime)s %(message)s')
    logging.info("Script Start\n")
    
    investigator = input("Investigator Name:  ")   # Enter Your Name at this prompt
    organization = input("Class Code  :       ")   # Enter the Class at this prompt i.e. CYBV-312 YOUR SECTION
    
    sysInfo = getSystemInfo()
    
    if sysInfo:
        logging.info("Investigator: %s", investigator)
        logging.info("Organization: %s", organization)
        
        root_path = 'C:/Users/katse/Documents/Classes/CYBV 312'  # Replace with your folder path
        for root, dirs, files in os.walk(root_path):
            for file in files:
                filename = os.path.join(root, file)
                size = os.path.getsize(filename)
                modTime = os.path.getmtime(filename)
                accessTime = os.path.getatime(filename)
                createTIme = os.path.getctime(filename)
                
                with open(filename, 'rb') as f:
                    contents = f.read()
                    sha256 = hashlib.sha256(contents).hexdigest()
                    
                logging.info("File: %s", filename)
                logging.info("Size: %d bytes", size)
                logging.info("Modified: %s", modTime)
                logging.info("Accessed: %s", accessTime)
                logging.info("Created: %s", createTIme)
                logging.info("SHA256 Hash: %s\n", sha256)

if __name__ == '__main__':
    
    print("\n\nWeek-6 Logging Starter Script - Luke \n")
    main()
    print("\nScript End")