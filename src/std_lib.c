#include "std_lib.h"

int div(int a, int b) {
  int result, sign;
  result = 0;
  sign = 1;
  if (b == 0) return 0;

  if (a < 0) {
    a = -a;
    sign *= -1;
  }
  if (b < 0) {
    b = -b;
    sign *= -1;
  }

  while (a >= b) {
    a -= b;
    result++;
  }

  return result * sign;
}

int mod(int a, int b) {
  int sign;
  if (b == 0) return 0;
  sign = (a < 0) ? -1 : 1;

  if (a < 0) a = -a;
  if (b < 0) b = -b;

  while (a >= b) {
    a -= b;
  }

  return a * sign;
}

bool strcmp(char *str1, char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return false;
    }
    i++;
  }
  return str1[i] == str2[i];
}


void strcpy(char *dst, char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
}

void clear(byte *buf, unsigned int size) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}


void atoi(char *str, int *num) {
  int i, result, sign;
  i = 0;
  result = 0;
  sign = 1;

  if (str[0] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }

  *num = result * sign;
}

void itoa(int num, char *str) {
  int i, j, sign;
  char temp;
  i = 0;
  sign = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    sign = 1;
    num = -num;
  }

  while (num > 0) {
    str[i++] = mod(num, 10) + '0';
    num = div(num, 10);
  }

  if (sign) str[i++] = '-';
  str[i] = '\0';

  for (j = 0; j < i / 2; j++) {
    temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}
