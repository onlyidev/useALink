#pragma once
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* 
    textToPara:
    "I am text" => "<p>I am text</p>"
 */
void textToPara(char **text);

/* 
    textToSpan:
    "I am text" => "<span>I am text</span>"
 */

void textToSpan(char **text);

/* 
    textToHeading:
    ("I am text", [1-6]) => "<h[1-6]>I am text</h[1-6]>"
 */
void textToHeading(char **text, int level);

/* 
    makeLink:
    ("I am text", "https://whatever.com") => "<h href='https://whatever.com'>I am text</h>"
 */
void makeLink(char **text, char *url);

/* 
    textToTitle:
    "I am text" => "<title>I am text</title>"
 */
void textToTitle(char **text);

/* 
    applyStyle:
    ("<p>I am text</p>", "display: none;") => "<p style='display: none;'>I am text</p>"
 */
void applyStyle(char **html, char *css);

/* 
    makeStyle:
    ".no-display {display: none;}" => "<style>.no-display {display: none;}</style>"
 */
void makeStyle(char **css);

/* 
    makeBody:
    "<p>I am text</p>" => "<body><p>I am text</p></body>"
 */
void makeBody(char **html);

/* 
    makeHead:
    "<title>I am text</title>" => "<head><title>I am text</title></head>"
 */
void makeHead(char **html);

/* 
    generateHTML:
    Output html to file
 */
void generateHTML(char *html, FILE *file);

void ual_concat(int argc, char **buff, ...);

void addAtribute(char **html, char *attr, char *value);
