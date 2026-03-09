
#include <stdio.h>
#include "auth.h"
#include "user.h"
#include "utils.h"
#include "commands.h"
#include "menu.h"
#include "denah.h"
#include "antrian.h"
#include "config.h"
#include "pengobatan.h"
#include "map.h"

#define idle 2

/*Jika ingin mencoba main, pindah ke folder src di terminal, lalu make.
Setelah selesai, harap make clean*/

//perm check sementara (baru fungsi manager dan pasien)
boolean is_manager(User *user) {
    return user != NULL && strcmp(user->role, "manager") == 0;
}

int main(int argc, char* argv[]){
    // clear_screen();
    /*Init semua komponen yang diperlukan (denah default, user,dkk)*/
    UserDatabase database;
    create_user_database(&database);
    // printf("userdatabase\n");
    Denah denah;
    int baris = atoi(argv[2]);
    int kolom = atoi(argv[1]);
    int kapasitas = atoi(argv[3]);
    create_denah(&denah, kolom, baris, kapasitas);
    // printf("denah\n");
    load_default_user(&database);
    // printf("Defaultuser\n");
    load_config(&database, &denah);
    // printf("config\n");
    Map relasiPenyakitObat;
    insert_relasi_obat_penyakit(&relasiPenyakitObat);

    int maxID = 100;

    boolean exit = false;
    int count = 0;
    while(!exit){
        print_interface("Rumah Sakit Nimons", getCurrentUser());
        printmenu();
        
        char cmd[50];
        print_prompt("Masukkan Command: ");
        scanf("%s", cmd);
        // printf("baris %d, kolom %d\n", denah.baris, denah.kolom);
        comlist parsed = command_parse(cmd);

        //Cek perm
         User *current = getCurrentUser();
        boolean allowed = false;

        switch(parsed) {
            case CARI_USER:
            case LIHAT_USER:
            case TAMBAH_DOKTER:
            case ASSIGN_DOKTER:
            case LIHAT_ANTRIAN:
                if (is_manager(current)) allowed = true;
                break;
            case LIHAT_DENAH:
            case LIHAT_RUANGAN:
                if(current != NULL) allowed = true; 
            case HELP:
            case LOGIN:
            case LOGOUT:
            case REGISTER:
            case EXIT:
                allowed = true;
                break;
            case LUPA_PASS:
                if (current == NULL) allowed = true;
                break;
            case DIAGNOSIS:
            case NGOBATIN:
                if(strcmp(current->role,"dokter") == 0) allowed = true;
            case ANTRIAN:
            case DAFTAR_CHECKUP:
            case MINUM_OBAT:
            case MINUM_PENAWAR:
            case PULANG:
                if (strcmp(current->role, "pasien") == 0) allowed = true;
                break;
            default:
            allowed = true;
                break;
        }

        if (!allowed) {
            print_padded("%s%sAkses ditolak! Anda tidak memiliki izin untuk menjalankan perintah ini.%s",BOLD, RED, RESET);
            wait(idle);
            clear_screen();
            count++;
        continue;
        }

        switch (parsed)
        {
        case LOGIN: login(&database); clear_screen(); break;
        case REGISTER: register_pasien(&database, &maxID);wait(idle);clear_screen();break;
        case LOGOUT: logout();wait(idle);clear_screen();break;
        case LIHAT_USER: lihat_user(&database); back_to_menu();clear_screen();break;
        case HELP: print_interface("HELP", getCurrentUser());help(getCurrentUser());back_to_menu();clear_screen();break;
        case LIHAT_DENAH: {
            lihat_denah(denah);
            char opt[10];
            while (1) {
                print_prompt("Ingin lihat ruangan? (Y untuk ya, N untuk tidak): ");
                scanf("%s", opt);

                if (opt[0] == 'Y' || opt[0] == 'y') {
                    // int idRuangan;
                    // printf("Masukkan ID ruangan yang ingin dilihat (0-%d): ", panjang * lebar - 1);
                    // scanf("%d", &idRuangan);
                    lihat_ruangan(denah, &database);
                }
                else{
                    break;
                }
            }

            back_to_menu();clear_screen();
            break;
        }   
        case LIHAT_RUANGAN: {
            lihat_denah(denah);
            print_padded("Ruangan mana yang ingin anda lihat? ");
            // int idruang;
            // scanf("%d",&idruang);
            lihat_ruangan(denah, &database);
            back_to_menu();
            clear_screen();break;
        }
        case LUPA_PASS: lupa_password(&database);wait(idle);clear_screen();break;
        case TAMBAH_DOKTER: tambah_dokter(&database, &maxID);wait(idle);clear_screen();break;
        case ASSIGN_DOKTER: assign_dokter(&denah, &database);wait(idle);clear_screen();break;
        case CARI_USER: cari_user(&database);back_to_menu();clear_screen();break;
        case DAFTAR_CHECKUP: daftar_checkup(&*getCurrentUser(), &denah, &database);back_to_menu();clear_screen();break;
        case ANTRIAN: antrian_saya(*getCurrentUser(), database);wait(idle); clear_screen();break;
        case LIHAT_ANTRIAN: lihat_antrian(denah, database);back_to_menu(); clear_screen();break;
        case DIAGNOSIS:{
            if(current->ruangTugas == NULL){
                print_padded("%s%sAnda belum ditempatkan di ruangan! Tunggu manager untuk menassign anda.%s", RED, BOLD, RESET);
            }else{
                diagnosis(current->ruangTugas);
            }
            back_to_menu(); clear_screen();break;
        }
        case NGOBATIN:{
            if(current->ruangTugas == NULL){
                print_padded("%s%sAnda belum ditempatkan di ruangan! Tunggu manager untuk menassign anda.%s", RED, BOLD, RESET);
            }else{
                ngobatin(current->ruangTugas, &relasiPenyakitObat, daftar_obat);
            }
            back_to_menu(); clear_screen(); break;
        }
        case MINUM_OBAT:minum_obat(current);back_to_menu(); clear_screen();break;
        case MINUM_PENAWAR:minum_penawar(current);back_to_menu(); clear_screen(); break;
        case PULANG:boleh_pulang(current, &relasiPenyakitObat); back_to_menu(); clear_screen();break;
        case INVALID: print_padded("%s%sCommand invalid!%s",RED, BOLD, RESET);wait(idle);clear_screen(); break;
        case EXIT:exit = true; break;
        default:
            break;
        }
        count++;
    }
    



    // printf("DEBUG: user\n");
    // lihat_user(&database);
    
    
    //Denah
    // load_default_user(&database.listById);
    // printmenu();
    // inisialisasi_denah(&denah,5,3);

    // lihat_denah(&denah);
    // lihat_ruangan(&denah, 1, &database.listById);

    //debugging
    // char *rletest = "AABBBCCDDDD";
    // char *encoded = (char *)malloc(strlen(rletest) * 2 + 1);
    // run_length_encoder(rletest, encoded);
    // printf("%s\n", encoded);
}