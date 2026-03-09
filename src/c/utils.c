#include "utils.h"


/*Encode username untuk ID unik, AABBC - > 2A2BC*/
void *run_length_encoder(const char* input, char* output){
/*
I.S Output sudah di malloc diluar fungsi sebesar input, input sudah terdefinisi diluar fungsi
F.S Output terdefinisi, yaitu versi encoded dari input
*/
    int rlen;
    int length = strlen(input);

    int i,j = 0;

    for(i = 0; i<length; i++){
        rlen = 1;
        //Mengecek ada berapa huruf yang sama
        while(i+1 < length && input[i] == input[i+1]){
            rlen++;
            i++;
        }

        if(rlen > 1){
            char countStr[12];
            snprintf(countStr, sizeof(countStr), "%d", rlen);

            //Copy angka yang diconvert jadi string ke output
            for (int k = 0; countStr[k] != '\0'; k++) {
                output[j++] = countStr[k];
            }
        }

        output[j++] = input[i]; //copy kemunculan char pertama dalam string
    }

    //end string
    output[j] = '\0';
    return output;

    //Diadaptasi dari https://www.geeksforgeeks.org/run-length-encoding/
}

/*Untuk search, agar menjadi case insensitive*/
void *to_lower(const char* input, char* output){
/*
I.S Output sudah di malloc diluar fungsi sebesar input, input sudah terdefinisi diluar fungsi
F.S Output terdefinisi, yaitu versi all lowercase dari input
*/
    

    //Looping seluruh string sampai \0
    for(int i = 0; input[i] != '\0' ; i++){

        //Bila huruf kapital, maka
        if(input[i] >= 'A' && input[i]<= 'Z'){

            //(a - A), ascii, huruf kapital ditambah selisih kapital dan lowercase di ASCII 
            output[i] = input[i] + ('a' - 'A');
        }else{
            output[i] = input[i];
        }
    }

    output[strlen(input)] = '\0';
    return output;

}

/*Mengembalikan boolean jika string sama atau tidak menggunakan to lower*/
boolean cmp_insensitive(const char* str1, const char* str2){

    //malloc untuk lowercase
    int len =strlen(str1);
    char* lower1 = (char*)malloc(sizeof(char) * (len+1) );
    len = strlen(str2);
    char* lower2 = (char*)malloc(sizeof(char) * (len+1) );

    //jadikan semua lowercase
    to_lower(str1, lower1);
    to_lower(str2, lower2);

    //compare
    boolean result = (strcmp(lower1,lower2) == 0);

    //free memory
    free(lower1);
    free(lower2);

    return result;
}

boolean cmp_sensitive(const char* str1, const char* str2){
    if(strcmp(str1,str2) == 0){
        return true;
    }
    else{
        return false;
    }
}

int compare_username_sensitive(const void* a, const void* b){
    char* key =   (char*)a;
    User* user = *(User**)b;


    int result = strcmp(key, user->username);
    return result;

}

int compare_username(const void* a, const void* b){
    char* key =   (char*)a;
    User* user = *(User**)b;

    // int keyLen = strlen(key);
    // int usernameLen = strlen(user->username);
    
    char keyLower[MAX_USERNAME];
    char usernameLower[MAX_USERNAME];

    to_lower(key, keyLower);
    to_lower(user->username, usernameLower);
    // printf("%s\n", usernameLower);
    // printf("%s\n", keyLower);

    int result = strcmp(keyLower, usernameLower);
    // free(keyLower);
    // free(usernameLower);

    // printf("%d\n", strcmp(key, user->username));
    return result;

}

int compare_id(const void* a, const void* b){
    int key =   *(int*)a;
    User *user = (User*)b;

    if(key < user->id) return -1;
    else if(key == user->id) return 0;
    else return 1;

}

int binary_search(UserDatabase db, int low, int high, void* key, CompareFunc compare){
    while (low <= high){
        int mid = low + (high-low)/2;
        int result;

        if(compare == compare_id){
            result = compare(key, &db.listById[mid]);
        }else{
            result = compare(key, &db.listByUsername[mid]);
        }
        
        //printf("%d\n", result);

        if(result == 0) {
            return mid;}
        else if(result < 0) {high = mid-1;}
        else { low = mid +1;}
    }
    // printf("not found\n");
    return IDX_UNDEF;
    
}

int sequential_search(UserDatabase db, const char* username){
    for(int i = 0; i < db.count; i++){
        if(strcmp(username, db.listById[i].username) == 0){
            return i;
        }
    }
    return IDX_UNDEF;
}

void back_to_menu(){
    print_padded("Input apapun untuk kembali ke menu");
    clear_input_buffer();
    while( getchar()!='\n');
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void wait(int seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
}

void print_interface(const char* sectionTitle, const User* currentUser) {

    // Top
    printf("\n%s%s", BOLD, GREEN);
    for (int i = 0; i < WIDTH; i++) printf("=");
    printf("%s\n", RESET);

    // Center
    int pad = (WIDTH - (int)strlen(sectionTitle) - 10) / 2;
    printf("%s%s||", BOLD, GREEN);
    for (int i = 0; i < pad; i++) printf(" ");
    printf("[ %s%s%s ]", YELLOW, sectionTitle, GREEN);
    for (int i = 0; i < WIDTH - pad - (int)strlen(sectionTitle) - 8; i++) printf(" ");
    printf("||%s\n", RESET);

    // Bottom
    printf("%s", GREEN);
    for (int i = 0; i < WIDTH; i++) printf("=");
    printf("%s\n", RESET);

    // Logged-in status
    if (currentUser != NULL) {
        printf("%s%-15s%s %-20s   %s%-5s%s %-10s\n",
            GREY, "Login sebagai:", RESET, currentUser->username,
            GREY, "Role:", RESET, currentUser->role
        );
    } else {
        printf("%s%-15s%s %-20s\n", GREY, "Belum login", RESET, "-");
    }

    // Separator
    printf("%s", GREEN);
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("%s\n", RESET);
}

//Removes ANSI colors from length calculation
int visible_length(const char* str) {
    int len = 0;
    while (*str) {
        if (*str == '\033') {
            // Skip ANSI
            while (*str && *str != 'm') str++;
            if (*str == 'm') str++;
        } else {
            len++;
            str++;
        }
    }
    return len;
}

void print_padded(const char* text, ...){

    char buffer[256];
    va_list variables; //List argumen/variabel untuk dimasukkan ke text
    va_start(variables, text); // Mulai membaca variable setelah text
    vsnprintf(buffer, sizeof(buffer), text, variables);
    va_end(variables); // Clean variables



    int len = visible_length(buffer);
    int padding = WIDTH - len - 4;

    int leftPad = 4;
    int rightPad = padding - leftPad;

    /*Kalau teks panjang*/
    if (len >= WIDTH){
        printf("%s||%s",GREEN,RESET);
        printf("%s",buffer);
        printf("%s||%s\n",GREEN,RESET);
    }

    printf("%s||%s",GREEN,RESET);
    for(int i = 0; i<leftPad; i++) printf(" ");
    printf("%s",buffer);
    for(int i = 0; i<rightPad;i++) printf(" ");
    printf("%s||%s\n",GREEN,RESET);
    /*Kalau teks panjang*/
    if (len >= WIDTH){
        printf("%s\n",text);
    }
}

void print_prompt(const char* text, ...){
    char buffer[256];
    va_list variables; //List argumen/variabel untuk dimasukkan ke text
    va_start(variables, text); // Mulai membaca variable setelah text
    vsnprintf(buffer, sizeof(buffer), text, variables);
    va_end(variables); // Clean variables

    printf("%s||    %s>>>%s %s",GREEN, CYAN, RESET, text);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
