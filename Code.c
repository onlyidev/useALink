#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htmlFunctions.h"

int main(int argc, char *argv[]) {
    
    FILE* web = fopen("website.html", "w");
    char webLink[256] = "labas";

    if(web == NULL){
        printf("error when creating a website.html file :<");
        exit(420);
    }

    fprintf(web, "<html>\n\t<head>\n\t<title>Naudingos nuorodos</title>\n </head>\n\n <body leftmargin=\"200\" bgcolor=\"azure\">\n\t\t<h1 align=\"center\">Vartotojo įvestos nuorodos</h1>\n\t\t<p align=\"right\">Liudas Kasperavičius<br>Naglis Kontautas<br>Rokas Jurėnas</p>\n\n");
    printf("This program creates html site where user's links are presented.\nInsert \"0\" to end the program.\nEnter a link: ");

    scanf("%256[^\n]", &webLink);
    while(*webLink != '0'){
        getchar();
        fprintf(web,"%s", makeLink(webLink));
        printf("\nEnter a link: ");
        scanf("%256[^\n]", &webLink);
    }

    printf("The program ended ;)");
    fprintf(web,"\t</body>\n</html>");
    fclose(web);
    return 0;
}

char *textToPara(char *text) {

    return "";
}

char *textToSpan(char *text) {

    return "";
}

char *textToHeading(char *text, int level) {

    return "";
}

char *makeLink(char *url){
    char *link = calloc(strlen(url)*2+26, 1);
    sprintf(link, "\t\t<p><a href=\"%s\">%s</a></p>\n", url, url);
    return link;
}

char *textToTitle(char *text) {

    return "";
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

char *concat(int argc, ...) {

    return "";
}

char *addAttribute(char *html, char *attr, char *value) {

    return "";
}