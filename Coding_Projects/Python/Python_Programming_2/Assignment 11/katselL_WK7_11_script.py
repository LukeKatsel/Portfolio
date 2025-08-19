'''
Luke Katsel
Assignment 11
10/11/23
'''

import socket           # Import Python Standard Socket Library
import sys

print("Client Application")
print("Establish a connection to a server")
print("Available on the same host using PORT 5555")

PORT = 5555          # Port Number of Server
    
try:
    # Create a Socket
    clientSocket = socket.socket()
    
    # Get my local host address
    localHost = socket.gethostname()
    
    print("\nAttempt Connection to: ", localHost, PORT)
    
    clientSocket.connect((localHost, PORT))
    
    # Sending message if there was a connection
    print("Socket Connected ...")
    print("Sending Message to Server")
    
    while True:
        msg = input("Enter Message to Send or EXIT to End: ")
        messageBytes = bytes(str(msg).encode("utf-8"))
        clientSocket.sendall(messageBytes)
    
        hashVal = clientSocket.recv(2048)
        print(hashVal)
    
    
    buffer = clientSocket.recv(2048)
    print(buffer)
    
    
except Exception as err:
    sys.exit(err)

            
