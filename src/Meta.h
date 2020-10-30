#ifndef INCLUDE_META
#define INCLUDE_META

#include "String.h"

typedef struct {
    String *title, *time, *author, *link, *localLink;
    int rate, comments;
} Meta;

Meta* newMeta();

void clearMeta(Meta* meta);

void copyToSharedMeta(const Meta* to_copy, Meta* to_write);

void freeMeta(Meta* meta);

void printMeta(Meta* meta);

#endif // INCLUDE_META
