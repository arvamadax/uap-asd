#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "user_add.h"

// Menyalin string sumber ke tujuan tanpa <cstring>
void salinStr(char* tujuan, const char* sumber) {
    int i = 0;
    while (sumber[i] != '\0') {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

// Menghitung panjang C-string
int panjangStr(const char* s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

// Menampilkan data sensor pada konsol
void tampilkanSensor(SensorData s) {
    cout << "  Temperature  : " << s.temperature << " C\n";
    cout << "  Humidity     : " << s.humidity    << " %\n";
    cout << "  Air Quality  : " << s.airQuality  << "\n";
    cout << "  Smoke        : " << (s.smoke ? "1 (TERDETEKSI)" : "0 (Aman)") << "\n";
    cout << "  Noise        : " << s.noise       << " dB\n";
}

// Menampilkan detail lengkap satu user
void tampilkanDetailUser(UserNode* node) {
    cout << "+-----------------------------------------+\n";
    cout << "  User ID          : " << node->userID << "\n";
    cout << "  Nama Pelanggan   : " << node->nama   << "\n";
    cout << "  Monitoring Score : " << node->monitoringScore << "%\n";
    cout << "  Wilayah          : " << getWilayah(node->userID) << "\n";
    cout << "  Data Sensor:\n";
    tampilkanSensor(node->sensor);
    cout << "+-----------------------------------------+\n";
}

// Mencari pelanggan berdasarkan userID
// Jika ditemukan: tampilkan detail lengkap beserta data sensor
// Jika tidak ditemukan: tampilkan pesan error
void cariUser(LinkedList& list, char* userID) {
    if (list.head == nullptr) {
        cout << "[!] Sistem belum memiliki data pelanggan.\n";
        return;
    }

    toUpperCase(userID);

    UserNode* current = list.head;
    while (current != nullptr) {
        if (strSama(current->userID, userID)) {
            cout << "\n[OK] User ditemukan!\n";
            tampilkanDetailUser(current);
            return;
        }
        current = current->next;
    }

    cout << "[!] User dengan ID \"" << userID << "\" tidak ditemukan.\n";
}

// Memperbarui data pelanggan yang sudah ada
// Jika tidak ditemukan: tampilkan pesan error
// Jika ditemukan: tampilkan data lama -> input data baru -> update node -> recalculate score
void updateUser(LinkedList& list, char* userID) {
    if (list.head == nullptr) {
        cout << "[!] Sistem belum memiliki data pelanggan.\n";
        return;
    }

    toUpperCase(userID);

    UserNode* current = list.head;
    while (current != nullptr) {
        if (strSama(current->userID, userID)) {
            cout << "\n[OK] User ditemukan!\n";
            cout << "--- Data Lama ---\n";
            tampilkanDetailUser(current);

            cout << "\nMasukkan nama baru (atau tekan Enter untuk skip): ";
            char namaBaru[100];
            cin.ignore();
            cin.getline(namaBaru, 100);

            if (panjangStr(namaBaru) > 0) {
                toUpperCase(namaBaru);
                salinStr(current->nama, namaBaru);
            }

            cout << "Masukkan data sensor baru:\n";
            SensorData sensorBaru = inputSensor();

            current->sensor = sensorBaru;

            float skorLama = current->monitoringScore;
            current->monitoringScore = hitungMonitoringScore(current->sensor);

            cout << "\n[OK] Data berhasil diperbarui.\n";
            cout << "  Monitoring Score : " << skorLama
                 << "% -> " << current->monitoringScore << "%\n";
            cout << "--- Data Baru ---\n";
            tampilkanDetailUser(current);
            return;
        }
        current = current->next;
    }

    cout << "[!] User dengan ID \"" << userID << "\" tidak ditemukan.\n";
}

// Menghapus data pelanggan berdasarkan userID secara permanen
// Tangani 2 kasus: node adalah head, atau node bukan head
// Jika tidak ditemukan: tampilkan pesan error
void hapusUser(LinkedList& list, char* userID) {
    if (list.head == nullptr) {
        cout << "[!] Sistem belum memiliki data pelanggan.\n";
        return;
    }

    toUpperCase(userID);

    if (strSama(list.head->userID, userID)) {
        UserNode* hapus = list.head;
        list.head = list.head->next;
        delete hapus;
        list.count--;
        cout << "[OK] User dengan ID \"" << userID
             << "\" berhasil dihapus dari sistem.\n";
        return;
    }

    UserNode* prev    = list.head;
    UserNode* current = list.head->next;

    while (current != nullptr) {
        if (strSama(current->userID, userID)) {
            prev->next = current->next;
            delete current;
            list.count--;
            cout << "[OK] User dengan ID \"" << userID
                 << "\" berhasil dihapus dari sistem.\n";
            return;
        }
        prev    = current;
        current = current->next;
    }

    cout << "[!] User dengan ID \"" << userID << "\" tidak ditemukan.\n";
}

// Menampilkan ringkasan semua pelanggan dalam format tabel sederhana
// (tanpa sort dan statistik - lihat showLaporan di user_report.h untuk laporan lengkap)
// Jika list kosong: tampilkan pesan kosong
void tampilkanSemuaUser(LinkedList& list) {
    if (list.head == nullptr || list.count == 0) {
        cout << "[!] Belum ada data pelanggan dalam sistem.\n";
        return;
    }

    cout << "\n=================================================================\n";
    cout << "  RINGKASAN PELANGGAN (Total: " << list.count << ")\n";
    cout << "=================================================================\n";
    cout << "  No   User ID    Wilayah   Score     Nama Pelanggan\n";
    cout << "-----------------------------------------------------------------\n";

    UserNode* current = list.head;
    int no = 1;
    while (current != nullptr) {
        cout << "  " << no
             << "    " << current->userID
             << "      " << getWilayah(current->userID)
             << "        " << current->monitoringScore << "%"
             << "     " << current->nama << "\n";
        current = current->next;
        no++;
    }

    cout << "=================================================================\n";
    cout << "Gunakan perintah 'show' untuk laporan lengkap (statistik + sort).\n";
}

#endif
