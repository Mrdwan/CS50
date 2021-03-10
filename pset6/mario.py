from cs50 import get_int

while True:
    height = get_int("height:")
    if height > 0 and height < 9:
        break


for i in range(1, height + 1):
    for j in range(height):
        if j > height - i - 1:
            print("#", end="")
        else:
            print(" ", end="")

    print(" " * 2, end="")

    for l in range(i):
        print("#", end="")
    print()