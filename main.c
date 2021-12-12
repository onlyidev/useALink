#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "htmlFunctions.h"

void getUserInput(FILE **input, char **title, char **heading, char **sideText) {

    char *str = calloc(256, 1);

    printf("What's the title of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *title = textToTitle(str);
    memset(str, 0, 256);

    printf("What is the Heading of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *heading = textToHeading(str, 1);
    memset(str, 0, 256);



    printf("What's the side text (html) of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *sideText = textToPara(str);
    memset(str, 0, 256);


    fileinput:
    printf("What is the filename of useful links? ");
    scanf("%256[^\n]", str);
    getchar();

    if(!(*input = fopen(str, "r"))) {
        printf("Unable to open file. Does it exist? Check permissions.\n");
        goto fileinput;
    }

    free(str);

}

char *getLinks(FILE *input) {
    char str[256];

    fseek(input, 0L, SEEK_END);

    if(ftell(input) > 1300) {
        printf("Sorry, that's a little too many links for this version.\n");
        exit(0);
    }

    char *link = calloc(ftell(input)*4, 1); //Guess

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

    char *body = makeBody(ual_concat(3, 
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

    generateHTML(ual_concat(2,
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
    
  return ual_concat(3, "<p>", text, "</p>");
}

char *textToSpan(char *text) {

    return ual_concat(3, "<span>", text, "</span>");
}

char *textToHeading(char *text, int level) {
    
    char heading[5], cheading[6];

    sprintf(heading, "<h%d>", level);
    sprintf(cheading, "</h%d>", level);

    return ual_concat(3, heading, text, cheading);
}

char *makeLink(char *text, char *url) {

    int _url = strlen(url);

    char *openA = calloc(_url + 15, 1);
    sprintf(openA, "<a href='%*s'>", _url, url);

    char *str = ual_concat(3, openA, text, "</a>");

    free(openA);

    return str;
}

char *textToTitle(char *text) {

    return ual_concat(3, "<title>", text, "</title>");
}

char *applyStyle(char *html, char *css) {
    int len;

    for(len = 0; html[len] != '>'; ++len) 
        ;

    char *str = calloc(len, 1);

    strncpy(str, html, len);
    
    char *ret = ual_concat(5, str, " style='", css, "'", html + len);

    free(str);

    return ret;
}

char *makeStyle(char *css) {

    return ual_concat(3, "<style>", css, "</style>");
}

char *makeBody(char *html) {
    
    return ual_concat(3, "<body>", html, "</body>");
}

char *makeHead(char *html) {

    return ual_concat(3, "<head>", html, "</head>");
}

char *addAtribute(char *html, char *attr, char *value) {
    
    int len = 0;

    while(html[len] != '>')
        ++len;

    char *str = calloc(len, 1);

    strncpy(str, html, len);

    char *ret = ual_concat(7, str, " ", attr, "='", value, "'", html+len);

    free(str);

    return ret;
}

char *ual_concat(int argc, ...) {
    va_list args;

    int len = 0;

    va_start(args, argc);
    for(int i = 0; i < argc; ++i) 
        len += strlen(va_arg(args, char *));
    va_end(args);

    char *str = calloc(len, 1);

    va_start(args, argc);

    for(int i = 0; i < argc; ++i)
        strcat(str, va_arg(args, char *));
    va_end(args);

    return str;

}

void generateHTML(char *html, FILE *file) {
    
    char *str = ual_concat(3, "<html>", html, "</html>");

    fprintf(file, "%s", str);

    free(str);

    return;
}