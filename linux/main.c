#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GUNLUK_DOSYASI "/var/log/syslog"  // Syslog dosyasinin yolu
#define MAKS_SATIR 1024  // Maksimum satir uzunlugu

// Bagli liste dugumu tanimi
typedef struct GunlukKaydi {
    char mesaj[MAKS_SATIR]; // Gunluk mesajini saklayan karakter dizisi
    struct GunlukKaydi* sonraki; // Bir sonraki dugume isaretci
} GunlukKaydi;

// Yeni bir dugum olusturma fonksiyonu
GunlukKaydi* dugumOlustur(const char* gunlukMesaji) {
    GunlukKaydi* yeniDugum = (GunlukKaydi*)malloc(sizeof(GunlukKaydi));
    if (yeniDugum) {
        strncpy(yeniDugum->mesaj, gunlukMesaji, MAKS_SATIR);
        yeniDugum->mesaj[MAKS_SATIR - 1] = '\0';  // Guvenlik icin son karakteri null yap
        yeniDugum->sonraki = NULL;
    }
    return yeniDugum;
}

// Bagli listeye yeni dugum ekleme fonksiyonu
void dugumEkle(GunlukKaydi** bas, const char* gunlukMesaji) {
    GunlukKaydi* yeniDugum = dugumOlustur(gunlukMesaji);
    if (!yeniDugum) {
        printf("Bellek tahsis hatasi!\n");
        return;
    }
    if (*bas == NULL) {
        *bas = yeniDugum;
    } else {
        GunlukKaydi* temp = *bas;
        while (temp->sonraki) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeniDugum;
    }
}

// Bagli listedeki gunlukleri ekrana yazdirma fonksiyonu
void gunlukleriYazdir(GunlukKaydi* bas) {
    GunlukKaydi* temp = bas;
    while (temp) {
        printf("%s", temp->mesaj);
        temp = temp->sonraki;
    }
}

// Bagli listeyi temizleme fonksiyonu
void gunlukleriTemizle(GunlukKaydi* bas) {
    GunlukKaydi* temp;
    while (bas) {
        temp = bas;
        bas = bas->sonraki;
        free(temp); // Bellekte ayrilan alani serbest birakma
    }
}

int main() {
    FILE* gunlukDosya = fopen(GUNLUK_DOSYASI, "r"); // Gunluk dosyasini okuma modunda ac
    if (!gunlukDosya) {
        perror("Gunluk dosyasi acilamadi");
        return 1;
    }

    GunlukKaydi* gunlukListesi = NULL; // Bagli liste icin baslangic isaretcisi
    char satir[MAKS_SATIR];
    
    while (fgets(satir, sizeof(satir), gunlukDosya)) { // Dosyadan satir satir okuma
        dugumEkle(&gunlukListesi, satir);
    }
    fclose(gunlukDosya); // Dosyayi kapatma
    
    // Gunluk kayitlarini ekrana yazdirma
    gunlukleriYazdir(gunlukListesi);
    
    // Bellegi temizleme
    gunlukleriTemizle(gunlukListesi);
    
    return 0;
}

