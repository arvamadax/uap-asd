#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "user_add.h"

// Mencari pelanggan berdasarkan userID
// Jika ditemukan: tampilkan detail lengkap beserta data sensor
// Jika tidak ditemukan: tampilkan pesan error
void cariUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Memperbarui data pelanggan yang sudah ada
// Jika tidak ditemukan: tampilkan pesan error
// Jika ditemukan: tampilkan data lama -> input data baru -> update node -> recalculate score
void updateUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Menghapus data pelanggan berdasarkan userID secara permanen
// Tangani 2 kasus: node adalah head, atau node bukan head
// Jika tidak ditemukan: tampilkan pesan error
void hapusUser(LinkedList& list, char* userID) {
    // TODO: implementasi
}

// Menampilkan ringkasan semua pelanggan dalam format tabel
// Jika list kosong: tampilkan pesan kosong
void tampilkanSemuaUser(LinkedList& list) {
    // TODO: implementasi
}

#endif
