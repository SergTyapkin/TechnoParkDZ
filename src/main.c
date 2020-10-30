/* Вариант #76
Реализовать программу, позволяющую осуществлять замену слов текста
на определённую подстроку с помощью wildcard-запросов.
На вход поступает текст произвольной длины, wildcard-маска слова, которое нужно найти,
а также строку, на которую нужно заменить все совпадения (которая может быть и пустой).
В маске допускаются обычные символы, а также специальные символы ? и *,
означающие единичный произвольный символ и любую последовательность символов (включая нулевую).
На экран вывести изменённый текст, а также количество заменённых слов.
*/

//C:\CodeBlocks\MinGW\bin\gcc.exe main.c String.c Array.c WildMatch.c -ll
#include <stdio.h>
#include "WildMatch.h"
#include "String.h"
#include "Array.h"

int main() {
    String *pattern, *replace;
    Array *tokens, *text;

    printf("Enter wildcard-find: ");
    pattern = createString();
    getLine(pattern);
    tokens = createArray();
    makeTokens(pattern, tokens);

    printf("Enter replace: ");
    replace = createString();
    getLine(replace);

    printf("Enter text:\n");
    text = createArray();
    getWordsText(text);

    int words = printReplacedText(tokens, text, replace);
    printf("\nWords replaced: %d\n", words);

    deleteString(pattern);
    deleteString(replace);
    deleteArray(tokens);
    deleteArray(text);
    return 0;
}
