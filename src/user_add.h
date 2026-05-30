#ifndef USER_ADD_H
#define USER_ADD_H

#include "structures.h"

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

#endif
