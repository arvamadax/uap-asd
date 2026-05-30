# 🏠 IoT Home Monitoring System
### UAP Algoritma dan Struktur Data — Teknik Komputer FILKOM UB 2025/2026
### Kelas E — Kelompok 7

---

## Tentang Proyek Ini

Proyek ini adalah sistem pengelolaan monitoring rumah berbasis IoT yang dibangun menggunakan **C++** murni tanpa STL. Sistem ini mensimulasikan bagaimana sebuah perusahaan penyedia layanan IoT mengelola data rumah pelanggan beserta sensor-sensor lingkungan yang terpasang di dalamnya.

Setiap rumah pelanggan dipantau oleh **5 jenis sensor**:

| Sensor | Rentang | Kondisi Ideal |
|---|---|---|
| 🌡️ Temperature | -10°C – 50°C | 20°C – 27°C |
| 💧 Humidity | 0% – 100% | 40% – 60% |
| 🌬️ Air Quality | 0 – 500 | 0 – 50 |
| 🔥 Smoke | 0 / 1 | 0 (tidak ada asap) |
| 🔊 Noise | 0 dB – 120 dB | 30 dB – 55 dB |

Semakin banyak sensor yang berada di kondisi ideal, semakin tinggi **Monitoring Score** rumah tersebut.

```
Monitoring Score = (Jumlah Sensor Ideal / Total Sensor) × 100%
```

---

## Fitur Program

- ✅ **Tambah User** — Menambahkan data rumah pelanggan baru beserta data sensor
- 🔍 **Cari User** — Mencari data pelanggan berdasarkan User ID
- ✏️ **Update User** — Memperbarui data pelanggan dan sensor yang sudah ada
- 🗑️ **Hapus User** — Menghapus data pelanggan secara permanen
- 📊 **Laporan & Peringkat** — Menampilkan seluruh data terurut berdasarkan Monitoring Score

---

## Struktur Data & Algoritma

Program ini dibangun menggunakan:
- **Singly Linked List** — struktur data dinamis untuk menyimpan seluruh data pelanggan
- **Merge Sort** — algoritma pengurutan O(n log n) untuk menampilkan peringkat

---

## Kode Wilayah

Setiap User ID harus diawali dengan salah satu kode wilayah berikut:

| Wilayah | Prefix | Pemilik |
|---|---|---|
| Wilayah 1 | `053xxxx` | Arva Mada Jayastu |
| Wilayah 2 | `044xxxx` | Harry Widjaya |
| Wilayah 3 | `046xxxx` | Muh. Khaliq Fattah Qaid |
| Wilayah 4 | `077xxxx` | Daniel Jalayar Ananda |

---

## Struktur Repository

```
uap-asd/
├── README.md                          ← Anda sedang membacanya
├── TUTORIAL.md                        ← Panduan GitHub untuk pemula
├── UAP_ASD_Kelas E_Kelompok 7.cpp     ← File final yang dikumpulkan
└── src/
    ├── structures.h                   ← Modul 1: Struct & Helper (Arva)
    ├── user_add.h                     ← Modul 2: Tambah User (Harry)
    ├── user_manage.h                  ← Modul 3: Cari, Update, Hapus (Khaliq)
    ├── user_report.h                  ← Modul 4: Laporan & Sort (Daniel)
    └── main.cpp                       ← Modul 5: Main Program (Arva)
```

---

## Pembagian Tugas

| Modul | File | Anggota | NIM |
|---|---|---|---|
| 1 — Core Structures | `structures.h` | Arva Mada Jayastu | 255150300111053 |
| 2 — Tambah User | `user_add.h` | Harry Widjaya | 255150300111044 |
| 3 — Cari, Update, Hapus | `user_manage.h` | Muh. Khaliq Fattah Qaid | 255150300111046 |
| 4 — Laporan & Sort | `user_report.h` | Daniel Jalayar Ananda | 255150307111077 |
| 5 — Main Program | `main.cpp` | Arva Mada Jayastu | 255150300111053 |

---

## Cara Berkontribusi

Bagi anggota kelompok yang baru pertama kali menggunakan GitHub, silakan baca panduan lengkapnya terlebih dahulu:

### 📖 [Baca TUTORIAL.md — Panduan GitHub untuk Pemula](./TUTORIAL.md)

Tutorial tersebut mencakup mulai dari instalasi Git, clone repo, membuat branch, push kode, hingga merge ke `main`.

---

## Anggota Kelompok

- Arva Mada Jayastu — 255150300111053
- Harry Widjaya — 255150300111044
- Muh. Khaliq Fattah Qaid — 255150300111046
- Daniel Jalayar Ananda — 255150307111077

**FILKOM — Universitas Brawijaya | 2025/2026**
