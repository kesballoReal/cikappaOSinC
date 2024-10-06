
// cmd.c

#include "cmd.h"
#include "stdint.h"
#include "kernel_interrupts.h"
#include "input.h"


void cli() {
    while (1) {
        print_cli();

        for (volatile int i = 0; i < speed; i++);

        char* input = inputline();

        if (input == NULL || strCmp(input, "") == 0) {
            continue;
        }
        else if (strCmp(input, "clear") == 0) {
            clear();
        } 
        else if (strCmp(input, "shutdown") == 0) {
            print_string("\nShutdown..");

            for (volatile int i = 0; i < speed; i++);

            print_string("   DONE!");

            for (volatile int i = 0; i < speed; i++);

            shutdown();
            break;
        }
        else if (strCmp(input, "ver") == 0) {
            print_version();
        }
        else if (strCmp(input, "username") == 0) {
            change_username();
        }
        else if (strCmp(input, "whoami") == 0) {
            whoami();
        }
        else if (strCmp(input, "echo") == 0) {
            echo();
        }
        else if (strCmp(input, "uname") == 0) {
            uname();
        }
        else if (strCmp(input, "help") == 0) {
            help();
        }
        else if (strCmp(input, "kbdspeed") == 0) {
            kbd_speed();
        }
        
        else {
            print_cli_error(input);

            continue;

        }
    }
}