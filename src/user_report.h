#ifndef USER_REPORT_H
#define USER_REPORT_H

#include "structures.h"
#include <iostream>
using namespace std;

// Menyalin linked list ke array pointer
UserNode** salinKeArray(LinkedList& list) {
    if (list.count == 0) return nullptr;

    UserNode** arr = new UserNode*[list.count];

    UserNode* current = list.head;
    int i = 0;

    while (current != nullptr) {
        arr[i++] = current;
        current = current->next;
    }

    return arr;
}

// Merge untuk Merge Sort Ascending Monitoring Score
void merge(UserNode** arr, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    UserNode** L = new UserNode*[n1];
    UserNode** R = new UserNode*[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[kiri + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[tengah + 1 + j];

    int i = 0;
    int j = 0;
    int k = kiri;

    while (i < n1 && j < n2) {
        if (L[i]->monitoringScore <= R[j]->monitoringScore) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Merge Sort
void mergeSort(UserNode** arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);

        merge(arr, kiri, tengah, kanan);
    }
}

// Menghitung rekap sensor ideal
void hitungRekap(LinkedList& list,
                 int& rTemp,
                 int& rHumidity,
                 int& rAir,
                 int& rSmoke,
                 int& rNoise) {

    rTemp = 0;
    rHumidity = 0;
    rAir = 0;
    rSmoke = 0;
    rNoise = 0;

    UserNode* current = list.head;

    while (current != nullptr) {

        SensorData s = current->sensor;

        if (s.temperature >= 20 && s.temperature <= 27)
            rTemp++;

        if (s.humidity >= 40 && s.humidity <= 60)
            rHumidity++;

        if (s.airQuality >= 0 && s.airQuality <= 50)
            rAir++;

        if (s.smoke == 0)
            rSmoke++;

        if (s.noise >= 30 && s.noise <= 55)
            rNoise++;

        current = current->next;
    }
}

// Menampilkan laporan lengkap
void showLaporan(LinkedList& list) {

    if (list.head == nullptr) {
        cout << "\nBelum ada data pelanggan.\n";
        return;
    }

    int totalPelanggan = list.count;

    float totalScore = 0;
    int jumlahIdeal = 0;

    UserNode* current = list.head;

    while (current != nullptr) {

        totalScore += current->monitoringScore;

        if (current->monitoringScore == 100)
            jumlahIdeal++;

        current = current->next;
    }

    float rataRata = totalScore / totalPelanggan;

    int rTemp, rHumidity, rAir, rSmoke, rNoise;

    hitungRekap(list,
                rTemp,
                rHumidity,
                rAir,
                rSmoke,
                rNoise);

    UserNode** arr = salinKeArray(list);

    mergeSort(arr, 0, totalPelanggan - 1);

    cout << "\n=========================================\n";
    cout << "      LAPORAN MONITORING IOT\n";
    cout << "=========================================\n";

    cout << "\nStatistik Monitoring\n";
    cout << "Jumlah User Dengan Pembacaan Ideal : "
         << jumlahIdeal << endl;

    cout << "Jumlah User Dengan Pembacaan Tidak Ideal : "
         << (totalPelanggan - jumlahIdeal) << endl;

    cout << "Total Pelanggan : "
         << totalPelanggan << endl;

    cout << "Rata-rata Score : "
         << rataRata << "%\n";

    cout << "\nRekap Sensor:\n";
    cout << "Temperature : " << rTemp << " rumah\n";
    cout << "Humidity : " << rHumidity << " rumah\n";
    cout << "Air Quality : " << rAir << " rumah\n";
    cout << "Smoke : " << rSmoke << " rumah\n";
    cout << "Noise : " << rNoise << " rumah\n";

    cout << "\n=========================================\n";
    cout << "PERINGKAT RUMAH USER\n";
    cout << "=========================================\n";

    for (int i = 0; i < totalPelanggan; i++) {

        cout << "\n----------------------------------------------\n";
        cout << "Peringkat " << (i + 1) << endl;
        cout << "User ID: "
             << arr[i]->userID << endl;

        cout << "Nama Pelanggan: "
             << arr[i]->nama << endl;

        cout << "Monitoring Score: "
             << arr[i]->monitoringScore
             << "%\n";

        cout << "Wilayah: "
             << getWilayah(arr[i]->userID)
             << endl;

        cout << "Data Sensor:\n";

        cout << "Temp: "
             << arr[i]->sensor.temperature
             << " C\n";

        cout << "Humidity: "
             << arr[i]->sensor.humidity
             << " %\n";

        cout << "Air Quality: "
             << arr[i]->sensor.airQuality
             << endl;

        cout << "Smoke: "
             << arr[i]->sensor.smoke
             << endl;

        cout << "Noise: "
             << arr[i]->sensor.noise
             << " dB\n";
    }

    cout << "\n----------------------------------------------\n";

    delete[] arr;
}

#endif