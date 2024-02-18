#ifndef STACK_CHAR_H
#define STACK_CHAR_H

#include <stdlib.h>

typedef struct {
  int top;
  unsigned capacity;
  char* array;
} StackChar;

StackChar* createStackChar(unsigned capacity);
void destroyStackChar(StackChar* stack);
int isEmptyChar(StackChar* stack);
void pushChar(StackChar* stack, char item);
char popChar(StackChar* stack);
char peekChar(StackChar* stack);

#endif