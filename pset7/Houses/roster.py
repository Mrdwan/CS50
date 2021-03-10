import csv
import sys
import cs50

if len(sys.argv) != 2:
    print("Usage: python roster.py house")
    sys.exit(0)

# connect to the database
db = cs50.SQL("sqlite:///students.db")

students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

for student in students:
    if student['middle'] == None:
        print(f"{student['first']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['middle'] } {student['last']}, born {student['birth']}")