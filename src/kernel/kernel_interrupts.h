
// kernel_interrupts.h

#ifndef KRNL_INT
#define KRNL_INT

static inline void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

static inline unsigned char inb(uint16_t port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outw(unsigned short port, unsigned short data) {
    __asm__ volatile ("outw %0, %1" : : "a"(data), "Nd"(port));
}

void shutdown() {
    outw(0x604, 0x2000);
}


#endif