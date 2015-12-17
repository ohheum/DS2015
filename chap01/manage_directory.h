//
// Created by Oh-Heum Kwon on 8/18/15.
//

#ifndef MANAGE_DIRECTORY_H
#define MANAGE_DIRECTORY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string_tools.h"

#define INIT_CAPACITY 3
#define BUFFER_LENGTH 100
#define MAX_TOKENS 20

typedef struct {
    char * name;
    char * number;
    char * email;
    char * group;
} Person;

void init_directory();
void match(int s, int t, char *keywords[]);
void load(char *fileName);
void save(char *fileName);
void status();
void find(char *name);
int search(char *name);
void print_person(Person p);
void add(char * name, char * number, char * email, char * type);
void remove(char *name);

#endif //MANAGE_DIRECTORY_H
