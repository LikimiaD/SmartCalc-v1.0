#include "../include/poland_notation.h"

#define MAX_LEN 255

static int getPriority(char op) {
  switch (op) {
    case 'p':
    case 'r':
      return 6;
    case '^':
      return 5;
    case 'c':
    case 's':
    case 't':
    case 'o':
    case 'i':
    case 'a':
    case 'q':
    case 'n':
    case 'g':
      return 4;
    case '*':
    case '/':
    case 'm':
      return 3;
    case '+':
    case '-':
      return 2;
    default:
      return 1;
  }
}

static int isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void readString(char* string, StackChar* stack, char* output) {
  int index = 0, space = 0;
  for (size_t i = 0; i < strlen(string); i++) {
    char sym = string[i];
    if (isdigit(sym) || sym == '.' || sym == 'x') {
      output[index++] = sym;
      space = 1;
    } else {
      if (space) {
        output[index++] = ' ';
        space = 0;
      }
      if (sym == '(') {
        pushChar(stack, sym);
      } else if (sym == ')') {
        while (!isEmptyChar(stack) && peekChar(stack) != '(') {
          output[index++] = popChar(stack);
          output[index++] = ' ';
        }
        popChar(stack);
      } else if (sym == 'c') {
        pushChar(stack, 'c');
        i += 2;  // skip os
      } else if (sym == 's') {
        if (string[i + 1] == 'i') {
          pushChar(stack, 's');
          i += 2;  // skip in
        } else {
          pushChar(stack, 'q');
          i += 3;  // skip qrt
        }
      } else if (sym == 't') {
        pushChar(stack, 't');
        i += 2;  // skip an
      } else if (sym == 'a') {
        if (string[i + 1] == 'c')
          pushChar(stack, 'o');
        else if (string[i + 1] == 's')
          pushChar(stack, 'i');
        else
          pushChar(stack, 'a');
        i += 3;  // skip cos/sin/tan
      } else if (sym == 'm') {
        pushChar(stack, 'm');
        i += 2;  // skip od
      } else if (sym == 'l') {
        if (string[i + 1] == 'n') {
          pushChar(stack, 'n');
          i++;  // skip n
        } else {
          pushChar(stack, 'g');
          i += 2;  // skip og
        }
      } else if ((!isdigit(string[i + 1]) || i == 0 || string[i - 1] == '(') &&
                 sym == '+' && isdigit(string[i + 1])) {  // unary +
        pushChar(stack, 'p');
      } else if ((!isdigit(string[i + 1]) || i == 0 || string[i - 1] == '(') &&
                 sym == '-' && isdigit(string[i + 1])) {  // unary -
        pushChar(stack, 'r');
      } else if (isOperator(sym)) {
        while (!isEmptyChar(stack) &&
               getPriority(peekChar(stack)) >= getPriority(sym)) {
          output[index++] = popChar(stack);
          output[index++] = ' ';
        }
        pushChar(stack, sym);
      }
    }
  }
  while (!isEmptyChar(stack)) {
    if (index > 0 && output[index - 1] !=
                         ' ') {  // Проверяем, нужен ли пробел перед оператором
      output[index++] = ' ';
    }
    output[index++] = popChar(stack);
  }
  output[index] = '\0';
}

// int main() {
//   StackChar* stack = createStackChar(MAX_LEN);
//   char string[MAX_LEN] = "cos(x+3)*2\0";
//   char output[MAX_LEN] = {""};
//   readString(string, stack, output);
//   printf("%s\n", output);
//   destroyStackChar(stack);
//   return 0;
// }