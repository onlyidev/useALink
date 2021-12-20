#pragma once
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
char *chooseBgColor(int number);
/* 
    textToPara:
    "I am text" => "<p>I am text</p>"
 */
char *textToPara(char *text);

/* 
    textToSpan:
    "I am text" => "<span>I am text</span>"
 */

char *textToSpan(char *text);

/* 
    textToHeading:
    ("I am text", [1-6]) => "<h[1-6]>I am text</h[1-6]>"
 */
char *textToHeading(char *text, int level);

/* 
    makeLink:
    ("I am text", "https://whatever.com") => "<h href='https://whatever.com'>I am text</h>"
 */
char *makeLink(char *url);

/* 
    textToTitle:
    "I am text" => "<title>I am text</title>"
 */
char *textToTitle(char *text);

/* 
    applyStyle:
    ("<p>I am text</p>", "display: none;") => "<p style='display: none;'>I am text</p>"
 */
char *applyStyle(char *html, char *css);

/* 
    makeStyle:
    ".no-display {display: none;}" => "<style>.no-display {display: none;}</style>"
 */
char *makeStyle(char *css);

/* 
    makeBody:
    "<p>I am text</p>" => "<body><p>I am text</p></body>"
 */
char *makeBody(char *html);

/* 
    makeHead:
    "<title>I am text</title>" => "<head><title>I am text</title></head>"
 */
char *makeHead(char *html);

/* 
    generateHTML:
    Output html to file
 */
void generateHTML(char *html, FILE *file);

/* 
    concat:
    (3, "He", "l", "lo") ==> "Hello"
 */

char *concat(int argc, ...);

/* 
    addAttribute: 
    ("<p>Hello</p>", "align", "center") ==> "<p align='center'>Hello</p>"
 */

char *addAttribute(char *html, char *attr, char *value);
