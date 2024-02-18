#include "../include/stack_char.h"

StackChar* createStackChar(unsigned capacity) {
  StackChar* stack = (StackChar*)malloc(sizeof(StackChar));
  if (!stack) return NULL;
  stack->capacity = capacity;
  stack->top = 0;
  stack->array = (char*)malloc(sizeof(char) * capacity);
  return stack;
}
void destroyStackChar(StackChar* stack) {
  if (stack) {
    free(stack->array);
    free(stack);
  }
}
int isEmptyChar(StackChar* stack) { return stack->top == 0; }
void pushChar(StackChar* stack, char item) {
  if (stack->top < (int)stack->capacity) {
    stack->array[stack->top++] = item;
  }
}

char popChar(StackChar* stack) {
  if (!isEmptyChar(stack)) {
    return stack->array[--stack->top];
  }
  return '\0';
}

char peekChar(StackChar* stack) {
  if (!isEmptyChar(stack)) {
    return stack->array[stack->top - 1];
  }
  return '\0';
}