# Variabili
NASM=nasm
GCC=gcc
LD=ld
BOOTLOADER=build/bootloader.bin
KERNEL_OBJ=build/kernel.o build/memory.o  # Rimosso process.o
KERNEL_BIN=build/kernel.bin
ISO=cikappaOS.iso

all: $(BOOTLOADER) $(KERNEL_BIN) $(ISO)

# Compilazione del bootloader
$(BOOTLOADER): src/bootloader/bootloader.asm
	$(NASM) -f bin -o $@ $<

# Compilazione del kernel
build/kernel.o: src/kernel/kernel.c
	$(GCC) -m32 -ffreestanding -c $< -o $@

# Compilazione del gestore della memoria
build/memory.o: src/kernel/memory.c
	$(GCC) -m32 -ffreestanding -c $< -o $@

# Linking del kernel
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) -m elf_i386 -T linker.ld -o $@ $(KERNEL_OBJ)  # Usa la variabile corretta per oggetti

# Creazione dell'immagine ISO
$(ISO): $(BOOTLOADER) $(KERNEL_BIN)
	mkdir -p build/iso/boot/grub
	cp $(KERNEL_BIN) build/iso/my_os.bin
	echo 'set timeout=0' > build/iso/boot/grub/grub.cfg
	echo 'set default=0' >> build/iso/boot/grub/grub.cfg
	echo 'menuentry "cikappaOS" {' >> build/iso/boot/grub/grub.cfg
	echo '    multiboot /my_os.bin' >> build/iso/boot/grub/grub.cfg
	echo '    boot' >> build/iso/boot/grub/grub.cfg
	echo '}' >> build/iso/boot/grub/grub.cfg
	grub-mkrescue -o build/cikappaOS.iso build/iso

# Pulizia
clean:
	rm -f build/*.bin build/*.o build/iso/*.bin build/cikappaOS.iso
