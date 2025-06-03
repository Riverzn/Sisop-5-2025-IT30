#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

byte currentColor = 0x07;

void setColor(byte color) {
  currentColor = color;
}

byte getColor() {
  return currentColor;
}

// Fungsi mencetak string ke layar menggunakan interrupt 0x10, AH = 0x0E
void printString(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    interrupt(0x10, 0x0E00 + str[i], 0x0001 | (currentColor << 8), 0, 0);
    i++;
  }
}

// Fungsi membaca input string dari keyboard, disimpan ke buf
void readString(char *buf) {
  int i = 0;
  char c = 0;
  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0); // Read char from keyboard
    if (c == 0x0D) { // Enter
      break;
    } else if (c == 0x08 && i > 0) { // Backspace
      i--;
      printString("\b \b");
    } else if (c >= 32 && c <= 126 && i < 127) { // Printable ASCII
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0x0001 | (currentColor << 8), 0, 0);
    }
  }
  buf[i] = '\0';
  printString("\r\n");
}

// Fungsi membersihkan layar (80x25 karakter)
void clearScreen() {
  int i;
  for (i = 0; i < 80 * 25; i++) {
    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, currentColor); // Warna putih di latar hitam
  }

  // Reset posisi kursor (baris 0, kolom 0)
  interrupt(0x10, 0x0200, 0, 0, 0);
}
