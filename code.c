#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define db_name "db_stock.txt"

void menu();
void add();
void del();
void edit();
void srch();

int main() {

    FILE *f;
    char buffer[100];
    system("cls");
    puts("=====System Management Inventory=====");

    if ((f = fopen(db_name, "r")) == NULL)
    {
        puts("Tidak ada data.....");

    }

    rewind(f);

    puts("Daftar barang yang tersedia");
    while (fgets(buffer, sizeof(buffer), f))
    {
        printf("%s", buffer);
    }

    fclose(f);
    menu();
}

void menu() {
    int choice;
    puts("");
    puts("1. Tambahkan barang");
    puts("2. Hapus barang");
    puts("3. Perbarui data barang");
    puts("4. Cari barang");
    puts("5. Keluar");

    puts("------------------------------------------------------");

    printf("Masukkan pilihan anda: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            add();
            break;
        case 2:
            del();
            break;
        case 3:
            edit();
            break;
        case 4:
            srch();
            break;
        case 5:
            puts("Program berhenti berjalan .....");
            break;
        default:
            puts("Masukan pilihan yang tersedia .....");
            menu();
    }
}

void add() {
    FILE *f;
    char cat[10], brand[10], item[20], buffer[100], id[10];
    int qty, prc, a;

    f = fopen(db_name, "a+");
    if (f == NULL) {
        printf("Gagal membuka file.\n");
    }

    printf("Masukkan kategori: ");
    scanf(" %[^\n]%*c", cat);
    printf("Masukkan merek: ");
    scanf(" %[^\n]%*c", brand);
    printf("Masukkan nama barang: ");
    scanf(" %[^\n]%*c", item);

    int found = 0;
    rewind(f);
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, item) != NULL) {
            puts("\nBarang sudah ada .....");
            puts("------------------------------------------------------");
            found = 1;

            puts("0. Kembali ke menu");
            scanf("%d", &a);

            if (a == 0) {
                main();
            }
            else {
                main();
            }
            break;
        }
    }

    if(!found) {
        printf("Masukkan id barang: ");
        scanf(" %[^\n]%*c", id);
        printf("Masukkan jumlah: ");
        scanf("%d", &qty);
        printf("Masukkan harga: ");
        scanf("%d", &prc);

        fprintf(f, "| %-10s | %-10s | %-20s | %-10s | %-15d | %-15d  |\n", cat, brand, item, id, qty, prc);

        puts("Item telah ditambahkan .....");
    }
    fclose(f);
    main();
}

void del() {
    FILE *f, *temp;
    char item[20], buffer[100];
    int found = 0, a;

    f = fopen(db_name, "a+");
    temp = fopen("temp.txt", "a+" );

    printf("Masukkan nama barang yang akan dihapus: ");
    scanf(" %[^\n]%*c", item);

    rewind(f);
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, item) != NULL) {
            found = 1;
            break;
        }
        fprintf(temp, buffer); 

        remove(db_name);
        rename("temp.txt", db_name);
    }   

    fclose(f);
    fclose(temp);

    if (!found) {
        printf("Barang dengan nama '%s' tidak ditemukan.\n", item);
        remove("temp.txt"); 
    } else {
        printf("Barang telah dihapus.\n");
        if (remove(db_name) != 0) {
            printf("Gagal menghapus file asli.\n");
            remove("temp.txt"); 
        } else if (rename("temp.txt", db_name) != 0) {
            printf("Gagal mengganti nama file sementara.\n");
        }
    }
    
    puts(" ");
    puts("0. Kembali ke menu");
    scanf("%d", &a);

    if (a == 0) {
        main();
    }
    else {
        exit(0);
    }

    main();
}


void edit() {
    FILE *f, *temp;
    char item[20], buffer[200];
    char new_cat[10], new_brand[10], new_item[20], new_id[15];
    int new_qty, new_prc;

    f = fopen(db_name, "r");
    if (f == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Gagal membuka file sementara.\n");
        fclose(f);
        return;
    }

    printf("Masukkan nama barang yang ingin diedit: ");
    scanf(" %[^\n]%*c", item);

    int found = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, item) != NULL) {
            found = 1;
            printf("Barang ditemukan: %s\n", buffer);

            printf("Masukkan kategori baru: ");
            scanf(" %[^\n]%*c", new_cat);
            printf("Masukkan merek baru: ");
            scanf(" %[^\n]%*c", new_brand);
            printf("Masukkan nama barang baru: ");
            scanf(" %[^\n]%*c", new_item);
            printf("Masukkan ID barang baru: ");
            scanf(" %[^\n]%*c", new_id);
            printf("Masukkan jumlah barang baru: ");
            scanf("%d", &new_qty);
            printf("Masukkan harga barang baru: ");
            scanf("%d", &new_prc);

            fprintf(temp, "| %-10s | %-10s | %-20s | %-10s | %-15d | %-15d  |\n", new_cat, new_brand, new_item, new_id, new_qty, new_prc);
        } 
        
        else {
            fprintf(temp, "%s", buffer);
        }
    }

    fclose(f);
    fclose(temp);

    if (!found) {
        printf("Barang dengan nama '%s' tidak ditemukan.\n", item);
        remove("temp.txt");
    } 
    
    else {
        remove(db_name);
        rename("temp.txt", db_name);
        printf("Data barang berhasil diperbarui.\n");
    }

    main();
}



void srch() {
    FILE *f;
    char item[20], buffer[100];
    int a;

    f = fopen(db_name, "r");
    if (f == NULL) {
        printf("Gagal membuka file.\n");
    }

    printf("Masukkan nama/id barang yang akan dicari: ");
    scanf(" %[^\n]%*c", item);

    puts("+------------+------------+----------------------+------------+-----------------+------------------+");
    puts("|Kategori    |Merek       |Nama Barang           |ID Barang   |Jumlah Barang    |Harga Barang 	   |");
    puts("+------------+------------+----------------------+------------+-----------------+------------------+");

    rewind(f);
    int found = 0;  
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, item) != NULL) {          
            printf("%s\n", buffer);  
            found = 1;
        }
    }

    if (!found) {
        printf("Barang dengan nama '%s' tidak ditemukan.\n", item);
    }

    fclose(f);

    puts(" ");
    puts("0. Kembali ke menu");
    scanf("%d", &a);

    if (a == 0) {
        main();
    }
    else {
        exit(0);
    }

    main();
}

