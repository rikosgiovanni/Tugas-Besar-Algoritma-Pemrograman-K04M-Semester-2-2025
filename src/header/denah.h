#ifndef DENAH_H
#define DENAH_H

#include "user.h"
#include "Boolean.h"

typedef struct Antrian* Address;
typedef struct Antrian {
    User* pasien;
    Address next;
} Antrian;

struct Ruangan{
    int id;
    char roomId[10];
    int kapasitas;
    User* dokter;
    int jumlahPasien;
    User* pasien[20]; // pasien dalam ruangan
    Address antri;
};

typedef struct Ruangan Ruangan;
typedef struct {
    Ruangan ruang[10][10];
    int kolom;
    int baris;
    int jumlah;
}Denah;

/**
 * @brief Mengonversi karakter huruf (misalnya 'A', 'B') menjadi indeks numerik (0, 1) yang sesuai.
 * Fungsi ini sangat penting untuk memetakan input pengguna berbasis karakter ke indeks array
 * matriks denah rumah sakit, di mana 'A' biasanya mewakili baris pertama (indeks 0), 'B' baris kedua (indeks 1), dst.
 * @param x Karakter huruf yang akan dikonversi.
 * @return int Nilai integer yang merepresentasikan indeks baris.
 */
int char_to_num(char x);

/**
 * @brief Menginisialisasi struktur data Denah rumah sakit dengan ukuran baris dan kolom yang ditentukan.
 * Fungsi ini membuat matriks ruangan, menetapkan ID unik untuk setiap ruangan,
 * menginisialisasi nama ruangan dalam format string (misalnya "A1", "B2"),
 * mengatur kapasitas ruangan, dan memastikan setiap ruangan awalnya kosong (tidak ada dokter atau pasien).
 * @param l Pointer ke struktur Denah yang akan diinisialisasi.
 * @param x Jumlah baris untuk denah rumah sakit.
 * @param y Jumlah kolom untuk denah rumah sakit.
 * @param z Kapasitas pasien default untuk setiap ruangan.
 */
void create_denah(Denah *l, int x, int y, int z);

/**
 * @brief Memeriksa apakah koordinat ruangan yang diberikan (indeks kolom dan baris) valid dalam denah.
 * Fungsi ini memastikan bahwa upaya akses ruangan tidak akan menyebabkan kesalahan di luar batas array (out-of-bounds access).
 * @param d Struktur Denah rumah sakit yang akan diperiksa batasnya.
 * @param x Indeks kolom ruangan yang akan diperiksa (0-indexed).
 * @param y Indeks baris ruangan yang akan diperiksa (0-indexed).
 * @return boolean Mengembalikan TRUE jika koordinat ruangan valid dan berada dalam batas denah, FALSE jika tidak.
 */
boolean search_room(Denah d,int x, int y);

/**
 * @brief Menampilkan representasi visual dari denah rumah sakit.
 * Fungsi ini mencetak tata letak grid ruangan, menunjukkan ID ruangan (misalnya "A1", "B2")
 * di setiap sel, memberikan gambaran umum tentang struktur rumah sakit.
 * @param l Struktur Denah rumah sakit yang akan ditampilkan.
 */
void lihat_denah(Denah l);

/**
 * @brief Menampilkan informasi detail tentang ruangan tertentu yang dipilih pengguna.
 * Pengguna diminta untuk memasukkan ID ruangan (misalnya "A1").
 * Fungsi ini kemudian menampilkan kapasitas ruangan, dokter yang ditugaskan (jika ada),
 * dan daftar pasien yang saat ini berada di dalam ruangan tersebut.
 * @param l Struktur Denah rumah sakit.
 * @param userDatabase Pointer ke UserDatabase yang berisi data semua pengguna (untuk menampilkan nama dokter/pasien).
 */
void lihat_ruangan(Denah l, UserDatabase *userDatabase);

/**
 * @brief Fungsi pembantu untuk mencetak detail informasi dari satu objek Ruangan.
 * Ini digunakan oleh fungsi lain (misalnya `lihat_ruangan` atau `lihat_antrian`)
 * untuk menampilkan informasi terstruktur tentang ruangan, termasuk dokter, pasien di dalam, dan antrian.
 * @param currRoom Pointer ke objek Ruangan yang akan dicetak detailnya.
 * @param userDatabase Pointer ke UserDatabase untuk mencari detail pengguna (dokter/pasien) berdasarkan ID.
 */
void print_ruangan(Ruangan *currRoom, const UserDatabase *userDatabase);

/**
 * @brief Menetapkan seorang dokter ke ruangan tertentu dan membuat hubungan dua arah.
 * Fungsi ini mengatur pointer dokter di ruangan ke objek User dokter yang sesuai,
 * dan juga mengatur pointer ruangTugas di objek User dokter ke ruangan ini.
 * @param db Pointer ke UserDatabase.
 * @param r Pointer ke objek Ruangan tempat dokter akan ditugaskan.
 * @param dokter Pointer ke objek User dokter yang akan ditugaskan.
 */
void set_dokter(UserDatabase *db, Ruangan *r, User *dokter);

/**
 * @brief Menangani proses penugasan dokter ke ruangan di rumah sakit.
 * Pengguna diminta untuk memasukkan username dokter dan ID ruangan.
 * Fungsi ini memvalidasi keberadaan dokter dan ruangan, serta memeriksa apakah ruangan sudah ditempati
 * atau jika dokter sudah ditugaskan ke ruangan lain. Setelah validasi, dokter akan ditugaskan ke ruangan yang dipilih.
 * @param denah Pointer ke struktur Denah rumah sakit.
 * @param db Pointer ke UserDatabase yang berisi data semua pengguna.
 */
void assign_dokter(Denah *denah, UserDatabase *db);
#endif