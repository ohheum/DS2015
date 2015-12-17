#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_CAPACITY 3
#define BUFFER_SIZE 100

char ** names;            /* names */
char ** numbers;          /* phone numbers */
int capacity = INIT_CAPACITY;
int n = 0;                   /* number of people in phone directory */

void add(char * ,char *);
void handleFind(char *);
void handleStatus();
void handleDelete(char *);
void handleRead(char *);
void handleSave(char *);
int read_line(char *, int);

const char * delim = " ";

int main() {
    names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));

    char command[BUFFER_SIZE];
    char argument[BUFFER_SIZE];
    char * ptr1, *ptr2;

    while (1) {
        printf("$ ");
        scanf(" %s", command);
        if (strcmp(command, "read") == 0) {
            int arglen = read_line(argument, BUFFER_SIZE);
            if (arglen <= 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleRead(argument);
        }
        else if (strcmp(command, "add") == 0) {
            ptr1 = strtok(NULL, delim);
            ptr2 = strtok(NULL, delim);
            if (ptr1 == NULL || ptr2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            add(ptr1, ptr2);
        }
        else if (strcmp(command, "find") == 0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleFind(ptr1);
        }
        else if (strcmp(command, "status")==0)
            handleStatus();
        else if (strcmp(command, "delete")==0) {
            ptr1 = strtok(NULL, delim);
            if (ptr1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleDelete(ptr1);
        }
        else if (strcmp(command, "save")==0) {
            ptr1 = strtok(NULL, delim);
            ptr2 = strtok(NULL, delim);
            if (ptr1 == NULL || strcmp("as", ptr1) != 0 || ptr2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleSave(ptr2);
        }
        else if (strcmp(command, "exit")==0)
            break;
    }
    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;
    while ((ch=getchar()) == ' ');
    while (i<n && ch != '\n') {
        str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}

void handleRead(char * fileName) {
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }
    while ((fscanf(fp, "%s", buf1)!=EOF)) {
        fscanf(fp, "%s", buf2);
        add(buf1, buf2);
    }
    fclose(fp);
}

void handleSave(char * fileName) {
    int i;
    FILE *fp = fopen(fileName, "w");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    for (i=0; i<n; i++) {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
    }
    fclose(fp);
}

int search(char *name) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(name, names[i])==0) {
            return i;
        }
    }
    return -1;
}

void handleDelete(char * name) {

    int i = search(name);  /* returns -1 if not exists */
    if (i == -1) {
        printf("No person named '%s' exists.\n", name);
        return;
    }

    int j = i;
    for (; j<n-1; j++) {
        names[j] = names[j+1];
        numbers[j] = numbers[j+1];
    }
    n--;
    printf("'%s' was deleted successfully. \n", name);
}

void handleStatus() {
    int i;
    for (i=0; i<n; i++)
        printf("%s  %s\n", names[i], numbers[i]);
    printf("Total %d persons.\n", n);
}


void handleFind(char * name) {
    int index = search(name);
    if (index==-1)
        printf("No person named '%s' exists.\n", name);
    else
        printf("%s\n", numbers[index]);
}

void reallocate()
{
    int i;
    capacity *= 2;
    char ** tmp1 = (char **)malloc(capacity*sizeof(char *));
    char ** tmp2 = (char **)malloc(capacity*sizeof(char *));
    for (i=0; i<n; i++) {
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }
    names = tmp1;
    numbers = tmp2;
}

void add(char * name, char * number) {
    if (n>=capacity)
        reallocate();
    int i=n-1;
    while (i>=0 && strcmp(names[i], name) > 0) {
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }

    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);
    n++;
    printf("%s was added successfully.\n", name);
}

