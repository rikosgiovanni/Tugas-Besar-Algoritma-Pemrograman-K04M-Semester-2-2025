#ifndef PENGOBATAN_H
#define PENGOBATAN_H
#include "user.h"
#include "map.h"
#include "antrian.h"
#include "denah.h"

#define MAX_PENYAKIT 100
#define MAX_OBAT 100

typedef struct {
    int id;
    char nama_penyakit[MAX_DISEASE];
    float suhu_tubuh_min;
    float suhu_tubuh_max;
    int tekanan_darah_sistolik_min;
    int tekanan_darah_sistolik_max;
    int tekanan_darah_diastolik_min;
    int tekanan_darah_diastolik_max;
    int detak_jantung_min;
    int detak_jantung_max;
    float saturasi_oksigen_min;
    float saturasi_oksigen_max;
    int kadar_gula_darah_min;
    int kadar_gula_darah_max;
    float berat_badan_min;
    float berat_badan_max;
    int tinggi_badan_min;
    int tinggi_badan_max;
    int kadar_kolesterol_min;
    int kadar_kolesterol_max;
    int trombosit_min;
    int trombosit_max;
} Penyakit;

typedef struct {
    int id_obat;
    int id_penyakit;
    int urutan;
}ObatPenyakit;

extern Obat daftar_obat[MAX_OBAT];
extern Penyakit daftar_penyakit[MAX_PENYAKIT];

// /** @brief Melakukan inisialisasi dengan membaca data relasi antara penyakit dan obat, lalu mengisinya  
//  * ke dalam struktur Mapyang merepresentasikan hubungan dari id penyakit ke daftar obat sesuai urutan. 
//  * Data dimasukkan secara hard coded di dalam fungsi.
//  */
void insert_relasi_obat_penyakit();

/** @brief Diagnosis sesuai ketentuan info penyakit dan info pasien. Setelah diagnosis, set variabel
 * boolean sudahDiagnosis pada struktur pasien ke true. Ketika ingin mendiagnosis, dokter juga mengecek
 * apakah pasien sudah di diagnosis sebelumnya atau tidak
 */
void diagnosis(Ruangan* ruang);

/** @brief Setelah pasien didiagnosis, cek id penyakit di relasi obat_penyakit dan masukkan obat yang benar
 * ke dalam array inventory pasien (bebas terurut atau tidak, lebih baik terurut sesuai urutan)
 * Bila ada obat dalam inventory pasien, berarti pasien sudah diobati sebelumnya, tampilkan bahwa pasien sudah diobati*/
void ngobatin(Ruangan* ruang, Map *mapObat, Obat daftar_obat[]);

/** @brief Pasien memilih salah satu obat di inventoryinya untuk dipush ke stack perut pasien, obat hilang dari inventory
 * dan masuk ke dalam push pasien. Gunakan temp saat push. Stack perut dan array inventory didefinisikan di user.h
*/
void minum_obat(User* pasien);

/** @brief Pasien meminum penawar, stack perut pasien pop obat terakhir, lalu obat terakhir masuk ke array inventory 
 * Kalau perut kosong, tampilkan message yang sesuai.
*/
void minum_penawar(User* pasien);

/** @brief Pengecekan pada variabel : sudahDiagnosis, apakah inventory masih ada obat (belum habis), dan urutan obat sudah benar apa belum 
 * Boleh nanti DataRelasi jadi extern juga sesuai sample
*/

void boleh_pulang(User* pasien, Map* mapObat);

/** @brief Mencetak seluruh isi stack perut pasien dari elemen paling atas ke bawah. 
 * Jika stack perut kosong, tampilkan pesan bahwa perut kosong.
 */
void print_perut(User* pasien);

/** @brief Mencetak seluruh isi array inventory pasien.
 * Jika inventory kosong (tidak ada obat), tampilkan pesan bahwa inventory kosong.
 */
void print_inventory(User* pasien);

/** @brief Mengembalikan pointer ke pasien yang berada di antrian paling depan dalam suatu ruangan.
 * Jika tidak ada pasien di antrian, kembalikan NULL.
 */
User* lihat_pasien_terdepan(Ruangan* ruangan);

/** @brief Melakukan dequeue pasien yang berada di antrian paling depan dalam suatu ruangan.
 * Jika antrian kosong, tampilkan pesan bahwa tidak ada pasien dalam antrian.
 */
void dequeue_pasien(Ruangan* ruangan);


#endif
