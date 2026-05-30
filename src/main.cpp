#include <iostream>
#include "user_manage.h"
#include "user_report.h"
using namespace std;

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
