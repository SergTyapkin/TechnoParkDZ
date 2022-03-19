#include "Meta.h"
#include "String.h"
#include <stdio.h>
#include <stdlib.h>

Meta* newMeta() {
    Meta* meta = (Meta*)malloc(sizeof(Meta));
    if (meta != NULL) {
        meta->title = newString();
        meta->time = newString();
        meta->author = newString();
        meta->link = newString();
        meta->localLink = newString();
        meta->rate = meta->comments = 0;
    }
    return meta;
}

void clearMeta(Meta* meta) {
    meta->title->len = meta->time->len = meta->author->len = \
    meta->link->len = meta->localLink->len = meta->rate = meta->comments = 0;
}

/*
void copyToSharedMeta(const Meta* to_copy, Meta* to_write) {
    to_write->title = newSharedStr(to_copy->title);
    printf("AFTER COPY: %d:", to_write->title->len); print(0, to_write->title->len, to_write->title); putchar('\n');
    to_write->time = newSharedStr(to_copy->time);
    to_write->author = newSharedStr(to_copy->author);
    to_write->link = newSharedStr(to_copy->link);
    to_write->localLink = newSharedStr(to_copy->localLink);
    to_write->rate = to_copy->rate;
    to_write->comments = to_copy->comments;
}
*/

void freeMeta(Meta* meta) {
    deleteString(meta->title);
    deleteString(meta->time);
    deleteString(meta->author);
    deleteString(meta->link);
    deleteString(meta->localLink);
    free(meta);
}

void printMeta(Meta* meta) {
    print(0, meta->title->len, meta->title); putchar('\n');
    print(0, meta->time->len, meta->time); putchar('\n');
    printf("Author: "); print(0, meta->author->len, meta->author);
    printf(". Rate: %d. Comments: %d\n", meta->rate, meta->comments);
    print(0, meta->link->len, meta->link); putchar('\n');
    printf("Putted there: "); print(0, meta->localLink->len, meta->localLink);
    putchar('\n'); putchar('\n');
}
