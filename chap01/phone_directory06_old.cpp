/* implement partial search functionality
 * implemented as separate modules
 */
#include <stdio.h>
#include <string.h>
#include "my_string_tools.h"
#include "manage_directory.h"

void process_command();
void handle_add(char *);
char * delim = " ";

int main() {
    init_directory();
    process_command();

    return 0;
}

void process_command() {
    char command_line[BUFFER_LENGTH];
    char argument[BUFFER_LENGTH];
    char * tokens [MAX_TOKENS];

    while (1) {
        printf("$ ");
        int command_length = read_line_elim_leading_blank(stdin, command_line, BUFFER_LENGTH);
        int n_tokens = parse_line(MAX_TOKENS, tokens, command_line, delim);
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
            if (strcmp(tokens[1], "-p") == 0) {
                if (n_tokens < 3) {
                    printf("Invalid arguments.\n");
                    continue;
                }
                match(2, n_tokens, tokens);
            }
            else {
                merge_tokens(1, n_tokens, tokens, BUFFER_LENGTH, argument);
                find(argument);
            }
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

