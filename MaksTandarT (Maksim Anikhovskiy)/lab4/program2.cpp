#include <iostream>
#include <fstream>

#define MAX_WORD_LENGTH 256
#define PATH_TO_FILE "program2.txt"

int length (char *stroke) {
  for(int i = 0; ; i++) if(stroke[i] == '\0') return i;
}

void append (char *stroke, char el) {
  stroke[length(stroke) + 1] = '\0';
  stroke[length(stroke)] = el;
}

char toLower (char ch) {
  char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char lower[] = "abcdefghijklmnopqrstuvwxyz";

  for(int i = 0; i < 26; i++) {
    if (ch == upper[i]) {
      ch = lower[i];
      break;
    }
  }

  return ch;
}

void appendToArray (char **strokes, char *el, int &lengthArray) {
  strokes[lengthArray] = el;
  lengthArray++;
}

int indexOf(char *stroke, char ch, bool withRegistry = false) {
  int index = -1;
  for(int i = 0; i < length(stroke); i++) {
    if(withRegistry ? stroke[i] == ch : toLower(stroke[i]) == toLower(ch)) {
      index = i;
      break;
    }
  }

  return index;
}

void erase(char *stroke, int index) {
  for(int i = index; i < length(stroke); i++) {
    stroke[i] = stroke[i + 1];
  }
}

void eraseArray(char **strokes, int index, int &length) {
  for(int i = index + 1; i < length; i++) {
    strokes[i - 1] = strokes[i];
  }
  length--;
}

bool checkForEqualsChars (char *stroke1, char *stroke2) {
  if(length(stroke2) != length(stroke1)) return false;

  int equalsCount = 0;
  char * copy = new char [length(stroke2)];
  for(int i = 0; i <= length(stroke2); i++) {
    copy[i] = stroke2[i];
  }
  

  for(int i = 0; i < length(stroke1); i++) {
    if(indexOf(copy, stroke1[i]) != -1) {
      erase(copy, indexOf(copy, stroke1[i]));
    } else return false;
  }

  return true;
}

void checkWords (char **words, int wordsLength) {
  
  for(int i = 0; i < wordsLength; i++) {
    for(int j = 0; j != i, j < wordsLength; j++) {
      if(checkForEqualsChars(words[i], words[j])) {
        std::cout << words[i] << ", " << words[j] << std::endl;
        eraseArray(words, j, wordsLength);
        eraseArray(words, i, wordsLength);
        
      }
    }
  }
}
 
int stringsCountInFile(char *path) {
  int count = 0;
  std::ifstream fs(path);

  while (true) {
    if (!fs.eof()) {
      char word[MAX_WORD_LENGTH];
      fs.getline(word, MAX_WORD_LENGTH);
      count++;
    }
    else break;
  }

	fs.close();
  return count;
}

int main()
{
  int wordsLength = stringsCountInFile(PATH_TO_FILE);
  char **words = new char*[wordsLength];

	std::ifstream fs(PATH_TO_FILE);
  char *word;
  for(int i = 0; i < wordsLength; i++){
    word = new char[MAX_WORD_LENGTH];
    fs.getline(word, MAX_WORD_LENGTH);
    words[i] = word;
  }

  fs.close();

  for (int i = 0; i < wordsLength; i++) {
    std::cout << words[i] << std::endl;
  }

  std::cout << std::endl;

  checkWords(words, wordsLength);

	return 0;
}