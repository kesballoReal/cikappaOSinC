#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_MEMORY (0xB8000) // Indirizzo della memoria video
#define MAX_WIDTH 80 // Larghezza dello schermo
#define MAX_HEIGHT 25 // Altezza dello schermo

extern unsigned int cursor_x; // Dichiarazione della variabile cursore x
extern unsigned int cursor_y; // Dichiarazione della variabile cursore y

void video_init(); // Dichiarazione della funzione video_init
void print_string(const char* str); // Dichiarazione della funzione print_string
void put_char(char c); // Dichiarazione della funzione put_char

#endif // VIDEO_H
