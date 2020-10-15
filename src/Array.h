#ifndef INCLUDE_ARRAY
#define INCLUDE_ARRAY

#include "String.h"

typedef struct {
    String** data;
    int len, maxLen;
} Array;


Array* createArray();

int addWord(Array* text, String* word);

void deleteArray(Array* arr);

#endif // INCUDE_ARRAY
