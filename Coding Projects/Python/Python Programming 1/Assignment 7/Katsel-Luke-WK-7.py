'''Searching for Images with PIL
Luke Katsel
CYBV 312
April 2023
'''

import sys
import os
from PIL import Image
from prettytable import PrettyTable

def process_image(image_path):
    ext = os.path.splitext(image_path)[1]
    try:
        with Image.open(image_path) as im:
            table.add_row([image_path, ext, im.format, im.width, im.height, im.mode])
    except Exception as err:
        print("Error processing image: ", image_path)

extracted_folder = "extracted_photos"

# Create a PrettyTable
table = PrettyTable()
table.field_names = ["File", "Ext", "Format", "Width", "Height", "Mode"]

# Iterate over files in the extracted folder
folder_path = os.path.join(extracted_folder, "")
for file_name in os.listdir(folder_path):
    file_path = os.path.join(folder_path, file_name)
    if os.path.isfile(file_path):
        process_image(file_path)

# Display the PrettyTable
print(table)

print("Script Done")