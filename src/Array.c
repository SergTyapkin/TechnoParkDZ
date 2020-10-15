#include "Array.h"
#include "String.h"
#include <stdlib.h>
#include <stdio.h>

Array* createArray() {
    Array* newA;
    if (!(newA = (Array*)malloc(sizeof(Array))))
        exit(-2);
    if (!(newA->data = (String**)malloc(sizeof(String*))))
        exit(-2);
    newA->maxLen = newA->len = 0;
    return newA;
}

int addWord(Array* text, String* word) {
    if (text->len == text->maxLen) {
        if (text->len != 0) {
            text->maxLen *= 2;
            if (!(text->data = (String**)realloc(text->data, sizeof(String*) * text->maxLen)))
                exit(-2);
        } else {
            if (!(text->data = (String**)malloc(sizeof(String*) * 1)))
                exit(-2);
            text->maxLen = 1;
        }
    }
    text->data[text->len++] = word;
    return text->len;
}

void deleteArray(Array* arr) {
    for (size_t i = 0; i < arr->len; i++)
        deleteString(arr->data[i]);
    free(arr);
}
