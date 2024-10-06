// kernel.c

#include "stdint.h"
#include "memory.h"
#include "video.h"
#include "keyboard.h"
#include "input.c"
#include "string.h"
#include "utils.c"
#include "cmd.c"
#include "bool.h"

#define ONE_MB (1 * 1024 * 1024)

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

void kernel_main() {
    memory_init();  
    video_init();   
    
    print_string("Starting cikappaOS..");

    for (volatile int i = 0; i < 350000000; i++);

    print_string("  DONE!\n");

    void* cli_memory = memory_alloc(ONE_MB);
    cli();
}
