#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[64] = "user";
char companyTitle[16] = "";
bool isGurtMode = false;

char *yogurtResponses[] = {
  "yo",
  "ts unami gng </3",
  "sygau"
};

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];

  printString("Welcome to EorzeOS!\r\n");

  while (true) {
    if (isGurtMode) {
    printString("gurt> ");
    } else {
      printString(username);
      if (companyTitle[0] != '\0') {
      printString("@");
      printString(companyTitle);
    }
    printString("> ");
    }

    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "yo")) {
      printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
      printString("yo\r\n");
    } else if (strcmp(cmd, "user")) {
      if (arg[0][0] == '\0') {
        strcpy(username, "user");
        printString("Username changed to user\r\n");
      } else {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(username);
        printString("\r\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        setColor(0x04); // Merah
        clearScreen();
        strcpy(companyTitle, "Storm");
      } else if (strcmp(arg[0], "twinadder")) {
        setColor(0x0E); // Kuning
        clearScreen();
        strcpy(companyTitle, "Serpent");
      } else if (strcmp(arg[0], "immortalflames")) {
        setColor(0x01); // Biru
        clearScreen();
        strcpy(companyTitle, "Flame");
      } else {
        printString("Unknown Grand Company\r\n");
      }
      continue;
    } else if (strcmp(cmd, "clear")) {
      setColor(0x07); // Putih
      strcpy(companyTitle, "");
      clearScreen();
    } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
      int a, b, result;
      char resultStr[64];

      // Konversi argumen
      atoi(arg[0], &a);
      atoi(arg[1], &b);

      if (strcmp(cmd, "add")) {
        result = a + b;
      } else if (strcmp(cmd, "sub")) {
        result = a - b;
      } else if (strcmp(cmd, "mul")) {
        result = a * b;
      } else if (strcmp(cmd, "div")) {
        if (b == 0) {
          printString("Error: division by zero\r\n");
          continue;
        } else {
          result = div(a, b); // ← fungsi div dari std_lib.c
        }
      }

      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");

    } else if (strcmp(cmd, "yogurt")) {
      int i;
      int tick;
      isGurtMode = true;
      i = getBiosTick();
      tick = mod((i * 17 + 73), 3);
      printString("gurt> ");
      if (tick == 0) {
        printString("yo");
      } else if (tick == 1) {
        printString("ts unami gng </3");
      } else {
        printString("sygau");
      }
      printString("\r\n");
      isGurtMode = false;
      continue;

    } else {
      printString(buf);
      printString("\r\n");
    }
  }
}


void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, word = 0;

  clear(cmd, 64);
  clear(arg[0], 64);
  clear(arg[1], 64);

  while (buf[i] != '\0') {
    if (buf[i] == ' ') {
      word++;
      j = 0;
      i++;
      continue;
    }

    if (word == 0 && j < 64) {
      cmd[j++] = buf[i];
    } else if (word == 1 && j < 64) {
      arg[0][j++] = buf[i];
    } else if (word == 2 && j < 64) {
      arg[1][j++] = buf[i];
    }

    i++;
  }
}


// Tambahkan fungsi bila perlu
