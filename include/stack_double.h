#ifndef STACK_DOUBLE_H
#define STACK_DOUBLE_H

#include <stdlib.h>

typedef struct {
  int top;
  unsigned capacity;
  double* array;
} StackDouble;

typedef struct {
  double value;
  int status;
} StackResult;

StackDouble* createStackDouble(unsigned capacity);
int isEmptyDouble(StackDouble* stack);
void pushDouble(StackDouble* stack, double item);
StackResult popDouble(StackDouble* stack);
StackResult peekDouble(StackDouble* stack);
void destroyStackDouble(StackDouble* stack);

#endif