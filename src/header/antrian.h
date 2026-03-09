#ifndef ANTRIAN_H
#define ANTRIAN_H
#include "user.h"
#include "denah.h"
#include "utils.h"

/**
 * @brief Menambahkan pasien ke akhir antrian ruangan.
 * @param ruang Pointer ke Ruangan tempat pasien akan ditambahkan.
 * @param pasien Pointer ke User (pasien) yang akan ditambahkan.
 * @I.S. "ruang" dan "pasien" terdefinisi. Antrian di "ruang" bisa kosong atau sudah berisi.
 * @F.S. "pasien" ditambahkan sebagai node terakhir dalam linked list antrian "ruang". Jumlah pasien di "ruang" bertambah satu.
 */
void enqueue_pasien(Ruangan *ruang, User *pasien);

/** @brief untuk daftar checkup
 * Alur:
 * -Pasien memasukkan semua data
 * -Pasien ditampilkan data dokter yang sudah ada di ruangan (looping listByUsername role dokter, cari yang infoRuang != IDX_UNDEF)
 * -Data dokter ditampilkan, dengan ruangan dan inforuangannya (buat pointer atau bisa langsung call array ruangan, buat lihat antrian)
 * -struktur infoRuang int array, index 1 buat baris (A,B,C), index 0 buat kolom (1,2,3). ,Index dari 0 tapi ruangan dari 1, huruf dari 0
 * -Pilih dokter
 * -Kalau berhasil, set pointer ruangan pasien (terdaftar) ke ruangan yang dipilih (denah.ruang[123][ABC]) ABC pakai fungsi char_to_num atau manual
 * lalu masukkan ke ruangna (kalau antrian = NULL/kosong) atau ke linked list antrian
 * @param pasien Pointer ke User (pasien) yang mendaftar.
 * @param denah Pointer ke Denah rumah sakit.
 * @param database Pointer ke UserDatabase.
 * @I.S. "pasien", "denah", dan "database" terdefinisi. Pasien mungkin sudah terdaftar atau belum.
 * @F.S. Jika pasien belum terdaftar, data check-up pasien diinput, pasien memilih dokter, dan ditambahkan ke antrian dokter yang dipilih. Pointer "terdaftar" pada "pasien" menunjuk ke ruangan yang dipilih. Jika sudah terdaftar, tampilkan pesan.
 */
void daftar_checkup(User *pasien, Denah *denah, UserDatabase *database);

/**
 * @brief Menampilkan status antrian pasien saat ini.
 * @param pasien Objek User yang status antriannya ingin dilihat.
 * @param database UserDatabase untuk mencari data jika diperlukan (meski implementasi saat ini tidak terlalu memakainya).
 * @I.S. "pasien" terdefinisi. Pasien mungkin terdaftar dalam antrian atau tidak.
 * @F.S. Jika pasien terdaftar, menampilkan nama dokter, ruangan, dan posisi antrian pasien. Jika tidak, menampilkan pesan bahwa pasien belum terdaftar.
 */
void antrian_saya(User pasien, UserDatabase database);

/** @brief Menampilkan denah dan detail antrian untuk setiap ruangan yang memiliki dokter atau pasien. Looping semua matriks denah dan tampilkan data pasien di ruangan, linked list antrian, dan dokter
 * @param denah Objek Denah rumah sakit.
 * @param database UserDatabase untuk mencari data jika diperlukan.
 * @I.S. "denah" dan "database" terdefinisi. Ruangan bisa kosong atau berisi dokter dan/atau pasien.
 * @F.S. Menampilkan denah rumah sakit, diikuti dengan detail setiap ruangan yang tidak kosong (Dokter, pasien di dalam, dan antrian pasien).
 */
void lihat_antrian(Denah denah, UserDatabase database);

#endif
