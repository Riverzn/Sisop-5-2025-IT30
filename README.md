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

6. Fungsi clearScreen()
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

### shell.c

### std_lib.c

### makefile

