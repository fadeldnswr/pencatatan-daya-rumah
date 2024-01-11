// Aplikasi Pencatatan Daya Rumah
// Fadel Achmad Daniswara, 2206830220, 14
// Farhan Nur Ardianto, 2206830031, 14
// 5 Desember 2023
// Version 1.0
// Final Project Kelompok 14 Daskom-02
// Referensi Stackoverflow
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Nama Alat
typedef struct {
    char name[50];
    int dayaAlat;
} RumahTangga;

// Struct Pemilik
typedef struct {
    char name[50];
    int houseCode;
    int housePower;
    int userBalance;
    RumahTangga** peralatan; 
} UserApp;

// Fungsi Menampilkan List Rumah
void displayHouse(UserApp houseList[], int totalHouse){
    printf("\t\t=========== LIST RUMAH ===========\n");
    printf("|| Kode ||      Pemilik         || Jml Barang || Saldo Pengguna    ||\n");
    for (int i = 0; i < totalHouse; i++){
        // panjang string dan saldo untuk konversi ke string
        int nameLength = strlen(houseList[i].name); // untuk menghitung panjang string
        int balanceLen = snprintf(NULL, 0, "%d", houseList[i].userBalance); // untuk mengkonversi dari int ke string 
        
        // Spasi yang diperlukan untuk rata tengah
        int namePadding = (20 - nameLength) / 2;
        int balancePadding = (14 - balanceLen) / 2; // 14, karena "Saldo Pengguna" terdiri dari 14 karakter termasuk spasi
        
        // print spasi untuk nama yang rata tengah
        printf("|| %4d ||", houseList[i].houseCode);
        printf(" %*s%s%*s ||", namePadding, "", houseList[i].name, nameLength % 2 == 0 ? namePadding : namePadding + 1, ""); 
        
        // Jumlah barang dan saldo untuk rata tengah
        printf(" %-10d ||", houseList[i].housePower);
        printf(" Rp.%*s%d%*s ||\n", balancePadding, "", houseList[i].userBalance, balanceLen % 2 == 0 ? balancePadding : balancePadding + 1, "");
    }
    printf("\n");
}

// Fungsi Melihat list Barang pada Suatu Rumah
void displayAlat(UserApp houseList[], int totalHouse){
    int houseNumber;

    printf("Masukkan Kode Rumah : ");
    scanf("%d", &houseNumber);

    // Mengecek kondisi user input
    if(houseNumber >= 1 && houseNumber <= totalHouse){
        printf("==========LIST BARANG RUMAH %d===========\n", houseList[houseNumber - 1].houseCode);
        printf("|| Nama Barang  || Daya Digunakan  ||\n");

        for (int i = 0; i < houseList[houseNumber - 1].housePower; i++){
            printf("|| %-12s || %-15d ||\n", houseList[houseNumber - 1].peralatan[i]->name, houseList[houseNumber - 1].peralatan[i]->dayaAlat);
        }
    } 
    else {
        printf("\nKode rumah yang anda masukkan tidak terdaftar...\n\n");
    }
}

// Fungsi Menambah List Rumah
void addHouse(UserApp houseList[], int* totalHouse){
    if (*totalHouse < 50){
        printf("Masukkan Nama Pemilik: ");
        scanf(" %[^\n]", houseList[*totalHouse].name); // Membaca seluruh input user sampai user menginput newline

        printf("Masukkan Kode Rumah: ");
        scanf("%d", &houseList[*totalHouse].houseCode); 

        printf("Saldo pemilik: ");
        scanf("%d", &houseList[*totalHouse].userBalance);

        // Menginput Daya per Barang
        int jumlahBarang;
        printf("Input Jumlah Barang: ");
        scanf("%d", &jumlahBarang);

        // Memory Allocation
        houseList[*totalHouse].peralatan = malloc(sizeof(RumahTangga*) * jumlahBarang);

        if(houseList[*totalHouse].peralatan == NULL) {
            printf("Gagal mengalokasikan memori untuk peralatan\n");
            return;
        }

        for (int i = 0; i < jumlahBarang; i++) {
            houseList[*totalHouse].peralatan[i] = malloc(sizeof(RumahTangga)); 
            if (houseList[*totalHouse].peralatan[i] == NULL) {
                printf("Gagal mengalokasikan memori untuk peralatan ke-%d\n", i);
                // Membebaskan Memori
                while(i-- > 0) {
                    free(houseList[*totalHouse].peralatan[i]);
                }
                free(houseList[*totalHouse].peralatan);
                return;
            }

            printf("Input Barang: ");
            scanf(" %[^\n]", houseList[*totalHouse].peralatan[i]->name);

            printf("Input Daya: ");
            scanf("%d", &houseList[*totalHouse].peralatan[i]->dayaAlat);
        }

        houseList[*totalHouse].housePower = jumlahBarang;
        (*totalHouse)++; // Menambah jumlah peralatan
        printf("\nRumah telah ditambahkan kedalam Database...\n\n");
    } 
    else {
        printf("Database sudah penuh!\n\n");
    }
}

// Fungsi Menambah Daya Rumah
void powerUp(UserApp houseList[], int totalHouse) {
    int houseNumber;

    printf("Masukkan Kode Rumah yang ingin ditambah daya : ");
    scanf("%d", &houseNumber);

    if (houseNumber >= 1 && houseNumber <= totalHouse) {
        int tambahDaya;
        char pilihanUser;

        printf("Berapa daya yang ingin ditambahkan?\n");
        printf("(100/200/300/400/500 watt)\n");
        printf(">> ");
        scanf("%d", &tambahDaya);

        switch(tambahDaya) {
        case 100:
            printf("Apakah anda ingin menambah 100 watt sebesar Rp.10000?(Y/N)\n");
            printf(">> ");
            scanf(" %c", &pilihanUser);

            if(pilihanUser == 'Y'){
                if(houseList->userBalance < 10000){
                    printf("Saldo anda tidak cukup...\n\n");
                }

                else if(houseList->userBalance >= 10000){
                printf("Daya telah berhasil ditambahkan...\n\n");
                houseList[houseNumber - 1].userBalance -= 10000;
                }

            }
            else if(pilihanUser == 'N'){
                printf("User tidak jadi menambah daya...\n\n");
            }
            break;

        case 200:
            printf("Apakah anda ingin menambah 200 watt sebesar Rp.20000?(Y/N)\n");
            printf(">> ");
            scanf(" %c", &pilihanUser);

            if(pilihanUser == 'Y'){
                if(houseList->userBalance < 20000){
                    printf("Saldo anda tidak cukup...\n\n");
                }

                else if(houseList->userBalance >= 20000){
                printf("Daya telah berhasil ditambahkan...\n\n");
                houseList[houseNumber - 1].userBalance -= 20000;
                }

            } 
            else if(pilihanUser == 'N'){
                printf("User tidak jadi menambah daya...\n\n");
            }
            break;

        case 300:
            printf("Apakah anda ingin menambah 300 watt sebesar Rp.30000?(Y/N)\n");
            printf(">> ");
            scanf(" %c", &pilihanUser);

            if(pilihanUser == 'Y'){
                if(houseList->userBalance < 30000){
                    printf("Saldo anda tidak cukup...\n\n");
                }

                else if(houseList->userBalance >= 30000){
                printf("Daya telah berhasil ditambahkan...\n\n");
                houseList[houseNumber - 1].userBalance -= 30000;
                }
            } 
            else if(pilihanUser == 'N'){
                printf("User tidak jadi menambah daya...\n\n");
            }
            break;

        case 400:
            printf("Apakah anda ingin menambah 400 watt sebesar Rp.40000?(Y/N)\n");
            printf(">> ");
            scanf(" %c", &pilihanUser);

            if(pilihanUser == 'Y'){
                if(houseList->userBalance < 40000){
                    printf("Saldo anda tidak cukup...\n\n");
                }

                else if(houseList->userBalance >= 40000){
                printf("Daya telah berhasil ditambahkan...\n\n");
                houseList[houseNumber - 1].userBalance -= 40000;
                }
            } 
            else if(pilihanUser == 'N'){
                printf("User tidak jadi menambah daya...\n\n");
            }
            break;

        case 500:
            printf("Apakah anda ingin menambah 500 watt sebesar Rp.50000?(Y/N)\n");
            printf(">> ");
            scanf(" %c", &pilihanUser);

            if(pilihanUser == 'Y'){
                if(houseList->userBalance < 50000){
                    printf("Saldo anda tidak cukup...\n\n");
                }

                else if(houseList->userBalance >= 50000){
                printf("Daya telah berhasil ditambahkan...\n\n");
                houseList[houseNumber - 1].userBalance -= 50000;
                }    
            } 
            else if(pilihanUser == 'N'){
                printf("User tidak jadi menambah daya...\n\n");
            }
            break;

        default:
            printf("Input yang anda masukkan tidak valid, silahkan masukkan input yang tertera...\n\n");
            break;
        }
    }
    else{
        printf("\nKode rumah yang anda masukkan tidak valid, silahkan coba lagi..\n\n");
    }
}

// Fungsi Menghapus List Rumah
void deleteHouse(UserApp houseList[], int* totalHouse){
    int houseCode;
    printf("Masukkan kode rumah yang ingin dihapus : ");
    scanf("%d", &houseCode);

    for (int i = 0; i < *totalHouse; i++) {
        if (houseList[i].houseCode == houseCode) {
            for (int j = i; j < (*totalHouse - 1); j++){
                houseList[j] = houseList[j + 1];
            }
            (*totalHouse)--;
            printf("Rumah dengan kode %d telah dihapus..\n\n", houseCode);
            return;
        }
    }

    printf("Rumah dengan kode %d tidak ditemukan..\n", houseCode);
}


// Fungsi untuk membebaskan memori yang telah digunakan
void freeMemory(UserApp houseList[], int totalHouse){
    for (int i = 0; i < totalHouse; i++){
        for (int j = 0; j < houseList[i].housePower; j++){
            free(houseList[i].peralatan[j]);
        }
        free(houseList[i].peralatan);
    }
}

int main() {
    // Declare Variabel
    int userInput;
    UserApp* houseList = malloc(50 * sizeof(UserApp));
    int totalHouse = 0;

    do{
        printf("\n==========DATABASE PENCATATAN DAYA RUMAH==========\n");
        printf("1. Tampilkan List Rumah\n");
        printf("2. Tampilkan List Barang pada suatu rumah\n");
        printf("3. Tambah List Rumah\n");
        printf("4. Tambah Daya\n");
        printf("5. Hapus List Rumah\n");
        printf("6. Exit\n");
        printf(">> ");
        scanf("%d", &userInput);
        
        printf("\n");

        switch (userInput) {
        case 1:
            displayHouse(houseList, totalHouse);
            break;
        case 2:
            displayAlat(houseList, totalHouse);
            break;
        case 3:
            addHouse(houseList, &totalHouse);
            break;
        case 4:
            powerUp(houseList, totalHouse);
            break;
        case 5:
            deleteHouse(houseList, &totalHouse);
            break;
        case 6:
            printf("Anda telah keluar dari aplikasi...\n");
            break;
        default:
            printf("Opsi yang anda masukkan tidak valid, silahkan coba lagi...\n");
            break;
        }
    } while (userInput != 6);

    // Membersihkan Memori
    freeMemory(houseList, totalHouse);
    free(houseList);

    return 0;
}
