#ifndef CONFIG_H
#define CONFIG_H

#include "antrian.h"
#include "denah.h"
#include "user.h"

/** @brief load config dari config txt
    2 3 - Ukuran Ruangan 2x3
    3 4 - Kapasitas ruangan 3, antrian maks 4, total 7
    10 2 3 1 16 20 START set ruangan - Id dokter, antrian pasien
    11 4 5
    12 6
    13 8 7
    0
    15 0 END set ruangan
    2 Dua pasien punya obat di inventory
    2 3 pasien id 2 punya id 3 di inventory
    4 3 2 pasien id 4 punya id 3 2 obat di inventory
    1 satu pasien telah meminum obat
    4 4 5 perut pasien id 4 ada obat id 4 dan 5
    */
void load_config(UserDatabase *database, Denah *denah);
#endif
