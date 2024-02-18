#include "../include/poland_notation.h"
#include "../include/stack_char.h"
#include "../include/stack_double.h"

#define MAX_LEN 255
#define split(__string, __delimiters) strtok(__string, __delimiters)
#define check(__string, __str) strpbrk(__string, __str)
#define len(__str) strlen(__str)

static int calcSym(char sym, double* answer, StackDouble* stack) {
  int status = 1;
  StackResult ans1;
  StackResult ans2;
  StackResult ans;
  switch (sym) {
    case '+':
      if (stack->top < 1) {
        status = -1;
      } else {
        ans2 = popDouble(stack);
        ans1 = popDouble(stack);
        if (ans1.status == 0 && ans2.status == 0) {
          *answer = ans1.value + ans2.value;
          status = 0;
        }
      }
      break;
    case '-':
      ans2 = popDouble(stack);
      ans1 = popDouble(stack);
      if (ans1.status == 0 && ans2.status == 0) {
        *answer = ans1.value - ans2.value;
        status = 0;
      }
      break;
    case '*':
      ans2 = popDouble(stack);
      ans1 = popDouble(stack);
      if (ans1.status == 0 && ans2.status == 0) {
        *answer = ans1.value * ans2.value;
        status = 0;
      }
      break;
    case '/':
      ans2 = popDouble(stack);
      ans1 = popDouble(stack);
      if (ans1.status == 0 && ans2.status == 0) {
        *answer = ans1.value / ans2.value;
        status = 0;
      }
      break;
    case '^':
      ans2 = popDouble(stack);
      ans1 = popDouble(stack);
      if (ans1.status == 0 && ans2.status == 0) {
        *answer = powl(ans1.value, ans2.value);
        status = 0;
      }
      break;
    case 'm':
      ans2 = popDouble(stack);
      ans1 = popDouble(stack);
      if (ans1.status == 0 && ans2.status == 0) {
        *answer = fmod(ans1.value, ans2.value);
        status = 0;
      }
      break;
    case 'c':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = cos(ans.value);
        status = 0;
      }
      break;
    case 's':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = sin(ans.value);
        status = 0;
      }
      break;
    case 't':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = tan(ans.value);
        status = 0;
      }
      break;
    case 'o':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = acos(ans.value);
        status = 0;
      }
      break;
    case 'i':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = asin(ans.value);
        status = 0;
      }
      break;
    case 'a':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = atan(ans.value);
        status = 0;
      }
      break;
    case 'q':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = sqrt(ans.value);
        status = 0;
      }
      break;
    case 'n':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = log(ans.value);
        status = 0;
      }
      break;
    case 'g':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = log10(ans.value);
        status = 0;
      }
      break;
    case 'r':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = ans.value * -1;
        status = 0;
      }
      break;
    case 'p':
      ans = popDouble(stack);
      if (ans.status == 0) {
        *answer = ans.value;
        status = 0;
      }
    default:
      break;
  }
  if (*answer == -0.0f) {
    *answer = fabs(*answer);
  }
  return status;
}

double parsePoland(char* string) {
  double answer = 0.0;
  const unsigned int size = strlen(string);  // Используем strlen вместо len

  StackDouble* stackDouble = createStackDouble(size);

  const char* sep = " \0";
  char* token = strtok(
      string,
      sep);  // Используем стандартную функцию strtok для разбиения строки
  while (token != NULL) {
    if (strlen(token) == 1 && strchr("+-/*^cstoiaqngmpr", token[0]) != NULL) {
      // Если токен - это оператор, сразу выполняем операцию
      if (calcSym(token[0], &answer, stackDouble) == 0) {
        // printf("CALC| %lf| SYM '%c'\n", answer, token[0]);
        pushDouble(stackDouble, answer);
      }
    } else {
      // Если токен - это число, помещаем его в стек чисел
      pushDouble(stackDouble, atof(token));
    }
    token = strtok(NULL, sep);
  }

  // В конце все результаты должны быть объединены в стеке чисел,
  // так что итоговый ответ - это верхний элемент стека
  if (!isEmptyDouble(stackDouble)) {
    answer = popDouble(stackDouble).value;
  }

  destroyStackDouble(stackDouble);

  return answer;
}

// int main() {
//     printf("START\n\n");
//     // 1.111 r 2.222 p + 3.3 r 4.44444 * 5.555 / - 4 5 ^ + 5 6 m + 4 p + 4 r
//     + 1 c + 0 s + 1 t + 1 o + 1 i + 1 a + 4 q + 1 n + 1 g +
//     // 1.111 r 2.222 p + 3.3 r 4.44444 * 5.555 / - 4 5 ^ + 5 6 m + 4 p + 4 r
//     + 1 c + 0 s + 1 t + 1 o + 1 i + 1 a + 4 q + 1 n + 1 g +
//     // 1.111 r 2.222 p + 3.3 r 4.44444 * 5.555 / - 4 5 ^ + 5 6 m + 4 p + 4 r
//     + 1 c + 0 s + 1 t + 1 o + 1 i + 1 a + 4 q + 1 n + 1 g + char
//     string[MAX_LEN] = "1.111 r 2.222 p + 3.3 r 4.44444 * 5.555 / - 4 5 ^ + 5
//     6 m + 102 g +"; parsePoland(string); return 0;
// }