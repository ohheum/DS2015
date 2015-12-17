/*
 * Name consists of more than one word
 */
#include "my_string_tools.h"
#include "manage_directory.h"

#define BUFFER_LENGTH 100

void process_command();
void handle_add(char *);

int main() {
    init_directory();
    process_command();

    return 0;
}

void process_command() {

    char command_line[BUFFER_LENGTH];
    char *command, *argument;
    char name_str[BUFFER_LENGTH];

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH)<=0)
            continue;

        command = strtok(command_line, " ");

        if (strcmp(command, "read") == 0) {
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            load(argument);
        }
        else if (strcmp(command, "add") == 0) {
            if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            handle_add(name_str);
        }
        else if (strcmp(command, "find") == 0) {

//            if (n_tokens < 2) {
//                printf("Invalid arguments.\n");
//                continue;
//            }
//            if (strcmp(tokens[1], "-p") == 0) {
//                if (n_tokens < 3) {
//                    printf("Invalid arguments.\n");
//                    continue;
//                }
//                match(2, n_tokens, tokens);
//            }
//            else {
//                merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
//                find(argument);
//            }

            if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            find(name_str);
        }
        else if (strcmp(command, "status")==0) {
            status();
        }
        else if (strcmp(command, "delete")==0) {
            if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            remove(name_str);
        }
        else if (strcmp(command, "save")==0) {
            argument = strtok(NULL, " ");
            if (strcmp(argument, "as") != 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            save(argument);
        }
        else if (strcmp(command, "exit")==0)
            break;
    }
}

void handle_add(char * name)  {
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
    char empty[] = " ";

    printf("  Phone: ");
    read_line(stdin, number, BUFFER_LENGTH);
    printf("  Email: ");
    read_line(stdin, email, BUFFER_LENGTH);
    printf("  Group: ");
    read_line(stdin, group, BUFFER_LENGTH);

    add(name, (char *)(strlen(number)>0 ? number : empty),  (char *)(strlen(email)>0 ? email : empty),  (char *)(strlen(group)>0 ? group : empty));
}

