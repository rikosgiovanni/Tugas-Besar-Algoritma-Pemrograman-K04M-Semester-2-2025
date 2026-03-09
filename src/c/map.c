#include <stdio.h>
#include "map.h"

void initMap(Map* map) {
    map->size = 0;
}

void insertMap(Map* map, int key, int value, int urutan) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            map->entries[i].values[map->entries[i].count] = value;
            map->entries[i].urutan[map->entries[i].count] = urutan;
            map->entries[i].count++;
            return;
        }
    }
    // Tambah entry baru
    map->entries[map->size].key = key;
    map->entries[map->size].values[0] = value;
    map->entries[map->size].urutan[0] = urutan;
    map->entries[map->size].count = 1;
    map->size++;
}

int getMapValues(Map* map, int key, int* values, int* urutanValues) {
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key == key) {
            // Salin nilai obat dan urutannya ke dalam array values dan urutanValues
            for (int j = 0; j < map->entries[i].count; j++) {
                values[j] = map->entries[i].values[j];
                urutanValues[j] = map->entries[i].urutan[j];
            }
            return map->entries[i].count; // Mengembalikan jumlah obat yang ditemukan
        }
    }
    return 0; // Jika tidak ditemukan penyakit dengan key tersebut
}

