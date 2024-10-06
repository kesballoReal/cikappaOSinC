
// input.c
// Author: kesballoReal

#include "keyboard.h"
#include <stddef.h>

#define INPUT_BUFFER_SIZE 100

static char full[INPUT_BUFFER_SIZE];

int speed = 35000000;

void clear_last_char() {
    put_char('\b');
}

char* inputline() {
    int index = 0; 

    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
        full[i] = '\0';
    }

    while (index < INPUT_BUFFER_SIZE - 1) {
        char c = input();

        if (c == '\n') {
            break;
        }
        if (c == '\b') {  
            if (index > 0) { 
                index--;
                clear_last_char();
                full[index] = '\0'; 
            }
        }
        else if (c != '\0') {
            put_char(c); 
            full[index] = c;
            index++;
        }

        for (volatile int i = 0; i < speed; i++);
    }

    full[index] = '\0';
    return full;
}
