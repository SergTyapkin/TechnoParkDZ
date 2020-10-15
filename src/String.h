#ifndef INCLUDE_STRING
#define INCLUDE_STRING

#include <stddef.h>

typedef struct {
    char* text;
    int len, maxLen;
} String;


String* createString();

void deleteString(String* str);

int addText(char* _text, String* str);

int addChar(char _sym, String* str);

int print(size_t begin, size_t end, const String* str);

#endif // INCUDE_STRING
