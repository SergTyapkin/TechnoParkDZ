#ifndef INCLUDE_WILDMATCH
#define INCLUDE_WILDMATCH

#include "String.h"
#include "Array.h"

typedef struct {
    int start, end;
} Range;

void makeTokens(String* pattern, Array* tokens);

size_t wildFind(const String* substr, const String* str, int from);

Range match(int tokenId, const Array* tokens, int inpb, const String* input);

void getWordsText(Array* text);

void getLine(String* text);

int printReplacedText(const Array* tokens, const Array* text, const String* replace);

#endif // INCLUDE_WILDMATCH
