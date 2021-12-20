#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htmlFunctions.h"

int main(int argc, char *argv[]){
    FILE* linksFile = NULL;
    FILE* web = fopen("website.html", "w");
    char webLink[256] = "\0";
    char linkFileName[256] = "";

    if(web == NULL){
        printf("error opening a Links.txt file :<");
        exit(1);
    }

    printf("\nEnter file name and extension, where links are: ");
    
    while(linksFile == NULL){
        getchar();
        scanf("%256[^\n]", &linkFileName);
        linksFile = fopen(linkFileName, "r");
        if(linksFile == NULL){
            printf("\nNo file detected.\nPlease enter again:<");
        }
    }
    printf("\nThis program creates html site where user's links are presented.\n");
    
    printf("MENU\nType a number of a background color to choose it.\n0 - White\n1 - Azure\n2 - Beige\n3 - Chocolate\n4 - SkyBlue\n5 - Cornsilk\n6 - Silver\n7 - DarkSeaGreen\n");
    int bgColorNum = -1;
    while(bgColorNum < 0 || bgColorNum > 7){
        scanf("%d", &bgColorNum);
        if(bgColorNum > 7 || bgColorNum < 0){
            printf("please insert a valid number\n");
        }
    }
    
    fprintf(web, "<html>\n\t<head>\n\t<title>Naudingos nuorodos</title>\n </head>\n\n <body leftmargin=\"200\"%s\n\t\t<h1 align=\"center\">Vartotojo įvestos nuorodos</h1>\n\t\t<p align=\"right\">Liudas Kasperavičius<br>Naglis Kontautas<br>Rokas Jurėnas</p>\n\n", chooseBgColor(bgColorNum));

    while(!feof(linksFile)){
        fscanf(linksFile, "%s", &webLink);
        fprintf(web,"%s", makeLink(webLink));
    }
    fprintf(web, "\n\t\t<p align=\"right\"><img src=\"minion.jpg\">\n");

    fprintf(web,"\t</body>\n</html>");
    fclose(web);
    fclose(linksFile);
    printf("The program has ended ;)");
    return 0;
}

char *chooseBgColor(int number){
    char color[][15]= {"White", "Azure", "Beige", "Chocolate", "SkyBlue", "Cornsilk", "Silver", "DarkSeaGreen"};
    char *bgStyle = calloc(strlen(color[number]) + 14, 1);
    sprintf(bgStyle, " bgcolor=\"%s\">", color[number]);
    return bgStyle;
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