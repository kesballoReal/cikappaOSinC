
// kernel.c

#include "stdint.h"
#include "memory.h"
#include "video.h"
#include "keyboard.h"
#include "input.c"
#include "string.h"
#include "utils.c"


#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

typedef struct {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
} multiboot_header_t;

__attribute__((section(".multiboot")))
multiboot_header_t multiboot_header = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM,
    0,
    0,
    0,
    0,
    0,
};

void cli() {
    while (1) {
        print_cli();

        for (volatile int i = 0; i < 35000000; i++);

        char* input = inputline();

        if (input == NULL || strCmp(input, "") == 0) {
            continue;
        }
        else if (strCmp(input, "clear") == 0) {
            clear();
            continue;
        } 
        else if (strCmp(input, "exit") == 0) {
            break;
        }
        else if (strCmp(input, "ver") == 0) {
            print_version();
            continue;
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
        
        else {
            print_cli_error(input);

            continue;

        }
    }
}

void kernel_main() {
    memory_init();  
    video_init();   
    
    print_string("Starting cikappaOS...");

    for (volatile int i = 0; i < 350000000; i++);

    print_string("  DONE!\n");
    
    cli();
}
