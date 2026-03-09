#include "antrian.h"

void enqueue_pasien(Ruangan *ruang, User *pasien) {
    Address newAntrianNode = (Address)malloc(sizeof(Antrian));
    newAntrianNode->pasien = pasien; 
    newAntrianNode->next = NULL; 

    if (ruang->antri == NULL) {
        ruang->antri = newAntrianNode;
    } else {
        Address temp = ruang->antri;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAntrianNode; 
    }
    
    pasien->terdaftar = ruang;
    ruang->jumlahPasien++;
}

void daftar_checkup(User *pasien, Denah *denah, UserDatabase *database) {
    if (pasien->terdaftar != NULL) {
        print_padded("Anda sudah terdaftar dalam antrian check-up!");
        print_padded("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.");
        return;
    }
    print_padded("Silakan masukkan data check-up Anda:");
    print_prompt("Suhu Tubuh (Celcius): ");
    while (scanf("%f", &pasien->suhuTubuh)!= 1 || pasien->suhuTubuh <= 0) {
        clear_input_buffer();
        print_padded("Suhu tubuh harus berupa angka positif!");
        print_prompt("Suhu Tubuh (Celcius): ");
    }
    clear_input_buffer();

    print_prompt("Tekanan Darah (sistol/diastol, contoh 120 80): ");
    while (scanf("%d %d", &pasien->tekananDarahSistolik, &pasien->tekananDarahDiastolik) != 2 || pasien->tekananDarahSistolik <= 0 || pasien->tekananDarahDiastolik <= 0) {
        clear_input_buffer();
        print_padded("Tekanan darah harus berupa angka positif!");
        print_prompt("Tekanan Darah (sistol/diastol, contoh 120 80): ");

    }
    clear_input_buffer();

    print_prompt("Detak Jantung (bpm): ");
    while (scanf("%d", &pasien->detakJantung) != 1 || pasien->detakJantung <= 0) {
        clear_input_buffer();
         print_padded("Detak jantung harus berupa angka positif!");
         print_prompt("Detak Jantung (bpm): ");
    }
    clear_input_buffer();

    print_prompt("Saturasi Oksigen (persentase): ");
    
     while (scanf("%f", &pasien->saturasiOksigen)!=1|| pasien->saturasiOksigen <= 0 || pasien->saturasiOksigen > 100) {
        clear_input_buffer();
         print_padded("Saturasi oksigen harus antara 0-100!");
         print_prompt("Saturasi Oksigen (persentase): ");
    }
    clear_input_buffer();

    print_prompt("Kadar Gula Darah (mg/dL): ");
    while (scanf("%d", &pasien->kadarGulaDarah)!=1|| pasien->kadarGulaDarah <= 0) {
        clear_input_buffer();
         print_padded("Kadar gula darah harus berupa angka positif!");
         print_prompt("Kadar Gula Darah (mg/dL):");
    }
    clear_input_buffer();

    print_prompt("Berat Badan (kg): ");
    while (scanf("%f", &pasien->beratBadan)!= 1|| pasien->beratBadan <= 0) {
        clear_input_buffer();
         print_padded("Berat badan harus berupa angka positif!");
         print_prompt("Berat Badan (kg): ");
         
        
    }
    clear_input_buffer();

    print_prompt("Tinggi Badan (cm): ");
    while (scanf("%d", &pasien->tinggiBadan)!= 1 || pasien->tinggiBadan <= 0) {
        clear_input_buffer();
         print_padded("Tinggi badan harus berupa angka positif!");
         print_prompt("Tinggi Badan (cm): ");
    }
    clear_input_buffer();

    print_prompt("Kadar Kolestrol (mg/dL): ");
    while (scanf("%d", &pasien->kadarKolesterol)!= 1||pasien->kadarKolesterol <= 0) {
        clear_input_buffer();
         print_padded("Kadar kolestrol harus berupa angka positif!");
         print_prompt("Kadar Kolestrol (mg/dL): ");
    }
    clear_input_buffer();

    print_prompt("Trombosit (ribu/uL): ");
    while (scanf("%d", &pasien->trombosit) != 1 || pasien->trombosit <= 0) {
        clear_input_buffer();
         print_padded("Trombosit harus berupa angka positif!");
         print_prompt("Trombosit (ribu/uL): ");
         
    }
    clear_input_buffer();
    
    print_padded("Berikut adalah daftar dokter yang tersedia:");
    for (int i = 0; i < denah->kolom; i++) {
        for (int j = 0; j <= denah->baris; j++) {
            Ruangan *ruangan = &denah->ruang[i][j];
            // print_padded("%s", ruangan->roomId);
            if (ruangan->dokter != NULL) {
                int antrian = ruangan->jumlahPasien - ruangan->kapasitas;
                if(antrian < 0) antrian = 0;
                print_padded("ID: %d, Dr. %s - Ruangan %s (Antrian: %d orang)", ruangan->dokter->id , ruangan->dokter->username,ruangan->roomId, antrian);
            }
        }
    }
    print_prompt("Pilih dokter dengan id: ");
    int pilihan;
    scanf("%d", &pilihan);
    int idxDokter = binary_search(*database, 0, database->count - 1, &pilihan, compare_id);
    while (idxDokter == IDX_UNDEF || database->listById[idxDokter].ruangTugas == NULL) {
        print_padded("Pilihan tidak valid!");
        print_prompt("Masukkan pilihan yang benar: ");
        clear_input_buffer();
        scanf("%d", &pilihan);
        idxDokter = binary_search(*database, 0, database->count - 1, &pilihan, compare_id);
}
    
    User* dokter = &database->listById[idxDokter];
    Ruangan* ruangan = dokter->ruangTugas;

    enqueue_pasien(ruangan, pasien);
    print_padded("Pendaftaran check-up untuk pasien %s berhasil!", pasien->username);
    print_padded("Anda terdaftar pada antrian Dr. %s di ruangan %s.", dokter->username, dokter->ruangTugas->roomId);
    Address antrian = ruangan->antri;
    int posisi = 1;
    while (antrian != NULL && antrian->pasien->id != pasien->id) {
        posisi++;
        antrian = antrian->next;
    }
    if (posisi <= ruangan->kapasitas) {
        print_padded("Anda sedang berada di dalam ruangan dokter!");
        return;
    }
    else{
        print_padded("Posisi antrian Anda: %d dari %d", posisi - ruangan->kapasitas, ruangan->jumlahPasien - ruangan->kapasitas);
        return;  
    }
}
    
 void antrian_saya(User pasien, UserDatabase database) {
    if (pasien.terdaftar == NULL) {
        print_padded("Anda belum terdaftar dalam antrian check-up!");
        print_padded("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.");
        return;
    }
    Ruangan *ruang = pasien.terdaftar; 

    Address antrian = ruang->antri;
    int posisi = 1;
    while (antrian != NULL && antrian->pasien->id != pasien.id) {
        posisi++;
        antrian = antrian->next;
    }
    

    print_padded("Status antrian Anda:");
    if (ruang->dokter != NULL) {
        print_padded("Dokter: %s", ruang->dokter->username); 
    } else {
        print_padded("Dokter: Tidak ada dokter");
    }
    print_padded("Ruangan: %s", ruang->roomId);

    if (posisi <= ruang->kapasitas) {
        print_padded("Anda sedang berada di dalam ruangan dokter!");
        return;
    }
    else{
        print_padded("Posisi antrian Anda: %d dari %d", posisi - ruang->kapasitas, ruang->jumlahPasien - ruang->kapasitas);
        return;  
    }
    
    print_padded("Pasien %s tidak ditemukan dalam antrian ruangan tersebut.", pasien.username);
}


/** @brief Looping semua matriks denah dan tampilkan data pasien di ruangan, linked list antrian, dan dokter
 * (sesuai spesifikasi)
 */
void lihat_antrian(Denah denah, UserDatabase database) { 
     lihat_denah(denah);
     for (int i = 0; i <= denah.kolom; i++) {
         for (int j = 0; j <= denah.baris; j++) {
             Ruangan *ruangan = &denah.ruang[i][j];
             if (ruangan->jumlahPasien > 0 || ruangan->antri != NULL || ruangan->dokter != NULL) {
                print_ruangan(ruangan, &database);
                print_padded("");
             }
         }
     }
 }
