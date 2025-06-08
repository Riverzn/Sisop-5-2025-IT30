# Sisop-5-2025-IT30

## Kelompok

Nama | NRP
--- | ---
Adiwidya Budi Pratama | 5027241012
Dimas Satya Andhika | 5027241032
Ahmad Rafi Fadhillah Dwiputra | 5027241068

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan
### kernel.c
 1. Fungsi main()
```c
int main() {
  clearScreen();
  shell();
}
```
- Fungsi `clearScreen()` dipanggil untuk menghapus semua isi layar saat program dijalankan.
- Fungsi `shell()` adalah sebuah loop atau program utama shell, yang tidak ditampilkan di sini, tapi diasumsikan sebagai antarmuka baris perintah tempat pengguna bisa mengetik perintah.
 ---

2. Variabel Global `currentColor`
```c
byte currentColor = 0x07;
```
- byte adalah alias dari unsigned char, digunakan untuk mewakili 8-bit data.
- 0x07 adalah warna default: putih di latar belakang hitam (atribut teks untuk mode teks di VGA):
    - Format warna: 0x[background][foreground]
    - 0x07 = black background (0) + light gray/white foreground (7)
---

3. Fungsi `setColor()` dan `getColor()`
```c
void setColor(byte color) {
  currentColor = color;
}

byte getColor() {
  return currentColor;
}
```
- `setColor()` memungkinkan perubahan warna teks.
- `getColor()` mengembalikan warna saat ini.
- Warna ini digunakan dalam `printString()` dan `clearScreen()` untuk menentukan warna karakter yang ditampilkan.
---

4. Fungsi `printString()`
```c
void printString(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    interrupt(0x10, 0x0E00 + str[i], 0x0001 | (currentColor << 8), 0, 0);
    i++;
  }
}
```
- Fungsi ini mencetak string karakter demi karakter ke layar.
- Menggunakan BIOS Interrupt `0x10` dengan fungsi `AH=0x0E` (teletype output):
    - `0x0E00 + str[i]` → AH=0x0E dan AL=str[i]
    - `currentColor << 8` → memberi atribut warna untuk karakter
- `interrupt(...)` adalah wrapper untuk inline interrupt call BIOS (mungkin disediakan oleh lingkungan OS mini).
- Tidak otomatis menggeser baris saat penuh – fitur seperti ini harus ditambahkan secara manual.
---

5. Fungsi  `readString()`
```c
void readString(char *buf) {
  int i = 0;
  char c = 0;
  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0); // Read char from keyboard
    if (c == 0x0D) { // Enter
      break;
    } else if (c == 0x08 && i > 0) { // Backspace
      i--;
      printString("\b \b"); // Menghapus karakter terakhir
    } else if (c >= 32 && c <= 126 && i < 127) { // Karakter valid ASCII
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0x0001 | (currentColor << 8), 0, 0); // Echo char
    }
  }
  buf[i] = '\0';
  printString("\r\n"); // Pindah ke baris baru
}
```
- Fungsi ini membaca karakter dari keyboard menggunakan BIOS interrupt `0x16`(keyboard input).
- Memroses:
    - Enter (0x0D): selesai input
    - Backspace (0x08): hapus karakter sebelumnya
    - Karakter printable (ASCII 32–126): simpan dan tampilkan
- Disimpan di `buf`, kemudian diterminasi dengan \0 (akhir string).
---

6. Fungsi `clearScreen()`
```c
void clearScreen() {
  int i;
  for (i = 0; i < 80 * 25; i++) {
    putInMemory(0xB800, i * 2, ' '); // karakter kosong
    putInMemory(0xB800, i * 2 + 1, currentColor); // warna untuk karakter
  }

  // Reset posisi kursor ke baris 0, kolom 0
  interrupt(0x10, 0x0200, 0, 0, 0);
}
```
- Layar teks di mode VGA 80x25 disimpan di memori video `0xB800`.
    - Setiap karakter terdiri dari 2 byte: [karakter][atribut warna]
- Mengisi seluruh layar dengan spasi `' '` dan warna dari `currentColor`.
- `putInMemory(segment, offset, value)` menulis langsung ke memori.
- Reset posisi kursor menggunakan `interrupt 0x10, AH=0x02` (set cursor position).
---
### shell.c
 1. Variabel Global
```c
char username[64] = "user";
char companyTitle[16] = "";
bool isGurtMode = false;

char *yogurtResponses[] = {
  "yo",
  "ts unami gng </3",
  "sygau"
};
```
- `username`: Nama pengguna (default: `"user"`).
- `companyTitle`: Grand Company (Maelstrom/Serpent/Flame); ditampilkan di prompt.
- `isGurtMode`: Menandai apakah sedang di "gurt mode".
- `yogurtResponses`: Array dari string balasan acak untuk perintah `yogurt`.
---

2. Fungsi `shell()`
```c
void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];
```
Inisialisasi:
- `buf`: Menyimpan input dari user.
- `cmd`: Kata pertama (nama perintah).
- `arg`: Dua argumen setelah perintah.
--- 

3. Prompt dan Input
```c
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
```
- Menampilkan prompt tergantung mode.
- `readString()` membaca baris input dari keyboard.
- `parseCommand()` memisah input menjadi `cmd`, `arg[0]`, dan `arg[1]`.
---

4. Pemrosesan Perintah
#### `yo dan gurt`
```c
if (strcmp(cmd, "yo")) {
  printString("gurt\r\n");
} else if (strcmp(cmd, "gurt")) {
  printString("yo\r\n");
}
```
- Perintah `yo` → membalas "gurt"
- Perintah `gurt` → membalas "yo"

#### `user`
```c
else if (strcmp(cmd, "user")) {
  if (arg[0][0] == '\0') {
    strcpy(username, "user");
  } else {
    strcpy(username, arg[0]);
  }
  printString("Username changed to ...");
}
```
- Ubah nama pengguna. Jika tidak diberi argumen, kembalikan ke `"user"`.

#### `grandcompany`
```c
else if (strcmp(cmd, "grandcompany")) {
  if (strcmp(arg[0], "maelstrom")) {
    setColor(0x04); // merah
    clearScreen();
    strcpy(companyTitle, "Storm");
  } else if (strcmp(arg[0], "twinadder")) {
    setColor(0x0E); // kuning
    clearScreen();
    strcpy(companyTitle, "Serpent");
  } else if (strcmp(arg[0], "immortalflames")) {
    setColor(0x01); // biru
    clearScreen();
    strcpy(companyTitle, "Flame");
  } else {
    printString("Unknown Grand Company\r\n");
  }
  continue;
}
```
- Menyetel afiliasi dengan Grand Company dan mengubah warna layar:
    - `maelstrom` → merah
    - `twinadder` → kuning
    - `immortalflames` → biru

#### `clear`
```c
else if (strcmp(cmd, "clear")) {
  setColor(0x07); // putih
  strcpy(companyTitle, "");
  clearScreen();
}
```
- Membersihkan layar dan mereset warna/prompt.
---

5. Operasi Matematika: add, sub, mul, div
```c
else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || ...) {
  atoi(arg[0], &a);
  atoi(arg[1], &b);
  ...
  itoa(result, resultStr);
  printString(resultStr);
  printString("\r\n");
}
```
- `atoi()` mengubah string ke integer.
- `div()` untuk pembagian (fungsi dari `std_lib.c`)
- `itoa()` mengubah hasil ke string.
- Menangani pembagian nol!
---

6. `yogurt` acak
```c
else if (strcmp(cmd, "yogurt")) {
  isGurtMode = true;
  i = getBiosTick();
  tick = mod((i * 17 + 73), 3);
  ...
  isGurtMode = false;
  continue;
}
```
- Masuk mode "gurt", tampilkan prompt, dan pilih salah satu respon acak dari `yogurtResponses[]` berdasarkan tick BIOS:
    - `getBiosTick()` → baca waktu sistem
    - `mod()` → fungsi modulo (di `std_lib.c`)
---

7. Fallback
```c
else {
  printString(buf);
  printString("\r\n");
}
```
- Jika perintah tidak dikenali, ulangi inputnya sebagai output.
---

8. Deklarasi dan Reset Buffer
```c
int i = 0, j = 0, word = 0;

clear(cmd, 64);
clear(arg[0], 64);
clear(arg[1], 64);
```
- `i` → indeks untuk membaca karakter input buf
- `j` → indeks untuk menulis ke cmd/arg
- `word` → menandai bagian mana dari input yang sedang ditulis:
    - `0` → perintah utama
    - `1` → argumen pertama
    - `2` → argumen kedua
- Semua buffer dibersihkan dulu (isi di-nul-kan).
---

9. Loop Pemrosesan Karakter
```c
while (buf[i] != '\0') {
```
Loop berjalan sampai akhir string (karakter null '\0').
---

10. Deteksi Spasi
```c
if (buf[i] == ' ') {
  word++;  // pindah ke bagian selanjutnya
  j = 0;   // reset penulisan
  i++;
  continue;
}
```
- Saat menemui spasi, berarti kita pindah ke kata berikutnya (misal dari `cmd `ke `arg[0]`).
- `j = 0` → mulai tulis dari awal lagi ke buffer berikutnya.
---

11. Simpan Karakter Sesuai Bagiannya
```c
if (word == 0 && j < 64) {
  cmd[j++] = buf[i];
} else if (word == 1 && j < 64) {
  arg[0][j++] = buf[i];
} else if (word == 2 && j < 64) {
  arg[1][j++] = buf[i];
}
```
- Karakter non-spasi disimpan sesuai `word`:
    - `word == 0`: isi `cmd`
    - `word == 1`: isi `arg[0]`
    - `word == 2`: isi `arg[1]`
- `j < 64` → agar tidak menulis melebihi batas buffer.
---
### std_lib.c
- `#include "std_lib.h"`
➡️ Mengimpor header std_lib.h yang berisi:
  - Definisi fungsi (div, mod, dll)
  - Tipe data seperti byte, bool, dan true/false.

A.  Fungsi Div(Pembagian)
  ```
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
  ```
- `int div(int a, int b) {`
➡️ Deklarasi fungsi div, menerima dua int, kembalikan hasil pembagian a / b.

- `int result, sign;`
➡️ result menyimpan hasil akhir. sign menyimpan tanda hasil (positif/negatif).

- `result = 0;
  sign = 1;`
➡️ Inisialisasi result ke 0 dan sign ke positif (1).

- `if (b == 0) return 0;`
➡️ Cek pembagi 0 (error), kembalikan 0 untuk menghindari crash.

   `if (a < 0) {
    a = -a;
    sign *= -1;
  }`
➡️ Ubah a jadi positif, dan ubah sign jika a negatif.

- `if (b < 0) {
    b = -b;
    sign *= -1;
  }`
➡️ Ubah b jadi positif, dan ubah sign jika b negatif.

- `while (a >= b) {
    a -= b;
    result++;
  }`
➡️ Kurangi a terus dengan b dan hitung berapa kali bisa dilakukan = hasil bagi.

- `return result * sign;
}`
➡️ Kembalikan hasil akhir (result) dengan tanda (sign).

B.  Fungsi mod – Sisa Pembagian
```
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
```
- `int mod(int a, int b) {`
➡️ Deklarasi fungsi mod, menghitung a % b.

- `int sign;
  if (b == 0) return 0;`
➡️ Jika b == 0, langsung return 0 (hindari crash).

- `sign = (a < 0) ? -1 : 1;`
➡️ Simpan tanda dari a untuk hasil akhir (-1 jika negatif, 1 jika positif).

- `if (a < 0) a = -a;
  if (b < 0) b = -b;`
➡️ Ubah a dan b jadi positif.

- `while (a >= b) {
    a -= b;
  }`
➡️ Kurangi a dengan b sampai tak bisa lagi = sisa pembagian.

- `return a * sign;
}`
➡️ Kembalikan sisa pembagian (a) sesuai tanda asli.

C. Fungsi strcmp – Bandingkan String
```
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
```
- `bool strcmp(char *str1, char *str2) {`
➡️ Membandingkan dua string karakter demi karakter.
- `while (str1[i] != '\0' && str2[i] != '\0') {`
➡️ Loop selama kedua string belum mencapai akhir (\0).
- `if (str1[i] != str2[i]) {
      return false;
    }`
➡️ Jika ada karakter berbeda, return false.

- `i++;
  }`
➡️ Lanjut ke karakter selanjutnya.
- `return str1[i] == str2[i];
}`
➡️ Jika satu string selesai tapi yang lain belum, return false. Kalau dua-duanya selesai bersamaan (\0), return true.

D. Fungsi strcpy – Salin String
```
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
```
- `void strcpy(char *dst, char *src) {`
➡️ Menyalin isi src ke dst.
- `int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }`
➡️ Salin karakter satu per satu sampai akhir (\0).

- `dst[i] = '\0';
}`
➡️ Tambahkan null terminator di akhir dst.

E. Fungsi clear – Set Buffer ke 0

- `void clear(byte *buf, unsigned int size) {`
➡️ Mengisi array buf sepanjang size dengan 0.
- `unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}`
➡️ Loop dari 0 ke size-1, dan set setiap elemen buffer ke 0.

F. Fungsi atoi – String ke Angka

- `void atoi(char *str, int *num) {`
➡️ Mengubah string angka ke integer (misal: "123" → 123).

- `int i, result, sign;
  i = 0;
  result = 0;
  sign = 1;`
➡️ Inisialisasi index, hasil, dan tanda (positif).

- `if (str[0] == '-') {
    sign = -1;
    i++;
  }`
➡️ Jika string diawali -, set sign jadi negatif.

- `while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }`
➡️ Ambil digit satu per satu dan tambahkan ke result.

- `*num = result * sign;
}`
➡️ Simpan hasil konversi ke variabel num.

G.  Fungsi itoa – Angka ke String

- `void itoa(int num, char *str) {`
➡️ Mengubah int menjadi string (misal: 123 → "123").
- `int i, j, sign;
  char temp;
  i = 0;
  sign = 0;`
➡️ Inisialisasi index i, indeks loop balik j, dan sign (0 artinya positif).

- `if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }`
➡️ Penanganan khusus jika num == 0.

- `if (num < 0) {
    sign = 1;
    num = -num;
  }`
➡️ Jika negatif, simpan tanda dan ubah ke positif.

- `while (num > 0) {
    str[i++] = mod(num, 10) + '0';
    num = div(num, 10);
  }`
➡️ Ambil digit terakhir (mod 10) dan simpan ke str.

- `if (sign) str[i++] = '-';`
➡️ Tambahkan tanda minus jika perlu.

- `str[i] = '\0';`
➡️ Tambahkan null terminator di akhir string.

- `for (j = 0; j < i / 2; j++) {
    temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}`
➡️ Balik string (123 awalnya tersimpan sebagai "321" → dibalik).

---
### makefile
A. Compiler dan Assembler

- `AS=nasm`
➡️ AS adalah assembler. Di sini, kita pakai nasm untuk file .asm.

- `CC=bcc`
➡️ CC adalah compiler C. Di sini, pakai bcc (Borland C Compiler).
- LD=ld86
➡️ LD adalah linker. ld86 dipakai untuk menggabungkan object file .o menjadi binary.

- `CFLAGS=-ansi -c`
➡️ -ansi: Gunakan standar ANSI C.
➡️ -c: Compile saja, jangan link (hasilkan file .o).

- `INCLUDES=-Iinclude/`
➡️ Direktori header tambahan (misalnya include/std_lib.h).

B. Direktori
- `SRC_DIR=src
BIN_DIR=bin`
➡️ Lokasi source code (src/) dan output binary (bin/).
```
BOOTLOADER_SRC=$(SRC_DIR)/bootloader.asm
KERNEL_C_SRC=$(SRC_DIR)/kernel.c
KERNEL_ASM_SRC=$(SRC_DIR)/kernel.asm
SHELL_SRC=$(SRC_DIR)/shell.c
STDLIB_SRC=$(SRC_DIR)/std_lib.c
```
➡️ Path ke source file: bootloader, kernel, shell, dan library.
```
BOOTLOADER_BIN=$(BIN_DIR)/bootloader.bin
KERNEL_BIN=$(BIN_DIR)/kernel.bin
FLOPPY_IMG=$(BIN_DIR)/floppy.img
```
➡️ File output setelah build:

Bootloader → bootloader.bin

Kernel → kernel.bin

Disk image → floppy.img

C. Object Files
```
KERNEL_O=$(BIN_DIR)/kernel.o
KERNEL_ASM_O=$(BIN_DIR)/kernel_asm.o
SHELL_O=$(BIN_DIR)/shell.o
STDLIB_O=$(BIN_DIR)/std_lib.o
```
➡️ Semua file .o hasil compile masing-masing modul.

- `all: build`
➡️ Target default saat jalankan make = akan menjalankan build.
```
prepare:
	mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
```
- ➡️ Persiapan:

Buat folder bin jika belum ada.

Buat floppy kosong 1.44 MB (2880 sektor × 512 byte).

- ```
  bootloader: $(BOOTLOADER_SRC)
	$(AS) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc
  ```
➡️ Assemble bootloader jadi .bin, lalu salin ke sektor pertama (MBR) dari floppy.


- `stdlib: $(STDLIB_SRC)
	$(CC) $(CFLAGS) $(STDLIB_SRC) -o $(STDLIB_O) $(INCLUDES)`
➡️ Compile std_lib.c menjadi object file .o, dengan menyertakan folder header.
- `shell: $(SHELL_SRC)
	$(CC) $(CFLAGS) $(SHELL_SRC) -o $(SHELL_O) $(INCLUDES)`
➡️ Compile shell.c menjadi object file .o.

- ```
  kernel: $(KERNEL_C_SRC) $(KERNEL_ASM_SRC)
	$(AS) -f as86 $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_O)
	$(CC) $(CFLAGS) $(KERNEL_C_SRC) -o $(KERNEL_O) $(INCLUDES)`
  ```
➡️ Compile bagian kernel:
  - Kernel ASM (.asm) → kernel_asm.o
  - Kernel C (.c) → kernel.o
- ```
  link: $(BOOTLOADER_BIN) $(KERNEL_O) $(KERNEL_ASM_O) $(SHELL_O) $(STDLIB_O)
	$(LD) -o $(KERNEL_BIN) -d $(KERNEL_O) $(KERNEL_ASM_O) $(SHELL_O) $(STDLIB_O)
  ```
➡️ Gabungkan semua object file jadi kernel.bin menggunakan ld86.

- ```
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) bs=512 count=1 conv=notrunc
	dd if=$(KERNEL_BIN) of=$(FLOPPY_IMG) bs=512 seek=1 conv=notrunc
  ```
➡️ Tulis bootloader.bin ke sektor 0, lalu tulis kernel.bin ke sektor selanjutnya (mulai sektor 1).

- `build: prepare bootloader stdlib shell kernel link`
➡️ Bangun seluruh sistem secara lengkap dari awal:
  - Siapkan floppy
  - Assemble bootloader
  - Compile stdlib
  - Compile shell
  - Compile kernel
  - Link dan gabungkan semua

- `clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.bin $(BIN_DIR)/*.img`
➡️ Hapus semua file hasil compile/link untuk bersih-bersih (reset build).


