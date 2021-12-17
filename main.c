#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "htmlFunctions.h"


int memAlloc;

void *__wrap_malloc(size_t size) {
    ++memAlloc;
    printf("Allocations: %d\n", memAlloc);
    return __real_malloc(size);
}

void getUserInput(FILE **input, char **title, char **heading, char **sideText) {

    char *str = calloc(256, 1);

    printf("What's the title of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *title = malloc(strlen(str));
    strcpy(*title, str);
    memset(str, 0, 256);

    printf("What is the Heading of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *heading = malloc(strlen(str));
    strcpy(*heading, str);
    memset(str, 0, 256);



    printf("What's the side text (html) of the page? ");
    scanf("%256[^\n]", str);
    getchar();
    *sideText = malloc(strlen(str));
    strcpy(*sideText, str);
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

/* char *getLinks(FILE *input) {
    char str[256];

    int newLines = 0;

    for(char c = getc(input); c != EOF; c = getc(input))
        newLines += (c == '\n' ? 1 : 0);

    fseek(input, 0L, SEEK_END);
    char *link = calloc(ftell(input) + 15*newLines, 1);

    memset(link, 0, strlen(link));

    printf("Found %d links.\n", newLines);

    rewind(input);
    
    while(!feof(input)) {
        if(!fgets(str, 255, input))
            break;
        
        sscanf(str, "%255[^\n]", str);

        strcat(link, textToPara(makeLink(str, str)));
    }


    return link;

} */

int main(int argc, char *argv[]) {

    FILE *out = fopen("index.html", "w");
    FILE *in = NULL;

    char *title, *heading, *sideText;

    getUserInput(&in, &title, &heading, &sideText);

    fprintf(out, "<html>\n");

    textToTitle(&title);
    makeHead(&title);
    fprintf(out, "%s", title);

    textToHeading(&heading, 1);
    textToPara(&sideText);
    ual_concat(3, &heading, "<body>", heading, sideText);
    fprintf(out, "%s", heading);

    // Scan links one by one
    while(!feof(in)) {
        char *str = malloc(256);
        if(!fscanf(in, "%256[^\n]", str) || !strcmp(str, "\n"))
            break;
        getc(in);

        makeLink(&str, str);
        textToPara(&str);
        fprintf(out, "%s", str);
        // printf("%s\n\n", str);
        free(str);
    }
    fprintf(out, "</body></html>");

    free(title);
    free(sideText);
    free(heading);

    fclose(in);
    fclose(out);

    return 0;
}

void textToPara(char **text) {

    char *str = malloc(strlen(*text));
    strcpy(str, *text);
    ual_concat(3, text, "<p>", str, "</p>");
    free(str);
}

void textToSpan(char **text) {

    char *str = malloc(strlen(*text));
    strcpy(str, *text);
    ual_concat(3, text, "<span>", str, "</span>");
    free(str);
}

void textToHeading(char **text, int level) {
    
    char heading[5], cheading[6];

    sprintf(heading, "<h%d>", level);
    sprintf(cheading, "</h%d>", level);

    char *str = malloc(strlen(*text));
    strcpy(str, *text);
    ual_concat(3, text, heading, str, cheading);
    free(str);
}

void makeLink(char **text, char *url) {

    int _url = strlen(url);

    char *openA = calloc(_url + 15, 1);
    sprintf(openA, "<a href='%*s'>", _url, url);

    char *str = malloc(strlen(*text));
    strcpy(str, *text);
    ual_concat(3, text, openA, str, "</a>");
    free(str);
    free(openA);
}

void textToTitle(char **text) {

    char *str = malloc(strlen(*text));
    strcpy(str, *text);
    ual_concat(3, text, "<title>", str, "</title>");
    free(str);
}

/* char *applyStyle(char *html, char *css) {
    int len;

    for(len = 0; html[len] != '>'; ++len) 
        ;

    char *str = calloc(len, 1);

    strncpy(str, html, len);
    
    char *ret = ual_concat(5, str, " style='", css, "'", html + len);

    free(str);

    return ret;
} */

/* char *makeStyle(char *css) {

    return ual_concat(3, "<style>", css, "</style>");
} */

void makeBody(char **html) {
    
    char *str = malloc(strlen(*html));
    strcpy(str, *html);
    ual_concat(3, html, "<body>", str, "</body>");
    free(str);
}

void makeHead(char **html) {
    
    char *str = malloc(strlen(*html));
    strcpy(str, *html);
    ual_concat(3, html, "<head>", str, "</head>");
    free(str);
}

void addAtribute(char **html, char *attr, char *value) {
    
    int len = 0;

    while(*html[len] != '>')
        ++len;

    char *str = calloc(len, 1);

    strncpy(str, *html, len);

    char *cpy = malloc(strlen(*html));
    strcpy(cpy, *html);

    ual_concat(7, html, cpy, " ", attr, "='", value, "'", cpy+len);

    free(str);
    free(cpy);
}

void ual_concat(int argc, char **buff, ...) {
    va_list args;

    int len = 0;

    va_start(args, buff);
    for(int i = 0; i < argc; ++i) 
        len += strlen(va_arg(args, char *));
    va_end(args);

    if(strlen(*buff) < len)
        *buff = realloc(*buff, len);
    memset(*buff, 0L, strlen(*buff));

    va_start(args, buff);

    for(int i = 0; i < argc; ++i)
        strcat(*buff, va_arg(args, char *));
    va_end(args);

    printf("%s\n", *buff);

}

void generateHTML(char *html, FILE *file) {
    
    char *str;
    ual_concat(3, &str, "<html>", html, "</html>");

    fprintf(file, "%s", str);

    free(str);

    return;
}