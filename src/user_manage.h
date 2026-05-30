#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "user_add.h"

bool strSama(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

void salinStr(char* tujuan, const char* sumber) {
    int i = 0;
    while (sumber[i] != '\0') {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

int panjangStr(const char* s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void tampilkanSensor(SensorData s) {
    cout << "  Temperature  : " << s.temperature << " C\n";
    cout << "  Humidity     : " << s.humidity    << " %\n";
    cout << "  Air Quality  : " << s.airQuality  << "\n";
    cout << "  Smoke        : " << (s.smoke ? "1 (TERDETEKSI)" : "0 (Aman)") << "\n";
    cout << "  Noise        : " << s.noise       << " dB\n";
}

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

// ============================================================
//  1. CARI USER
// ============================================================
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

// ============================================================
//  2. UPDATE USER
// ============================================================
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

// ============================================================
//  3. HAPUS USER
// ============================================================
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

// ============================================================
//  Helper Sorting: Insertion Sort ascending by monitoringScore
// ============================================================
void insertionSortByScore(UserNode** arr, int n) {
    for (int i = 1; i < n; i++) {
        UserNode* kunci = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j]->monitoringScore > kunci->monitoringScore) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}

// ============================================================
//  4. TAMPILKAN SEMUA USER
// ============================================================
void tampilkanSemuaUser(LinkedList& list) {
    if (list.head == nullptr || list.count == 0) {
        cout << "[!] Belum ada data pelanggan dalam sistem.\n";
        return;
    }

    int n = list.count;

    // Kumpulkan pointer ke array sementara
    UserNode** arr = new UserNode*[n];
    UserNode* cur  = list.head;
    for (int i = 0; i < n; i++) {
        arr[i] = cur;
        cur    = cur->next;
    }

    // Hitung statistik
    int   jumlahIdeal = 0;
    float totalScore  = 0.0f;
    int   rekap[5]    = {0, 0, 0, 0, 0};

    for (int i = 0; i < n; i++) {
        SensorData s = arr[i]->sensor;
        totalScore  += arr[i]->monitoringScore;

        if (isIdealSensor(s)) jumlahIdeal++;

        if (s.temperature >= 20.0f && s.temperature <= 27.0f) rekap[0]++;
        if (s.humidity    >= 40.0f && s.humidity    <= 60.0f) rekap[1]++;
        if (s.airQuality  >= 0     && s.airQuality  <= 50   ) rekap[2]++;
        if (s.smoke == 0)                                      rekap[3]++;
        if (s.noise >= 30.0f       && s.noise       <= 55.0f) rekap[4]++;
    }

    float rataRata = totalScore / n;

    // Sort ascending
    insertionSortByScore(arr, n);

    // Cetak laporan
    cout << "\n============================================\n";
    cout << "         LAPORAN MONITORING IOT\n";
    cout << "============================================\n";

    cout << "\n[Statistik Monitoring]\n";
    cout << "  Jumlah User Score 100% (Ideal)   : " << jumlahIdeal       << "\n";
    cout << "  Jumlah User Score < 100%         : " << (n - jumlahIdeal) << "\n";
    cout << "  Total Pelanggan                  : " << n                  << "\n";
    cout << "  Rata-rata Score                  : " << rataRata           << "%\n";

    cout << "\n[Rekap Sensor (jumlah rumah dengan nilai ideal)]\n";
    cout << "  Temperature  : " << rekap[0] << " rumah\n";
    cout << "  Humidity     : " << rekap[1] << " rumah\n";
    cout << "  Air Quality  : " << rekap[2] << " rumah\n";
    cout << "  Smoke        : " << rekap[3] << " rumah\n";
    cout << "  Noise        : " << rekap[4] << " rumah\n";

    cout << "\n[Peringkat Rumah (Score Terendah -> Tertinggi)]\n";
    for (int i = 0; i < n; i++) {
        cout << "----------------------------------------------\n";
        cout << "Peringkat " << (i + 1) << "\n";
        cout << "  User ID          : " << arr[i]->userID                  << "\n";
        cout << "  Nama Pelanggan   : " << arr[i]->nama                    << "\n";
        cout << "  Monitoring Score : " << arr[i]->monitoringScore         << "%\n";
        cout << "  Wilayah          : " << getWilayah(arr[i]->userID)      << "\n";
        cout << "  Data Sensor:\n";
        tampilkanSensor(arr[i]->sensor);
    }
    cout << "----------------------------------------------\n";

    // Bebaskan array pointer saja, bukan node-nya
    delete[] arr;
}

#endif
