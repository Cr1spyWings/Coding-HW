"""
English to Pig-Latin, Pig-Latin to English translator
Author: Chris Wong
Date: 10/25/2022
"""

while True:
    sentence, new_text = "", ""
    line_of_text = str(input("Enter a line of text that you would like translated: ")).lower()
    for c in line_of_text:
        new_text += c if ord("a") <= ord(c) <= ord("z") or c == " " or c == "-" else ""
    words_inputted = new_text.split()
    if words_inputted:
        for word in words_inputted:
            word = (word + "-yay" if word[0] in "aeiouy" else word[1:] + "-" + word[0] + "ay") if "-" not in word else (word[:-4] if "-y" in word[-4: -1] else word[-3] + word[:-4])
            sentence += word + " "
        print("Translated to Pig-Latin") if "-" in sentence else print("Translated to English:")
        print(sentence)
    else:
        break
