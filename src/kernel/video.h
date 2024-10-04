
// video.h
// Author: kesballoReal

#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_MEMORY (0xB8000) 
#define MAX_WIDTH 80 
#define MAX_HEIGHT 25 

extern unsigned int cursor_x; 
extern unsigned int cursor_y;

void video_init(); 
void print_string(const char* str);
void put_char(char c); 
void clear();


#endif 
