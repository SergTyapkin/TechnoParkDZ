#include "String.h"
#include <stdio.h>
#include <stdlib.h>
//#include <sys/mman.h>

#define ALLOCATE_ERROR -2

void arrAdd(char* to_arr, const char* from_arr, int from, int len) {
    for (int i = from; i < len; i++) {
        to_arr[i] = from_arr[i-from];
    }
}

String* newString() {
    String* newS = (String*)malloc(sizeof(String));
    if (!(newS))
        exit(ALLOCATE_ERROR);
    newS->text = (char*)malloc(sizeof(char) * 1);
    if (!(newS->text))
        exit(ALLOCATE_ERROR);
    newS->maxLen = newS->len = 0;
    return newS;
}

void deleteString(String* str) {
    free(str->text);
    free(str);
}

int addSizedText(String* str, const char* _text, int size) {
    int lastLen = str->len;
    str->len += size;

    if (str->len > str->maxLen)
        str->maxLen = str->len;
    str->text = (char*)realloc(str->text, sizeof(char) * str->len);
    if (!(str->text))
        exit(ALLOCATE_ERROR);
    arrAdd(str->text, _text, lastLen, str->len);
    //printf("_tEXt: %s\nTEXT: ", _text);
    //print(0, str->len, str);
    return str->len;
}

int addText(String* str, const char* _text) {
    int lastLen = str->len;
    int i;
    for (i = 0; _text[i] != '\0'; i++) {;}
    str->len += i;

    if (str->len > str->maxLen)
        str->maxLen = str->len;
    str->text = (char*)realloc(str->text, sizeof(char) * str->len);
    if (!(str->text))
        exit(ALLOCATE_ERROR);
    arrAdd(str->text, _text, lastLen, str->len);
    //printf("_tEXt: %s\nTEXT: ", _text);
    //print(0, str->len, str);
    return str->len;
}

int addChar(char _sym, String* str) {
    if (str->len == str->maxLen) {
        if (str->maxLen == 0)
            str->maxLen = 1;
        else
            str->maxLen *= 2;
    }
    str->text = (char*)realloc(str->text, sizeof(char) * str->maxLen);
    if (!(str->text))
        exit(ALLOCATE_ERROR);
    str->text[str->len++] = _sym;
    return str->len;
}

int copyStr(const String* to_copy, String* to_write) {
    to_write->len = 0;
    addSizedText(to_write, to_copy->text, to_copy->len);
    return to_write->len;
}

int print(size_t begin, size_t end, const String* str) {
    for (size_t i = begin; i < end; i++) {
        printf("%c", str->text[i]);
    }
    return str->len;
}

/*
String* newSharedStr(const String* to_copy) {
    String* str = mmap(NULL, sizeof(String), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    str->text = mmap(NULL, sizeof(char) * (to_copy->len), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    arrAdd(str->text, to_copy->text, 0, to_copy->len);
    str->len = to_copy->len;
    printf("SSSSS\n");
    return str;
}
*/
