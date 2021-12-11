#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htmlFunctions.h"


int main(int argc, char *argv[]) {

    char *text = malloc(50);
    strcpy(text, "I am text");

    // printf("%s\n", text = textToPara(text));
    // printf("%s\n", text = textToSpan(text));
    // printf("%s\n", text = textToTitle(text));
    // printf("%s\n", text = textToHeading(text, 3));

    char *link = malloc(50);
    strcpy(link, "https://google.com");

    link = makeLink(text, link);

    puts(link);

    free(text);
    free(link);

    return 0;
}

char *textToPara(char *text) {
    
    int len;

    sscanf(text, "%[^\n]%n", text, &len);

    char *str = malloc(len + 7);

    strcpy(str, "<p>");
    strcpy(str+3, text);
    strcpy(str + len + 3, "</p>");

    free(text);

    return str;
}

char *textToSpan(char *text) {
    
    int len;

    sscanf(text, "%[^\n]%n", text, &len);

    char *str = malloc(len + 13);

    strcpy(str, "<span>");
    strcpy(str+6, text);
    strcpy(str + len + 6, "</span>");

    free(text);

    return str;
}

char *textToHeading(char *text, int level) {
    
    int len;

    sscanf(text, "%[^\n]%n", text, &len);

    char *str = malloc(len + 9);

    char heading[5], cheading[6];

    sprintf(heading, "<h%d>", level);
    sprintf(cheading, "</h%d>", level);

    strcpy(str, heading);
    strcpy(str+4, text);
    strcpy(str + len + 4, cheading);

    free(text);

    return str;
}

char *makeLink(char *text, char *url) {

    int textLen, urlLen;

    sscanf(text, "%[^\n]%n", text, &textLen);
    sscanf(url, "%[^\n]%n", url, &urlLen);


    char *openA = malloc(urlLen + 11);
    sprintf(openA, "<a href='%*s'>", urlLen, url);

    char *str = malloc(textLen + urlLen + 15); 

    strcpy(str, openA);
    strcpy(str + urlLen + 11, text);
    strcpy(str + urlLen + 11 + textLen, "</a>");

    free(openA);
    free(url);

    return str;
}

char *textToTitle(char *text) {
    
    int len;

    sscanf(text, "%[^\n]%n", text, &len);

    char *str = malloc(len + 15);

    strcpy(str, "<title>");
    strcpy(str+7, text);
    strcpy(str + len + 7, "</title>");

    free(text);

    return str;
}

char *applyStyle(char *html, char *css) {

    return "";
}

char *makeStyle(char *css) {

    return "";
}

char *makeBody(char *html) {

    return "";
}

char *makeHead(char *html) {

    return "";
}

void generateHTML(char *html, FILE *file) {

    return;
}