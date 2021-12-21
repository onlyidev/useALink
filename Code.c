#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htmlFunctions.h"
#include <regex.h>

void findAndPrint(FILE *input);
void changeLinkName(FILE *input, int opt);

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

    printf("The program ended ;)\n");
    fprintf(web,"\t</body>\n</html>");
    // fclose(web);

    freopen("website.html", "r+", web);
    findAndPrint(web);

    // int option;
    // printf("----------------------\nSelect link number to change. Type 0 to stop.\n");
    // scanf("%d", &option);
    // if(option > 0)
    //     changeLinkName(web, option);

    return 0;
}

char *makeLink(char *url){
    char *link = calloc(strlen(url)*2+26, 1);
    sprintf(link, "\t\t<p><a href=\"%s\">%s</a></p>\n", url, url);
    return link;
}

void findAndPrint(FILE *input) {

    rewind(input);

    char line[256];

    regex_t regex;
    regmatch_t m;

    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    reti = regcomp(&regex, "href=['\"].*['\"]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    int matchCount = 0;

    while(!feof(input)) {
        if(!fgets(line, 256, input))
            break;

        /* Execute regular expression */
        reti = regexec(&regex, line, 1, &m, 0);
        if (!reti) {
            printf("%d: %.*s\n", ++matchCount, (m.rm_eo - m.rm_so - 7), (line + m.rm_so + 6));
        }
        else if(reti != REG_NOMATCH) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    regfree(&regex);

}

void changeLinkName(FILE *input, int opt) {
    rewind(input);

    int matchCount = 0;

}