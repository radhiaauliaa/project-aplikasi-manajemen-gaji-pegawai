#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur Jabatan
struct Jabatan {
    char nama[20];
    float gaji_pokok;
};

// Definisi struktur Departemen
struct Departemen {
    char nama[20];
};

// Definisi struktur Pegawai
struct Pegawai {
    char kode[8];
    char nama[30];
    struct Jabatan jabatan;
    struct Departemen departemen;
    int lama_bekerja;
    struct Pegawai *next; // Pointer ke pegawai berikutnya
};

// Fungsi untuk menampilkan judul program
void tampilkanJudul() {
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t 	Program Aplikasi Manajemen Gaji Pegawai\n");
    printf("\t\t\t\t	Perusahaan RABBIE IT \n");
    printf("\t\t\t\t   By Radhia Aulia Nisa (23343049) \n");
    printf("\t\t\t=====================================================\n");
}

// Fungsi untuk menghasilkan otomatis kode pegawai
void kodePegawai(int jumlah_pegawai, char *kode) {
    sprintf(kode, "PGW%03d", jumlah_pegawai + 1);
}

// Fungsi untuk input data pegawai
void inputPegawai(struct Pegawai **head, int *jumlah_pegawai) {
    struct Pegawai *pegawai = (struct Pegawai *)malloc(sizeof(struct Pegawai));
    printf("\nMasukkan Nama Pegawai: ");
    scanf("%29s", pegawai->nama);

    kodePegawai(*jumlah_pegawai, pegawai->kode);
    printf("Kode Pegawai: %s\n", pegawai->kode);

    printf("Pilih Jabatan (senior/middle/junior): ");
    scanf("%19s", pegawai->jabatan.nama);

    if (strcmp(pegawai->jabatan.nama, "senior") == 0) {
        pegawai->jabatan.gaji_pokok = 7000000;
    } else if (strcmp(pegawai->jabatan.nama, "middle") == 0) {
        pegawai->jabatan.gaji_pokok = 5000000;
    } else if (strcmp(pegawai->jabatan.nama, "junior") == 0) {
        pegawai->jabatan.gaji_pokok = 3000000;
    } else {
        printf("Jabatan tidak valid.\n");
        free(pegawai);
        return;
    }

    printf("Masukkan Nama Departemen: ");
    scanf("%19s", pegawai->departemen.nama);

    printf("Masukkan Lama Bekerja (dalam tahun): ");
    scanf("%d", &pegawai->lama_bekerja);

    pegawai->next = *head;
    *head = pegawai;
    (*jumlah_pegawai)++;
}

// Fungsi untuk menghitung pesangon
float hitungPesangon(struct Pegawai *pegawai) {
    return pegawai->lama_bekerja * 0.5 * pegawai->jabatan.gaji_pokok;
}

// Fungsi untuk menampilkan data pegawai
void tampilData(struct Pegawai *pegawai) {
    printf("\nKode Pegawai: %s\n", pegawai->kode);
    printf("Nama: %s\n", pegawai->nama);
    printf("Jabatan: %s\n", pegawai->jabatan.nama);
    printf("Gaji Pokok: %.2f\n", pegawai->jabatan.gaji_pokok);
    printf("Departemen: %s\n", pegawai->departemen.nama);
    printf("Lama Bekerja: %d tahun\n", pegawai->lama_bekerja);

    float potongan_pajak = 0.1 * pegawai->jabatan.gaji_pokok;
    printf("Potongan Pajak: %.2f\n", potongan_pajak);

    float total_gaji = pegawai->jabatan.gaji_pokok - potongan_pajak;
    printf("Total Gaji: %.2f\n", total_gaji);

    float pesangon = hitungPesangon(pegawai);
    printf("Pesangon: %.2f\n", pesangon);
}

// Fungsi untuk melihat pesangon pegawai berdasarkan kode pegawai
void lihatPesangon(struct Pegawai *head) {
    char kode[8];
    printf("\nMasukkan Kode Pegawai: ");
    scanf("%7s", kode);

    struct Pegawai *current = head;
    while (current != NULL) {
        if (strcmp(current->kode, kode) == 0) {
            tampilData(current);
            return;
        }
        current = current->next;
    }
    printf("Pegawai dengan kode %s tidak ditemukan.\n", kode);
}

// Fungsi untuk mengedit data pegawai berdasarkan kode
void editPegawai(struct Pegawai *head) {
    char kode[8];
    printf("\nMasukkan Kode Pegawai yang ingin diedit: ");
    scanf("%7s", kode);

    struct Pegawai *current = head;
    while (current != NULL) {
        if (strcmp(current->kode, kode) == 0) {
            printf("Masukkan Nama Pegawai: ");
            scanf("%29s", current->nama);

            printf("Pilih Jabatan (senior/middle/junior): ");
            scanf("%19s", current->jabatan.nama);

            if (strcmp(current->jabatan.nama, "senior") == 0) {
                current->jabatan.gaji_pokok = 7000000;
            } else if (strcmp(current->jabatan.nama, "middle") == 0) {
                current->jabatan.gaji_pokok = 5000000;
            } else if (strcmp(current->jabatan.nama, "junior") == 0) {
                current->jabatan.gaji_pokok = 3000000;
            } else {
                printf("Jabatan tidak valid.\n");
                return;
            }

            printf("Masukkan Nama Departemen: ");
            scanf("%19s", current->departemen.nama);

            printf("Masukkan Lama Bekerja (dalam tahun): ");
            scanf("%d", &current->lama_bekerja);

            printf("Data Pegawai berhasil diedit.\n");
            return;
        }
        current = current->next;
    }
    printf("Pegawai dengan kode %s tidak ditemukan.\n", kode);
}

// Fungsi untuk menghapus data pegawai berdasarkan kode
void hapusPegawai(struct Pegawai **head) {
    char kode[8];
    printf("\nMasukkan Kode Pegawai yang ingin dihapus: ");
    scanf("%7s", kode);

    struct Pegawai *current = *head;
    struct Pegawai *prev = NULL;

    while (current != NULL && strcmp(current->kode, kode) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Pegawai dengan kode %s tidak ditemukan.\n");
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Data Pegawai berhasil dihapus.\n");
}

// Fungsi untuk mengurutkan data pegawai berdasarkan kode menggunakan bubble sort
void urutkanPegawai(struct Pegawai **head) {
    if (*head == NULL) {
        return;
    }

    int swapped;
    struct Pegawai *ptr1;
    struct Pegawai *lptr = NULL;
    struct Pegawai *prev = NULL;

    // Bubble sort
    do {
        swapped = 0;
        ptr1 = *head;
        prev = NULL;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->kode, ptr1->next->kode) > 0) {
                // Tukar node
                struct Pegawai *tmp = ptr1->next;
                ptr1->next = tmp->next;
                tmp->next = ptr1;

                if (prev == NULL) {
                    *head = tmp;
                } else {
                    prev->next = tmp;
                }

                // Update pointers
                prev = tmp;
                swapped = 1;
            } else {
                prev = ptr1;
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}

// Fungsi untuk mencari pegawai berdasarkan nama
void cariPegawai(struct Pegawai *head) {
    char nama[30];
    printf("\nMasukkan Nama Pegawai yang ingin dicari: ");
    scanf("%29s", nama);

    struct Pegawai *current = head;
    while (current != NULL) {
        if (strcmp(current->nama, nama) == 0) {
            tampilData(current);
            return;
        }
        current = current->next;
    }
    printf("Pegawai dengan nama %s tidak ditemukan.\n", nama);
}

int main() {
    struct Pegawai *head = NULL;
    int pilihan, jumlah_pegawai = 0;

    tampilkanJudul();

    do {
        printf("\n\n");
        printf("+----------------------------+\n");
        printf("|           MENU             |\n");
        printf("+----------------------------+\n");
        printf("| 1. Input Data Pegawai      |\n");
        printf("| 2. Tampil Data Pegawai     |\n");
        printf("| 3. Lihat Pesangon Pegawai  |\n");
        printf("| 4. Edit Data Pegawai       |\n");
        printf("| 5. Hapus Data Pegawai      |\n");
        printf("| 6. Urutkan Data Pegawai    |\n");
        printf("| 7. Cari Data Pegawai       |\n");
        printf("| 8. Keluar                  |\n");
        printf("+----------------------------+\n");
        printf("\nPilih Menu (1-8): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputPegawai(&head, &jumlah_pegawai);
                printf("Data Pegawai berhasil diinput.\n");
                break;
            case 2: {
                printf("\nData Seluruh Pegawai:\n");
                printf("======================\n");
                struct Pegawai *current = head;
                while (current != NULL) {
                    tampilData(current);
                    current = current->next;
                }
                break;
            }
            case 3:
                lihatPesangon(head);
                break;
            case 4:
                editPegawai(head);
                break;
            case 5:
                hapusPegawai(&head);
                jumlah_pegawai--;
                break;
            case 6:
			    urutkanPegawai(&head);
			    printf("Data Pegawai berhasil diurutkan.\n");
			    break;
            case 7:
                cariPegawai(head);
                break;
            case 8:
                printf("\nProgram selesai.\n");
                break;
            default:
                printf("\nPilihan tidak valid.\n");
        }
    } while (pilihan != 8);

    return 0;
}

