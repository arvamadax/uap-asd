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
//   ||         FILE FINAL - SIAP DIKUMPULKAN                  ||
//   ============================================================
//   File ini adalah hasil akhir gabungan dari seluruh modul
//   yang telah dikerjakan oleh masing-masing anggota kelompok
//   di dalam folder src/.
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

// Membandingkan dua C-string tanpa menggunakan <cstring>
bool strSama(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

// Memeriksa apakah 3 karakter pertama userID sesuai kode wilayah yang valid
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

// Menghitung monitoring score berdasarkan jumlah sensor bernilai ideal
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
bool isUserIDExist(LinkedList& list, char* userID) {
    UserNode* current = list.head;

    while (current != nullptr) {
        if (strSama(current->userID, userID)) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Memeriksa apakah semua nilai sensor berada dalam range yang diperbolehkan
bool validasiSensor(SensorData s) {
    return (s.temperature >= -10 && s.temperature <= 50) &&
           (s.humidity >= 0 && s.humidity <= 100) &&
           (s.airQuality >= 0 && s.airQuality <= 500) &&
           (s.noise >= 0 && s.noise <= 120);
}

// Meminta input semua data sensor dari user dengan validasi range
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

// =====================================================================
//   MODUL 3 - CARI, UPDATE, HAPUS, LIST USER  (Muh. Khaliq Fattah Qaid)
// =====================================================================

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

// Menghapus data pelanggan berdasarkan userID
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
// (laporan lengkap dengan statistik & sort ada di showLaporan)
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

// =====================================================================
//   MODUL 4 - LAPORAN & MERGE SORT  (Daniel Jalayar Ananda)
// =====================================================================

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

// Merge untuk Merge Sort ascending by monitoringScore
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

// Fungsi rekursif merge sort O(n log n)
void mergeSort(UserNode** arr, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);

        merge(arr, kiri, tengah, kanan);
    }
}

// Menghitung rekap sensor ideal per jenis sensor
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

// Menampilkan laporan lengkap dengan merge sort
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

// =====================================================================
//   MODUL 5 - MAIN PROGRAM  (Arva Mada Jayastu)
// =====================================================================

// Membersihkan seluruh node linked list dari memori
void cleanupList(LinkedList& list) {
    UserNode* current = list.head;
    while (current != nullptr) {
        UserNode* next = current->next;
        delete current;
        current = next;
    }
    list.head = nullptr;
    list.count = 0;
}

// Menampilkan banner header program saat startup
void tampilkanHeader() {
    cout << "===========================================================\n";
    cout << "        IoT HOME MONITORING SYSTEM\n";
    cout << "   UAP Algoritma dan Struktur Data | Kelas E - Kelompok 7\n";
    cout << "   Teknik Komputer FILKOM Universitas Brawijaya 2025/2026\n";
    cout << "===========================================================\n\n";
}

// Menampilkan menu perintah yang tersedia
void tampilkanMenu() {
    cout << "\n-----------------------------------------------------------\n";
    cout << "  MENU PERINTAH\n";
    cout << "-----------------------------------------------------------\n";
    cout << "  tambah  -> Tambah data pelanggan baru\n";
    cout << "  cari    -> Cari pelanggan berdasarkan User ID\n";
    cout << "  update  -> Perbarui data pelanggan\n";
    cout << "  hapus   -> Hapus data pelanggan\n";
    cout << "  list    -> Tampilkan ringkasan tabel semua pelanggan\n";
    cout << "  show    -> Tampilkan laporan lengkap (Merge Sort)\n";
    cout << "  exit    -> Keluar dari program\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Masukkan perintah: ";
}

int main() {
    LinkedList list;
    list.head = nullptr;
    list.count = 0;

    tampilkanHeader();

    char perintah[20];
    char userID[20];

    while (true) {
        tampilkanMenu();
        cin >> perintah;
        toUpperCase(perintah);

        if (strSama(perintah, "TAMBAH")) {
            tambahUser(list);
        }
        else if (strSama(perintah, "CARI")) {
            cout << "Masukkan User ID yang dicari: ";
            cin >> userID;
            cariUser(list, userID);
        }
        else if (strSama(perintah, "UPDATE")) {
            cout << "Masukkan User ID yang akan diupdate: ";
            cin >> userID;
            updateUser(list, userID);
        }
        else if (strSama(perintah, "HAPUS")) {
            cout << "Masukkan User ID yang akan dihapus: ";
            cin >> userID;
            hapusUser(list, userID);
        }
        else if (strSama(perintah, "LIST")) {
            tampilkanSemuaUser(list);
        }
        else if (strSama(perintah, "SHOW")) {
            showLaporan(list);
        }
        else if (strSama(perintah, "EXIT")) {
            cout << "\nTerima kasih telah menggunakan IoT Home Monitoring System.\n";
            cout << "Membersihkan memori...\n";
            cleanupList(list);
            cout << "Program selesai.\n";
            return 0;
        }
        else {
            cout << "[!] Perintah \"" << perintah << "\" tidak dikenal. Coba lagi.\n";
        }
    }

    cleanupList(list);
    return 0;
}
