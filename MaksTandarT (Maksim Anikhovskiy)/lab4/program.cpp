/*
* Аниховский Максим Андреевич <anikhovskiy00@mail.ru>
* Группа №953504.
* 
* Пишу с неверной для C++ табуляцией (2 пробела) потому,
* что в основном пишу на JavaScript и пользуюсь EsLint
* StyleGuide'ом "airbnb-style-guide", который требует
* два пробела в табе, а не 4. Заранее извиняюсь.
*/

#include <iostream>

// длина массива символов
int length (char *stroke) {
  for(int i = 0; ; i++) if(stroke[i] == '\0') return i;
}

// добавить в конец массива символов
void append (char *stroke, char el) {
  stroke[length(stroke) + 1] = '\0'; 
  stroke[length(stroke)] = el; 
  
}

// имитация функции для string
void replace (char *stroke, int start, int end, char *sub) {
  const int replaceLength = end - start + 1; // длина подстроки для замены
  const int delta = length(sub) - replaceLength; // дельта длин замены

  if (delta > 0) {
    // "раздвигаем" текст на дельта символов
    for (int i = length(stroke); i >= start; i--) stroke[i + delta] = stroke[i]; 
  }
  if (delta < 0) {
    // "сдвигаем" текст на дельта символов
    for (int i = end; i < length(stroke) + 1; i++) stroke[i + delta] = stroke[i];
  }
  // записываем подстроку в нужное место
  for (int i = start, k = 0; i < start + replaceLength && k < length(sub); i++, k++) stroke[i] = sub[k];
}

// перевод из int в char*
char *intToText (int number) {
  char *numberStroke = new char [1];
  numberStroke[0] = '\0';

  int *digits = new int[0]; 
  int i;
  for(i = 0; number != 0; i++) {
    digits[i] = number % 10;
    
    number /= 10;
  }

  for(int j = i - 1; j >= 0; j--) append(numberStroke, (char)(((int)'0') + digits[j]));
  return numberStroke;
}

 // вычисление умножения и деления (в первую очередь) 
void multDiv (char *stroke) {
  for (int i = 0; i < length(stroke); i++){
    if (stroke[i] == '*' || stroke[i] == '/') {
      int answer; // ответ
      int left = 0; // число слева от знака
      int right = 0; // число справа от знака
      int k;
      int j;
      int start; // начало локального выражения
      int end; // конец локального выражения

      // к началу и записываем число
      for (j = i - 1, k = 1; ; j--, k *= 10) { 
        if (j < 0 || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        left += (stroke[j] - '0') * k;
      }

      start = j + 1; // сохраняем координаты начала

      j = i + 1;
      while (true) {
        if (j >= length(stroke) || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        j++; // переходим к концу выражения
      } 

      end = j - 1; // сохраняем координаты конца

      

      // к середине и записываем второе
      for (j = end, k = 1; ; j--, k *= 10) { 
        if (j < 0 || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        right += (stroke[j] - '0') * k;
      }
      

      switch (stroke[i]) { // вычисление ответа в числе
        case '*':
          answer = left * right;
          break;
        case '/':
          answer = left / right;
          break;
      }

      // std::cout << "answer: " << answer << "  " << intToText(answer) << std::endl;


      // std::cout << start << "  " << end << std::endl;


      replace(stroke, start, end, intToText(answer));

      multDiv(stroke);
      break;
      
    }
  }
}

 // вычисление умножения и деления (в первую очередь) 
void plusMinus (char *stroke) {
  for (int i = 0; i < length(stroke); i++){
    if (stroke[i] == '+' || stroke[i] == '-') {
      int answer; // ответ
      int left = 0; // число слева от знака
      int right = 0; // число справа от знака
      int k;
      int j;
      int start; // начало локального выражения
      int end; // конец локального выражения

      // к началу и записываем число
      for (j = i - 1, k = 1; ; j--, k *= 10) { 
        if (j < 0 || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        left += (stroke[j] - '0') * k;
      }

      start = j + 1; // сохраняем координаты начала

      j = i + 1;
      while (true) {
        if (j >= length(stroke) || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        j++; // переходим к концу выражения
      } 

      end = j - 1; // сохраняем координаты конца

      

      // к середине и записываем второе
      for (j = end, k = 1; ; j--, k *= 10) { 
        if (j < 0 || stroke[j] == '+' || stroke[j] == '-' || stroke[j] == '*' || stroke[j] == '/') break;
        right += (stroke[j] - '0') * k;
      }
      

      switch (stroke[i]) { // вычисление ответа в числе
        case '+':
          answer = left + right;
          break;
        case '-':
          answer = left - right;
          break;
      }




      replace(stroke, start, end, intToText(answer));

      plusMinus(stroke);
      
    }
  }
}

int main () {
  char *stroke = new char [255];
  std::cout << "Enter the expression: ";
  std::cin.getline(stroke, 255);


  // Когда я писал эти функции полько я и бог знали как они работают.
  multDiv(stroke);
  plusMinus(stroke);
  // Теперь знает только бог...

  std::cout << stroke << std::endl;


  system("pause");
  return 0;
}