import csv
from sys import argv, exit
from cs50 import get_int, get_string

if len(argv) != 3:
    print("Usage: dna.py csv txt")
    exit(1)

with open(argv[1], "r") as file:
    reader = list(csv.reader(file))
    reader[0].remove("name")
    i = reader[0]

with open(argv[2], "r") as sequence:
    data = sequence.read()

dna = []

for STR in i:
    count = 0
    maxCount = 0
    lastPosition = 0
    offset = len(STR)

    for position in range(len(data)):
        if data[position:position + offset] == STR:
            if lastPosition == position - offset:
                count += 1
            else:
                count = 1
            if maxCount < count:
                maxCount = count

            lastPosition = position
    dna.append(maxCount)

dna = list(map(str, dna))

persons = list(reader)
persons.pop(0)

returnValue = "No match"
# match the person
for person in persons:
    if person[1:] == dna:
        returnValue = person[0]
        break

print(returnValue)