//
// Created by Oh-Heum Kwon on 8/18/15.
//

#include "manage_directory.h"

Person * directory;
int capacity = INIT_CAPACITY;
int n = 0;

void init_directory()  {
    directory = (Person *)malloc(INIT_CAPACITY*sizeof(Person));
}

void match(int s, int t, char *keywords[]) {
    for (int i=s; i<t; i++) {
        for (int j=0; j<n; j++) {
            if (is_match(keywords[i], directory[j].name)) {
                print_person(directory[j]);
            }
        }
    }
}

void load(char *fileName) {
    char buffer[BUFFER_LENGTH];
    char * name, *number, *email, *group;

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    while (1) {
        if (read_line(fp, buffer, BUFFER_LENGTH)<=0)
            break;
        name = strtok(buffer, "#");
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(name, number, email, group);
    }
    fclose(fp);
}

void save(char *fileName) {
    int i;
    FILE *fp = fopen(fileName, "w");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    for (i=0; i<n; i++) {
        fprintf(fp, "%s#", directory[i].name);
        fprintf(fp, "%s#", directory[i].number);
        fprintf(fp, "%s#", directory[i].email);
        fprintf(fp, "%s#\n", directory[i].group);
    }
    fclose(fp);
}

int search(char *name) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(name, directory[i].name)==0) {
            return i;
        }
    }
    return -1;
}

void remove(char *name) {
    int i = search(name);  /* returns -1 if not exists */
    if (i == -1) {
        printf("No person named '%s' exists.\n", name);
        return;
    }

    int j = i;
    for (; j<n-1; j++) {
        directory[j] = directory[j+1];
    }
    n--;
    printf("'%s' was deleted successfully. \n", name);
}

void print_person(Person p)
{
    printf("%s:\n", p.name);
    printf("   Phone: %s\n", p.number);
    printf("   Email: %s\n", p.email);
    printf("   Group: %s\n", p.group);
}


void status() {
    int i;
    for (i=0; i<n; i++)
        print_person(directory[i]);
    printf("Total %d persons.\n", n);
}

void find(char *name) {
    int index = search(name);
    if (index==-1)
        printf("No person named '%s' exists.\n", name);
    else
        print_person(directory[index]);
}

void reallocate()
{
    int i;
    capacity *= 2;
    Person * tmp = (Person *)malloc(capacity*sizeof(Person));
    for (i=0; i<n; i++) {
        tmp[i] = directory[i];
    }
    free(directory);
    directory = tmp;
}

void add(char * name, char * number, char * email, char * group) {

    if (n>=capacity)
        reallocate();

    int i=n-1;
    while (i>=0 && strcmp(directory[i].name, name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }

    directory[i+1].name = strdup(name);
    directory[i+1].number = strdup(number);
    directory[i+1].email = strdup(email);
    directory[i+1].group = strdup(group);
    n++;
}