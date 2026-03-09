# IF1210-Tubes-01

## Repository Note
This repository contains a migrated version of a previous group project developed for the IF1210 course.  
The original project was previously hosted under a different GitHub account.  
This repository is maintained under my current account for documentation, development, and portfolio purposes.

## Pembagian Tugas

| Nama | Modul | Deskripsi |
|-----|------|-----------|
| Riko | Denah | Implementasi struktur denah rumah sakit berbasis matriks, fitur LIHAT_DENAH, serta pengelolaan data ruangan |
| Riko & Fariz | Dokumentasi | Penyusunan README, dokumentasi command, dan penjelasan modul sistem |
| Emir | Auth | Implementasi fitur login dan logout |
| Fariz | Auth | Implementasi register dan reset password |
| Chia | User | Struktur data user dan inisialisasi akun default |
| Qaddy | View User | Sorting user dan pencarian menggunakan binary search |
| Rafi | Utils | Fungsi helper seperti case-sensitive check dan run length encoder |

# VERSI v2.0
```
username manager: zeru
password : pass77
```
### **Modularisasi Header dan Source File**
| Modul       | File Header (`.h`) | File Implementasi (`.c`) | Isi modul                                                  |
|-------------|--------------------|---------------------------|--------------------------------------------------------------|
| `main`      | -                  | `main.c`                  | command handler                                             |
| `auth`      | `auth.h`           | `auth.c`                  | login, logout, register_pasien, lupa_password               |
| `user`      | `user.h`           | `user.c`                  | ADT `User`, list user,beserta fungsi-fungsi yang berinteraksi dengannya                                  |
| `denah`     | `denah.h`          | `denah.c`                 | Denah matriks beserta fungsi-fungsi yang berinteraksi dengannya                                            |
| `utils`     | `utils.h`          | `utils.c`                 | Fungsi-Fungsi helper             |
| `pengobatan`     | `pengobatan.h`          | `pengobatan.c`                 | fitur ngobatin, minum obat, penawar, pulang dok              |
| `antrian`     | `antrian.h`          | `antrian.c`                 | antrian setiap ruangan beserta fungsi yang berkaitan|              |
| `map`     | `map.h`          | `map.c`                 | Fungsi untuk mapping relasi obat dan penyakit |
| `menu`     | `menu.h`          | `antrmenuian.c`                 | Tampilan menu & help              |
| `config`     | `config.h`          | `config.c`                 | Fungsi yang meload config.txt secara manual             |

---

# Panduan Pemakaian Command - Sistem Manajemen Rumah Sakit Nimons
Berikut adalah panduan untuk menggunakan program **Sistem Manajemen Rumah Sakit Nimons**. Semua perintah yang tersedia di program ini dijelaskan di bawah ini. 

---

## **Daftar Command yang Tersedia**
### 1. **LOGIN**
- **Command**: **`LOGIN`**
- **Deskripsi**: Untuk melakukan login ke dalam sistem dengan memasukkan **username** dan **password**.
- **Contoh Penggunaan**:
  ```
  Masukkan Username: admin
  Masukkan Password: password123
  ```
- **Contoh Output**:
  ```
  Selamat pagi Manager nimonsslatte!
  ```

### 2. **REGISTER**
- **Command**: **`REGISTER`**
- **Deskripsi**: Untuk mendaftar pengguna baru dengan memasukkan **username** dan **password**.
- **Contoh Penggunaan**:
  ```
  Username: Denis
  Password: aditgimananihdit
  ```
- **Contoh Output**:
  ```
  Pasien Denis berhasil ditambahkan!
  ```

### 3. **LOGOUT**
- **Command**: **`LOGOUT`**
- **Deskripsi**: Untuk keluar dari sistem dan mengakhiri sesi pengguna.
- **Contoh Penggunaan**:
  ```
  Command: LOGOUT
  ```
- **Contoh Output**:
  ```
  Keluar dari akun
  Sampai jumpa!
  ```

### 4. **LIHAT_USER**
- **Command**: **`LIHAT_USER`**
- **Deskripsi**: Menampilkan daftar pengguna yang terdaftar dalam sistem.
- **Contoh Penggunaan**:
  ```
  Command: LIHAT_USER
  ```
- **Contoh Output**:
  ```
  Urutkan berdasarkan?
  1. ID
  2. Nama
  Pilihan: 1
  Urutan sort?
  1. ASC (A-Z)
  2. DESC (Z-A)
  Pilihan: 1
  Menampilkan semua pengguna dengan ID terurut ascending...
  ID | Nama     | Role     | Penyakit
  -------------------------------------
  1  | Jeffrey  | Dokter   | -
  2  | Erik     | Pasien   | Maag
  3  | Neroifa  | Dokter   | -
  4  | Daev     | Pasien   | Flu
  5  | Remon    | Pasien   | Maag
  6  | Alpin    | Dokter   | -
  ```

### 5. **CARI_USER**
- **Command**: **`CARI_USER`**
- **Deskripsi**: Mencari pengguna berdasarkan **username**.
- **Contoh Penggunaan**:
  ```
  Command: CARI_USER
  Username: admin
  ```
- **Contoh Output**:
  ```
  Pengguna ditemukan:
  Username: admin
  Role: Manager
  ```

### 6. **LUPA_PASS**
- **Command**: **`LUPA_PASS`**
- **Deskripsi**: Fitur untuk mereset password pengguna jika lupa.
- **Contoh Penggunaan**:
  ```
  Command: LUPA_PASS
  Username: Jeffreey
  Kode Unik: Je2fr2ey
  ```
- **Contoh Output**:
  ```
  Halo Dokter Jeffreey, silakan daftarkan ulang password anda!
  Password Baru: JR1234
  ```

### 7. **HELP**
- **Command**: **`HELP`**
- **Deskripsi**: Menampilkan daftar perintah yang tersedia di program.
- **Contoh Penggunaan**:
  ```
  Command: HELP
  ```
- **Contoh Output**:
  ```
  ========== HELP =========
  Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.

  1. LOGIN: Masuk ke dalam akun yang sudah terdaftar
  2. REGISTER: Membuat akun baru
  3. LOGOUT: Keluar dari akun yang sedang digunakan
  4. LIHAT_USER: Lihat daftar pengguna
  5. CARI_USER: Cari pengguna berdasarkan username
  6. LUPA_PASS: Reset password
  7. LIHAT_DENAH: Lihat denah rumah sakit
  8. LIHAT_RUANGAN: Lihat daftar ruangan
  9. TAMBAH_DOKTER: Menambah dokter baru
  10. EXIT: Keluar dari sistem
  ```

### 8. **EXIT**
- **Command**: **`EXIT`**
- **Deskripsi**: Keluar dari sistem dan menutup program.
- **Contoh Penggunaan**:
  ```
  Command: EXIT
  ```
### 9. **LIHAT_DENAH**
- **Command**: **`LIHAT_DENAH`**
- **Deskripsi**: Menampilkan denah rumah sakit secara horizontal dengan ID ruangan.


### 10. **LIHAT_RUANGAN**
- **Command**: **`LIHAT_RUANGAN`**
- **Deskripsi**: Menampilkan detail sebuah ruangan, termasuk kapasitas, dokter, dan pasien yang ada.
- **Contoh Output**:
```
--- Detail Ruangan 1 ---
Kapasitas : 3
Dokter : Dr. Jeffrey
Pasien di dalam ruangan:
1. Erik
2. Remon
```
### 11. **TAMBAH_DOKTER**
- **Command**: **`TAMBAH_DOKTER`**
- **Deskripsi**: Menambah akun untuk dokter


### 12. **ASSIGN_DOKTER**
- **Command**: **`ASSIGN_DOKTER`**
- **Deskripsi**: Menugaskan dokter ke sebuah ruangan, jika dokter dan ruangan belum ditempati.
- **Contoh Penggunaan**:
- Username: Jeffrey
- Ruangan(0,1,2,3,4,5): 3
- **Contoh Output**:
```
Dokter Jeffrey berhasil diassign ke ruangan 3!
```
### 13. **DAFTAR_CHECKUP**
-   **Command**: **`DAFTAR_CHECKUP`**
-   **Deskripsi**: Memungkinkan pasien untuk mendaftarkan diri untuk pemeriksaan medis. Pasien diminta mengisi data kondisi tubuh (suhu, tekanan darah, dll.) dan memilih dokter yang tersedia untuk antrian.
-   **Contoh Penggunaan**:
    ```
    Command: DAFTAR_CHECKUP
    Suhu Tubuh (Celcius): 36.5
    Tekanan Darah (sistol/diastol, contoh 120 80): 120 80
    ... (dan data medis lainnya) ...
    Berikut adalah daftar dokter yang tersedia:
    ID: 10, Dr. Neronimo - Ruangan A1 (Antrian: 3 orang)
    ID: 11, Dr. Ciciko - Ruangan B1 (Antrian: 1 orang)
    Pilih dokter dengan id: 10
    ```
-   **Contoh Output**:
    ```
    Pendaftaran check-up untuk pasien Anda berhasil!
    Anda terdaftar pada antrian Dr. Neronimo di ruangan A1.
    Posisi antrian Anda: 4
    ```

### 14. **ANTRIAN**
-   **Command**: **`ANTRIAN`**
-   **Deskripsi**: Menampilkan status antrian terkini untuk pasien yang sedang terdaftar. Pasien dapat melihat dokter yang dituju, ruangan, dan posisi mereka dalam antrian.
-   **Contoh Penggunaan**:
    ```
    Command: ANTRIAN
    ```
-   **Contoh Output**:
    ```
    Status antrian Anda:
    Dokter: Dr. Neronimo
    Ruangan: A1
    Anda sedang menunggu di antrian.
    Posisi antrian Anda: 3 dari 5
    ```

### 15. **DIAGNOSIS**
-   **Command**: **`DIAGNOSIS`**
-   **Deskripsi**: Memungkinkan dokter untuk memeriksa data medis pasien yang berada di baris depan antrian mereka dan menentukan diagnosis penyakit berdasarkan kondisi tubuh pasien.
-   **Contoh Penggunaan**:
    ```
    Command: DIAGNOSIS
    ```
-   **Contoh Output**:
    ```
    Pasien Erik terdiagnosa penyakit Maag!
    ```

### 16. **NGOBATIN**
-   **Command**: **`NGOBATIN`**
-   **Deskripsi**: Setelah diagnosis, dokter memberikan obat yang sesuai kepada pasien. Obat akan ditambahkan ke inventory pasien berdasarkan relasi obat-penyakit yang telah ditentukan.
-   **Contoh Penggunaan**:
    ```
    Command: NGOBATIN
    ```
-   **Contoh Output**:
    ```
    Obat yang harus diberikan:
    1. Antacid
    2. Omeprazole
    ```

### 17. **MINUM_OBAT**
-   **Command**: **`MINUM_OBAT`**
-   **Deskripsi**: Pasien memilih dan meminum obat dari inventory mereka. Obat yang diminum akan dimasukkan ke "perut" pasien.
-   **Contoh Penggunaan**:
    ```
    Command: MINUM_OBAT
    ============ DAFTAR OBAT (INVENTORY) ============
    1. Antacid
    2. Omeprazole
    Pilih obat untuk diminum: 1
    ```
-   **Contoh Output**:
    ```
    GLEKGLEKGLEK... Antacid berhasil diminum!!!
    ```

### 18. **MINUM_PENAWAR**
-   **Command**: **`MINUM_PENAWAR`**
-   **Deskripsi**: Pasien dapat "memuntahkan" obat terakhir yang diminum dari perut mereka, mengembalikannya ke inventory.
-   **Contoh Penggunaan**:
    ```
    Command: MINUM_PENAWAR
    ```
-   **Contoh Output**:
    ```
    Uwekkk!!! Antacid keluar dan kembali ke inventory
    ```

### 19. **PULANGDOK**
-   **Command**: **`PULANGDOK`**
-   **Deskripsi**: Memungkinkan pasien untuk menanyakan apakah mereka sudah boleh pulang. Dokter akan memeriksa apakah pasien sudah menghabiskan semua obat yang diresepkan dengan urutan yang benar.
-   **Contoh Penggunaan**:
    ```
    Command: PULANGDOK
    ```
-   **Contoh Output (Jika belum boleh pulang)**:
    ```
    Dokter sedang memeriksa keadaanmu...
    Maaf, tapi kamu masih belum bisa pulang!
    Urutan obat yang diharapkan:
    Antacid -> Omeprazole
    Urutan obat yang kamu minum:
    Omeprazole -> Antacid
    Silahkan konsultasi lagi dengan dokter!
    ```
-   **Contoh Output (Jika sudah boleh pulang)**:
    ```
    Dokter sedang memeriksa keadaanmu...
    Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!
    ```

---
### **Catatan Implementasi**
- **Pengelolaan Username**: Sistem memastikan **username** unik dan tidak ada duplikasi. 
- **ADT Stack dan Queue**: Pengelolaan obat yang diminum (perut) menggunakan ADT Stack, dan antrian pasien di ruangan menggunakan ADT Queue (Linked List).
- **Relasi Obat-Penyakit**: Relasi antara penyakit dan obat yang diresepkan dikelola menggunakan struktur data Map/Hash Table.
- **Validasi Input**: Sebagian besar input pengguna telah dilengkapi dengan validasi untuk mencegah kesalahan dan *buffer overflow*.
---
