#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "htmlFunctions.h"

void getUserInput(FILE **input, char **title, char **heading, char **sideText) {

    char str[256];

    printf("What's the title of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *title = textToTitle(str);

    printf("What is the Heading of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *heading = textToHeading(str, 1);


    printf("What's the side text (html) of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *sideText = textToPara(str);


    fileinput:
    printf("What is the filename of useful links? ");
    scanf("%256[^\n]", str);
    getchar();

    if(!(*input = fopen(str, "r"))) {
        printf("Unable to open file. Does it exist? Check permissions.\n");
        goto fileinput;
    }

}

char *getLinks(FILE *input) {
    char str[256];

    fseek(input, 0L, SEEK_END);

    char *link = calloc(ftell(input)*4, 1);

    rewind(input);

    while(!feof(input)) {
        if(!fgets(str, 255, input))
            break;
        
        sscanf(str, "%255[^\n]", str);

        strcat(link, textToPara(makeLink(str, str)));
    }

    return link;

}

int main(int argc, char *argv[]) {

    FILE *out = fopen("index.html", "w");
    FILE *in = NULL;

    char *title, *heading, *sideText, *links;

    getUserInput(&in, &title, &heading, &sideText);

    char *body = makeBody(concat(3, 
        addAtribute(heading, "align", "center"),
        addAtribute(sideText, "align", "right"),
        links = getLinks(in)
    ));

    char *head = makeHead(title);

    free(title);
    free(heading);
    free(sideText);
    free(links);

    body = addAtribute(body, "leftmargin", "200");
    body = addAtribute(body, "bgcolor", "azure");

    generateHTML(concat(2,
        head,
        body
    ), out);

    free(head),
    free(body);

    fclose(in);
    fclose(out);

    return 0;
}

char *textToPara(char *text) {
    
    char *str = calloc(strlen(text) + 7, 1);


    strcpy(str, "<p>");
    strcat(str, text);
    strcat(str, "</p>");

    return str;
}

char *textToSpan(char *text) {

    char *str = calloc(strlen(text) + 13, 1);

    strcpy(str, "<span>");
    strcat(str, text);
    strcat(str, "</span>");


    return str;
}

char *textToHeading(char *text, int level) {
    
    char *str = calloc(strlen(text) + 9, 1);

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

    char *openA = calloc(_url + 15, 1);
    sprintf(openA, "<a href='%*s'>", _url, url);

    char *str = calloc(_text + _url + 12, 1); 

    strcpy(str, openA);
    strcat(str, text);
    strcat(str, "</a>");

    free(openA);

    return str;
}

char *textToTitle(char *text) {
    
    char *str = calloc(strlen(text) + 15, 1);

    strcpy(str, "<title>");
    strcat(str, text);
    strcat(str, "</title>");

    return str;
}

char *applyStyle(char *html, char *css) {
    int len;

    for(len = 0; html[len] != '>'; ++len) 
        ;

    char *str = calloc(strlen(html) + strlen(css) + 9, 1);

    strncpy(str, html, len);
    strcat(str, " style='");
    strcat(str, css);
    strcat(str, "'");
    strcat(str, html + len);

    return str;
}

char *makeStyle(char *css) {

    char *str = calloc(strlen(css) + 14, 1);

    strcpy(str, "<style>");
    strcat(str, css);
    strcat(str, "</style>");

    return str;
}

char *makeBody(char *html) {
    
    char *str = calloc(strlen(html) + 13, 1);

    strcpy(str, "<body>");
    strcat(str, html);
    strcat(str, "</body>");

    return str;
}

char *makeHead(char *html) {

    char *str = calloc(strlen(html) + 13, 1);

    strcpy(str, "<head>");
    strcat(str, html);
    strcat(str, "</head>");

    return str;
}

char *addAtribute(char *html, char *attr, char *value) {
    
    char *str = calloc(strlen(html) + strlen(attr) + strlen(value) + 4, 1);

    int len = 0;

    while(html[len] != '>')
        ++len;


    strncpy(str, html, len);
    strcat(str, " ");
    strcat(str, attr);
    strcat(str, "='");
    strcat(str, value);
    strcat(str, "'");
    strcat(str, html + len);

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
    
    char *str = calloc(strlen(html) + 13, 1);

    strcpy(str, "<html>");
    strcat(str, html);
    strcat(str, "</html>");

    fprintf(file, "%s", str);

    free(str);

    return;
}