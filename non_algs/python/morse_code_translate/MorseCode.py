#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def englishToMorse(char):
    match char.lower():
        case 'a':
            return ".-"
        case 'b':
            return "-..."
        case 'c':
            return "-.-."
        case 'd':
            return "-.."
        case 'e':
            return "."
        case 'f':
            return "..-."
        case 'g':
            return "--."
        case 'h':
            return "...."
        case 'i':
            return ".."
        case 'j':
            return ".---"
        case 'k':
            return "-.-"
        case 'l':
            return ".-.."
        case 'm':
            return "--"
        case 'n':
            return "-."
        case 'o':
            return "---"
        case 'p':
            return ".--."
        case 'q':
            return "--.-"
        case 'r':
            return ".-."
        case 's':
            return "..."
        case 't':
            return "-"
        case 'u':
            return "..-"
        case 'v':
            return "...-"
        case 'w':
            return ".--"
        case 'x':
            return "-..-"
        case 'y':
            return "-.--"
        case 'z':
            return "--.."
        case _:
            return "eeee"
        
def morseToEnglish(val):
    if val == "/":
        return " "
    elif val == ".-":
        return "a"
    elif val == "-...":
        return "b"
    elif val == "-.-.":
        return "c"
    elif val == "-..":
        return "d"
    elif val == ".":
        return "e"
    elif val == "..-.":
        return "f"
    elif val == "--.":
        return "g"
    elif val == "....":
        return "h"
    elif val == "..":
        return "i"
    elif val == ".---":
        return "j"
    elif val == "-.-":
        return "k"
    elif val == ".-..":
        return "l"
    elif val == "--":
        return "m"
    elif val == "-.":
        return "n"
    elif val == "---":
        return "o"
    elif val == ".--.":
        return "p"
    elif val == "--.-":
        return "q"
    elif val == ".-.":
        return "r"
    elif val == "...":
        return "s"
    elif val == "-":
        return "t"
    elif val == "..-":
        return "u"
    elif val == "...-":
        return "v"
    elif val == ".--":
        return "w"
    elif val == "-..-":
        return "x"
    elif val == "-.--":
        return "y"
    elif val == "--..":
        return "z"
    else:
        return "?"

try:
    # try to read in an english file to convert to morse code
    file = open(r"absolute\path\short.txt", "r") # replace with absolute path of short.txt
    output = ""

    for row in file:
        words = row.split(' ')
        newline = words[-1].find("\n") # remove newline characters from end of sentence
        if newline != -1:
            words[-1] = words[-1][0:newline]
        #print(words)

        for i, word in enumerate(words):
            for j, char in enumerate(word):
                if j != len(word) - 1:
                    output += englishToMorse(char) + "|"
                else:
                    output += englishToMorse(char)
            if i != len(words) - 1:
                output += "|\|"
        output += "\n"

    print("morse code:\n" + output)
    file.close()
except FileNotFoundError:
    print("File not found")

try:
    # try to read in a morse code file to convert to english
    file = open(r"absolute\path\shortmc.txt", "r") # replace with absolute path of shortmc.txt
    output = ""

    for row in file:
        words = row.split('|')
        newline = words[-1].find("\n") # remove newline characters from end of sentence
        if newline != -1:
            words[-1] = words[-1][0:newline]
        #print(words)

        for i, word in enumerate(words):
            if i != len(words) - 1:
                output += morseToEnglish(word)
            else:
                output += morseToEnglish(word) + "\n"

    print("english:\n" + output)
except FileNotFoundError:
    print("File not found")