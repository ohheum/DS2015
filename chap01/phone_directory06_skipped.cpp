/*
 * Implement partial search function
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_CAPACITY 3
#define BUFFER_LENGTH 100
#define MAX_TOKENS 20

typedef struct {
    char * name;
    char * number;
    char * email;
    char * type;
} Person;

Person * directory;
int capacity = INIT_CAPACITY;
int n = 0;                   /* number of people in phone directory */

void handleAdd(char *);
void handleFind(char *);
void handleStatus();
void handleDelete(char *);
void handleRead(char *);
void handleSave(char *);
int read_line(FILE *, char *, int);
void add(char*, char*, char*, char*);
int parse_line(int max_tokens, char * tokens[], char * line, const char * delim);
int merge_tokens(int s, int t, char * tokens[], int, char * merged);
void handle_partial_find(int s, int t, char * keywords []);
int is_match(char * pattern, char * text);
void print_person(Person p);

const char * delim = " ";

int main() {
    directory = (Person *)malloc(INIT_CAPACITY*sizeof(Person));
    char command_line[BUFFER_LENGTH];
    char argument[BUFFER_LENGTH];
//    char * ptr1, *ptr2;
    char * tokens [MAX_TOKENS];

    while (1) {
        printf("$ ");
        int command_length = read_line(stdin, command_line, BUFFER_LENGTH);
//        fgets(command_line, BUFFER_LENGTH, stdin);
//        command_line[strlen(command_line)-1] = '\0';

        int n_tokens = parse_line(MAX_TOKENS, tokens, command_line, delim);
        if (n_tokens<=0)
            continue;

//        for (int i=0; i<n_tokens; i++)
//            printf("%s\n", tokens[i]);

        if (strcmp(tokens[0], "read") == 0) {
            if (n_tokens != 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleRead(tokens[1]);
        }
        else if (strcmp(tokens[0], "add") == 0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
            handleAdd(argument);
        }
        else if (strcmp(tokens[0], "find") == 0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            if (strcmp(tokens[1], "-p") == 0) {
                if (n_tokens < 3) {
                    printf("Invalid arguments.\n");
                    continue;
                }
                //merge_tokens(2, n_tokens, tokens, BUFFER_LENGTH, argument);
                handle_partial_find(2, n_tokens, tokens);
            }
            else {
                merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
                handleFind(argument);
            }
        }
        else if (strcmp(tokens[0], "status")==0) {
            if (n_tokens > 1) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleStatus();
        }
        else if (strcmp(command_line, "delete")==0) {
            if (n_tokens < 2) {
                printf("Invalid arguments.\n");
                continue;
            }
            merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
            handleDelete(argument);
        }
        else if (strcmp(tokens[0], "save")==0) {
            if (n_tokens != 3 || strcmp(tokens[1], "as") != 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            handleSave(tokens[2]);
        }
        else if (strcmp(tokens[0], "exit")==0)
            break;
    }
    return 0;
}

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

void handle_partial_find(int s, int t, char * keywords []) {
    for (int i=s; i<t; i++) {
        for (int j=0; j<n; j++) {
            if (is_match(keywords[i], directory[j].name)) {
                print_person(directory[j]);
            }
        }
    }
}

int merge_tokens(int s, int t, char * tokens[], int limit, char * merged)
{
    int length = 0;
    strcpy(merged, tokens[s]);
    length = strlen(merged);
    for (int i=s+1; length < limit && i<t; i++) {
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
        tokens[i++] = strdup(ptr);
        ptr = strtok(NULL, delim);
    }
    return i;
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

void handleRead(char *fileName) {
    char buffer[BUFFER_LENGTH];
    char * ptr;
    char * tokens [MAX_TOKENS];

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    while (!feof(fp)) {
//        if (fgets(buffer, BUFFER_LENGTH, fp)==NULL)
//            break;
        int cnt = read_line(fp, buffer, BUFFER_LENGTH);
        if (cnt <= 0) break;
//        printf("--- %s\n", buffer);
//        buffer[strlen(buffer)-1] = '\0';
        int n_tokens = parse_line(MAX_TOKENS, tokens, buffer, "|");
//        for (int i=0; i<n_tokens; i++)
//            printf("%s\n", tokens[i]);

        if (strcmp(tokens[1], " ")==0) tokens[1] = NULL;
        if (strcmp(tokens[2], " ")==0) tokens[2] = NULL;
        add(tokens[0], tokens[1], tokens[2], ((n_tokens < 4 || strcmp(tokens[3], " ")==0) ? NULL : tokens[3]));
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

void handleDelete(char * name) {
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


/*
void handleDelete() {
    char buf[BUFFER_LENGTH];
    scanf(" %s", buf);
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(buf, names[i])==0) {
            names[i] = names[n-1];
            numbers[i] = numbers[n-1];
            n--;
            printf("'%s' was deleted successfully. \n", buf);
            return;
        }
    }
    printf("No person named '%s' exists.\n", buf);
}
*/

void print_person(Person p)
{
    printf("%s:\n", p.name);
    printf("   Phone: %s\n", (p.number!=NULL?p.number:"---"));
    printf("   Email: %s\n", (p.email!=NULL?p.email:"---"));
    printf("   Relation: %s\n", (p.type!=NULL?p.type:"---"));
}

void handleStatus() {
    int i;
    for (i=0; i<n; i++)
        print_person(directory[i]);
    printf("Total %d persons.\n", n);
}


void handleFind(char * name) {
    int index = search(name);
    if (index==-1)
        printf("No person named '%s' exists.\n", name);
    else
        print_person(directory[index]);
}


/*
void handleFind() {
    char buf[BUFFER_LENGTH];
    scanf(" %s", buf);
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(buf, names[i])==0) {
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("No person named '%s' exists.\n", buf);
}
*/

void reallocate()
{
    int i;
    capacity *= 2;
    Person * tmp = (Person *)malloc(capacity*sizeof(Person));
    for (i=0; i<n; i++) {
        tmp[i] = directory[i];
    }
    delete directory;
    directory = tmp;
}

void handleAdd(char * name)  {
    char buffer[BUFFER_LENGTH];
    char * number, * email, *type;

    printf("  Phone: ");
    read_line(stdin, buffer, BUFFER_LENGTH);
    number = (strlen(buffer)>0 ? strdup(buffer) : NULL);

    printf("  Email: ");
    read_line(stdin, buffer, BUFFER_LENGTH);
    email = (strlen(buffer)>0 ? strdup(buffer) : NULL);

    printf("  Type: ");
    read_line(stdin, buffer, BUFFER_LENGTH);
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
//    printf("%s was added successfully.\n", name);
}

/*
void handleAdd() {
    char buf1[BUFFER_LENGTH], buf2[BUFFER_LENGTH];
    scanf(" %s", buf1);
    scanf(" %s", buf2);

    names[n] = strdup(buf1);
    numbers[n] = strdup(buf2);
    n++;
    printf("%s was added successfully.\n", buf1);
}
*/



