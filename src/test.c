#include <stdio.h>
#include <string.h>
#include "pengobatan.h"
#include "user.h"

int main() {
    // Menyiapkan database pasien dan data relasi
    UserDatabase db;
    create_user_database(&db);

    // Menambahkan pasien contoh
    User pasien1 = {1, "john_doe", "password", "Pasien", "Sehat", 37.0, 120, 80, 80, 98.5, 100, 70.0, 175, 150, 100000, {0}};
    User pasien2 = {2, "jane_doe", "password", "Pasien", "Sehat", 38.0, 130, 90, 85, 97.0, 100, 80.0, 160, 160, 200000, {0}};
    
    // Memasukkan pasien ke dalam database
    add_user(&db, pasien1);
    add_user(&db, pasien2);

    // Menyiapkan data penyakit dan obat
    Penyakit daftar_penyakit[MAX_PENYAKIT] = {
        {1, "Maag", 36.5, 38.0, 100, 130, 70, 90, 60, 100, 95.0, 100.0, 80, 150, 45.0, 100.0, 140, 190, 150000, 400000},
        {2, "Hipertensi", 36.0, 37.5, 140, 180, 90, 120, 60, 100, 95.0, 100.0, 80, 150, 45.0, 100.0, 140, 190, 150000, 400000}
    };

    Obat daftar_obat[MAX_OBAT] = {
        {1, "Paracetamol"},
        {2, "Oralit"},
        {3, "Aspirin"},
    };

    DataRelasi data;
    // Mengisi data relasi penyakit dengan obat (contoh)
    data.dataRelasi[0] = (ObatPenyakit){1, 1, 1}; // Paracetamol untuk Maag
    data.dataRelasi[1] = (ObatPenyakit){2, 1, 2}; // Oralit untuk Maag
    data.dataRelasi[2] = (ObatPenyakit){3, 1, 3}; // Aspirin untuk Maag

    // Kasus 1: Pasien belum didiagnosis
    printf(">>> PULANGDOK\n");
    boleh_pulang(&pasien1, data);

    // Kasus 2: Pasien belum menghabiskan obat
    // Diagnosis pasien
    pasien1.riwayatPenyakit[0] = '\0';  // Set ulang riwayat penyakit
    diagnosis(&pasien1);
    ngobatin(&pasien1, data, daftar_obat);
    printf("\n>>> PULANGDOK\n");
    boleh_pulang(&pasien1, data);

    // Kasus 3: Urutan peminuman obat salah
    // Simulasi peminum obat oleh pasien
    pasien1.perut.buffer[0] = daftar_obat[0];  // Paracetamol
    pasien1.perut.buffer[1] = daftar_obat[1];  // Oralit
    pasien1.perut.buffer[2] = daftar_obat[2];  // Aspirin
    pasien1.perut.buffer[3] = daftar_obat[0];  // Paracetamol (Salah urutan)
    pasien1.perut.top = 4;  // Mengatur top stack perut

    printf("\n>>> PULANGDOK\n");
    boleh_pulang(&pasien1, data);

    // Kasus 4: Semua obat sudah habis dan urutan benar
    // Simulasi peminum obat oleh pasien dengan urutan yang benar
    pasien1.perut.buffer[0] = daftar_obat[0];  // Paracetamol
    pasien1.perut.buffer[1] = daftar_obat[1];  // Oralit
    pasien1.perut.buffer[2] = daftar_obat[0];  // Paracetamol
    pasien1.perut.buffer[3] = daftar_obat[2];  // Aspirin
    pasien1.perut.top = 4;  // Mengatur top stack perut

    printf("\n>>> PULANGDOK\n");
    boleh_pulang(&pasien1, data);

    return 0;
}
