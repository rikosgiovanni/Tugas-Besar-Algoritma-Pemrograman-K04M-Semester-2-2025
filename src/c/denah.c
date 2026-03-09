#include <stdio.h>
#include <stdlib.h>
#include "denah.h"
#include "Boolean.h"
#include <string.h>
#include "utils.h"

void create_denah(Denah *l, int row, int col, int z) { 
    l->baris = row; 
    l->kolom = col; 
    l->jumlah = row * col;
    // printf("inisialisasi baris %d kolom %d\n", l->baris, l->kolom);
    int count = 0;
    for(int i = 0; i < l->baris; i++){ //BARIS
        for(int j = 0; j < l->kolom; j++){//KOLOM
            l->ruang[i][j].antri = NULL;
            l->ruang[i][j].id = count++;
            snprintf(l->ruang[i][j].roomId, sizeof(l->ruang[i][j].roomId), "%c%d", 'A' + i, j + 1); //no overflow
            l->ruang[i][j].dokter = NULL;
            l->ruang[i][j].jumlahPasien = 0;
            l->ruang[i][j].kapasitas = z;
        }
    }
}

int char_to_num(char y){
    return y - 'A';
}

boolean search_room(Denah d,int x, int y) {
    if (d.kolom > x && d.baris > y){
        return true;
    }
    return false;
}

void lihat_denah(Denah l) {
    //Init padding untuk denah
    print_padded("");
    int leftPad = 4;
    int padding = WIDTH - (l.kolom*6+1);
    int rightPad = padding - leftPad - 6;

    //printing denah
    //Label kolom
    printf("%s||%s",GREEN,RESET);
    for(int i = 0; i<leftPad; i++) printf(" "); //Pad Left
    printf("   ");
    for(int i = 1; i<=l.kolom; i++) printf("  %-4d", i);
    for(int i = 0; i<rightPad;i++) printf(" "); //Pad Right
    printf("%s||%s\n",GREEN,RESET);

    for (int i = 0; i < l.baris; i++) {
        

        printf("%s||%s",GREEN,RESET);
        for(int i = 0; i<leftPad; i++) printf(" "); //Pad Left
        printf("  ");
        for (int j = 0; j < l.kolom; j++) {
            printf("+-----");
        }
        printf("+");
        for(int i = 0; i<rightPad;i++) printf(" "); //Pad Right
        printf("%s||%s\n",GREEN,RESET);
        
        //ID ruangan
        printf("%s||%s",GREEN,RESET);
        for(int i = 0; i<leftPad; i++) printf(" "); //Pad Left
        char abc = 'A' + i;
        printf("%c ", abc );
        for (int j = 0; j < l.kolom; j++) {
            printf("|  %-3s", l.ruang[i][j].roomId);
        }
        printf("|");
        for(int i = 0; i<rightPad;i++) printf(" "); //Pad Right
        printf("%s||%s\n",GREEN,RESET);
    }

    // Batas bawah akhir
    printf("%s||%s",GREEN,RESET);
        for(int i = 0; i<leftPad; i++) printf(" "); //Pad Left
        printf("  ");
        for (int j = 0; j < l.kolom; j++) {
            printf("+-----");
        }
        printf("+");
        for(int i = 0; i<rightPad;i++) printf(" "); //Pad Right
        printf("%s||%s\n",GREEN,RESET);
    
    print_padded("");
}

void lihat_ruangan(Denah l, UserDatabase *userDatabase) {
    print_prompt("Masukkan ID ruangan: ");

    int col;
    char row;
    scanf(" %c%d", &row, &col);
    col--;
    boolean ruanganAda = search_room(l, col, char_to_num(row));
    

    while(ruanganAda == false){
        print_padded("Ruangan invalid! silahkan masukkan ruangan yang tersedia");
        print_prompt("Masukkan ID ruangan: ");
        scanf(" %c%d", &row, &col);
        col--;
        ruanganAda = search_room(l, col, char_to_num(row));
    }
    // printf("koordinat ruangan (col/row) %d %d\n", col, row);

    Ruangan* currRoom = &l.ruang[char_to_num(row)][col];
    print_ruangan(currRoom, userDatabase);


}

void print_ruangan(Ruangan *currRoom, const UserDatabase *userDatabase){
    print_padded("%s--- Detail Ruangan %s ---%s", YELLOW,currRoom->roomId,RESET);
    print_padded("Kapasitas : %d", currRoom->kapasitas);

    if (currRoom->dokter != NULL) {
        print_padded("Dokter    : Dr. %s", currRoom->dokter->username);
    } else {
        print_padded("Dokter    : -");
    }

    print_padded("%sPasien di dalam ruangan:%s", YELLOW, RESET);
    if (currRoom->jumlahPasien == 0) {
        print_padded("Tidak ada pasien terdaftar di dalam ruangan ini.");
    } else {
        Address temp = currRoom->antri;
        int antrian = 1;
        while(temp!=NULL && antrian <= currRoom->kapasitas) {
            print_padded("%d. %s%s%s", antrian, CYAN, temp->pasien->username, RESET);
            temp = temp->next;
            antrian++;
        }

        if(temp != NULL){
            antrian = 1;
            print_padded("%sAntrian :%s",YELLOW, RESET );
            while(temp!=NULL){
            print_padded("%d. %s%s%s", antrian, CYAN, temp->pasien->username, RESET);
            temp = temp->next;
            antrian++;
            }
        }
        
    }
    print_padded("--------------------------");
}
/*Testing pointer*/
void set_dokter(UserDatabase *db, Ruangan *r, User *dokter){
    r->dokter = dokter;
    dokter->ruangTugas = &(*r);
}

void assign_dokter(Denah *denah, UserDatabase *db) {
    char username[50];
    // int ruangan;
    
    print_prompt("Username dokter: ");
    scanf("%s", username);

    int userIdx = binary_search(*db, 0, db->count-1, username, compare_username);
    if (userIdx == IDX_UNDEF || strcmp(db->listByUsername[userIdx]->role,"dokter") != 0) {
        print_padded("Dokter dengan username %s tidak ditemukan!", username);
        return;
    }

    User* currDokter = db->listByUsername[binary_search(*db, 0, db->count-1, username, compare_username)];
    
    // int idDokter = binary_search(*db, 0, db->count, currDokter->id, compare_id); // TAG: HAPUS_USER
    //Debug
    // printf("id dokter yang akan di assign = %d\n", idDokter);

    int col;
    char row;
    
    print_prompt("Ruangan: ");
    scanf(" %c%d", &row, &col);
    col--;
    boolean ruanganAda = search_room(*denah, col, char_to_num(row));
    while(ruanganAda == false){
        print_padded("Ruangan invalid! silahkan masukkan ruangan yang tersedia");
        print_prompt("Masukkan ID ruangan: ");
        scanf(" %c%d", &row, &col);
        col--;
        ruanganAda = search_room(*denah, col, char_to_num(row));
    }
    Ruangan* currRoomID = &denah->ruang[char_to_num(row)][col];

    //Debug
    // printf("Room id %d\n", currRoomID->id);
    // printf("Dokter id di room %d\n", currRoomID->dokterIdx);
    
    // Apakah ruangan sudah ada dokter
    // printf("%d\n", cekDokter);   
    // Cases handling
    if (currRoomID->dokter == NULL) {  // gak ada dokter
        if (currDokter->ruangTugas == NULL) {  // dokter tidak di ruangan manapun
            // Case 1: dokter dan ruangan tersedia
            // set_dokter(db, currRoomID, idDokter, x, y);
            set_dokter(db, currRoomID, currDokter);
            print_padded("Dokter %s berhasil diassign ke ruangan %s!", username, currRoomID->roomId);
        } else {  
            // Case 2: dokter di ruangan lain
            print_padded("Dokter %s sudah diassign ke ruangan %s!", username, currDokter->ruangTugas->roomId);
        }
    } else {  //Ruangan sudah ada dokter
        
        char* dokterRuangan = currRoomID->dokter->username;;
        
        if (currDokter->ruangTugas == NULL) { 
            // Case 3: 
            print_padded("Ruangan %s sudah ditempati dokter %s!",currRoomID->roomId, dokterRuangan);
            printf("Silakan cari ruangan lain untuk dokter %s.", username);
        } else {  
            // Case 4: 
            
            print_padded("Dokter %s sudah menempati ruangan %s!", username,currDokter->ruangTugas->roomId);
            print_padded("Ruangan %s juga sudah ditempati dokter %s!", currRoomID->roomId, dokterRuangan);
        }
    }
}