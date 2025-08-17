import itertools
import hashlib
import pickle
from prettytable import PrettyTable

characters = "abc123&"
min_length = 4
max_length = 7

# List of all possible passwords of lengths 4-7
passwords = []
for length in range(min_length, max_length + 1):
    for permutation in itertools.product(characters, repeat=length):
        password = "".join(permutation)
        passwords.append(password)

# Dictionary of password hashes
rainbow_table = {}
for password in passwords:
    md5_hash = hashlib.md5(password.encode()).hexdigest()
    rainbow_table[md5_hash] = password

# Serialized rainbow table and save it as rainbow.db
with open("rainbow.db", "wb") as f:
    pickle.dump(rainbow_table, f)

# Pretty table to display the first and last 5 entries
table = PrettyTable()
table.field_names = ["MD5 HASH VALUE", "PASSWORD"]
for i, (hash, password) in enumerate(rainbow_table.items()):
    if i < 5:
        table.add_row([hash, password])
    elif len(rainbow_table) - i <= 5:
        table.add_row([hash, password])

print(table)