#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h" 

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_DISEASE  20
#define MAX_ROLE     20
#define CAPACITY     100  
#define IDX_UNDEF -1

struct Ruangan;
typedef struct Ruangan Ruangan;

typedef struct 
{
    int id_obat;
    char* nama_obat;
}Obat;

typedef struct {
    Obat buffer[5];
    int top;
}Perut;

typedef struct {
    //Default minimal dari spesifikasi
    int id;
    char username[MAX_USERNAME]; 
    char password[MAX_PASSWORD]; 
    char role[MAX_ROLE];        
    char riwayatPenyakit[MAX_DISEASE]; 
    float suhuTubuh;
    int tekananDarahSistolik;
    int tekananDarahDiastolik;
    int detakJantung;
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan;
    int tinggiBadan;
    int kadarKolesterol;
    int trombosit;

    /** @brief inventory array of id obat */
    Perut perut;
    Obat inventory[5];
    Ruangan* terdaftar;

    //Khusus Dokter
    Ruangan* ruangTugas;
    // int infoRuang[2];

} User;

typedef struct {
    User* listById;
    User** listByUsername;
    int    count;
    int    capacity; 
} UserDatabase;

// extern User defaultUsers[13];


/** @brief Membuat `UserDatabase` kosong.
 * @details Fungsi ini mengalokasikan memori untuk `listById` (array `User`) dan `listByUsername` (array pointer ke `User`),
 * serta menginisialisasi `count` menjadi 0 dan `capacity` menjadi `CAPACITY`.
 * Jika alokasi memori gagal, `listById` dan `listByUsername` akan diatur ke `NULL` dan `capacity` ke 0.
 * I.S.: `db` adalah pointer ke struktur `UserDatabase` yang belum terinisialisasi atau akan direset.
 * F.S.: `db` terinisialisasi sebagai database pengguna yang kosong dengan memori yang dialokasikan (jika berhasil).
 */
void create_user_database(UserDatabase *db);

/**
 * @brief Memuat pengguna-pengguna default ke dalam database.
 * @details Fungsi ini mengiterasi melalui array `defaultUsers` global dan menambahkan setiap pengguna ke `db`
 * menggunakan `add_user`, selama database belum penuh.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang sudah terinisialisasi.
 * F.S.: `db` berisi pengguna-pengguna default dari array `defaultUsers` (sebanyak `CAPACITY` atau jumlah default user, mana yang lebih kecil).
 */
void load_default_user(UserDatabase *db);

/** @brief Membebaskan memori yang dialokasikan untuk `UserDatabase`.
 * @details Fungsi ini membebaskan memori untuk `listByUsername` dan `listById`, serta mengatur `count` dan `capacity` ke 0.
 * I.S.: `list` adalah pointer ke `UserDatabase` yang sudah terinisialisasi dengan memori yang dialokasikan.
 * F.S.: Semua memori yang dialokasikan untuk `list` dibebaskan, dan `list` diatur ke kondisi kosong.
 */
void destroy_user_database(UserDatabase *list);

/** @brief Mengembalikan jumlah pengguna efektif dalam database.
 * @details Fungsi ini mengembalikan nilai dari atribut `count` dalam `UserDatabase`.
 * I.S.: `db` adalah `UserDatabase` yang valid.
 * F.S.: Mengembalikan jumlah elemen pengguna yang saat ini disimpan dalam `db`.
 */
int length_user_database(UserDatabase db);

// /** @brief Memeriksa apakah database pengguna kosong.
//  * @details Fungsi ini mengembalikan `true` jika `count` dalam `UserDatabase` adalah 0, `false` jika tidak.
//  * I.S.: `db` adalah `UserDatabase` yang valid.
//  * F.S.: Mengembalikan `true` jika `db` tidak mengandung pengguna, `false` sebaliknya.
//  */
// boolean is_empty_user_database(UserDatabase db);

/** @brief Memeriksa apakah database pengguna mencapai kapasitas penuh.
 * @details Fungsi ini mengembalikan `true` jika `count` sama dengan atau melebihi `capacity` dan `capacity` lebih dari 0.
 * I.S.: `db` adalah `UserDatabase` yang valid.
 * F.S.: Mengembalikan `true` jika `db` sudah penuh, `false` sebaliknya.
 */
boolean is_full_internal_list(UserDatabase db);

/* * @brief Mengurutkan `listById` berdasarkan ID pengguna menggunakan Bubble Sort.
 * @details Fungsi ini mengurutkan array `listById` berdasarkan atribut `id` secara ascending (menaik).
 * Proses pengurutan juga memastikan `listByUsername` tetap konsisten dengan menukar pointer.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid, dengan `listById` dan `listByUsername` mungkin tidak terurut berdasarkan ID.
 * F.S.: `db->listById` terurut berdasarkan `id` secara ascending.
 */
void sort_by_id(UserDatabase *db);

/* * @brief Mengurutkan `listByUsername` berdasarkan username pengguna menggunakan Bubble Sort.
 * @details Fungsi ini mengurutkan array `listByUsername` (array of pointers) berdasarkan atribut `username`
 * secara leksikografis (case-insensitive, diubah ke lowercase untuk perbandingan) secara ascending.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid, dengan `listByUsername` mungkin tidak terurut.
 * F.S.: `db->listByUsername` terurut berdasarkan `username` secara leksikografis ascending.
 */
void sort_by_username(UserDatabase *db);

/* * @brief Menambahkan pengguna baru ke database.
 * @details Fungsi ini menambahkan `newUser` ke `db->listById` dan membuat `db->listByUsername` menunjuk ke entri yang sama.
 * Setelah penambahan, `count` bertambah, dan kedua list (`listById`, `listByUsername`) diurutkan kembali.
 * Jika username sudah ada atau database penuh, penambahan gagal.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid. `newUser` adalah data `User` yang akan ditambahkan.
 * F.S.: Jika penambahan berhasil, `newUser` ditambahkan ke `db`, `db->count` bertambah, dan list diurutkan.
 * Mengembalikan `true` jika berhasil, `false` jika username duplikat atau database penuh.
 */
boolean add_user(UserDatabase *db, User newUser);

/* * @brief Menghapus pengguna pada indeks ke-i dari database.
 * @details Fungsi ini menghapus pengguna pada indeks `i` dari `db->listById` dan `db->listByUsername`,
 * menggeser elemen-elemen setelahnya ke depan. Setelah penghapusan, `count` berkurang, dan `listByUsername` diurutkan kembali.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid. `i` adalah indeks pengguna yang akan dihapus. `val` adalah pointer untuk menyimpan data pengguna yang dihapus (opsional).
 * F.S.: Pengguna pada indeks `i` dihapus dari `db`, `db->count` berkurang, dan `val` berisi data pengguna yang dihapus (jika `val` tidak `NULL`).
 */
void delete_user_at(UserDatabase *db, int i, User *val);

/** @brief Menampilkan daftar pengguna berdasarkan pilihan filter dan urutan.
 * @details Pengguna dapat memilih untuk melihat semua user, hanya pasien, atau hanya dokter.
 * Dapat diurutkan berdasarkan ID atau Username, serta urutan ascending atau descending.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid dan berisi data pengguna.
 * F.S.: Menampilkan daftar pengguna ke konsol sesuai dengan kriteria yang dipilih pengguna. Tidak ada perubahan pada data `db`.
 */
void lihat_user(UserDatabase *db);

/** @brief Mencari dan menampilkan detail pengguna berdasarkan ID atau Username.
 * @details Pengguna dapat memilih untuk mencari berdasarkan ID atau Username.
 * Jika ditemukan, detail pengguna akan ditampilkan. Jika tidak, pesan "tidak ditemukan" akan ditampilkan.
 * I.S.: `db` adalah pointer ke `UserDatabase` yang valid dan berisi data pengguna.
 * F.S.: Menampilkan detail pengguna yang dicari ke konsol (jika ditemukan). Tidak ada perubahan pada data `db`.
 */
void cari_user(UserDatabase *db);

#endif

