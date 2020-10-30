#ifndef INCLUDE_STRING
#define INCLUDE_STRING

#include <stddef.h>

typedef struct {
    char* text;
    int len, maxLen;
} String;


String* newString();

void deleteString(String* str);

int addSizedText(String* str, const char* _text, int size);

int addText(String* str, const char* _text);

int addChar(char _sym, String* str);

int copyStr(const String* to_copy, String* to_write);

int print(size_t begin, size_t end, const String* str);

//String* newSharedStr(const String* to_copy);

#endif // INCUDE_STRING
