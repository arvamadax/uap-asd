#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
using namespace std;

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
    // TODO: implementasi
}

// Memeriksa apakah 3 karakter pertama userID sesuai kode wilayah yang valid
// Return true jika valid, false jika tidak
bool isValidPrefix(char* userID) {
    // TODO: implementasi
    return false;
}

// Mengembalikan nomor wilayah (1-4) berdasarkan prefix userID
// Return 0 jika tidak ditemukan
int getWilayah(char* userID) {
    // TODO: implementasi
    return 0;
}

// Menghitung monitoring score berdasarkan jumlah sensor yang bernilai ideal
// Ideal: temperature 20-27, humidity 40-60, airQuality 0-50, smoke==0, noise 30-55
// Rumus: (jumlahIdeal / 5.0f) * 100.0f
float hitungMonitoringScore(SensorData s) {
    // TODO: implementasi
    return 0.0f;
}

// Return true jika semua sensor bernilai ideal (score == 100%)
bool isIdealSensor(SensorData s) {
    // TODO: implementasi
    return false;
}

#endif
