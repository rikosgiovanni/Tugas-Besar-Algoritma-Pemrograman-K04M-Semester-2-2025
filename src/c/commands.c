#include "commands.h"
#include "utils.h"

comlist command_parse(char *command){
    if(cmp_insensitive(command, "LOGIN")) return LOGIN;
    else if(cmp_insensitive(command, "REGISTER")) return REGISTER;
    else if(cmp_insensitive(command, "LOGOUT")) return LOGOUT;
    else if(cmp_insensitive(command, "HELP")) return HELP;
    else if(cmp_insensitive(command, "CARI_USER")) return CARI_USER;
    else if (cmp_insensitive(command, "LIHAT_USER")) return LIHAT_USER;
    else if (cmp_insensitive(command, "LUPA_PASS")) return LUPA_PASS;
    else if (cmp_insensitive(command, "LIHAT_DENAH")) return LIHAT_DENAH;
    else if (cmp_insensitive(command, "LIHAT_RUANGAN")) return LIHAT_RUANGAN;
    else if (cmp_insensitive(command, "TAMBAH_DOKTER")) return TAMBAH_DOKTER;
    else if (cmp_insensitive(command, "ASSIGN_DOKTER")) return ASSIGN_DOKTER;
    else if (cmp_insensitive(command, "DIAGNOSIS")) return DIAGNOSIS;
    else if (cmp_insensitive(command, "NGOBATIN")) return NGOBATIN;
    else if (cmp_insensitive(command, "PULANG")) return PULANG;
    else if (cmp_insensitive(command, "DAFTAR_CHECKUP")) return DAFTAR_CHECKUP;
    else if (cmp_insensitive(command, "ANTRIAN")) return ANTRIAN;
    else if (cmp_insensitive(command, "LIHAT_ANTRIAN")) return LIHAT_ANTRIAN;
    else if (cmp_insensitive(command, "MINUM_OBAT")) return MINUM_OBAT;
    else if (cmp_insensitive(command, "MINUM_PENAWAR")) return MINUM_PENAWAR;

    else if(cmp_insensitive(command, "EXIT")) return EXIT;
    else return INVALID;
}
