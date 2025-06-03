# Compiler and Assembler settings
AS=nasm
CC=bcc
LD=ld86

CFLAGS=-ansi -c
INCLUDES=-Iinclude/

# Directories
SRC_DIR=src
BIN_DIR=bin

# Files
BOOTLOADER_SRC=$(SRC_DIR)/bootloader.asm
KERNEL_C_SRC=$(SRC_DIR)/kernel.c
KERNEL_ASM_SRC=$(SRC_DIR)/kernel.asm
SHELL_SRC=$(SRC_DIR)/shell.c
STDLIB_SRC=$(SRC_DIR)/std_lib.c

BOOTLOADER_BIN=$(BIN_DIR)/bootloader.bin
KERNEL_BIN=$(BIN_DIR)/kernel.bin
FLOPPY_IMG=$(BIN_DIR)/floppy.img

# Object files
KERNEL_O=$(BIN_DIR)/kernel.o
KERNEL_ASM_O=$(BIN_DIR)/kernel_asm.o
SHELL_O=$(BIN_DIR)/shell.o
STDLIB_O=$(BIN_DIR)/std_lib.o

# Targets
all: build

prepare:
	mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880

bootloader: $(BOOTLOADER_SRC)
	$(AS) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib: $(STDLIB_SRC)
	$(CC) $(CFLAGS) $(STDLIB_SRC) -o $(STDLIB_O) $(INCLUDES)

shell: $(SHELL_SRC)
	$(CC) $(CFLAGS) $(SHELL_SRC) -o $(SHELL_O) $(INCLUDES)

kernel: $(KERNEL_C_SRC) $(KERNEL_ASM_SRC)
	$(AS) -f as86 $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_O)
	$(CC) $(CFLAGS) $(KERNEL_C_SRC) -o $(KERNEL_O) $(INCLUDES)

link: $(BOOTLOADER_BIN) $(KERNEL_O) $(KERNEL_ASM_O) $(SHELL_O) $(STDLIB_O)
	$(LD) -o $(KERNEL_BIN) -d $(KERNEL_O) $(KERNEL_ASM_O) $(SHELL_O) $(STDLIB_O)
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) bs=512 count=1 conv=notrunc
	dd if=$(KERNEL_BIN) of=$(FLOPPY_IMG) bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.bin $(BIN_DIR)/*.img
