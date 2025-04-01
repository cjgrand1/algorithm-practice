This program is designed to work with the Unix/Linux compiler. This program converts english to morse code, and morse code to english.

use the following command line input to run the program:
./MorseCode inputfile command outputfile

valid commands:
"-mc": to convert english to morse code
"-e": to convert morse code into english

This program was designed as practice with c/c++, and uses c strings. Enlish files should be limited to 255 characters (including spaces), while morse code files should output to at most 255 characters (7 * 255 = 1785), or 1785 characters.

results will be outputed to a given file, output is formated like such: "the cat" becomes -|....|.|/|-.-.|.-|-