// auth.h
#ifndef AUTH_H
#define AUTH_H

#include "user.h" // Gunakan User & UserList dari sini

/** @brief Pengecekan string, bilang string mengandung char selain alphabet, return false */
boolean is_alpha_only(const char *str);


/**
 * @brief Menangani proses login pengguna ke dalam sistem.
 * Pengguna diminta untuk memasukkan username dan password.
 * Jika sudah ada sesi login aktif, fungsi akan menampilkan pesan peringatan.
 * Fungsi ini melakukan pencarian biner username di database pengguna.
 * Jika username tidak ditemukan, pengguna diberi opsi untuk mencoba lagi.
 * Setelah username valid ditemukan, password dimasukkan dan dibandingkan secara peka huruf besar/kecil.
 * Jika password cocok, sesi pengguna saat ini akan diatur.
 * Fungsi ini dilengkapi dengan validasi input untuk mencegah buffer overflow pada username dan password.
 * @param db Pointer ke struktur data UserDatabase yang berisi data semua pengguna.
 */
void login(UserDatabase *db);

/**
 * @brief Menangani proses logout pengguna dari sistem.
 * Jika ada sesi login aktif, sesi saat ini akan dihentikan dan pengguna akan dikeluarkan.
 * Jika tidak ada sesi login yang aktif, fungsi akan menampilkan pesan bahwa logout tidak berhasil.
 */
void logout();

/**
 * @brief Mengembalikan pointer ke objek User yang sedang login di sesi saat ini.
 * Jika tidak ada pengguna yang login, fungsi ini akan mengembalikan NULL.
 * @return User* Pointer ke objek User yang sedang login, atau NULL jika tidak ada.
 */
User* getCurrentUser();

/**
 * @brief Memungkinkan pasien baru untuk mendaftar akun di sistem.
 * Fungsi ini meminta username dan password baru dari pengguna.
 * Melakukan validasi duplikasi username dan konfirmasi password.
 * Setelah validasi, pengguna baru dengan peran "pasien" akan ditambahkan ke UserDatabase.
 * Data medis pasien diinisialisasi ke nilai default.
 * Fungsi ini dilengkapi dengan validasi input untuk mencegah buffer overflow pada username dan password.
 * @param db Pointer ke struktur data UserDatabase tempat pengguna baru akan ditambahkan.
 * @param maxID Pointer ke integer yang menyimpan ID pengguna terakhir yang digunakan untuk menginisialisasi ID pengguna baru.
 */
void register_pasien(UserDatabase *db, int *maxID);

/**
 * @brief Memungkinkan pengguna untuk mengatur ulang password mereka jika lupa.
 * Pengguna diminta untuk memasukkan username terdaftar.
 * Setelah username ditemukan, sistem akan menghasilkan kode RLE (Run-Length Encoding) dari username tersebut.
 * Pengguna harus memasukkan kembali kode RLE untuk verifikasi.
 * Jika kode RLE cocok, pengguna dapat memasukkan dan mengonfirmasi password baru.
 * Password pengguna yang bersangkutan di database akan diperbarui.
 * Fungsi ini dilengkapi dengan validasi input untuk mencegah buffer overflow pada username, kode RLE, dan password.
 * @param db Pointer ke struktur data UserDatabase tempat data pengguna akan dicari dan diperbarui.
 */
void lupa_password(UserDatabase *db);

/**
 * @brief Memungkinkan manajer untuk menambahkan dokter baru ke sistem.
 * Fungsi ini meminta username dan password baru untuk dokter.
 * Melakukan validasi duplikasi username dan konfirmasi password.
 * Setelah validasi, pengguna baru dengan peran "dokter" akan ditambahkan ke UserDatabase.
 * Data medis dokter diinisialisasi ke nilai default atau nol, dan ruangan tugas diatur ke NULL.
 * Fungsi ini dilengkapi dengan validasi input untuk mencegah buffer overflow pada username dan password.
 * @param db Pointer ke struktur data UserDatabase tempat dokter baru akan ditambahkan.
 * @param maxID Pointer ke integer yang menyimpan ID pengguna terakhir yang digunakan untuk menginisialisasi ID dokter baru.
 */
void tambah_dokter(UserDatabase *db, int *maxID);

#endif
