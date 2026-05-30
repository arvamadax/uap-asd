# Superprompt — IoT Home Monitoring System
**UAP Algoritma dan Struktur Data — Teknik Komputer FILKOM UB 2025/2026**
**Kelas E — Kelompok 7**

---

## Instruksi untuk Claude Code

Salin seluruh teks di bawah ini dan paste ke Claude Code.

---

Kamu adalah asisten pemrograman C++ yang membantu membuat **kerangka kode (skeleton)** untuk proyek UAP Algoritma dan Struktur Data Teknik Komputer FILKOM Universitas Brawijaya 2025/2026.

Tugasmu adalah membuat **kerangka kode saja** — berisi definisi struct, deklarasi fungsi, dan komentar `// TODO: implementasi` di dalam setiap badan fungsi. **Jangan mengimplementasikan logika apapun.** Setiap fungsi hanya boleh berisi komentar TODO dan return statement kosong jika diperlukan.

---

## ATURAN WAJIB (TIDAK BOLEH DILANGGAR)

1. **Satu-satunya `#include` yang boleh ada di seluruh proyek adalah `#include <iostream>`**
2. **Gunakan `using namespace std;`**
3. **Dilarang menggunakan STL apapun** — tidak ada `vector`, `list`, `map`, `set`, `string` dari STL, `algorithm`, `sort`, atau library lainnya
4. **Semua string menggunakan `char` array** — gunakan `char` array dengan panjang yang cukup (contoh: `char userID[20]`, `char nama[100]`)
5. **Tidak ada komentar inline** di dalam baris kode — komentar hanya boleh di atas fungsi atau sebagai `// TODO:`
6. **Tidak ada fungsi `main()`** kecuali di `main.cpp`
7. Semua implementasi struktur data dilakukan secara **manual** menggunakan pointer

---

## STRUKTUR FILE YANG HARUS DIBUAT

Buat 5 file berikut secara berurutan:

```
src/structures.h
src/user_add.h
src/user_manage.h
src/user_report.h
src/main.cpp
```

---

## FILE 1 — `src/structures.h`

Header guard: `STRUCTURES_H`

### Konstanta

```cpp
const int JUMLAH_WILAYAH = 4;
const char KODE_WILAYAH[4][4] = {"053", "044", "046", "077"};
```

### Struct `SensorData`

Field:
- `float temperature`
- `float humidity`
- `int airQuality`
- `bool smoke`
- `float noise`

### Struct `UserNode`

Field:
- `char userID[20]`
- `char nama[100]`
- `SensorData sensor`
- `float monitoringScore`
- `UserNode* next`

### Struct `LinkedList`

Field:
- `UserNode* head` — diinisialisasi `nullptr`
- `int count` — diinisialisasi `0`

### Deklarasi fungsi (badan hanya berisi `// TODO: implementasi`)

```cpp
// Mengubah semua karakter char array menjadi huruf kapital
void toUpperCase(char* str);

// Memeriksa apakah 3 karakter pertama userID sesuai kode wilayah yang valid
// Return true jika valid, false jika tidak
bool isValidPrefix(char* userID);

// Mengembalikan nomor wilayah (1-4) berdasarkan prefix userID
// Return 0 jika tidak ditemukan
int getWilayah(char* userID);

// Menghitung monitoring score berdasarkan jumlah sensor yang bernilai ideal
// Ideal: temperature 20-27, humidity 40-60, airQuality 0-50, smoke==0, noise 30-55
// Rumus: (jumlahIdeal / 5.0f) * 100.0f
float hitungMonitoringScore(SensorData s);

// Return true jika semua sensor bernilai ideal (score == 100%)
bool isIdealSensor(SensorData s);
```

---

## FILE 2 — `src/user_add.h`

Header guard: `USER_ADD_H`

Include: `#include "structures.h"`

### Deklarasi fungsi (badan hanya berisi `// TODO: implementasi`)

```cpp
// Memeriksa apakah userID sudah ada di linked list
// Return true jika duplikat ditemukan
bool isUserIDExist(LinkedList& list, char* userID);

// Memeriksa apakah semua nilai sensor berada dalam range yang diperbolehkan
// Range: temperature -10~50, humidity 0~100, airQuality 0~500, noise 0~120
// Return true jika semua valid
bool validasiSensor(SensorData s);

// Meminta input semua data sensor dari user dengan validasi range
// Melakukan loop ulang jika nilai diluar range
// Return SensorData yang sudah valid
SensorData inputSensor();

// Menambahkan data pelanggan baru ke linked list
// Alur: input userID -> validasi prefix & duplikat -> input nama -> inputSensor()
// -> buat node baru -> insert ke tail linked list -> tampilkan hasil
void tambahUser(LinkedList& list);

// Generate sejumlah data acak menggunakan rand() untuk keperluan pengujian
void generateRandom(LinkedList& list, int jumlah);
```

---

## FILE 3 — `src/user_manage.h`

Header guard: `USER_MANAGE_H`

Include: `#include "user_add.h"`

### Deklarasi fungsi (badan hanya berisi `// TODO: implementasi`)

```cpp
// Mencari pelanggan berdasarkan userID
// Jika ditemukan: tampilkan detail lengkap beserta data sensor
// Jika tidak ditemukan: tampilkan pesan error
void cariUser(LinkedList& list, char* userID);

// Memperbarui data pelanggan yang sudah ada
// Jika tidak ditemukan: tampilkan pesan error
// Jika ditemukan: tampilkan data lama -> input data baru -> update node -> recalculate score
void updateUser(LinkedList& list, char* userID);

// Menghapus data pelanggan berdasarkan userID secara permanen
// Tangani 2 kasus: node adalah head, atau node bukan head
// Jika tidak ditemukan: tampilkan pesan error
void hapusUser(LinkedList& list, char* userID);

// Menampilkan ringkasan semua pelanggan dalam format tabel
// Jika list kosong: tampilkan pesan kosong
void tampilkanSemuaUser(LinkedList& list);
```

---

## FILE 4 — `src/user_report.h`

Header guard: `USER_REPORT_H`

Include: `#include "structures.h"`

### Deklarasi fungsi (badan hanya berisi `// TODO: implementasi`)

```cpp
// Menyalin semua pointer node dari linked list ke array of pointer
// Caller wajib delete[] hasil setelah selesai digunakan
// Return: UserNode** array berukuran list.count
UserNode** salinKeArray(LinkedList& list);

// Fungsi merge untuk menggabungkan dua bagian array secara ascending by monitoringScore
void merge(UserNode** arr, int kiri, int tengah, int kanan);

// Fungsi rekursif merge sort ascending berdasarkan monitoringScore
void mergeSort(UserNode** arr, int kiri, int kanan);

// Menghitung jumlah rumah yang sensor-nya bernilai ideal per jenis sensor
// Semua parameter adalah referensi yang diubah langsung di dalam fungsi
void hitungRekap(LinkedList& list, int& rTemp, int& rHumidity,
                 int& rAir, int& rSmoke, int& rNoise);

// Menampilkan laporan lengkap:
// 1. Statistik (total, rata-rata score, jumlah ideal vs tidak ideal)
// 2. Rekap sensor
// 3. Peringkat semua user terurut ascending by monitoringScore (pakai mergeSort)
void showLaporan(LinkedList& list);
```

---

## FILE 5 — `src/main.cpp`

Include:
```cpp
#include <iostream>
#include "user_manage.h"
#include "user_report.h"
using namespace std;
```

### Fungsi `main()`

Kerangka `main()` berisi:

```cpp
int main() {
    // TODO: inisialisasi LinkedList
    // list.head = nullptr; list.count = 0;

    // TODO: tampilkan header program sekali saat startup

    // TODO: loop menu utama dengan while(true)
    // Di dalam loop:
    //   - tampilkan menu
    //   - baca input perintah menggunakan char array + cin
    //   - dispatch ke fungsi yang sesuai:
    //       "tambah"      -> tambahUser(list)
    //       "cari"        -> baca ID lalu cariUser(list, id)
    //       "update"      -> baca ID lalu updateUser(list, id)
    //       "hapus"       -> baca ID lalu hapusUser(list, id)
    //       "show"        -> showLaporan(list)
    //       "list"        -> tampilkanSemuaUser(list)
    //       "random"      -> baca N lalu generateRandom(list, N)
    //       "exit"        -> tampilkan pesan keluar, bebaskan memori, return 0
    //       default       -> tampilkan pesan perintah tidak dikenal

    // TODO: cleanup memori linked list sebelum return 0

    return 0;
}
```

---

## RINGKASAN YANG DIHARAPKAN

Setelah Claude Code selesai, setiap file hanya berisi:
- Header guard
- Include yang sesuai
- Definisi struct (khusus `structures.h`)
- Deklarasi dan badan fungsi yang **kosong** (hanya `// TODO:` di dalamnya)
- Return statement placeholder jika fungsi memiliki return type bukan `void`

**Tidak ada logika, tidak ada loop, tidak ada kondisi if** — semua itu adalah tugas masing-masing anggota kelompok untuk diimplementasikan.
