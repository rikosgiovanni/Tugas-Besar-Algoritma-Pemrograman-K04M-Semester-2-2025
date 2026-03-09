#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Boolean.h"
#include "user.h"
#include <time.h>
#include <stdarg.h>
#include "denah.h"
#define maxstr 50

//ANSI COLORS
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define CYAN        "\033[36m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define WHITE       "\033[37m"
#define GREY        "\033[90m"
#define RED         "\033[31m"

#define WIDTH       120


typedef int (*CompareFunc)(const void* a, const void* b);
/**
 * @brief Mengenkode sebuah string (username) menggunakan Run-Length Encoding.
 * Ini digunakan untuk menghasilkan kode verifikasi unik, misalnya pada fitur "Lupa Password".
 * Fungsi ini mengkompresi karakter berulang berturut-turut menjadi jumlah diikuti karakter itu sendiri.
 * Contoh: "AABBC" menjadi "2A2BC".
 * @param input Pointer ke string input yang akan dienkode.
 * @param output Pointer ke buffer string output tempat hasil enkoding akan disimpan.
 * @return void* Pointer ke string output yang telah dienkode.
 */
void *run_length_encoder(const char* input, char* output);

/**
 * @brief Mengubah sebuah string menjadi representasi huruf kecilnya.
 * Ini digunakan untuk memastikan perbandingan string tidak peka huruf besar/kecil (case-insensitive).
 * Fungsi ini akan mengonversi semua karakter huruf besar dalam string input menjadi huruf kecil yang sesuai.
 * @param input Pointer ke string input yang akan diubah ke huruf kecil.
 * @param output Pointer ke buffer string output tempat string huruf kecil akan disimpan.
 * @return void* Pointer ke string output yang telah diubah ke huruf kecil.
 */
void *to_lower(const char* input, char* output);

/**
 * @brief Membandingkan dua string tanpa membedakan huruf besar/kecil (case-insensitive).
 * Fungsi ini menggunakan `to_lower` secara internal untuk mengonversi kedua string sementara sebelum membandingkannya.
 * @param str1 Pointer ke string pertama.
 * @param str2 Pointer ke string kedua.
 * @return boolean Mengembalikan TRUE jika kedua string sama (mengabaikan kapitalisasi), FALSE jika berbeda.
 */
boolean cmp_insensitive(const char* str1, const char* str2);

/**
 * @brief Membandingkan dua username untuk pencarian yang peka huruf besar/kecil (case-sensitive).
 * Ini digunakan dalam konteks fitur seperti Login (untuk membandingkan password) atau verifikasi RLE,
 * di mana perbedaan kapitalisasi penting.
 * @param a Pointer generik (void*) yang menunjuk ke kunci pencarian (char*).
 * @param b Pointer generik (void*) yang menunjuk ke elemen User yang akan dibandingkan (User**).
 * @return int Mengembalikan 0 jika sama, nilai negatif jika 'a' kurang dari 'b', atau nilai positif jika 'a' lebih dari 'b'.
 */
int compare_username_sensitive(const void* a, const void* b);

/**
 * @brief Membandingkan kunci (string username) dengan username User untuk pencarian biner (tidak peka huruf besar/kecil).
 * Fungsi ini mengonversi kedua username ke huruf kecil sebelum membandingkannya, memungkinkan pencarian yang fleksibel.
 * @param a Pointer generik (void*) yang menunjuk ke kunci pencarian (char*).
 * @param b Pointer generik (void*) yang menunjuk ke elemen User yang akan dibandingkan (User**).
 * @return int Mengembalikan 0 jika sama, nilai negatif jika 'a' kurang dari 'b', atau nilai positif jika 'a' lebih dari 'b'.
 */
int compare_username(const void* a, const void* b);

/**
 * @brief Membandingkan kunci (integer ID) dengan ID User untuk pencarian biner.
 * Ini digunakan dalam pencarian biner di UserDatabase berdasarkan ID unik pengguna.
 * @param a Pointer generik (void*) yang menunjuk ke kunci pencarian (int*).
 * @param b Pointer generik (void*) yang menunjuk ke elemen User yang akan dibandingkan (User*).
 * @return int Mengembalikan 0 jika sama, nilai negatif jika 'a' kurang dari 'b', atau nilai positif jika 'a' lebih dari 'b'.
 */
int compare_id(const void* a, const void* b);

/**
 * @brief Melakukan pencarian biner yang efisien pada UserDatabase.
 * Fungsi ini dapat mencari berdasarkan ID atau username tergantung pada fungsi perbandingan yang diberikan.
 * @param db Struktur data UserDatabase yang akan dicari.
 * @param low Batas bawah indeks pencarian.
 * @param high Batas atas indeks pencarian.
 * @param key Pointer generik (void*) ke nilai yang dicari.
 * @param compare Pointer ke fungsi perbandingan (CompareFunc) yang sesuai dengan tipe data kunci dan elemen database.
 * @return int Mengembalikan indeks elemen yang ditemukan, atau IDX_UNDEF jika tidak ditemukan.
 */
int binary_search(UserDatabase db, int low, int high, void* key, CompareFunc compare);

/**
 * @brief Melakukan pencarian sekuensial untuk username di UserDatabase.
 * Fungsi ini memindai setiap elemen dalam database secara berurutan hingga menemukan username yang cocok.
 * @param db Struktur data UserDatabase yang akan dicari.
 * @param username String username yang dicari.
 * @return int Mengembalikan indeks elemen yang ditemukan, atau IDX_UNDEF jika tidak ditemukan.
 */
int sequential_search(UserDatabase db, const char* username);

/**
 * @brief Membandingkan dua string dengan membedakan huruf besar/kecil (case-sensitive).
 * @param str1 Pointer ke string pertama.
 * @param str2 Pointer ke string kedua.
 * @return boolean Mengembalikan TRUE jika kedua string sama persis, FALSE jika berbeda.
 */
boolean cmp_sensitive(const char* str1, const char* str2);

/**
 * @brief Mencetak pesan selamat datang yang dipersonalisasi untuk pengguna saat ini.
 * Pesan disesuaikan berdasarkan peran pengguna (manajer, dokter, pasien).
 * @param current Objek User yang sedang login.
 */
void print_welcome(User current);

/**
 * @brief Menghentikan eksekusi program sementara dan menunggu input pengguna.
 * Pengguna diminta untuk menekan Enter (atau input apapun lalu Enter) untuk melanjutkan ke menu.
 */
void back_to_menu();

/**
 * @brief Membersihkan layar konsol.
 * Fungsi ini menggunakan perintah sistem yang spesifik OS (`cls` untuk Windows, `clear` untuk Unix/Linux).
 */
void clear_screen();

/**
 * @brief Menghentikan eksekusi program untuk jangka waktu tertentu.
 * Digunakan untuk jeda visual atau menunggu sebelum melanjutkan operasi.
 * @param seconds Durasi jeda dalam detik.
 */
void wait(int seconds);

/**
 * @brief Mencetak banner antarmuka yang diformat dengan judul bagian dan informasi pengguna saat ini.
 * Banner ini menyediakan visualisasi yang konsisten di seluruh aplikasi, menampilkan status login.
 * @param sectionTitle String judul untuk bagian antarmuka saat ini.
 * @param currentUser Pointer ke objek User yang sedang login; bisa NULL jika belum login.
 */
void print_interface(const char* sectionTitle, const User* currentUser);

/**
 * @brief Menghitung panjang string yang terlihat di konsol, mengabaikan kode warna ANSI.
 * Berguna untuk perhitungan padding dan tata letak UI yang akurat ketika string mengandung kode escape ANSI.
 * @param str Pointer ke string yang akan dihitung panjangnya.
 * @return int Panjang string yang terlihat (tanpa kode warna).
 */
int visible_length(const char* str);

/**
 * @brief Mencetak pesan yang diberi padding dan berbingkai di dalam antarmuka UI.
 * Pesan akan dipusatkan (centered) atau diberi padding agar sesuai dengan lebar antarmuka yang ditentukan (WIDTH).
 * @param text Format string pesan yang akan dicetak, dapat menyertakan specifier seperti printf.
 * @param ... Argumen variabel yang sesuai dengan format string.
 */
void print_padded(const char* text, ...);

/**
 * @brief Mencetak prompt yang diformat untuk input pengguna.
 * Prompt ini konsisten dengan gaya UI keseluruhan, memberikan indikator input yang jelas.
 * @param text Format string prompt yang akan dicetak, dapat menyertakan specifier seperti printf.
 * @param ... Argumen variabel yang sesuai dengan format string.
 */
void print_prompt(const char* text, ...);

/**
 * @brief Membersihkan karakter sisa di buffer input standar hingga karakter newline (`\n`) atau akhir file (EOF).
 * Ini mencegah masalah di mana `scanf` membaca sisa karakter dari input sebelumnya, yang dapat menyebabkan loop tak terbatas atau input dilewati.
 */
void clear_input_buffer();

#endif