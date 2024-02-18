#ifndef POLAND_NOTATION_H
#define POLAND_NOTATION_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_char.h"
#include "stack_double.h"

#define MAX_LEN 255
#define split(__string, __delimiters) strtok(__string, __delimiters)
#define check(__string, __str) strpbrk(__string, __str)
#define len(__str) strlen(__str)

void readString(char* string, StackChar* stack, char* output);
double parsePoland(char* string);

#endif