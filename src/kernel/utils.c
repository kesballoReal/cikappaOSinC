
// utils.c
// Author: kesballoReal

#include "video.h"
#include "utils.h"
#include "input.h"

char __version__[] = "0.3";

char username[] = "cikappa";

void change_username() {
    for (volatile int i = 0; i < 35000000; i++);

    print_string("\n\nInsert new username: ");
    char* new_user = inputline();

    int i = 0;
    while (new_user[i] != '\0') {
        username[i] = new_user[i];
        i++;
    }

    username[i] = '\0';
}

void uname() {
    print_string("\ncikappaOS");
}

void echo() {
    for (volatile int i = 0; i < 35000000; i++);

    print_string("\n\nString: ");
    char* echo_string = inputline();

    print_string("\n");
    print_string(echo_string);
}

void whoami() {
    print_string("\n");
    print_string(username);
}

void print_cli_error(char* input) {
    print_string("\nError: command '");
    print_string(input);
    print_string("' not found.");
}

void print_error(char* error) {
    print_string("\nError: ");
    print_string(error);
}

void print_cli() {
    print_string("\n");
    print_string(username);
    print_string("@iso > ");
}

void print_version() {
    print_string("\ncikappaOS ");
    print_string(__version__);
}