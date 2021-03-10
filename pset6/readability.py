from cs50 import get_string


text = get_string("Text:")
textCount = len(text)
letters = 0
words = 0
sentences = 0
isWord = False
isSentence = False

for letter in text:
    if letter.isalpha():
        # false means that this is the start of a new word
        if not isWord:
            isWord = True
            words += 1

        # false means that this is the start of a new sentence
        if not isSentence:
            isSentence = True
            sentences += 1

        letters += 1
    elif letter == " ":
        # new word begins if it's white space
        isWord = False
    elif letter in ['.', '!', '?']:
        # new sentence begins if it's the above marks
        isSentence = False

# printf("letters: %i\n", letters);
# printf("words: %i\n", words);
# printf("sentences: %i\n", sentences);

L = (letters / words) * 100
S = (sentences / words) * 100

# printf("L: %f\n", L);
# printf("S: %f\n", S);

index = round((0.0588 * L) - (0.296 * S) - 15.8)

# printf("index: %i\n", index);

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")