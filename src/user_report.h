#ifndef USER_REPORT_H
#define USER_REPORT_H

#include "structures.h"

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

#endif
