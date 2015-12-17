//
// Created by Oh-Heum Kwon on 8/18/15.
//

#ifndef CHAP01_COMMAND_LINE_H
#define CHAP01_COMMAND_LINE_H

#include <string.h>
#include <stdio.h>

int merge_tokens(int s, int t, char * tokens[], int limit, char merged[]);

int parse_line(int max_tokens, char * tokens[], char * line, char * delim);

int read_line(FILE * fp, char str[], int n);

int compose_name(char str[], int limit);

int is_match(char * pattern, char * text);

int read_line_elim_leading_blank(FILE * fp, char str[], int n);
#endif //CHAP01_COMMAND_LINE_H
