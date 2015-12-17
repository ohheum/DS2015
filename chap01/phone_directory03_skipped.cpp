
/*
 * introducing structure
 * support more fields, but still each name consists of a single word
 * handling exceptions ugly
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_CAPACITY 3
#define BUFFER_SIZE 100

typedef struct {
    char * name;
    char * number;
    char * email;
    char * type;
} Person;

Person * directory;
int capacity = INIT_CAPACITY;
int n = 0;                   /* number of people in phone directory */

void handle_add(char *);
void find(char *);
void status();
void remove(char *);
void load(char *);
void save(char *);
int read_line(FILE *, char *, int);
void add(char*, char*, char*, char*);

const char * delim = " ";

int main() {
    directory = (Person *)malloc(INIT_CAPACITY*sizeof(Person));

    char command[BUFFER_SIZE];
    char * ptr1, *ptr2;

    while (1) {
        printf("$ ");
        read_line(stdin, command, BUFFER_SIZE);
        ptr1 = strtok(command, delim);

        if (strcmp(command, "read") == 0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            load(ptr1);
        }
        else if (strcmp(command, "add") == 0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handle_add(strdup(ptr1));
        }
        else if (strcmp(command, "find") == 0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            find(ptr1);
        }
        else if (strcmp(command, "status")==0)
            status();
        else if (strcmp(command, "delete")==0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            remove(ptr1);
        }
        else if (strcmp(command, "save")==0) {
            ptr1 = strtok(NULL, delim);
            ptr2 = strtok(NULL, delim);
            if (ptr1 == NULL || strcmp("as", ptr1) != 0 || ptr2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            save(ptr2);
        }
        else if (strcmp(command, "exit")==0)
            break;
    }
    return 0;
}

int read_line(FILE * fp, char str[], int n)
{
    int ch, i = 0;
    while ((ch=fgetc(fp)) == ' ' );
    while (i < n && ch != '\n' && ch != EOF) {
        str[i++] = ch;
        ch = fgetc(fp);
    }
    str[i] = '\0';
    return i;

    /*
    int ch, i = 0;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
     */
}

void load(char *fileName) {
    char buffer[BUFFER_SIZE];
    char * ptr;

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    while (!feof(fp)) {
//        if (fgets(buffer, BUFFER_LENGTH, fp)==NULL)
//            break;
        if (read_line(fp, buffer, BUFFER_SIZE) <= 0)
            break;

        ptr = strtok(buffer, "|");
        char * name = strdup(ptr);
        ptr = strtok(NULL, "|");
        char * number = (ptr == NULL || *ptr==' ' || *ptr == '\n' ? NULL :  strdup(ptr));
        ptr = strtok(NULL, "|");
        char * email = (ptr == NULL || *ptr==' ' || *ptr == '\n' ? NULL : strdup(ptr));
        ptr = strtok(NULL, "|");
        char * type = (ptr == NULL || *ptr==' ' || *ptr == '\n' ? NULL : strdup(ptr));

        printf("Name: %s\n", name);
        printf("Number: %s\n", (number==NULL?"None":number));
        printf("Email: %s\n", (email==NULL?"None":email));
        printf("Type: %s\n", (type==NULL?"None":type));

        add(name, number, email, type);
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
        fprintf(fp, "%s", directory[i].name);
        fprintf(fp, "|");
        fprintf(fp, "%s", (directory[i].number != NULL ? directory[i].number : " "));
        fprintf(fp, "|");
        fprintf(fp, "%s", (directory[i].email != NULL? directory[i].email: " "));
        fprintf(fp, "|");
        fprintf(fp, "%s", (directory[i].type != NULL ? directory[i].type: ""));
        fprintf(fp, "\n");
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
    printf("   Phone: %s\n", (p.number!=NULL ? p.number:"---"));
    printf("   Email: %s\n", (p.email!=NULL ? p.email:"---"));
    printf("   Relation: %s\n", (p.type!=NULL ? p.type:"---"));
    //printf("%s %s %s %s\n", p.name, (p.number!=NULL?p.number:"None"), (p.email!=NULL?p.email:"None"), (p.type!=NULL?p.type:"None"));
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
    directory = tmp;
}

void handle_add(char *name)  {
    char buffer[BUFFER_SIZE];
    char * number, * email, *type;

    printf("  Phone: ");
    read_line(stdin, buffer, BUFFER_SIZE);
    number = (strlen(buffer)>0 ? strdup(buffer) : NULL);

    printf("  Email: ");
    read_line(stdin, buffer, BUFFER_SIZE);
    email = (strlen(buffer)>0 ? strdup(buffer) : NULL);

    printf("  Type: ");
    read_line(stdin, buffer, BUFFER_SIZE);
    type = (strlen(buffer)>0 ? strdup(buffer) : NULL);
    add(name, number, email, type);
}

void add(char * name, char * number, char * email, char * type) {
    if (n>=capacity)
        reallocate();
    int i=n-1;
    while (i>=0 && strcmp(directory[i].name, name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }

    directory[i+1].name = name;
    directory[i+1].number = number;
    directory[i+1].email = email;
    directory[i+1].type = type;
    n++;
}



