//
// Created by Oh-Heum Kwon on 8/18/15.
//

#include "my_string_tools.h"

int is_match(char * pattern, char * text) {
    for (int i=0; i<=strlen(text)-strlen(pattern); i++) {
        int j=0;
        for (; j<strlen(pattern); j++) {
            if (pattern[j] != text[i+j])
                break;
        }
        if (j>=strlen(pattern))
            return 1;
    }
    return 0;
}

int compose_name(char str[], int limit) {
    char * ptr;
    int length = 0;
    ptr = strtok(NULL, " ");
    if (ptr == NULL)
        return 0;
    strcpy(str, ptr);
    length += strlen(ptr);
    while ((ptr = strtok(NULL, " ")) != NULL) {
        if (length + strlen(ptr) + 1 < limit) {
            str[length++] = ' ';
            str[length] = '\0';
            strcat(str, ptr);
            length += strlen(ptr);
        }
    }
    return length;
}

int read_line(FILE * fp, char str[], int n)
{
    int ch, i = 0;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}


int merge_tokens(int s, int t, char *tokens[], int limit, char merged[])
{
    int length = 0;
    strcpy(merged, tokens[s]);
    length = strlen(merged);
    for (int i=s+1; i<t && length + strlen(tokens[i]) < limit - 1; i++) {
        merged[length++] = ' ';
        merged[length] = '\0';
        strcat(merged, tokens[i]);
        length += strlen(tokens[i]);
    }
    return length;
}

int parse_line(int max_tokens, char * tokens[], char * line, char * delim)
{
    char * ptr = strtok(line, delim);
    int i = 0;
    while(i<max_tokens && ptr != NULL)
    {
        tokens[i++] = strdup(ptr);
        ptr = strtok(NULL, delim);
    }
    return i;
}

int read_line_elim_leading_blank(FILE * fp, char str[], int n)
{
    int ch, i = 0;
    while ((ch=fgetc(fp)) == ' ' );
    while (ch != '\n' && ch != EOF) {
        if (i<n)
            str[i++] = ch;
        ch = fgetc(fp);
    }
    str[i] = '\0';
    return i;
}

