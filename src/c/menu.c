#include <stdio.h>
#include "auth.h" // untuk struct User
#include "menu.h"
#include "utils.h"


void printmenu(){
    // print_padded("\n");
    print_padded("Selamat datang di rumah sakit Nimons,butuh apa anda hari ini?");
    print_padded("HELP: Daftar command yang tersedia");
    print_padded("Bila ingin menjalankan suatu command, harap input commandnya,bukan angkanya! (HELP, bukan 3)");
}

void help(User* currentSession) {

    if (currentSession == NULL) {
        print_padded("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.");
        print_padded("");
        print_padded("   1. LOGIN: Masuk ke dalam akun yang sudah terdaftar");
        print_padded("   2. REGISTER: Membuat akun baru");
        
    } else if (strcmp(currentSession->role, "dokter") == 0) {
        print_padded("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:", currentSession->username);
        print_padded("");
        print_padded("   1. LOGOUT: Keluar dari akun yang sedang digunakan");
        print_padded("   2. LUPA_PASSWORD: Update password apabila password yang didaftarkan");
        print_padded("   3. LIHAT_DENAH: Melihat denah ruangan di rumah sakit");
        print_padded("   4. LIHAT_RUANGAN X: Melihat detail informasi ruangan (X menyatakan nomor ruangan)");
        print_padded("   5. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien");
        print_padded("   6. NGOBATIN: Memberi obat kepada pasien secara terurut");
        print_padded("   7. EXIT: Melakukan dekonstruksi rumah sakit");

    } else if (strcmp(currentSession->role, "pasien") == 0) {
        print_padded("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:", currentSession->username);
        print_padded("");
        print_padded("   1. LOGOUT: Keluar dari akun yang sedang digunakan");
        print_padded("   2. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter");
        print_padded("   3. LUPA_PASSWORD: Update password apabila password yang didaftarkan");
        print_padded("   4. LIHAT_DENAH: Melihat denah ruangan di rumah sakit");
        print_padded("   6. LIHAT_RUANGAN: Melihat detail informasi ruangan (X menyatakan nomor ruangan)");
        print_padded("   7. PULANGDOK: Aku boleh pulang ga, dok?");
        print_padded("   8. DAFTAR_CHECKUP: Mendaftar untuk melakukan check-up dengan dokter");
        print_padded("   9. ANTRIAN: Melihat status antrian setelah melakukan pendaftaran");
        print_padded("   10. MINUM_OBAT: Mengambil obat dari inventory dan memasukkannya ke dalam perut");
        print_padded("   11. PENAWAR: Mengeluarkan obat terakhir yang diminum dari perut dan mengembalikannya ke dalam inventory obat");
        print_padded("   12. EXIT: Melakukan dekonstruksi rumah sakit");

    } else if (strcmp(currentSession->role, "manager") == 0) {
        print_padded("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:", currentSession->username);
        print_padded("");
        print_padded("   1. LOGOUT: Keluar dari akun yang sedang digunakan");
        print_padded("   2. LUPA_PASSWORD: Update password apabila password yang didaftarkan");
        print_padded("   3. LIHAT_DENAH: Melihat denah ruangan di rumah sakit");
        print_padded("   4. LIHAT_RUANGAN X: Melihat detail informasi ruangan (X menyatakan nomor ruangan)");
        print_padded("   5. LIHAT_USER: Melihat seluruh data pengguna");
        print_padded("   6. CARI_USER/PASIEN/DOKTER: Mencari data pengguna/pasien/dokter secara spesifik");
        print_padded("   7. CARI_PASIEN: Mencari data pengguna secara spesifik");
        print_padded("   8. LIHAT_SEMUA_ANTRIAN: Melihat rincian di seluruh ruangan saat ini");
        print_padded("   9. TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem");
         print_padded("   10. ASSIGN_DOKTER: Menempatkan dokter di ruangan yang dipilih");
        print_padded("   11. EXIT: Melakukan dekonstruksi rumah sakit");

    }

    print_padded("");
    print_padded("Footnote:");
    print_padded("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar");
    print_padded("2. Jangan lupa untuk memasukkan input yang valid");
}
