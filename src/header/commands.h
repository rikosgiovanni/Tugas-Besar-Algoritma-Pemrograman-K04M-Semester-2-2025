#include "user.h"
#include "utils.h"

typedef enum {
    LOGIN = 1,
    REGISTER,
    LOGOUT,
    LIHAT_USER,
    CARI_USER,
    LUPA_PASS,
    LIHAT_DENAH,
    LIHAT_RUANGAN,
    TAMBAH_DOKTER,
    ASSIGN_DOKTER,
    DAFTAR_CHECKUP,
    ANTRIAN,
    LIHAT_ANTRIAN,
    DIAGNOSIS,
    PULANG,
    MINUM_OBAT,
    MINUM_PENAWAR,
    NGOBATIN,
    HELP,
    EXIT,
    INVALID
}comlist;

/** @brief parsing dari string ke jenis command yang ada pada enum comlist */
comlist command_parse(char *command);