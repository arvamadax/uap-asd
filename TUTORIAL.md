# 📖 Panduan GitHub untuk Pemula
### Khusus Anggota Kelompok 7 — UAP ASD Teknik Komputer

---

> **Tujuan dokumen ini:** Memandu kamu dari nol — mulai dari instalasi Git, clone repo, menulis kode di branch sendiri, hingga merge ke `main`. Ikuti langkah-langkah ini secara berurutan.

---

## Daftar Isi

1. [Apa itu Git dan GitHub?](#1-apa-itu-git-dan-github)
2. [Instalasi Git](#2-instalasi-git)
3. [Konfigurasi Awal Git](#3-konfigurasi-awal-git)
4. [Clone Repository](#4-clone-repository)
5. [Memahami Struktur Folder](#5-memahami-struktur-folder)
6. [Membuat Branch Sendiri](#6-membuat-branch-sendiri)
7. [Menulis Kode di Branch Kamu](#7-menulis-kode-di-branch-kamu)
8. [Menyimpan Perubahan (Commit)](#8-menyimpan-perubahan-commit)
9. [Push Branch ke GitHub](#9-push-branch-ke-github)
10. [Membuat Pull Request](#10-membuat-pull-request)
11. [Merge ke Main](#11-merge-ke-main)
12. [Update Local Setelah Merge](#12-update-local-setelah-merge)
13. [Rangkuman Perintah Penting](#13-rangkuman-perintah-penting)
14. [Troubleshooting](#14-troubleshooting)

---

## 1. Apa itu Git dan GitHub?

**Git** adalah alat untuk melacak perubahan pada kode. Bayangkan seperti tombol "Ctrl+Z" yang bisa kamu simpan selamanya dan bisa dibagi ke orang lain.

**GitHub** adalah website tempat menyimpan dan berbagi kode yang menggunakan Git. Repository (repo) adalah satu folder proyek di GitHub.

Analogi sederhananya:
- **GitHub** = Google Drive
- **Repository** = Satu folder di Google Drive
- **Branch** = Salinan folder itu untuk kamu kerjakan sendiri tanpa mengganggu yang lain
- **Commit** = Menyimpan snapshot perubahan kamu
- **Push** = Upload perubahan kamu ke GitHub
- **Merge** = Menggabungkan pekerjaan kamu ke folder utama

---

## 2. Instalasi Git

### Windows

1. Buka browser, pergi ke [https://git-scm.com/download/win](https://git-scm.com/download/win)
2. Download installer yang sesuai (biasanya 64-bit)
3. Jalankan installer, klik **Next** terus hingga selesai (pengaturan default sudah cukup)
4. Setelah selesai, buka **Git Bash** dari Start Menu

### Verifikasi Instalasi

Buka terminal (Git Bash di Windows, Terminal di Mac/Linux) lalu ketik:

```bash
git --version
```

Jika muncul sesuatu seperti `git version 2.x.x`, instalasi berhasil.

---

## 3. Konfigurasi Awal Git

Lakukan ini **sekali saja** setelah instalasi. Ganti dengan nama dan email GitHub kamu:

```bash
git config --global user.name "Nama Kamu"
git config --global user.email "email@kamu.com"
```

Contoh untuk Harry:
```bash
git config --global user.name "Harry Widjaya"
git config --global user.email "harry@example.com"
```

Verifikasi:
```bash
git config --list
```

---

## 4. Clone Repository

Clone artinya mengunduh seluruh isi repo ke komputer kamu.

1. Buka terminal
2. Pindah ke folder tempat kamu ingin menyimpan proyek, contoh:

```bash
cd Documents
```

3. Clone repo:

```bash
git clone https://github.com/arvamadax/uap-asd.git
```

4. Masuk ke folder repo:

```bash
cd uap-asd
```

5. Verifikasi isi folder:

```bash
ls
```

Kamu akan melihat `README.md`, `TUTORIAL.md`, dan folder `src/`.

---

## 5. Memahami Struktur Folder

Setelah clone, struktur foldernya seperti ini:

```
uap-asd/
├── README.md
├── TUTORIAL.md
├── UAP_ASD_Kelas E_Kelompok 7.cpp
└── src/
    ├── structures.h      ← Modul Arva
    ├── user_add.h        ← Modul Harry
    ├── user_manage.h     ← Modul Khaliq
    ├── user_report.h     ← Modul Daniel
    └── main.cpp          ← Modul Arva
```

Kamu **hanya perlu mengerjakan file milik kamu sendiri** sesuai pembagian tugas.

---

## 6. Membuat Branch Sendiri

Branch adalah "ruang kerja" milikmu sendiri yang tidak akan mengganggu pekerjaan anggota lain.

Pastikan kamu berada di branch `main` terlebih dahulu:

```bash
git checkout main
git pull origin main
```

Buat branch baru sesuai modul kamu:

```bash
# Untuk Arva (Modul 1 & 5)
git checkout -b feat/structures

# Untuk Harry (Modul 2)
git checkout -b feat/user-add

# Untuk Khaliq (Modul 3)
git checkout -b feat/user-manage

# Untuk Daniel (Modul 4)
git checkout -b feat/user-report
```

Verifikasi kamu sudah berada di branch yang benar:

```bash
git branch
```

Branch yang aktif ditandai dengan tanda `*`.

---

## 7. Menulis Kode di Branch Kamu

Sekarang kamu bebas menulis kode di file milikmu. Buka file menggunakan editor kode favoritmu (VS Code, Code::Blocks, atau Notepad++).

Contoh membuka dengan VS Code:

```bash
code src/user_add.h
```

Atau buka langsung dari File Explorer Windows, navigasi ke folder `uap-asd/src/`, lalu buka file yang sesuai.

> ⚠️ **Penting:** Hanya edit file milikmu sendiri. Jangan ubah file milik anggota lain untuk menghindari konflik.

---

## 8. Menyimpan Perubahan (Commit)

Setelah selesai menulis kode (atau setiap kali ada progres yang ingin disimpan):

**Langkah 1 — Cek perubahan apa saja yang ada:**

```bash
git status
```

File yang berubah akan muncul berwarna merah.

**Langkah 2 — Tambahkan file ke staging (siap di-commit):**

```bash
# Tambah file spesifik (lebih aman)
git add src/user_add.h

# Atau tambah semua perubahan sekaligus
git add .
```

**Langkah 3 — Commit dengan pesan yang jelas:**

```bash
git commit -m "feat: tambah fungsi tambahUser dengan validasi sensor"
```

> 💡 **Tips pesan commit yang baik:**
> - `feat: tambah fungsi X` — untuk fitur baru
> - `fix: perbaiki bug pada validasi Y` — untuk perbaikan bug
> - `docs: update komentar kode` — untuk perubahan dokumentasi

Kamu bisa commit berkali-kali. Tidak ada batasan.

---

## 9. Push Branch ke GitHub

Setelah commit, upload pekerjaanmu ke GitHub:

```bash
git push origin feat/user-add
```

Ganti `feat/user-add` dengan nama branch milikmu.

Jika ini pertama kali push branch ini, Git mungkin meminta konfirmasi. Ketik `yes` dan tekan Enter.

**Verifikasi:** Buka [https://github.com/arvamadax/uap-asd](https://github.com/arvamadax/uap-asd) di browser. Kamu akan melihat notifikasi branch baru yang baru saja di-push.

---

## 10. Membuat Pull Request

Pull Request (PR) adalah cara untuk meminta kode kamu digabungkan ke branch `main`.

1. Buka [https://github.com/arvamadax/uap-asd](https://github.com/arvamadax/uap-asd)
2. Kamu akan melihat banner kuning bertuliskan **"Compare & pull request"** — klik tombol tersebut
3. Isi form Pull Request:
   - **Title:** Isi dengan deskripsi singkat, contoh: `feat: implementasi user_add.h - Harry`
   - **Description:** Jelaskan apa yang sudah kamu kerjakan, contoh:
     ```
     Modul 2 - user_add.h
     - Implementasi fungsi tambahUser()
     - Validasi range semua sensor
     - Validasi prefix User ID (4 kode wilayah)
     - Cek duplikat ID
     - Kalkulasi monitoring score otomatis
     ```
4. Pada bagian **Reviewers**, tambahkan Arva sebagai reviewer
5. Klik **"Create pull request"**

---

## 11. Merge ke Main

Setelah Pull Request dibuat, Arva (sebagai koordinator) akan mereview dan melakukan merge.

**Jika kamu adalah Arva dan ingin merge PR:**

1. Buka tab **"Pull requests"** di repo
2. Klik PR yang ingin di-merge
3. Scroll ke bawah, klik **"Merge pull request"**
4. Klik **"Confirm merge"**
5. Klik **"Delete branch"** untuk membersihkan branch yang sudah tidak dipakai

---

## 12. Update Local Setelah Merge

Setelah semua modul di-merge, pastikan kode lokal kamu sudah up-to-date:

```bash
git checkout main
git pull origin main
```

Sekarang kamu punya versi terbaru dari semua kode yang sudah digabungkan.

---

## 13. Rangkuman Perintah Penting

| Perintah | Fungsi |
|---|---|
| `git clone <url>` | Download repo ke komputer |
| `git status` | Cek perubahan yang belum di-commit |
| `git add <file>` | Tandai file untuk di-commit |
| `git add .` | Tandai semua perubahan |
| `git commit -m "pesan"` | Simpan snapshot perubahan |
| `git push origin <branch>` | Upload ke GitHub |
| `git checkout <branch>` | Pindah ke branch lain |
| `git checkout -b <branch>` | Buat branch baru sekaligus pindah |
| `git pull origin main` | Download update terbaru dari main |
| `git branch` | Lihat daftar branch |
| `git log --oneline` | Lihat riwayat commit |

---

## 14. Troubleshooting

### ❌ "Permission denied" saat push

Kamu perlu login ke GitHub. Jalankan:

```bash
git config --global credential.helper store
```

Lalu coba push lagi. Git akan meminta username dan password (gunakan Personal Access Token dari GitHub, bukan password biasa).

Cara buat Personal Access Token:
1. Buka GitHub → Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Klik **"Generate new token"**
3. Centang scope **"repo"**
4. Copy token yang dihasilkan — gunakan ini sebagai "password" saat diminta

### ❌ "Your branch is behind 'origin/main'"

Branch kamu tertinggal dari versi terbaru. Jalankan:

```bash
git pull origin main
```

### ❌ "Merge conflict"

Ini terjadi ketika dua orang mengubah baris yang sama di file yang sama. Cara paling mudah menghindarinya adalah dengan **hanya mengedit file milikmu sendiri**.

Jika terlanjur terjadi, hubungi Arva untuk diselesaikan bersama.

### ❌ Tidak bisa buka Git Bash

Pastikan Git sudah terinstal. Coba uninstall dan install ulang dari [https://git-scm.com](https://git-scm.com).

---

> Jika ada pertanyaan atau kendala yang tidak ada di sini, hubungi Arva atau tanyakan di grup.

**Selamat mengerjakan! 💪**
