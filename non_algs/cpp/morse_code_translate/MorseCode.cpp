#include <string.h>

#include <fstream>
#include <iostream>
using namespace std;

const char* englishToMorse(char);
char morseToEnglish(const char*);

int main(int argc, char** argv) {
  if (argc == 4) {
    char* file = argv[1];    // read in input file
    char* print = argv[2];   // read in print command
    char* output = argv[3];  // read in output file

    ifstream infile(file);
    ofstream outfile(output);

    if (strcmp(print, "-mc") == 0 && infile.is_open()) {
      // for converting english to morse code
      //(requires valid file being read in)
      char buffer[255];  // limit of 255 words

      while (infile.getline(buffer, 255)) {
        char* token = strtok(buffer, " ");  // first read

        bool first = true;
        while (token != NULL) {
          // avoid adding space indicator on first loop
          if (!first) outfile << "|/|";
          first = false;

          // convert each word's character into morse code
          for (size_t i = 0; i < strlen(token); i++) {
            outfile << englishToMorse(token[i]);
            // don't add character separator on last character
            if (i != (strlen(token) - 1)) outfile << "|";
          }

          token = strtok(NULL, " ");  // get next word
        }
        outfile << "\n";
      }
    } else if (strcmp(print, "-e") == 0 && infile.is_open()) {
      // for converting morse code into english
      // (requires valid file being read in)
      char buffer[1785];  // limit of 255 words (worse case morse code is 7
                          // characters (----|/|) * 255 words)

      while (infile.getline(buffer, 1785)) {
        char* token = strtok(buffer, " ");  // first read

        while (token != NULL) {
          // printf("%s\n", token);

          char* word = strtok(token, "|");  // read in words seperated by |
          while (word != NULL) {
            outfile << morseToEnglish(word);

            word = strtok(NULL, "|");
          }

          token = strtok(NULL, " ");  // get next word
        }
        outfile << "\n";
      }
    } else {
      printf(
          "expected input: ./executable inputfile command outputfile\nvalid "
          "commands: -mc, -e\n");
    }

    infile.close();
    outfile.close();
  } else {
    printf(
        "expected input: ./executable inputfile command outputfile\nvalid "
        "commands: -mc, -e\n");
  }
}

const char* englishToMorse(char val) {
  switch (val) {
    case 'a':
    case 'A':
      return ".-";
      break;
    case 'b':
    case 'B':
      return "-...";
      break;
    case 'c':
    case 'C':
      return "-.-.";
      break;
    case 'd':
    case 'D':
      return "-..";
      break;
    case 'e':
    case 'E':
      return ".";
      break;
    case 'f':
    case 'F':
      return "..-.";
      break;
    case 'g':
    case 'G':
      return "--.";
      break;
    case 'h':
    case 'H':
      return "....";
      break;
    case 'i':
    case 'I':
      return "..";
      break;
    case 'j':
    case 'J':
      return ".---";
      break;
    case 'k':
    case 'K':
      return "-.-";
      break;
    case 'l':
    case 'L':
      return ".-..";
      break;
    case 'm':
    case 'M':
      return "--";
      break;
    case 'n':
    case 'N':
      return "-.";
      break;
    case 'o':
    case 'O':
      return "---";
      break;
    case 'p':
    case 'P':
      return ".--.";
      break;
    case 'q':
    case 'Q':
      return "--.-";
      break;
    case 'r':
    case 'R':
      return ".-.";
      break;
    case 's':
    case 'S':
      return "...";
      break;
    case 't':
    case 'T':
      return "-";
      break;
    case 'u':
    case 'U':
      return "..-";
      break;
    case 'v':
    case 'V':
      return "...-";
      break;
    case 'w':
    case 'W':
      return ".--";
      break;
    case 'x':
    case 'X':
      return "-..-";
      break;
    case 'y':
    case 'Y':
      return "-.--";
      break;
    case 'z':
    case 'Z':
      return "--..";
      break;
    case '\r':
      return "";
      break;
    default:
      return "eeee";
  }
}

char morseToEnglish(const char* val) {
  if ((strcmp(val, "/")) == 0) {
    return ' ';
  } else if ((strcmp(val, ".-")) == 0) {
    return 'a';
  } else if ((strcmp(val, "-...")) == 0) {
    return 'b';
  } else if ((strcmp(val, "-.-.")) == 0) {
    return 'c';
  } else if ((strcmp(val, "-..")) == 0) {
    return 'd';
  } else if ((strcmp(val, ".")) == 0) {
    return 'e';
  } else if ((strcmp(val, "..-.")) == 0) {
    return 'f';
  } else if ((strcmp(val, "--.")) == 0) {
    return 'g';
  } else if ((strcmp(val, "....")) == 0) {
    return 'h';
  } else if ((strcmp(val, "..")) == 0) {
    return 'i';
  } else if ((strcmp(val, ".---")) == 0) {
    return 'j';
  } else if ((strcmp(val, "-.-")) == 0) {
    return 'k';
  } else if ((strcmp(val, ".-..")) == 0) {
    return 'l';
  } else if ((strcmp(val, "--")) == 0) {
    return 'm';
  } else if ((strcmp(val, "-.")) == 0) {
    return 'n';
  } else if ((strcmp(val, "---")) == 0) {
    return 'o';
  } else if ((strcmp(val, ".--.")) == 0) {
    return 'p';
  } else if ((strcmp(val, "--.-")) == 0) {
    return 'q';
  } else if ((strcmp(val, ".-.")) == 0) {
    return 'r';
  } else if ((strcmp(val, "...")) == 0) {
    return 's';
  } else if ((strcmp(val, "-")) == 0) {
    return 't';
  } else if ((strcmp(val, "..-")) == 0) {
    return 'u';
  } else if ((strcmp(val, "...-")) == 0) {
    return 'v';
  } else if ((strcmp(val, ".--")) == 0) {
    return 'w';
  } else if ((strcmp(val, "-..-")) == 0) {
    return 'x';
  } else if ((strcmp(val, "-.--")) == 0) {
    return 'y';
  } else if ((strcmp(val, "--..")) == 0) {
    return 'z';
  } else {
    return '#';
  }
}