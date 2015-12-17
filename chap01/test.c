#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char str[] = "now # is the time # to start preparing ## for the exam##";  // char array
    char delims[] = "#";
    char *token = NULL;
    char *tokens[100];
    int i=0;

    printf("Before:%s\n", str);

//    token = strtok( str, delims );
//    while ( token != NULL ) {
//        printf( "next token is: %s:%d\n", token, strlen(token));
//        token = strtok( NULL, delims );
//        tokens[i++] = token;
//    }

    char * string = strdup(str);
    while ((token = strsep(&string, " ")) != NULL ) {
        printf( "next token is:%s:%d\n", token, strlen(token));
//        tokens[i++] = token;
    }
    printf("After:#%s#\n", str);
    return 0;
}