
#include "config.h"
#include <stdio.h>

void load_config(UserDatabase *database, Denah *denah){

    //Line 3
    Ruangan* ruang = &denah->ruang[0][0];
    int idDokter = 10;
    int idPasien = 2;
    // printf("Nama dokter A1 %s\n", database->listById[binary_search(*database, 0, database->count, &idDokter, compare_id)].username);
    set_dokter(database, ruang, &database->listById[binary_search(*database, 0, database->count-1, &idDokter, compare_id)]);
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);
    idPasien = 3;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);
    idPasien = 16;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);
    idPasien = 20;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);

    //Line 4
    ruang = &denah->ruang[0][1];
    idDokter = 11;
    set_dokter(database, ruang, &database->listById[binary_search(*database, 0, database->count-1, &idDokter, compare_id)]);
    idPasien = 4;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);
    idPasien = 5;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);

    //Line 5
    ruang = &denah->ruang[0][2];
    idDokter = 12;
    set_dokter(database, ruang, &database->listById[binary_search(*database, 0, database->count-1, &idDokter, compare_id)]);
    idPasien = 6;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);

    //Line 6
    ruang = &denah->ruang[1][0];
    idDokter = 13;
    set_dokter(database, ruang, &database->listById[binary_search(*database, 0, database->count-1, &idDokter, compare_id)]);
    idPasien = 8;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);
    idPasien = 7;
    enqueue_pasien(ruang, &database->listById[binary_search(*database, 0, database->count-1, &idPasien, compare_id)]);

    //Line 7
    //Do nothing

    //Line 8
    ruang = &denah->ruang[1][2];
    idDokter = 15;
    set_dokter(database, ruang, &database->listById[binary_search(*database, 0, database->count-1, &idDokter, compare_id)]);
    

}