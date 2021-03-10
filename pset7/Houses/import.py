import csv
import sys
import cs50

if len(sys.argv) != 2:
    print("Usage: python import.py filename")
    sys.exit(0)

# connect to the database
db = cs50.SQL("sqlite:///students.db")

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        # split name and iterate to check for middle name
        splitedName = row['name'].split()
        for name in splitedName:
            firstName = splitedName[0]
            middleName = None if len(splitedName) == 2 else splitedName[1]
            lastName = splitedName[1] if len(splitedName) == 2 else splitedName[2]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);",
            firstName, middleName, lastName, row['house'], row['birth']
        )