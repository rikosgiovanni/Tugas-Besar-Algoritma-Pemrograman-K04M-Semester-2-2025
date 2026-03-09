#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "utils.h"
#include <ctype.h>

static User* currentSession = NULL; // Session global

boolean is_alpha_only(const char *str) {
    while (*str) {
        if (!isalpha(*str)) return false;
        str++;
    }
    return true;
}


void login(UserDatabase *db) {
    if (currentSession != NULL) {
        print_padded("Anda sudah login sebagai %s (%s). Harap logout terlebih dahulu sebelum login kembali.",
               currentSession->username, currentSession->role);
               wait(2);
        return;
    }
    char inputUsername[MAX_USERNAME], inputPassword[MAX_PASSWORD];

    print_prompt("Username: ");
    scanf("%49s", inputUsername);
    int index = binary_search(*db, 0, db->count-1, inputUsername, compare_username);
    while (index == IDX_UNDEF){
        print_prompt("Username tidak ditemukan! apakah ingin mencoba lagi? Y/N: ");
        char option[5];
        scanf("%4s", option);
        if(strcmp(option,"Y") == 0){
        print_prompt("Username: ");
        scanf("%49s", inputUsername);
        }else{
                break;
            }
        index = binary_search(*db, 0, db->count-1, inputUsername, compare_username);
        
    }
    if(index == IDX_UNDEF) return;
    
    User *user = db->listByUsername[index];
    // print_padded("%s", user->username);
    print_prompt("Password: ");
    scanf("%49s", inputPassword);
    boolean pass = false;
    while(pass == false){
        if(cmp_sensitive(inputPassword, user->password)){
            pass = true;
            currentSession = user;
        }else{
            print_prompt("Password salah! apakah anda ingin mencoba lagi? Y/N: ");
            char option[5];
            scanf("%4s", option);
            if(strcmp(option,"Y") == 0){
                print_prompt("Password: ");
                scanf("%49s", inputPassword);
            }else{
                break;
            }
        }
    }
    return;
    
}

void logout() {
    if (currentSession != NULL) {
        print_padded("Sampai jumpa! %s", currentSession->username);
        currentSession = NULL;
    } else {
        print_padded("Logout gagal!Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout");
    }
}

User* getCurrentUser() {
    return currentSession;
}

void register_pasien(UserDatabase *db, int *maxID) {
    if (currentSession != NULL) {
        print_padded("Logout terlebih dahulu sebelum melakukan registrasi.");
        wait(2);
        return;
    }

    char newUsername[MAX_USERNAME], newPassword[MAX_PASSWORD];
    print_prompt("Masukkan username: ");
    scanf("%49s", newUsername);

    // Cek duplikat username
    while (!is_alpha_only(newUsername) || binary_search(*db, 0, db->count - 1, newUsername, compare_username) != IDX_UNDEF) {
        if (!is_alpha_only(newUsername)) {
            print_padded("%s%sUsername hanya boleh berisi huruf tanpa angka/simbol.%s", BOLD, RED, RESET);
        } else {
            print_padded("%s%sUsername tidak tersedia, silahkan pilih username lain%s", BOLD, RED, RESET);
        }
        print_prompt("Masukkan username: ");
        scanf("%49s", newUsername);
    }

    //password
    print_prompt("Masukkan password: ");
    scanf("%49s", newPassword);
    char checkPass[MAX_PASSWORD];
    print_prompt("Masukkan kembali passsword: ");
    scanf("%49s", checkPass);
    while(strcmp(newPassword,checkPass) != 0){
        print_padded("Password tidak sama!Masukkan password: ");
        print_prompt("Masukkan password: ");
        scanf("%49s", newPassword);
        print_prompt("Masukkan kembali passsword: ");
        scanf("%49s", checkPass);
    }

    User newUser;
    newUser.id = ++*maxID;
    strcpy(newUser.username, newUsername);
    strcpy(newUser.password, newPassword);
    strcpy(newUser.riwayatPenyakit, "");
    strcpy(newUser.role, "pasien");
    newUser.suhuTubuh = 0.0;
    newUser.tekananDarahSistolik = 0;
    newUser.tekananDarahDiastolik = 0;
    newUser.detakJantung = 0;
    newUser.saturasiOksigen = 0.0;
    newUser.kadarGulaDarah = 0;
    newUser.beratBadan = 0.0;
    newUser.tinggiBadan = 0;
    newUser.kadarKolesterol = 0;
    newUser.trombosit = 0;
    newUser.terdaftar = NULL;
    newUser.ruangTugas = NULL;
    add_user(db,newUser);

    print_padded("Anda berhasil registrasi! silahkan login dengan akun anda!");

}

void tambah_dokter(UserDatabase *db, int *maxID) {
    char newUsername[MAX_USERNAME], newPassword[MAX_PASSWORD];
    print_prompt("Username: ");
    scanf(" %49s", newUsername);

    // Cek duplikat username
    int idx = binary_search(*db, 0, db->count - 1, newUsername, compare_username);
    while (idx != IDX_UNDEF) {
        print_prompt("Username tidak tersedia, silahkan pilih username lain: ");
        scanf(" %49s", newUsername);
        idx = binary_search(*db, 0, db->count - 1, newUsername, compare_username);
    }

    // Input password
    print_prompt("Password: ");
    scanf(" %49s", newPassword);

    // Konfirmasi password
    char checkPass[MAX_PASSWORD];
    print_prompt("Masukkan kembali password: ");
    scanf(" %49s", checkPass);
    while (strcmp(newPassword, checkPass) != 0) {
        print_padded("Password tidak sama!");
        print_prompt("Password: ");
        scanf(" %49s", newPassword);
        print_prompt("Masukkan kembali password: ");
        scanf(" %49s", checkPass);
    }

    // Buat user baru sebagai dokter
    User newUser;
    newUser.id = ++*maxID;
    strcpy(newUser.username, newUsername);
    strcpy(newUser.password, newPassword);
    strcpy(newUser.riwayatPenyakit, "-"); // Dokter tidak punya riwayat penyakit
    strcpy(newUser.role, "dokter");
    newUser.ruangTugas = NULL;
    add_user(db, newUser);

    print_padded("Dokter %s berhasil ditambahkan!", newUsername);
}


void lupa_password(UserDatabase *db) {
    char username[MAX_USERNAME], inputKodeRLE[100], encodedUsername[100];
    print_prompt("Masukkan username Anda: ");
    scanf("%49s", username);
    while(binary_search(*db, 0, db->count-1,username,compare_username_sensitive) == IDX_UNDEF){
        print_padded("Username tidak ditemukan!");
        print_prompt("Masukkan username anda: ");
        scanf("%49s", username);
    }
    int idx = binary_search(*db, 0, db->count-1,username,compare_username_sensitive);
    User *user = db->listByUsername[idx]; //untuk pointer ke data

    run_length_encoder(username, encodedUsername);


    print_prompt("Masukkan kode RLE untuk verifikasi: ");
    scanf("%49s", inputKodeRLE);
    while(strcmp(inputKodeRLE,encodedUsername) != 0){
        print_padded("Kode RLE salah!");
        print_prompt("Masukkan kode RLE untuk verifikasi: ");
        scanf("%49s", inputKodeRLE);
    }

    print_padded("Kode RLE cocok.");
    print_prompt("Masukkan password baru: ");

    char resetPass[50];
    scanf("%49s", resetPass);
    char resetCheck[MAX_PASSWORD];
    print_prompt("Masukkan kembali passsword: ");
    scanf("%49s", resetCheck);
    while(strcmp(resetPass,resetCheck) != 0){
        print_padded("Password tidak sama!");
        print_prompt("Masukkan password: ");
        scanf("%49s", resetPass);
        print_prompt("Masukkan kembali passsword: ");
        scanf("%49s", resetCheck);
    }
    

    strcpy(user->password, resetPass);
    print_padded("Password berhasil diubah!");
}


