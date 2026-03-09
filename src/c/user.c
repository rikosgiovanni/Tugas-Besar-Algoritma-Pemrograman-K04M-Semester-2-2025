#include "user.h"
#include "utils.h"

static User defaultUsers[] = {
    /*Konversi dari CSV dibantu oleh AI */
    // Dokter
    {10, "neronimo", "pass1010", "dokter", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {11, "ciciko", "pass1111", "dokter", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {12, "cacako", "pass1212", "dokter", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {13, "kroket", "pass1313", "dokter", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {15, "risol", "pass1515", "dokter", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},

    // Manager
    {88, "zeru", "pass77", "manager", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},

    // Pasien
    {1, "stewart", "pass11", "pasien", "", 36.1, 92, 77, 66, 93.7, 127, 52.4, 177, 193, 328,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {7, "tuart", "paturrt", "pasien", "", 36.1, 92, 77, 66, 93.7, 127, 52.4, 177, 193, 328,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {2, "gro", "pass22", "pasien", "COVID-19", 36.6, 126, 85, 67, 96.5, 175, 45.7, 156, 235, 212,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {3, "kebin", "pass33", "pasien", "", 36.4, 96, 68, 94, 92.3, 162, 64.1, 158, 240, 380,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {6, "nikeb", "pnikeb", "pasien", "", 36.4, 96, 68, 94, 92.3, 162, 64.1, 158, 240, 380,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {4, "pop", "pass44", "pasien", "Diabetes Mellitus", 36.9, 110, 85, 73, 98.7, 152, 62.8, 157, 184, 390,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {8, "minonette", "pass88", "pasien", "", 36.7, 93, 87, 63, 97.8, 136, 77.0, 172, 227, 380,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {9, "tobo", "pass99", "pasien", "", 36.8, 114, 74, 61, 94.6, 100, 80.6, 173, 152, 386,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {17, "ropik", "pass110", "pasien", "", 36.2, 103, 87, 65, 96.6, 102, 72.3, 184, 150, 292,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {5, "opor", "oporkanajala", "pasien", "", 36.2, 103, 87, 65, 96.6, 102, 72.3, 184, 150, 292,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {16, "tobokan", "pass1234", "pasien", "", 36.8, 114, 74, 61, 94.6, 100, 80.6, 173, 152, 386,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {20, "popokan", "passpopokan", "pasien", "", 36.9, 110, 85, 73, 98.7, 152, 62.8, 157, 184, 390,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL},
    {100, "pendatang", "pendatangbaru", "pasien", "", 0.0, 0, 0, 0, 0.0, 0, 0.0, 0, 0, 0,
     .perut = {.buffer = {{0}}, .top = -1}, .inventory = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}},
     .terdaftar = NULL, .ruangTugas = NULL}
};


void load_default_user(UserDatabase *db) {
  for(int i = 0; i < 19; i++){
        
        if (!is_full_internal_list(*db)) { 
            add_user(db, defaultUsers[i]); 
        } 
    }
}


void create_user_database(UserDatabase *db) {
    if (db == NULL) return;

    db->listById = (User*) malloc(CAPACITY * sizeof(User));
    db->listByUsername = (User**) malloc(CAPACITY * sizeof(User*));
    db->count = 0;

    if (db->listById != NULL && db->listByUsername != NULL) {
        db->capacity = CAPACITY;
    } else {
        db->capacity = 0;
        if(db->listById != NULL) { 
            free(db->listById); db->listById = NULL; 
        } if(db->listByUsername != NULL) { 
            free(db->listByUsername); db->listByUsername = NULL; 
        }
    }
}

void destroy_user_database(UserDatabase *db) {
    if (db == NULL) return;
    if (db->listByUsername != NULL) {
        free(db->listByUsername);
        db->listByUsername = NULL;
    }
    if (db->listById != NULL) {
        free(db->listById);
        db->listById = NULL;
    }
    db->count = 0;
    db->capacity = 0;
}


int length_user_database(UserDatabase db){
    return db.count; 
}

// boolean is_empty_user_database(UserDatabase db){
//     return (db.count == 0);
// }

boolean is_full_internal_list(UserDatabase db) {
    return (db.capacity > 0 && db.count >= db.capacity);
}

void sort_by_id(UserDatabase *db){
    int i, j;
    boolean swapped;
    for(i = 0; i<db->count-1; i++){
        swapped = false;
        for(j = 0; j < db->count-i-1; j++){
            char uname1Lower[MAX_USERNAME], uname2Lower[MAX_USERNAME];
            to_lower(db->listByUsername[j]->username, uname1Lower);
            to_lower(db->listByUsername[j+1]->username, uname2Lower);

            if(db->listById[j].id > db->listById[j+1].id){
                User temp = db->listById[j];
                db->listById[j] = db->listById[j+1];
                db->listById[j+1] = temp;
                swapped = true;
            }
        }

        if(swapped == false){
            break;
        }
    }
}

void sort_by_username(UserDatabase *db){
    //Pointer of arrays (username) db->listbyUsername[index]
    int i, j;
    boolean swapped;
    for(i = 0; i<db->count-1; i++){
        swapped = false;
        for(j = 0; j < db->count-i-1; j++){
            char uname1Lower[MAX_USERNAME], uname2Lower[MAX_USERNAME];
            to_lower(db->listByUsername[j]->username, uname1Lower);
            to_lower(db->listByUsername[j+1]->username, uname2Lower);

            if(strcmp(uname1Lower, uname2Lower) > 0){
                User* temp = db->listByUsername[j];
                db->listByUsername[j] = db->listByUsername[j+1];
                db->listByUsername[j+1] = temp;
                swapped = true;
            }
        }

        if(swapped == false){
            break;
        }
    }
}


boolean add_user(UserDatabase *db, User newUser) {
    if (db == NULL) return false;

    if (binary_search(*db, 0, db->count-1, &newUser.username, compare_username) != IDX_UNDEF) return false;
    // printf("adding user...\n");
    db->listById[db->count] = newUser;
    db->listByUsername[db->count] = &db->listById[db->count ];
    db->count++;
    // printf("user count are now: %d", db->count);
    sort_by_username(db); 
    sort_by_id(db);
    return true;
}


/* Menghapus user terakhir */
void delete_last_user(UserDatabase *db, User *val) {
    delete_user_at(db, db->count - 1, val);
}

/* Menghapus user pada indeks ke-i */
void delete_user_at(UserDatabase *db, int i, User *val) {
    if (db == NULL || i < 0 || i >= db->count || db->listById == NULL || db->listByUsername == NULL) {
        if (val != NULL) memset(val, 0, sizeof(User));
        return;
    }

    if (val != NULL) {
        *val = db->listById[i]; 
    }
 
   for (int j = i; j < db->count - 1; j++) {
       db->listById[j] = db->listById[j+1];
       db->listByUsername[j] = db->listByUsername[j+1];
   }

    db->count--; 
    sort_by_username(db);
}


void delete_first_user(UserDatabase *db, User *val) {
        delete_user_at(db, 0, val);
}

void display_user(User * user){
    print_padded("%-4d| %-14s| %-12s| %s", user->id, user->username, user->role, user->riwayatPenyakit);
}

void lihat_user(UserDatabase *db){
    print_padded("LIHAT USER");
    print_padded("1. Lihat semua user");
    print_padded("2. Lihat pasien");
    print_padded("3. Lihat dokter"); 
    print_prompt("Pilihan(1/2/3): ");
    int viewChoice;
    scanf("%d", &viewChoice);
    clear_input_buffer(); 
    print_padded("");

    print_padded("Urutkan user berdasarkan?");
    print_padded("1. ID");
    print_padded("2. Username");
    print_prompt("Pilihan(1/2): ");
    int sortBy;
    scanf("%d", &sortBy);
    clear_input_buffer(); 
    print_padded("");

    print_padded("Urutan sort?");
    print_padded("1. ASC (A-Z)");
    print_padded("2. DESC(Z-A)");
    print_prompt("Pilihan(1/2): ");
    int ascDesc;
    scanf("%d", &ascDesc);
    clear_input_buffer(); 
    print_padded("");

    print_padded("ID  | Username      | Role        | Riwayat Penyakit");
    print_padded("--------------------------------------------------");

    char* roleFilter = NULL;
    if(viewChoice == 2){
        roleFilter = "pasien";
    }else if(viewChoice == 3){
        roleFilter = "dokter";
    }

    if(sortBy == 1){
        User* temp[db->count];
        int tempCount = 0;

        for(int i = 0; i < db->count; i++){
            if(roleFilter == NULL || strcmp(db->listById[i].role, roleFilter) == 0){
                temp[tempCount++] = &db->listById[i];
            }
        }

        if(ascDesc == 1){
            for(int i = 0; i<tempCount; i++){
                display_user(temp[i]);
            }
        }else{
            for(int i = tempCount-1; i>=0; i--){
                display_user(temp[i]);
            }
        }
    }else{
        User* temp[db->count];
        int tempCount = 0;

        for(int i = 0; i < db->count; i++){
            if(roleFilter == NULL || strcmp(db->listByUsername[i]->role, roleFilter) == 0){
                temp[tempCount++] = db->listByUsername[i];
            }
        }

        if(ascDesc == 1){
            for(int i = 0; i<tempCount; i++){
                display_user(temp[i]);
            }
        }else{
            for(int i = tempCount-1; i>=0; i--){
                display_user(temp[i]);
            }
        }
    }
}

void cari_user(UserDatabase *db){
    print_padded("Cari berdasarkan?");
    print_padded("1. ID");
    print_padded("2. Nama");
    print_padded("3. Penyakit");
    print_prompt("Pilihan (1/2/3): ");
    
    int viewChoice;
    scanf("%d", &viewChoice);
    clear_input_buffer();

    if(viewChoice == 1){
        int id;
        print_prompt("Masukkan ID >>> ");
        scanf("%d", &id);
        clear_input_buffer();

        int index = binary_search(*db, 0, db->count - 1, &id, compare_id);
        if(index == IDX_UNDEF){
            print_padded("Hasil pencarian tidak ditemukan!");
            return;
        }

        User temp = db->listById[index];
        print_padded("");
        print_padded("ID  | Username      | Role        | Riwayat Penyakit");
        print_padded("--------------------------------------------------");
        display_user(&temp);

    } else if (viewChoice == 2){
        char usn[MAX_USERNAME];
        print_prompt("Masukkan username >>> ");
        scanf("%s", usn);
        clear_input_buffer();

        int index=sequential_search(*db, usn);
        if(index==IDX_UNDEF){
            print_padded("Hasil pencarian tidak ditemukan!");
            return;
        }

        User temp =db->listById[index];
        print_padded("");
        print_padded("ID  | Username      | Role        | Riwayat Penyakit");
        print_padded("--------------------------------------------------");
        display_user(&temp);

    } else if (viewChoice== 3){
        char penyakit[MAX_DISEASE];
        print_prompt("Masukkan penyakit >>> ");
        scanf("%s", penyakit);
        clear_input_buffer();

        print_padded("");
        print_padded("ID  | Username      | Role        | Riwayat Penyakit");
        print_padded("--------------------------------------------------");

        boolean found =false;
        for(int i = 0; i< db->count; i++){
            if(strcasecmp(db->listById[i].riwayatPenyakit, penyakit) == 0){
                display_user(&db->listById[i]);
                found = true;
            }
        }

        if (!found){
            print_padded("Hasil pencarian tidak ditemukan!");
        }
    } else {
        print_padded("Pilihan tidak valid!");
    }
}