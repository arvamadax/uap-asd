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

#endif
