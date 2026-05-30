// =====================================================================
//   UAP ALGORITMA DAN STRUKTUR DATA - TEKNIK KOMPUTER FILKOM UB
//   TAHUN AJARAN 2025/2026 | KELAS E | KELOMPOK 7
//   JUDUL: IoT HOME MONITORING SYSTEM
// =====================================================================
//
//   ANGGOTA KELOMPOK:
//   - Arva Mada Jayastu       (255150300111053)  - Modul 1 & 5
//   - Harry Widjaya           (255150300111044)  - Modul 2
//   - Muh. Khaliq Fattah Qaid (255150300111046)  - Modul 3
//   - Daniel Jalayar Ananda   (255150307111077)  - Modul 4
//
// =====================================================================
//
//   ============================================================
//   ||   PERHATIAN - JANGAN DISENTUH SAMPAI FINALISASI       ||
//   ============================================================
//   File ini adalah FILE FINAL GABUNGAN yang akan dikumpulkan.
//   File ini HANYA akan diisi oleh Arva setelah semua modul
//   selesai dikerjakan masing-masing anggota di folder src/.
//
//   Anggota kelompok HARUS mengerjakan kodenya di file masing-masing
//   di dalam folder src/, BUKAN di file ini.
//
//     - Harry  -> src/user_add.h
//     - Khaliq -> src/user_manage.h
//     - Daniel -> src/user_report.h
//
//   Setelah semua modul selesai dan di-merge ke main, Arva akan
//   menggabungkan seluruh kode ke dalam file ini secara manual.
//
//   JANGAN MENG-EDIT, COMMIT, ATAU PUSH FILE INI SEBELUM DIIZINKAN.
//   ============================================================
//
// =====================================================================

#include <iostream>
using namespace std;

// =====================================================================
//   MODUL 1 - CORE STRUCTURES  (Arva Mada Jayastu)
// =====================================================================

const int JUMLAH_WILAYAH = 4;
const char KODE_WILAYAH[4][4] = {"053", "044", "046", "077"};

struct SensorData {
    float temperature;
    float humidity;
    int airQuality;
    bool smoke;
    float noise;
};

struct UserNode {
    char userID[20];
    char nama[100];
    SensorData sensor;
    float monitoringScore;
    UserNode* next;
};

struct LinkedList {
    UserNode* head = nullptr;
    int count = 0;
};

// Mengubah semua karakter char array menjadi huruf kapital
void toUpperCase(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
        i++;
    }
}

// Memeriksa apakah 3 karakter pertama userID sesuai kode wilayah yang valid
// Return true jika valid, false jika tidak
bool isValidPrefix(char* userID) {
    if (userID[0] == '\0' || userID[1] == '\0' || userID[2] == '\0') {
        return false;
    }
    for (int i = 0; i < JUMLAH_WILAYAH; i++) {
        if (userID[0] == KODE_WILAYAH[i][0] &&
            userID[1] == KODE_WILAYAH[i][1] &&
            userID[2] == KODE_WILAYAH[i][2]) {
            return true;
        }
    }
    return false;
}

// Mengembalikan nomor wilayah (1-4) berdasarkan prefix userID
// Return 0 jika tidak ditemukan
int getWilayah(char* userID) {
    if (userID[0] == '\0' || userID[1] == '\0' || userID[2] == '\0') {
        return 0;
    }
    for (int i = 0; i < JUMLAH_WILAYAH; i++) {
        if (userID[0] == KODE_WILAYAH[i][0] &&
            userID[1] == KODE_WILAYAH[i][1] &&
            userID[2] == KODE_WILAYAH[i][2]) {
            return i + 1;
        }
    }
    return 0;
}

// Menghitung monitoring score berdasarkan jumlah sensor yang bernilai ideal
// Ideal: temperature 20-27, humidity 40-60, airQuality 0-50, smoke==0, noise 30-55
// Rumus: (jumlahIdeal / 5.0f) * 100.0f
float hitungMonitoringScore(SensorData s) {
    int jumlahIdeal = 0;
    if (s.temperature >= 20.0f && s.temperature <= 27.0f) {
        jumlahIdeal++;
    }
    if (s.humidity >= 40.0f && s.humidity <= 60.0f) {
        jumlahIdeal++;
    }
    if (s.airQuality >= 0 && s.airQuality <= 50) {
        jumlahIdeal++;
    }
    if (s.smoke == 0) {
        jumlahIdeal++;
    }
    if (s.noise >= 30.0f && s.noise <= 55.0f) {
        jumlahIdeal++;
    }
    return (jumlahIdeal / 5.0f) * 100.0f;
}

// Return true jika semua sensor bernilai ideal (score == 100%)
bool isIdealSensor(SensorData s) {
    return hitungMonitoringScore(s) == 100.0f;
}

// =====================================================================
//   MODUL 2 - TAMBAH USER  (Harry Widjaya)
// =====================================================================

// Memeriksa apakah userID sudah ada di linked list
// Return true jika duplikat ditemukan
bool isUserIDExist(LinkedList& list, char* userID) {
    // TODO: implementasi
    return false;
}

// Memeriksa apakah semua nilai sensor berada dalam range yang diperbolehkan
// Range: temperature -10~50, humidity 0~100, airQuality 0~500, noise 0~120
// Return true jika semua valid
bool validasiSensor(SensorData s) {
    // TODO: implementasi
    return false;
}

// Meminta input semua data sensor dari user dengan validasi range
// Melakukan loop ulang jika nilai diluar range
// Return SensorData yang sudah valid
SensorData inputSensor() {
    // TODO: implementasi
    SensorData s;
    return s;
}

// Menambahkan data pelanggan baru ke linked list
// Alur: input userID -> validasi prefix & duplikat -> input nama -> inputSensor()
// -> buat node baru -> insert ke tail linked list -> tampilkan hasil
void tambahUser(LinkedList& list) {
    // TODO: implementasi
}

// Generate sejumlah data acak menggunakan rand() untuk keperluan pengujian
void generateRandom(LinkedList& list, int jumlah) {
    // TODO: implementasi
}

// =====================================================================
//   MODUL 3 - CARI, UPDATE, HAPUS USER  (Muh. Khaliq Fattah Qaid)
// =====================================================================

// Mencari pelanggan berdasarkan userID
// Jika ditemukan: tampilkan detail lengkap beserta data sensor
// Jika tidak ditemukan: tampilkan pesan error
void cariUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Memperbarui data pelanggan yang sudah ada
// Jika tidak ditemukan: tampilkan pesan error
// Jika ditemukan: tampilkan data lama -> input data baru -> update node -> recalculate score
void updateUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Menghapus data pelanggan berdasarkan userID secara permanen
// Tangani 2 kasus: node adalah head, atau node bukan head
// Jika tidak ditemukan: tampilkan pesan error
void hapusUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Menampilkan ringkasan semua pelanggan dalam format tabel
// Jika list kosong: tampilkan pesan kosong
void tampilkanSemuaUser(LinkedList& list) {
    // TODO: implementasi
}

// =====================================================================
//   MODUL 4 - LAPORAN & SORT  (Daniel Jalayar Ananda)
// =====================================================================

// Menyalin semua pointer node dari linked list ke array of pointer
// Caller wajib delete[] hasil setelah selesai digunakan
// Return: UserNode** array berukuran list.count
UserNode** salinKeArray(LinkedList& list) {
    // TODO: implementasi
    return nullptr;
}

// Fungsi merge untuk menggabungkan dua bagian array secara ascending by monitoringScore
void merge(UserNode** arr, int kiri, int tengah, int kanan) {
    // TODO: implementasi
}

// Fungsi rekursif merge sort ascending berdasarkan monitoringScore
void mergeSort(UserNode** arr, int kiri, int kanan) {
    // TODO: implementasi
}

// Menghitung jumlah rumah yang sensor-nya bernilai ideal per jenis sensor
// Semua parameter adalah referensi yang diubah langsung di dalam fungsi
void hitungRekap(LinkedList& list, int& rTemp, int& rHumidity,
                 int& rAir, int& rSmoke, int& rNoise) {
    // TODO: implementasi
}

// Menampilkan laporan lengkap:
// 1. Statistik (total, rata-rata score, jumlah ideal vs tidak ideal)
// 2. Rekap sensor
// 3. Peringkat semua user terurut ascending by monitoringScore (pakai mergeSort)
void showLaporan(LinkedList& list) {
    // TODO: implementasi
}

// =====================================================================
//   MODUL 5 - MAIN PROGRAM  (Arva Mada Jayastu)
// =====================================================================
//
//   CATATAN: Modul 5 (main) sengaja dikosongkan terlebih dahulu.
//   Akan diisi oleh Arva setelah Modul 2, 3, dan 4 selesai
//   dikerjakan dan ter-merge ke branch main.
//
// =====================================================================

int main() {
    // TODO: inisialisasi LinkedList
    // TODO: tampilkan header program sekali saat startup
    // TODO: loop menu utama dengan while(true)
    //       dispatch ke fungsi sesuai perintah:
    //         "tambah" "cari" "update" "hapus" "show" "list" "random" "exit"
    // TODO: cleanup memori linked list sebelum return 0

    return 0;
}
