#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "htmlFunctions.h"


int main(int argc, char *argv[]) {

    char *head, *body;

    printf("<html>\n%s\n%s</html>\n", head = makeHead(concat(2, 
    makeStyle("body {background: #333;}"),
    textToTitle("I am the title"))),
     body = makeBody(concat(2,
      textToHeading("Header 1", 1),
       makeLink(applyStyle(textToSpan("This is a span!"), "color: red;"), "https://google.com"))));

    free(head);
    free(body);

    return 0;
}

char *textToPara(char *text) {
    
    char *str = malloc(strlen(text) + 7);

    strcpy(str, "<p>");
    strcat(str, text);
    strcat(str, "</p>");

    return str;
}

char *textToSpan(char *text) {

    char *str = malloc(strlen(text) + 13);

    strcpy(str, "<span>");
    strcat(str, text);
    strcat(str, "</span>");

    return str;
}

char *textToHeading(char *text, int level) {
    
    char *str = malloc(strlen(text) + 9);

    char heading[5], cheading[6];

    sprintf(heading, "<h%d>", level);
    sprintf(cheading, "</h%d>", level);

    strcpy(str, heading);
    strcat(str, text);
    strcat(str, cheading);

    return str;
}

char *makeLink(char *text, char *url) {

    int _url = strlen(url);
    int _text = strlen(text);

    char *openA = malloc(_url + 11);
    sprintf(openA, "<a href='%*s'>", _url, url);

    char *str = malloc(_text + _url + 15); 

    strcpy(str, openA);
    strcat(str, text);
    strcat(str, "</a>");

    free(openA);

    return str;
}

char *textToTitle(char *text) {
    
    char *str = malloc(strlen(text) + 15);

    strcpy(str, "<title>");
    strcat(str, text);
    strcat(str, "</title>");

    return str;
}

char *applyStyle(char *html, char *css) {
    int len;

    for(len = 0; html[len] != '>'; ++len) 
        ;

    char *str = malloc(strlen(html) + strlen(css) + 9);

    strncpy(str, html, len);
    strcat(str, " style='");
    strcat(str, css);
    strcat(str, "'");
    strcat(str, html + len);

    return str;
}

char *makeStyle(char *css) {

    char *str = malloc(strlen(css) + 15);

    strcpy(str, "<style>");
    strcat(str, css);
    strcat(str, "</style>");

    return str;
}

char *makeBody(char *html) {
    
    char *str = malloc(strlen(html) + 13);

    strcpy(str, "<body>");
    strcat(str, html);
    strcat(str, "</body>");

    return str;
}

char *makeHead(char *html) {

    char *str = malloc(strlen(html) + 13);

    strcpy(str, "<head>");
    strcat(str, html);
    strcat(str, "</head>");

    return str;
}

char *concat(int argc, ...) {
    va_list args;

    int len = 0;

    va_start(args, argc);
    for(int i = 0; i < argc; ++i)
        len += strlen(va_arg(args, char *));
    va_end(args);

    char *str = malloc(len);

    va_start(args, argc);

    for(int i = 0; i < argc; ++i) 
        strcat(str, va_arg(args, char *));
    va_end(args);

    return str;

}

void generateHTML(char *html, FILE *file) {

    return;
}