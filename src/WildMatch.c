#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "Array.h"
#include "WildMatch.h"

void makeTokens(String* pattern, Array* tokens) {
    String* token;
    for (size_t begin = 0; begin < pattern->len; ) {
        token = createString();
        if (pattern->text[begin] != '*') {
            for (size_t i = begin; i < pattern->len; i++) {
                if (pattern->text[i] == '*')
                    break;
                addChar(pattern->text[i], token);
            }
        } else {
            addChar('\0', token);
        }
        begin += token->len;
        addWord(tokens, token);
    }
}

size_t wildFind(const String* substr, const String* str, int from) {
    unsigned short int find; // bool
    for (size_t id = from; id < str->len; id++) {
        find = 1;
        for (int n = 0; (n < substr->len); n++) {
            if ((str->text[id+n] != substr->text[n]) && (substr->text[n] != '?'))
                find = 0;
        }
        if (find)
            return id;
    }
    return -1;
}

Range match(int tokenId, const Array* tokens, int inpb, const String* input) {
    Range rez = {inpb, -1};
    Range nextRez;
    const String* token;

    if (tokenId >= tokens->len)
    {
        if (tokens->len < 1 || tokens->data[tokenId-1]->text[0] == '\0')
            rez.end = input->len;
        else
            rez.end = inpb-1;
        return rez;
    }
    token = tokens->data[tokenId];
    tokenId++;

    if (token->text[0] == '\0') {
        rez.start = inpb;
        rez.end = match(tokenId, tokens, inpb, input).end;
        return rez;
    } else {
        size_t submatch = wildFind(token, input, inpb);
        while ((rez.start = submatch) != -1)
        {
            nextRez = match(tokenId, tokens, submatch + token->len, input);
            if (nextRez.start != -1)
                rez.end = nextRez.end;
                return rez;

            submatch = wildFind(token, input, submatch+1);
        }
        return rez;
    }
}

void getWordsText(Array* text) {
    char sym;
    String* word = createString();
    unsigned short int stop = 0; // bool

    while (!stop) {
        sym = getchar();
        addChar(sym, word);
        if (sym == ' ' || sym == '\n' || sym == '\t' || sym == EOF) {
            if (sym == EOF)
                stop = 1;
            else
                addWord(text, word);
            word = createString();
        }
    }
    deleteString(word);
}

void getLine(String* text) {
    char sym;
    while (((sym = getchar()) != '\n') && (sym != EOF)) {
        addChar(sym, text);
    }
}

int printReplacedText(const Array* tokens, const Array* text, const String* replace) {
    Range range;
    int replacedWords = 0;
    for (size_t i = 0; i < text->len; i++) {
        range = match(0, tokens, 0, text->data[i]);
        if (range.end != -1) {
            replacedWords++;
            print(0, range.start, text->data[i]);
            print(0, replace->len, replace);
            print(range.end+1, text->data[i]->len, text->data[i]);
        } else {
            print(0, text->data[i]->len, text->data[i]);
        }
    }
    return replacedWords;
}

