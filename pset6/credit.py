from cs50 import get_int, get_string

counter = 0
sum = 0
digit = 0
firstTwoDigits = 0
firstOneDigit = 0

# get user credit
while True:
    cardNumber = get_int("card:")
    if (cardNumber > 0):
        break

# assign credit to another var
number = cardNumber;

# count credit
while number != 0:
    if (counter % 2 == 0):
        sum += (number % 10)
    else:
        # odd
        oddNumber = (number % 10) * 2
        if oddNumber < 9:
            sum += oddNumber
        else:
            while oddNumber > 0:
                sum += (oddNumber % 10)
                oddNumber //= 10

    # remove last digit then count
    number //= 10
    counter += 1

if sum % 10 > 0:
    # die if invalid algorithm
    print("INVALID")
    exit(0)

if counter == 13:
    firstOneDigit = cardNumber // 1000000000000

    if firstOneDigit == 4:
        print("VISA")
    else:
        print("INVALID")

if counter == 15:
    # american
    digit = cardNumber // 10000000000000
    if digit in [34, 37]:
        print("AMEX")
    else:
        print("INVALID")
elif counter == 16:
    firstTwoDigits = cardNumber // 100000000000000
    firstOneDigit = cardNumber // 1000000000000000

    if firstTwoDigits in [51, 52, 53, 54, 55]:
        print("MASTERCARD")
    elif firstOneDigit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")