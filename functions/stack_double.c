#include "../include/stack_double.h"

StackDouble* createStackDouble(unsigned capacity) {
  StackDouble* stack = (StackDouble*)malloc(sizeof(StackDouble));
  if (!stack) return NULL;
  stack->capacity = capacity;
  stack->top = 0;
  stack->array = (double*)malloc(sizeof(double) * capacity);
  return stack;
}

void destroyStackDouble(StackDouble* stack) {
  if (stack) {
    free(stack->array);
    free(stack);
  }
}

int isEmptyDouble(StackDouble* stack) { return stack->top == 0; }

void pushDouble(StackDouble* stack, double item) {
  if (stack->top < (int)stack->capacity) {
    stack->array[stack->top++] = item;
  }
}

StackResult popDouble(StackDouble* stack) {
  StackResult result;
  if (!isEmptyDouble(stack)) {
    stack->top--;
    result.value = stack->array[stack->top];
    result.status = 0;
  } else {
    result.value = 0;
    result.status = -1;
  }
  return result;
}

StackResult peekDouble(StackDouble* stack) {
  StackResult result;
  if (!isEmptyDouble(stack)) {
    result.value = stack->array[stack->top - 1];
    result.status = 0;
  } else {
    result.value = 0;
    result.status = -1;
  }
  return result;
}