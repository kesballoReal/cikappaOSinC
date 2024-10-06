
// utils.c
// Author: kesballoReal

#include "video.h"
#include "utils.h"
#include "input.h"


char __version__[] = "0.3";

char username[] = "cikappa";

void kbd_speed() {
    clear();

    int speedk;

    print_string("Select the speed of debounce: ");
    print_string("\n1): 1,5");
    print_string("\n2): 2,5");
    print_string("\n3): 3,5 (default)");
    print_string("\n4): 4,5");
    print_string("\n5): 5,5\n");

    for (volatile int i = 0; i < speed; i++);

    char* selection = inputline();

    if (strCmp(selection, "1") == 0) {
        speedk = 15000000;
        speed = speedk;
        
    }
    else if (strCmp(selection, "2") == 0) {
        speedk = 25000000;
        speed = speedk;
    }
    else if (strCmp(selection, "3") == 0) {
        speedk = 35000000;
        speed = speedk;
    }
    else if (strCmp(selection, "4") == 0) {
        speedk = 45000000;
        speed = speedk;
    }
    else if (strCmp(selection, "5") == 0) {
        speedk = 55000000;
        speed = speedk;
    }
    else {
        print_error("\nPlease enter a valid option!");
    }
}

void change_username() {
    for (volatile int i = 0; i < speed; i++);

    print_string("\n\nInsert new username: ");
    char* new_user = inputline();

    int i = 0;
    while (new_user[i] != '\0') {
        username[i] = new_user[i];
        i++;
    }

    username[i] = '\0';
}

void help() {
    print_string("\n");
    print_string("\nver         Shows cikappaOS version.");
    print_string("\nclear       Clears the screen.");
    print_string("\nusername    Changes the username of the user.");
    print_string("\nwhoami      Prints the username of the user.");
    print_string("\necho        Prints a string.");
    print_string("\nuname       Shows the name of the OS.");
    print_string("\nhelp        Shows this menu.");
    print_string("\nshutdown    Shutdowns the system.");
    print_string("\nkbdspeed    Changes the keyboard speed.\n");
}

void uname() {
    print_string("\ncikappaOS");
}

void echo() {
    for (volatile int i = 0; i < speed; i++);

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