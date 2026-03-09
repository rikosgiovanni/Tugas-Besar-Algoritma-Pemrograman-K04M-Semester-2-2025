#include <stdio.h>
#include <string.h>
#include "pengobatan.h"
#include "map.h"
#include "denah.h"
#include "antrian.h"

// Daftar Penyakit
Penyakit daftar_penyakit[MAX_PENYAKIT] = {
    { 1, "Influenza", 36.0, 38.5, 90, 120, 60, 80, 60, 100, 95.0, 100.0, 70, 140, 45.0, 90.0, 150, 185, 150, 240, 150, 450 },
    { 5, "Anemia", 36.0, 37.0, 90, 120, 60, 80, 60, 100, 95.0, 100.0, 70, 140, 45.0, 90.0, 150, 185, 150, 240, 150, 450 },
    { 2, "COVID-19", 36.0, 39.0, 90, 130, 60, 85, 60, 120, 90.0, 100.0, 70, 180, 45.0, 90.0, 150, 185, 150, 240, 150, 450 },
    { 3, "Hipertensi", 36.0, 37.5, 140, 180, 90, 120, 60, 100, 95.0, 100.0, 70, 140, 45.0, 100.0, 140, 190, 150, 250, 150, 450 },
    { 4, "Diabetes Mellitus", 36.0, 37.5, 90, 140, 60, 90, 60, 100, 95.0, 100.0, 70, 126, 45.0, 90.0, 150, 185, 150, 240, 150, 450 }
};

// Daftar Obat
Obat daftar_obat[MAX_OBAT] = {
    { 2, "Vitamin C" },
    { 1, "Oseltamivir" },
    { 4, "Lisinopril" },
    { 5, "Metformin" },
    { 3, "Remdesivir" },
};


int jumlah_penyakit = 5;
int jumlah_obat = 5;

void insert_relasi_obat_penyakit(Map *relasiPenyakitObat) {
    // Menambahkan relasi obat-penyakit ke map
    insertMap(relasiPenyakitObat, 1, 1, 1);  // Penyakit ID 1, Obat ID 1, Urutan 1
    insertMap(relasiPenyakitObat, 2, 3, 1);  // Penyakit ID 2, Obat ID 3, Urutan 1
    insertMap(relasiPenyakitObat, 1, 2, 2);  // Penyakit ID 1, Obat ID 2, Urutan 2
    insertMap(relasiPenyakitObat, 4, 4, 2);  // Penyakit ID 4, Obat ID 4, Urutan 2
    insertMap(relasiPenyakitObat, 3, 4, 1);  // Penyakit ID 3, Obat ID 4, Urutan 1
    insertMap(relasiPenyakitObat, 4, 5, 1);  // Penyakit ID 4, Obat ID 5, Urutan 1
    insertMap(relasiPenyakitObat, 5, 2, 2);  // Penyakit ID 5, Obat ID 2, Urutan 2
    insertMap(relasiPenyakitObat, 4, 3, 3);  // Penyakit ID 4, Obat ID 3, Urutan 3
    insertMap(relasiPenyakitObat, 4, 2, 4);  // Penyakit ID 4, Obat ID 2, Urutan 4
    insertMap(relasiPenyakitObat, 5, 3, 1);  // Penyakit ID 5, Obat ID 3, Urutan 1
}


// Fungsi untuk mendiagnosis pasien
void diagnosis(Ruangan* ruang) {
    // print_padded("Masuk fungsi");
    User* pasien = lihat_pasien_terdepan(ruang);
    if (pasien == NULL) {
        print_padded("Tidak ada pasien untuk diperiksa!");
        return;
    }

    // Kalau pasien sudah didiagnosis
    if (strcmp(pasien->riwayatPenyakit, "") != 0)
    {
        print_padded("Pasien sudah didiagnosis!");
        return;
    }
    
    // Kalau belum sudah didiagnosis
    for (int k = 0; k < jumlah_penyakit; k++) {
        Penyakit p = daftar_penyakit[k];

        if (pasien->suhuTubuh >= p.suhu_tubuh_min && pasien->suhuTubuh <= p.suhu_tubuh_max &&
            pasien->tekananDarahSistolik >= p.tekanan_darah_sistolik_min && pasien->tekananDarahSistolik <= p.tekanan_darah_sistolik_max &&
            pasien->tekananDarahDiastolik >= p.tekanan_darah_diastolik_min && pasien->tekananDarahDiastolik <= p.tekanan_darah_diastolik_max &&
            pasien->detakJantung >= p.detak_jantung_min && pasien->detakJantung <= p.detak_jantung_max &&
            pasien->saturasiOksigen >= p.saturasi_oksigen_min && pasien->saturasiOksigen <= p.saturasi_oksigen_max &&
            pasien->kadarGulaDarah >= p.kadar_gula_darah_min && pasien->kadarGulaDarah <= p.kadar_gula_darah_max &&
            pasien->beratBadan >= p.berat_badan_min && pasien->beratBadan <= p.berat_badan_max &&
            pasien->tinggiBadan >= p.tinggi_badan_min && pasien->tinggiBadan <= p.tinggi_badan_max &&
            pasien->kadarKolesterol >= p.kadar_kolesterol_min && pasien->kadarKolesterol <= p.kadar_kolesterol_max &&
            pasien->trombosit >= p.trombosit_min && pasien->trombosit <= p.trombosit_max) {

            print_padded("%s terdiagnosa penyakit %s!", pasien->username, p.nama_penyakit);
            strcpy(pasien->riwayatPenyakit, p.nama_penyakit);
            return;
        }
    }

    print_padded("%s tidak terdiagnosis penyakit apapun!", pasien->username);
    strcpy(pasien->riwayatPenyakit, "Sehat");
}


// Fungsi untuk memberikan obat setelah diagnosis
void ngobatin(Ruangan* ruang, Map *mapObat, Obat daftar_obat[]) {
    User* pasien = lihat_pasien_terdepan(ruang);
    if (pasien == NULL) {
        print_padded("Tidak ada pasien untuk diperiksa!");
        return;
    }

    // Kasus pasien belum didiagnosis
    if (strcmp(pasien->riwayatPenyakit, "") == 0) {
        print_padded("Pasien belum di diagnosis!");
        return;
    }

    // Kasus pasien sudah pernah diobatin (diberi obat di inventory) sebelumnya
    int sudah_dikasih = 0;
    for (int i = 0; i < 5; i++) {
        if (pasien->inventory[i].id_obat != 0) {
            sudah_dikasih = 1;
            break;
        }
    }

    if (sudah_dikasih) {
        print_padded("Pasien sudah pernah diberi obat sebelumnya!");
        return;
    }

    // Kasus penyakit tidak ada di daftar penyakit
    int id_penyakit = -1;
    for (int i = 0; i < jumlah_penyakit; i++) {
        if (strcmp(pasien->riwayatPenyakit, daftar_penyakit[i].nama_penyakit) == 0) {
            id_penyakit = daftar_penyakit[i].id;
            break;
        }
    }

    if (id_penyakit == -1) {
        print_padded("Penyakit tidak dikenali!");
        return;
    }

    // Ambil urutan obat seharusnya
    int values[10], urutan[10];
    int count = getMapValues(mapObat, id_penyakit, values, urutan);

    if (count == 0) {
        print_padded("Tidak ada obat untuk penyakit %s", pasien->riwayatPenyakit);
        return;
    }

    // Urutkan berdasarkan urutan
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (urutan[i] > urutan[j]) {
                int tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;

                int tmpUrutan = urutan[i];
                urutan[i] = urutan[j];
                urutan[j] = tmpUrutan;
            }
        }
    }

    print_padded("Memberikan obat untuk pasien %s yang terdiagnosa %s:", pasien->username, pasien->riwayatPenyakit);
    for (int i = 0; i < count; i++) {
        int obatId = values[i];
        int berhasil = 0;

        for (int j = 0; j < 5; j++) {
            if (pasien->inventory[j].id_obat == 0) {
                pasien->inventory[j].id_obat = obatId;
                for (int k = 0; k < jumlah_obat; k++) {
                    if (daftar_obat[k].id_obat == obatId) {
                        pasien->inventory[j].nama_obat = malloc(sizeof(char) * MAX_DISEASE);
                        strcpy(pasien->inventory[j].nama_obat, daftar_obat[k].nama_obat);
                        print_padded("- %s", daftar_obat[k].nama_obat);
                        break;
                    }
                }
                berhasil = 1;
                break;
            }
        }

        if (!berhasil) {
            print_padded("Inventory pasien penuh, tidak bisa memberikan %d", obatId);
        }
    }

    print_padded("Obat telah diberikan. Silakan minum obat sesuai urutan yang diberikan.");
}



// Fungsi untuk meminum obat
void minum_obat(User* pasien) {
    if (pasien->perut.top == 4) {
        print_padded("Perut pasien sudah penuh, tidak bisa minum obat lagi!");
        return;
    }

    print_padded("============ DAFTAR OBAT (INVENTORY) ============");
    int available = 0;
    for (int i = 0; i < 5; i++) {
        if (pasien->inventory[i].id_obat != 0) {
            print_padded("%d. %s", i + 1, pasien->inventory[i].nama_obat);
            available = 1;
        }
    }

    if (!available) {
        print_padded("Tidak ada obat di inventory!");
        return;
    }

    int pilihan;
    print_prompt("Pilih obat untuk diminum: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > 5 || pasien->inventory[pilihan - 1].id_obat == 0) {
        print_padded("Pilihan nomor tidak tersedia!");
        return;
    }


    char nama_obat[MAX_DISEASE];
    strcpy(nama_obat, pasien->inventory[pilihan - 1].nama_obat);

    if (pasien->perut.top < 5) {
        pasien->perut.top++;
        pasien->perut.buffer[pasien->perut.top] = pasien->inventory[pilihan - 1];
        pasien->inventory[pilihan - 1].id_obat = 0;
        pasien->inventory[pilihan - 1].nama_obat = NULL;

        print_padded("GLEKGLEKGLEK... %s berhasil diminum!!!", nama_obat);
    } else {
        print_padded("Perut sudah penuh! Tidak bisa minum obat lagi.");
    }
}

// Fungsi untuk meminum penawar (obat terakhir)
void minum_penawar(User* pasien) {
    if (pasien->perut.top == IDX_UNDEF) {
        print_padded("Perut kosong!! Belum ada obat yang dimakan.");
        return;
    }

    Obat obat_terakhir = pasien->perut.buffer[pasien->perut.top];

    for (int i = 0; i < 5; i++) {
        if (pasien->inventory[i].id_obat == 0) {
            pasien->inventory[i] = obat_terakhir;
            break;
        }
    }
    pasien->perut.buffer[pasien->perut.top].nama_obat = NULL;
    pasien->perut.buffer[pasien->perut.top].id_obat = 0;
    //pop
    pasien->perut.top--;

    print_padded("Uwekkk!!! %s keluar dan kembali ke inventory", obat_terakhir.nama_obat);
    print_padded("============ DAFTAR OBAT (INVENTORY) ============");

    for (int i = 0; i < 5; i++) {
        if (pasien->inventory[i].id_obat != 0) {
            print_padded("%d. %s", i + 1, pasien->inventory[i].nama_obat);
        }
    }
}

// Fungsi untuk menentukan apakah pasien boleh pulang
void boleh_pulang(User* pasien, Map* mapObat) {
    
    if (pasien->terdaftar == NULL) {
        print_padded("Tidak ada pasien untuk diperiksa!");
        return;
    }

    if (strcmp(pasien->riwayatPenyakit, "") == 0) {
        print_padded("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!");
        return;
    }

    if (strcmp(pasien->riwayatPenyakit, "Sehat") == 0) {
        print_padded("Dokter sedang memeriksa keadaanmu...");
        print_padded("Selamat! Kamu sudah dinyatakan sehat oleh dokter. Silahkan pulang dan semoga sehat selalu!");
        dequeue_pasien(pasien->terdaftar);
        return;
    }

    // Cari ID penyakit
    int id_penyakit = -1;
    for (int i = 0; i < jumlah_penyakit; i++) {
        if (strcmp(pasien->riwayatPenyakit, daftar_penyakit[i].nama_penyakit) == 0) {
            id_penyakit = daftar_penyakit[i].id;
            break;
        }
    }

    if (id_penyakit == -1) {
        print_padded("Penyakit pasien tidak dikenali!");
        return;
    }

    int expected_obat[10], expected_urutan[10];
    int expected_count = getMapValues(mapObat, id_penyakit, expected_obat, expected_urutan);

    if (expected_count == 0) {
        print_padded("Tidak ada relasi obat yang ditemukan untuk penyakit ini!");
        return;
    }

    // Cek apakah obat sudah diminum semua
    if (pasien->perut.top + 1 != expected_count) {
        print_padded("Dokter sedang memeriksa keadaanmu...");
        print_padded("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!");
        return;
    }

    // Urutkan obat berdasarkan urutan yang diharapkan
    for (int i = 0; i < expected_count - 1; i++) {
        for (int j = i + 1; j < expected_count-1; j++) {
            // Jika urutan[i] lebih besar dari urutan[j], tukar tempatnya
            if (expected_urutan[i] > expected_urutan[j]) {
                // Tukar ID obat
                int tempObat = expected_obat[i];
                expected_obat[i] = expected_obat[j];
                expected_obat[j] = tempObat;

                // Tukar urutan obat
                int tempUrutan = expected_urutan[i];
                expected_urutan[i] = expected_urutan[j];
                expected_urutan[j] = tempUrutan;
            }
        }
    }

    // Periksa urutan obat yang diminum
    boolean urutanBenar = true;
    for (int i = 0; i <= pasien->perut.top; i++) {
        if(pasien->perut.buffer[i].id_obat != expected_obat[i]){
            urutanBenar = false;
            break;
        }
    }

    if (!urutanBenar) {
        print_padded("Dokter sedang memeriksa keadaanmu...");
        print_padded("Maaf, tapi kamu masih belum bisa pulang!");
        print_padded("Urutan obat yang diharapkan:");
        printf("%s||    %s",GREEN,RESET);
        for (int i = 0; i < expected_count; i++) {
            for (int j = 0; j < jumlah_obat; j++) {
                if (daftar_obat[j].id_obat == expected_obat[i]) {
                    printf("%s", daftar_obat[j].nama_obat);
                    if (i < expected_count - 1) printf(" -> ");
                    break;
                }
            }
        }
        printf("\n");
        print_padded("");
        print_padded("Urutan obat yang kamu minum:");
        printf("%s||    %s",GREEN,RESET);
        for (int k = 0; k <= pasien->perut.top; k++) {
            printf("%s", pasien->perut.buffer[k].nama_obat);
            if (k < pasien->perut.top) printf(" -> ");
        }
        printf("\n");
        print_padded("");
        print_padded("Silahkan konsultasi lagi dengan dokter!");
        return;
    }

    // Jika urutan obat sudah benar, pasien boleh pulang
    print_padded("Dokter sedang memeriksa keadaanmu...");
    print_padded("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!");
    dequeue_pasien(pasien->terdaftar);
}





// Fungsi untuk mencetak isi perut pasien
void print_perut(User* pasien) {
    if (pasien->perut.top == -1) {
        print_padded("Perut pasien kosong, tidak ada obat yang diminum.");
    } else {
        print_padded("========== PERUT PASIEN ==========");
        for (int i = 0; i <= pasien->perut.top; i++) {
            print_padded("%d. %s", i + 1, pasien->perut.buffer[i].nama_obat);
        }
    }
}

// Fungsi untuk mencetak isi inventory pasien
void print_inventory(User* pasien) {
    print_padded("=========== INVENTORY PASIEN ===========");
    int available = 0;
    for (int i = 0; i < 5; i++) {
        if (pasien->inventory[i].id_obat != 0) {
            print_padded("%d. %s", i + 1, pasien->inventory[i].nama_obat);
            available = 1;
        }
    }
    if (!available) {
        print_padded("Tidak ada obat di inventory pasien!");
    }
}

User* lihat_pasien_terdepan(Ruangan* ruangan) {
    // Cek apakah antrian ada
    // print_padded("Masuk fungsi lihat");
    if (ruangan->antri == NULL) {
        print_padded("Tidak ada pasien dalam antrian.");
        return NULL;
    }
    // Mengambil pasien terdepan dalam antrian
    User* pasien_terdepan = ruangan->antri->pasien;

    // Menampilkan informasi pasien terdepan
    // print_padded("Pasien terdepan: %s", pasien_terdepan->username);
    return pasien_terdepan;
}

void dequeue_pasien(Ruangan* ruangan) {
    // Cek apakah antrian kosong
    if (ruangan->antri == NULL) {
        print_padded("Tidak ada pasien dalam antrian.");
        return;
    }

    // Ambil pasien terdepan dari antrian
    Address pasien_terdepan = ruangan->antri;
    ruangan->antri = pasien_terdepan->next;  // Pindahkan pointer antrian ke pasien berikutnya

    // Kurangi jumlah pasien di ruangan
    ruangan->jumlahPasien--;

     // Reset data pasien
    User* pasien = pasien_terdepan->pasien;

    // Reset data medis pasien
    pasien->suhuTubuh = 0.0;
    pasien->tekananDarahSistolik = 0;
    pasien->tekananDarahDiastolik = 0;
    pasien->detakJantung = 0;
    pasien->saturasiOksigen = 0.0;
    pasien->kadarGulaDarah = 0;
    pasien->beratBadan = 0.0;
    pasien->tinggiBadan = 0;
    pasien->kadarKolesterol = 0;
    pasien->trombosit = 0;

    // Reset riwayat penyakit pasien
    strcpy(pasien->riwayatPenyakit, "");

    // Kosongkan inventory obat pasien
    for (int i = 0; i < 5; i++) {
        pasien->inventory[i].id_obat = 0;
        pasien->inventory[i].nama_obat = NULL;  // Jika menggunakan malloc sebelumnya, pastikan dibebaskan
    }

    // Reset perut pasien
    pasien->perut.top = -1;
    for (int i = 0; i < 5; i++) {
        pasien->perut.buffer[i].id_obat = 0;
        pasien->perut.buffer[i].nama_obat = NULL;
    }

    pasien->terdaftar = NULL;

    // Tampilkan informasi pasien yang dikeluarkan dari antrian
    // print_padded("Pasien %s telah keluar dari antrian.", pasien_terdepan->pasien->username);

    // Menghapus node pasien terdepan (deallocate memory)
    free(pasien_terdepan);  
}


