#include "String.h"
#include <stdio.h>
#include <stdlib.h>

void arrAdd(char* to_arr, const char* from_arr, int from, int len) {
    for (size_t i = from; i < len; i++) {
        to_arr[from+i] = from_arr[i];
    }
}

String* createString() {
    String* newS;
    if (!(newS = (String*)malloc(sizeof(String))))
        exit(-2);
    if (!(newS->text = (char*)malloc(sizeof(char) * 1)))
        exit(-2);
    newS->maxLen = newS->len = 0;
    return newS;
}

void deleteString(String* str) {
    free(str->text);
    free(str);
}

int addText(char* _text, String* str) {
    int lastLen = str->len;
    for (; *_text != '\0'; _text++) {
        str->len++;
    }
    if (str->len > str->maxLen)
        str->maxLen = str->len;
    if (!(str->text = (char*)realloc(str->text, sizeof(char) * str->len)))
        exit(-2);
    arrAdd(str->text, _text, lastLen, str->len-lastLen);
    return str->len;
}

int addChar(char _sym, String* str) {
    if (str->len == str->maxLen)
        if (str->maxLen == 0)
            str->maxLen = 1;
        else
            str->maxLen *= 2;
    if (!(str->text = (char*)realloc(str->text, sizeof(char) * str->maxLen)))
        exit(-2);
    str->text[str->len++] = _sym;
    return str->len;
}

int print(size_t begin, size_t end, const String* str) {
    for (size_t i = begin; i < end; i++) {
        printf("%c", str->text[i]);
    }
    return str->len;
}
