#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "htmlFunctions.h"

int main(int argc, char *argv[]) {

    /* 
        <html>
    <head>
        <title>Naudingos nuorodos</title>
    </head>

    <body leftmargin="200 "bgcolor="azure">
        <h1 align="center">Vartotojo įvestos nuorodos</h1>
        <p align="right">Liudas Kasperavičius<br>Naglis Kontautas<br>Rokas Jurėnas</p>
        <!-- Sita dali kartojam -->
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <p><a href="NUORODA">NUORODA</a></p>
        <!-- Sita dali kartojam -->
    </body>
</html>
     */

    FILE *out = fopen("index.html", "w");

    char *body = concat(3, 
        addAtribute(textToHeading("Vartotojo įvestos nuorodos", 1), "align", "center"),
        addAtribute(textToPara("Liudas Kasperavičius<br>Naglis Kontautas<br>Rokas Jurėnas"), "align", "right"),
        textToPara(makeLink("NUORODA", "google.com"))
    );


    body = addAtribute(body, "leftmargin", "200");
    body = addAtribute(body, "bgcolor", "azure");

    generateHTML(concat(2,
        makeHead(textToTitle("Naudingos nuorodos")),
        makeBody(body)
    ), out);

    fclose(out);

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

char *addAtribute(char *html, char *attr, char *value) {
    
    char *str = malloc(strlen(html) + strlen(attr) + strlen(value) + 5);

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
    
    char *str = malloc(strlen(html) + 13);

    strcpy(str, "<html>");
    strcat(str, html);
    strcat(str, "</html>");

    fprintf(file, "%s", str);

    free(str);

    return;
}