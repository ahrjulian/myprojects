
import cs50
import numpy as np
#readabiliy python
text = cs50.get_string("Text:")#Text input
#string len(text)

letters = 0
words = 1
sentences = 0


for c in text:
    if c.isalpha():
        letters += 1
    elif c.isspace():
        words += 1
    elif (c == "."or c == "!" or c == "?"):
        sentences += 1

L = (letters / words) * 100
S = (sentences / words) * 100

readability_index = 0.0588 * L - 0.296 * S - 15.8 # L: average number of letters per 100 words  S: average number of sentences per 100 words

Grade_level = round(readability_index)

if readability_index < 1:
    print("Before Grade 1")
elif readability_index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {Grade_level}")


