#ifndef MAP_H
#define MAP_H

#define MAX_MAP_SIZE 100

typedef struct {
    int key;  // ID penyakit
    int values[10];  // ID obat (bisa lebih dari 1, misalnya max 10 obat per penyakit)
    int urutan[10];  // Urutan masing-masing obat
    int count;  // Banyak obat yang terhubung
} MapEntry;

typedef struct {
    MapEntry entries[MAX_MAP_SIZE];
    int size;
} Map;

// Fungsi Map

/** @brief Inisialisasi Map dengan mengatur size menjadi 0.
 * Harus dipanggil sebelum Map digunakan untuk pertama kali.
 */
void initMap(Map* map);

/** @brief Menambahkan relasi antara key (ID penyakit) dan value (ID obat) beserta urutannya ke dalam Map.
 * Jika key sudah ada, maka value dan urutan akan ditambahkan ke entry yang sama.
 * Jika key belum ada, buat entri baru di Map.
 */
void insertMap(Map* map, int key, int value, int urutan);

/** @brief Mengambil semua values (ID obat) dan urutan dari Map berdasarkan key (ID penyakit).
 * Nilai dikembalikan melalui parameter values dan urutanValues.
 * @return Banyaknya obat yang ditemukan untuk key tersebut, atau 0 jika tidak ditemukan.
 */
int getMapValues(Map* map, int key, int* values, int* urutanValues);

#endif
