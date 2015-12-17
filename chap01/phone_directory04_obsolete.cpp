
/*
 * Name consists of more than one word
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100
#define MAX_TOKENS 20

typedef struct {
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

Person directory[CAPACITY];
int n = 0;                   /* number of people in phone directory */

void handle_add(char *);
void find(char *);
void status();
void remove(char *);
void load(char *);
void save(char *);
int read_line(FILE *, char *, int);
void add(char*, char*, char*, char*);
int parse_line(int max_tokens, char * tokens[], char * line, const char * delim);
int merge_tokens(int s, int t, char * tokens[], int, char * merged);

int main() {

    char command_line[BUFFER_LENGTH];
    char argument[BUFFER_LENGTH];
    char * tokens [MAX_TOKENS];

    while (1) {
        printf("$ ");
        int command_length = read_line(stdin, command_line, BUFFER_LENGTH);
        int n_tokens = parse_line(MAX_TOKENS, tokens, command_line, " ");
        if (n_tokens<=0)
            continue;

        if (strcmp(tokens[0], "read") == 0) {
            if (n_tokens != 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            load(tokens[1]);
        }
        else if (strcmp(tokens[0], "add") == 0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
            handle_add(argument);
        }
        else if (strcmp(tokens[0], "find") == 0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
            find(argument);
        }
        else if (strcmp(tokens[0], "status")==0) {
            if (n_tokens > 1) {
                printf("Invalid arguments.\n");
                continue;
            }
            status();
        }
        else if (strcmp(command_line, "delete")==0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
            remove(argument);
        }
        else if (strcmp(tokens[0], "save")==0) {
            if (n_tokens != 3 || strcmp(tokens[1], "as") != 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            save(tokens[2]);
        }
        else if (strcmp(tokens[0], "exit")==0)
            break;
    }
    return 0;
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

int parse_line(int max_tokens, char * tokens[], char * line, const char * delim)
{
    char * ptr = strtok(line, delim);
    int i = 0;
    while(i<max_tokens && ptr != NULL)
    {
        tokens[i++] = ptr;
        ptr = strtok(NULL, delim);
    }
    return i;
}

int read_line(FILE * fp, char str[], int n)
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

void load(char *fileName) {
    char buffer[BUFFER_LENGTH];
    char * ptr;
    char * tokens [MAX_TOKENS];

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    while (!feof(fp)) {
        int cnt = read_line(fp, buffer, BUFFER_LENGTH);
        if (cnt <= 0) break;
        int n_tokens = parse_line(MAX_TOKENS, tokens, buffer, "#");
        add(tokens[0], tokens[1], tokens[2], tokens[3]);
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

void handle_add(char * name)  {
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], type[BUFFER_LENGTH];
    printf("  Phone: ");
    int cnt = read_line(stdin, number, BUFFER_LENGTH);
    printf("  Email: ");
    read_line(stdin, email, BUFFER_LENGTH);
    printf("  Group: ");
    read_line(stdin, type, BUFFER_LENGTH);
    add(name, number, email, type);
}

void add(char * name, char * number, char * email, char * group) {
    int i=n-1;
    while (i>=0 && strcmp(directory[i].name, name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }
    directory[i+1].name = strdup(name);
//    directory[i+1].number = strdup(number);
//    directory[i+1].email = strdup(email);
//    directory[i+1].group = strdup(group);

    directory[i+1].number = (strlen(number)>0 ? strdup(number) : (char *)" ");
    directory[i+1].email = (strlen(email)>0 ? strdup(email) : (char *)" ");
    directory[i+1].group = (strlen(group)>0 ? strdup(group) : (char *)" ");
    n++;
}




