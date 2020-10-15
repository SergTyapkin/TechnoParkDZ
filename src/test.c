/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <check.h>

#include "String.h"
#include "Array.h"
#include "WildMatch.h"

START_TEST(string_lib_test) {
    String* str1 = createString();
    String* str2 = createString();
    String* str3 = createString();
    String* str4 = createString();

    addText("This ", str1);
    addText("is ", str1);
    addText("string xD", str1);

    addChar('I', str2);
    addText("'m not so good at ", str2);
    addChar('C', str2);

    addText('O', str3);
    addText(" is", str3);
    addText(" not ", str3);
    addChar('X', str3);

    fail_unless(str1->len == 17, "string_lib_test1");
    fail_unless(str2->len == 20, "string_lib_test2");
    fail_unless(str3->len == 10, "string_lib_test3");
    fail_unless(str4->len == 0, "string_lib_test3");

    deleteString(str1);
    deleteString(str2);
    deleteString(str3);
    deleteString(str4);
} END_TEST

START_TEST(array_lib_test) {
    String* str1 = createString();
    String* str2 = createString();
    String* str3 = createString();
    String* str4 = createString();
    String* str5 = createString();

    addText("Text1", str1);
    addText("Text22", str1);
    addText("Text333", str1);
    addText("Text4444", str1);
    addText("Text55555", str1);

    Array* arr1 = createArray();
    Array* arr2 = createArray();
    Array* arr3 = createArray();
    Array* arr4 = createArray();

    addWord(arr1, str1);
    addWord(arr1, str2);
    addWord(arr1, str3);

    addWord(arr2, str1);
    addWord(arr2, str3);
    addWord(arr2, str2);
    addWord(arr2, str4);

    addWord(arr3, str5);
    addWord(arr3, str4);
    addWord(arr3, str3);
    addWord(arr3, str2);
    addWord(arr3, str1);

    fail_unless(arr1->len == 3, "array_lib_test1");
    fail_unless(arr2->len == 4, "array_lib_test2");
    fail_unless(arr3->len == 5, "array_lib_test3");
    fail_unless(arr4->len == 0, "array_lib_test4");

    deleteArray(arr1);
    deleteArray(arr2);
    deleteArray(arr3);
    deleteArray(arr4);
} END_TEST

START_TEST(make_tokens_test) {
    String* pattern1 = createString();
    String* pattern2 = createString();
    String* pattern3 = createString();
    String* pattern4 = createString();
    String* pattern5 = createString();
    Array *tokens1 = createArray();
    Array *tokens2 = createArray();
    Array *tokens3 = createArray();
    Array *tokens4 = createArray();
    Array *tokens5 = createArray();
    addText("*r?o*s", pattern1); // glorious, forio[u]s[ly], maintainlious[ly]
    addText("*", pattern2); // any
    addText("***", pattern3); // any
    addText("*+*=?00", pattern4); // summary, where rezult ends in "00"
    addText("*.?", pattern5); // .c and .h files
    makeTokens(pattern1, tokens1);
    makeTokens(pattern2, tokens2);
    makeTokens(pattern3, tokens3);
    makeTokens(pattern4, tokens4);
    makeTokens(pattern5, tokens5);

    fail_unless(tokens1->len == 4, "make_tokens_test1");
    fail_unless(tokens2->len == 1, "make_tokens_test2");
    fail_unless(tokens3->len == 3, "make_tokens_test3");
    fail_unless(tokens4->len == 4, "make_tokens_test4");
    fail_unless(tokens5->len == 2, "make_tokens_test5");

    deleteArray(tokens1);
    deleteArray(tokens2);
    deleteArray(tokens3);
    deleteArray(tokens4);
    deleteArray(tokens5);
} END_TEST

START_TEST(wild_find_test) {
    fail_unless(wildFind("SUB", "stringWithSUBstring", 0) == 10, "wild_find_test1");
    fail_unless(wildFind("XXXXX", "XXXorXXXXbutXXXXX. it's nice.", 0) == 12, "wild_find_test2");
    fail_unless(wildFind("XXX", "XXX but XXX", 1) == 8, "wild_find_test3");
    fail_unless(wildFind("test", "now we test some tests for testing", 0) == 7, "wild_find_test4");
    fail_unless(wildFind("3hundred", "get 3hundred bucks", 0) == 4, "wild_find_test5");
    fail_unless(wildFind("0pos", "0pos 1pos 2pos 3pos", 0) == 0, "wild_find_test6");
} END_TEST

START_TEST(match_test) {
    String* pattern1 = createString();
    String* pattern2 = createString();
    String* pattern3 = createString();
    String* pattern4 = createString();
    String* pattern5 = createString();
    Array *tokens1 = createArray();
    Array *tokens2 = createArray();
    Array *tokens3 = createArray();
    Array *tokens4 = createArray();
    Array *tokens5 = createArray();
    addText("*r?o*s", pattern1); // glorious, forious[ly], maintainlious[ly]
    addText("*", pattern2); // any
    addText("***", pattern3); // any
    addText("*+*=?00", pattern4); // summary, where rezult ends in "00"
    addText("*.?", pattern5); // .c and .h files
    makeTokens(pattern1, tokens1);
    makeTokens(pattern2, tokens2);
    makeTokens(pattern3, tokens3);
    makeTokens(pattern4, tokens4);
    makeTokens(pattern5, tokens5);

    Range range;
    range = match(0, tokens1, 0, "gloriously");
    fail_unless(range.start == 0 && range.end == 7, "match_test1.1");
    range = match(0, tokens1, 0, "glori.us");
    fail_unless(range.end == -1, "match_test1.2");

    range = match(0, tokens2, 0, "any");
    fail_unless(range.start == 0 && range.end == 2, "match_test2");

    range = match(0, tokens3, 0, "any more");
    fail_unless(range.start == 0 && range.end == 7, "match_test3");

    range = match(0, tokens4, 0, "it evals: 87+513=600 that's all.");
    fail_unless(range.start == 10 && range.end == 19, "match_test4.1");
    range = match(0, tokens4, 0, "it evals: 87+513=666 that's all.");
    fail_unless(range.end == -1, "match_test4.2");

    range = match(0, tokens5, 0, "test.c and i have main.c");
    fail_unless(range.start == 0 && range.end == 5, "match_test5.1");
    range = match(0, tokens5, 0, "test c and i have main.");
    fail_unless(range.end == -1, "match_test5.2");
} END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, string_lib_test);
    tcase_add_test(tc1_1, array_lib_test);
    tcase_add_test(tc1_1, make_tokens_test);
    tcase_add_test(tc1_1, wild_find_test);
    tcase_add_test(tc1_1, match_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0? 0: 1;
}
