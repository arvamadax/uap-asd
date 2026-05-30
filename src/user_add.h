#ifndef USER_ADD_H
#define USER_ADD_H

#include "structures.h"

// Membandingkan dua string tanpa menggunakan <cstring>
bool isSameString(char* a, char* b) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

// Memeriksa apakah userID sudah ada di linked list
// Return true jika duplikat ditemukan
bool isUserIDExist(LinkedList& list, char* userID) {
    UserNode* current = list.head;

    while (current != nullptr) {
        if (isSameString(current->userID, userID)) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Memeriksa apakah semua nilai sensor berada dalam range yang diperbolehkan
// Range: temperature -10~50, humidity 0~100, airQuality 0~500, noise 0~120
// Return true jika semua valid
bool validasiSensor(SensorData s) {
    return (s.temperature >= -10 && s.temperature <= 50) &&
           (s.humidity >= 0 && s.humidity <= 100) &&
           (s.airQuality >= 0 && s.airQuality <= 500) &&
           (s.noise >= 0 && s.noise <= 120);
}

// Meminta input semua data sensor dari user dengan validasi range
// Melakukan loop ulang jika nilai diluar range
// Return SensorData yang sudah valid
SensorData inputSensor() {
    SensorData s;

    do {
        cout << "Temperature (-10 sampai 50): ";
        cin >> s.temperature;
    } while (s.temperature < -10 || s.temperature > 50);

    do {
        cout << "Humidity (0 sampai 100): ";
        cin >> s.humidity;
    } while (s.humidity < 0 || s.humidity > 100);

    do {
        cout << "Air Quality (0 sampai 500): ";
        cin >> s.airQuality;
    } while (s.airQuality < 0 || s.airQuality > 500);

    do {
        cout << "Smoke (0=Tidak, 1=Ya): ";
        cin >> s.smoke;
    } while (s.smoke != 0 && s.smoke != 1);

    do {
        cout << "Noise (0 sampai 120): ";
        cin >> s.noise;
    } while (s.noise < 0 || s.noise > 120);

    return s;
}

// Menambahkan data pelanggan baru ke linked list
// Alur: input userID -> validasi prefix & duplikat -> input nama -> inputSensor()
// -> buat node baru -> insert ke tail linked list -> tampilkan hasil
void tambahUser(LinkedList& list) {
    UserNode* newNode = new UserNode;

    while (true) {
        cout << "Masukkan User ID: ";
        cin >> newNode->userID;

        if (!isValidPrefix(newNode->userID)) {
            cout << "Prefix wilayah tidak valid!\n";
            continue;
        }

        if (isUserIDExist(list, newNode->userID)) {
            cout << "User ID sudah digunakan!\n";
            continue;
        }

        break;
    }

    cout << "Masukkan Nama: ";
    cin.ignore();
    cin.getline(newNode->nama, 100);

    newNode->sensor = inputSensor();

    newNode->monitoringScore =
        hitungMonitoringScore(newNode->sensor);

    newNode->next = nullptr;

    if (list.head == nullptr) {
        list.head = newNode;
    } else {
        UserNode* current = list.head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    list.count++;

    cout << "User berhasil ditambahkan!\n";
}

#endif
