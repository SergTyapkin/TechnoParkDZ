/**
Вариант #76
1. Реализовать программу, которая получает список лучших публикаций за последний год с ресурса habr.com.

2. Организовать программу в виде системной утилиты, которая принимает аргументы командной строки: количество статей и директорию,
в которую нужно положить скачанные страницы.

3. Механизм работы программы следующий: она должна зайти на главную страницу,
скачать её с помощью любой системной готовой системной утилиты (например, wget или curl).
Найти в ней все ссылки на посты. Далее пройтись по каждому из постов, скачать его в директорию, указанную в качестве входного аргумента.

4. А также сформировать метаинформацию об этой статье: название, время публикации, автор, рейтинг и количество комментариев,
а также оригинальную ссылку на эту публикацию и путь к файлу с этим постом на диске.
В качестве своего результата программа должна выдать список с этой метаинформацией пользователю, отсортированную по рейтингу постов.

6. Параллельную реализацию выполнить с использованием нескольких процессов.
**/
//gcc curl_main.c String.c -lcurl && ./a.out ./PUT

#include "String.h"
#include "Meta.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#define URL "https://habr.com/ru/top/yearly/"
#define ARTICLES_ON_PAGE 20

#define ERR_LOW_ARGS       -11 // -1X - user input errors
#define ERR_WRONG_FILENAME -12
#define ERR_WRONG_URL      -13
#define ERR_WRONG_DIRNAME  -14
#define ERR_BAD_LINK    -21 // -2X - program runtime errors
#define ERR_BAD_TITLE   -22
#define ERR_NEW_PROCESS -23


int fillStringFromURL (String* data, const char* url) {
    size_t writeFuncForCurl(char *buffer, size_t size, size_t nmemb, String *data) { // читается всё кусками, потому что буфер не резиновый
        // size = 1 обычно. Знать бы, зачем он вообще.
        int result = 0;
        if (buffer != NULL) {
            addSizedText(data, buffer, size*nmemb);
            result = size * nmemb;
        }
        return result;
    }

    int lastlen = data->len;
    CURL* curl; // дескриптор
    curl = curl_easy_init(); // получаем дескриптор
    curl_easy_setopt(curl, CURLOPT_URL, url); // общаться надо с этим адресом
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFuncForCurl); // писать в мою структуру надо по такой функции
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data); // писать надо в data
    curl_easy_perform(curl); // общение с сайтом так, как мы описали в setopt
    curl_easy_cleanup(curl); // деструктор дескриптора
    return (data->len - lastlen);
}

int fillStringFromFile(String* data, const char* filename) {
    FILE *html = fopen (filename, "r");
    if (html == NULL)
        return 0;
    char buf[2056];
    int lines = 0;
    while (fgets(buf, 2056, html) != NULL) {
        addText(data, buf);
        lines++;
    }
    fclose(html);
    return lines;
}

int fillFileFromURL (const char* filePath, const char* url) {
    size_t writeFuncForCurl(char *buffer, size_t size, size_t nmemb, FILE *file) { // читается всё кусками, потому что буфер не резиновый
        // size = 1 обычно. Знать бы, зачем он вообще.
        int result = 0;
        if (buffer != NULL) {
            fprintf(file, "%s", buffer);
            result = size * nmemb;
        }
        return result;
    }

    FILE *file = fopen(filePath, "w");
    if (file == NULL)
        return 0;
    CURL* curl; // дескриптор
    curl = curl_easy_init(); // получаем дескриптор
    curl_easy_setopt(curl, CURLOPT_URL, url); // общаться надо с этим адресом
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFuncForCurl); // писать в мой файл надо по такой функции
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file); // писать надо в file
    curl_easy_perform(curl); // общение с сайтом так, как мы описали в setopt
    curl_easy_cleanup(curl); // деструктор дескриптора
    fclose(file);
    return 1;
}

int addBetween(const String* to_find, String* to_add, const char* first, const char* second, int from) {
    if (from == EOF)
        return EOF;
    int i;
    for (;from < to_find->len; from++) {
        i = 0;
        while (first[i] != '\0' && from+i < to_find->len && to_find->text[from+i] == first[i]) {
            i++;
        }
        if (first[i] == '\0') {
            from += i;
            for (;from < to_find->len; from++) {
                i = 0;
                while (second[i] != '\0' && from+i < to_find->len && to_find->text[from+i] == second[i]) {
                    i++;
                }
                if (second[i] == '\0') {
                    return from;
                }
                addChar(to_find->text[from+i], to_add);
            }
            return EOF;
        }
    }
    return EOF;
}

int articlesToFiles(const String* to_read, const char* dirname, int from, int to, int* articleId) {
    Meta* info = newMeta();
    String* forInt = newString();
    char tmpStr[10];

    do {
        from++;
        clearMeta(info);
        from = addBetween(to_read, info->author, "<span class=\"user-info__nickname user-info__nickname_small\">", "</span>", from++);
        if (from >= to)
            break;
        from = addBetween(to_read, info->time, "<span class=\"post__time\">", "</span>", from++);
        from = addBetween(to_read, info->link, "<a href=\"", "\" class=\"post__title_link\">", from++);
        from = addBetween(to_read, info->title, "class=\"post__title_link\">", "</a>", from++);

        from = addBetween(to_read, forInt, "<span class=\"post-stats__result-counter voting-wjt__counter_positive \" title=\"", "\">", from++);
        forInt->len = 0; //clear
        from = addBetween(to_read, forInt, "\">", "</span>", from++);
        addChar('\0', forInt);
        info->rate = atoi(forInt->text);

        from = addBetween(to_read, forInt, "<span class=\"post-stats__comments-count\" title=\"", "\">", from++);
        forInt->len = 0; //clear
        from = addBetween(to_read, forInt, "\">", "</span>", from++);
        addChar('\0', forInt);
        info->comments = atoi(forInt->text);

        if (from != EOF) {
            (*articleId)++;
            addText(info->localLink, dirname);
            addText(info->localLink, "/id_");
            sprintf(tmpStr, "%d", *articleId);
            addText(info->localLink, tmpStr);
            addText(info->localLink, "_rate_");
            sprintf(tmpStr, "%d", info->rate);
            addText(info->localLink, tmpStr);
            addChar('\0', info->localLink);
            addChar('\0', info->link);
            fillFileFromURL(info->localLink->text, info->link->text);

            //printf(">>>:%d is %d/%d/%d\n", getpid(), lastfrom, from, to);
            printMeta(info);
            //copyToSharedMeta(info, &(articles[(*articleId) - 1]));
            //printf("SHARED WITH: %d - %d\n", (*articleId) - 1, articles[(*articleId) - 1].title->len);
            //printf("Title len: %d, %d, %d\n", articles[0].title->len, (int)articles[0].title, (int)articles[(*articleId) - 1].title);
        }
        from = addBetween(to_read, forInt, "<header class=\"post__meta\">", " ", from++);
    } while (from != EOF && from < to);
    return 0;
}

int main(int argc, char** argv) {
    time_t startTime = time(NULL);
    String* data = newString();
    //if (!fillStringFromFile(data, "view-source_https___habr.com_ru_top_yearly_.html"))
    //    return ERR_WRONG_FILENAME;
    if (argc != 2) {
        printf("%s using: %s [directory_name]\n", argv[0], argv[0]);
        return ERR_LOW_ARGS;
    }

    DIR* dir;
    if ((dir = opendir(argv[1])) == NULL) {
        printf("Directory %s doesn't exist.\n", argv[1]);
        return ERR_WRONG_DIRNAME;
    }
    closedir(dir);

    if (!fillStringFromURL(data, URL))
        return ERR_WRONG_URL;
    //print(0, data->len, data);

    int cores = sysconf(_SC_NPROCESSORS_CONF);
    //printf(">>>DATA LENGTH: %d\n", data->len);
    pid_t pids[cores];
    pid_t pid = 1;
    int* articleId = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //Meta* articles = mmap(NULL, sizeof(Meta) * ARTICLES_ON_PAGE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int procNum = 0; pid > 0 && procNum < cores; procNum++) {
        pid = fork();
        pids[procNum] = pid;
        switch (pid) {
        case -1:
            printf("Can't open new process.");
            return ERR_NEW_PROCESS;
        case 0:
            //printf("%d:=== %d-%d\n", getpid(), data->len/cores*procNum, data->len/cores*(procNum+1));
            articlesToFiles(data, argv[1], data->len/cores*procNum, data->len/cores*(procNum+1), articleId);
            return 0;
        }
    }
    int status;
    for (int procNum = 0; procNum < cores; procNum++) {
        waitpid(pids[procNum], &status, WUNTRACED | WCONTINUED);
        //printf("Proc %d ends\n", pids[procNum]);
    }

    time_t endTime = time(NULL);
    printf("Time at all: %d sec.\n", (int)difftime(endTime, startTime));
    /*
    for (int i = 0; i < 3; i++) {
        printMeta(&(articles[i]));
    }
    */
    return 0;
}
