#include <iostream>
#include <fstream>
#include <cstring>
#include <locale.h>
#include <windows.h>

using namespace std;

struct Musteri {
    int id;
    char ad[30];
    char soyad[30];
    char telefon[20];
    char adres[100];
    int stokAdet;
    int borcAdet;
    float birimFiyat;
};

struct node {
    Musteri data;
    node* link;
};

node* list = NULL;
int sonrakiID = 1;
//klavye
void temizle() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// NODE OLUÞTUR

node* newnode() {
    node* yeninode = new node;
    yeninode->link = NULL;
    return yeninode;
}

// LÝSTENÝN SON NODE ADRESÝNÝ BUL

node* last(node* list) {
    if (list != NULL) {
        while (list->link != NULL) {
            list = list->link;
        }
    }

    return list;
}

// NODE'U LÝSTENÝN SONUNA EKLE

void addlast(node* yeninode, node*& list) {
    if (list == NULL) {
        list = yeninode;
    }
    else {
        last(list)->link = yeninode;
    }
}

// AD / SOYAD KONTROL

int adSoyadKontrol(char metin[]) {
    int i;

    if (strlen(metin) == 0) {
        return 0;
    }

    for (i = 0; metin[i] != '\0'; i++) {
        if (metin[i] >= '0' && metin[i] <= '9') {
            return 0;
        }

        if (
            metin[i] == '!' || metin[i] == '?' ||
            metin[i] == '*' || metin[i] == '/' ||
            metin[i] == '+' || metin[i] == '=' ||
            metin[i] == '_' || metin[i] == '.' ||
            metin[i] == ',' || metin[i] == ';' ||
            metin[i] == ':' || metin[i] == '@' ||
            metin[i] == '#'
        ) {
            return 0;
        }
    }

    return 1;
}

// TELEFON KONTROL

int telefonKontrol(char tel[]) {
    int i;
    int uzunluk = strlen(tel);

    if (uzunluk < 10 || uzunluk > 11) {
        return 0;
    }

    for (i = 0; tel[i] != '\0'; i++) {
        if (!(tel[i] >= '0' && tel[i] <= '9')) {
            return 0;
        }
    }

    return 1;
}

// ADRES KONTROL

int bosKontrol(char metin[]) {
    if (strlen(metin) == 0) {
        return 0;
    }

    return 1;
}

// METÝN ALMA

void adSoyadAl(const char mesaj[], char alan[], int uzunluk) {
    do {
        cout << mesaj;
        cin.getline(alan, uzunluk);

        if (!adSoyadKontrol(alan)) {
            cout << "Hatalý giriþ! Ad ve soyad boþ olamaz, rakam veya özel karakter içeremez.\n";
        }

    } while (!adSoyadKontrol(alan));
}

void telefonAl(const char mesaj[], char alan[], int uzunluk) {
    do {
        cout << mesaj;
        cin.getline(alan, uzunluk);

        if (!telefonKontrol(alan)) {
            cout << "Hatalý telefon! Telefon 10 veya 11 haneli olmalý ve sadece rakam içermelidir.\n";
        }

    } while (!telefonKontrol(alan));
}

void adresAl(const char mesaj[], char alan[], int uzunluk) {
    do {
        cout << mesaj;
        cin.getline(alan, uzunluk);

        if (!bosKontrol(alan)) {
            cout << "Adres boþ býrakýlamaz.\n";
        }

    } while (!bosKontrol(alan));
}

// SAYI ALMA

int tamSayiAl(const char mesaj[]) {
    int sayi;

    while (1) {
        cout << mesaj;
        cin >> sayi;

        if (!cin.fail() && sayi >= 0) {
            temizle();
            return sayi;
        }

        cout << "Hatalý giriþ! Lütfen 0 veya pozitif tam sayý giriniz.\n";
        temizle();
    }
}

float ondalikSayiAl(const char mesaj[]) {
    float sayi;

    while (1) {
        cout << mesaj;
        cin >> sayi;

        if (!cin.fail() && sayi >= 0) {
            temizle();
            return sayi;
        }

        cout << "Hatalý giriþ! Lütfen 0 veya pozitif sayý giriniz.\n";
        temizle();
    }
}

// ID'YE GÖRE NODE BUL

node* locate(int arananID, node* list) {
    node* yer = NULL;

    while (list != NULL) {
        if (list->data.id == arananID) {
            yer = list;
            break;
        }
        else {
            list = list->link;
        }
    }

    return yer;
}

// KAYIT EKLE

void kayitEkle() {
    node* yeninode = newnode();

    yeninode->data.id = sonrakiID++;

    cout << "\n========== YENÝ MÜÞTERÝ EKLE ==========\n";

    adSoyadAl("Ad: ", yeninode->data.ad, 30);
    adSoyadAl("Soyad: ", yeninode->data.soyad, 30);
    telefonAl("Telefon: ", yeninode->data.telefon, 20);
    adresAl("Adres: ", yeninode->data.adres, 100);

    yeninode->data.stokAdet =
        tamSayiAl("Stok Adedi: ");

    yeninode->data.borcAdet =
        tamSayiAl("Borçlu Damacana Adedi: ");

    yeninode->data.birimFiyat =
        ondalikSayiAl("Birim Fiyat: ");

    addlast(yeninode, list);

    cout << "\nKayýt baþarýyla eklendi. Müþteri ID: "
         << yeninode->data.id
         << endl;
}

// KAYIT LÝSTELE

void kayitListele() {
    node* p = list;

    if (p == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    cout << "\n========== MÜÞTERÝ LÝSTESÝ ==========\n";

    while (p != NULL) {
        cout << "\nID: " << p->data.id;
        cout << "\nAd Soyad: " << p->data.ad << " " << p->data.soyad;
        cout << "\nTelefon: " << p->data.telefon;
        cout << "\nAdres: " << p->data.adres;
        cout << "\nStok Adedi: " << p->data.stokAdet;
        cout << "\nBorçlu Damacana Adedi: " << p->data.borcAdet;
        cout << "\nBirim Fiyat: " << p->data.birimFiyat << " TL";
        cout << "\nToplam Borç: "
             << p->data.borcAdet * p->data.birimFiyat
             << " TL";
        cout << "\n-------------------------------------\n";

        p = p->link;
    }
}

// KAYIT ARA

void kayitAra() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int arananID = tamSayiAl("\nAranacak müþteri ID: ");

    node* bulunan = locate(arananID, list);

    if (bulunan == NULL) {
        cout << "\nKayýt bulunamadý.\n";
    }
    else {
        cout << "\n========== KAYIT BULUNDU ==========\n";
        cout << "ID: " << bulunan->data.id << endl;
        cout << "Ad Soyad: "
             << bulunan->data.ad
             << " "
             << bulunan->data.soyad
             << endl;
        cout << "Telefon: " << bulunan->data.telefon << endl;
        cout << "Adres: " << bulunan->data.adres << endl;
        cout << "Stok Adedi: " << bulunan->data.stokAdet << endl;
        cout << "Borçlu Damacana Adedi: " << bulunan->data.borcAdet << endl;
        cout << "Birim Fiyat: " << bulunan->data.birimFiyat << " TL" << endl;
        cout << "Toplam Borç: "
             << bulunan->data.borcAdet * bulunan->data.birimFiyat
             << " TL"
             << endl;
    }
}

// KAYIT GÜNCELLE

void kayitGuncelle() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int id = tamSayiAl("\nGüncellenecek müþteri ID: ");

    node* bulunan = locate(id, list);

    if (bulunan == NULL) {
        cout << "\nKayýt bulunamadý.\n";
        return;
    }

    cout << "\n========== KAYIT GÜNCELLE ==========\n";

    adSoyadAl("Yeni Ad: ", bulunan->data.ad, 30);
    adSoyadAl("Yeni Soyad: ", bulunan->data.soyad, 30);
    telefonAl("Yeni Telefon: ", bulunan->data.telefon, 20);
    adresAl("Yeni Adres: ", bulunan->data.adres, 100);

    bulunan->data.stokAdet =
        tamSayiAl("Yeni Stok Adedi: ");

    bulunan->data.borcAdet =
        tamSayiAl("Yeni Borçlu Damacana Adedi: ");

    bulunan->data.birimFiyat =
        ondalikSayiAl("Yeni Birim Fiyat: ");

    cout << "\nKayýt baþarýyla güncellendi.\n";
}

// KAYIT SÝL

void kayitSil() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int id = tamSayiAl("\nSilinecek müþteri ID: ");

    node* silinecek = locate(id, list);

    if (silinecek == NULL) {
        cout << "\nKayýt bulunamadý.\n";
        return;
    }

    if (silinecek == list) {
        list = list->link;
        delete silinecek;
    }
    else {
        node* p = list;

        while (p->link != silinecek) {
            p = p->link;
        }

        p->link = silinecek->link;
        delete silinecek;
    }

    cout << "\nKayýt baþarýyla silindi.\n";
}

// DOSYAYA AKTAR

void dosyayaAktar() {
    ofstream dosya("hazir_su_kayitlari.bin", ios::binary);

    if (!dosya) {
        cout << "\nDosya açýlamadý.\n";
        return;
    }

    dosya.write((char*)&sonrakiID, sizeof(sonrakiID));

    node* p = list;
    int sayac = 0;

    while (p != NULL) {
        dosya.write((char*)&p->data, sizeof(Musteri));
        sayac++;
        p = p->link;
    }

    dosya.close();

    cout << "\n"
         << sayac
         << " kayýt binary dosyaya aktarýldý.\n";
}

// DOSYADAN AL

void dosyadanAl() {
    ifstream dosya("hazir_su_kayitlari.bin", ios::binary);

    if (!dosya) {
        cout << "\nBinary dosya bulunamadý.\n";
        return;
    }

    while (list != NULL) {
        node* sil = list;
        list = list->link;
        delete sil;
    }

    dosya.read((char*)&sonrakiID, sizeof(sonrakiID));

    Musteri m;
    int sayac = 0;

    while (dosya.read((char*)&m, sizeof(Musteri))) {
        node* yeninode = newnode();

        yeninode->data = m;
        yeninode->link = NULL;

        addlast(yeninode, list);

        sayac++;
    }

    dosya.close();

    cout << "\n"
         << sayac
         << " kayýt binary dosyadan listeye aktarýldý.\n";
}

// BORÇ RAPORU

void borcRaporu() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    node* p = list;
    float toplam = 0;
    int borcluVar = 0;

    cout << "\n========== BORÇ RAPORU ==========\n";

    while (p != NULL) {
        if (p->data.borcAdet > 0) {
            float tutar =
                p->data.borcAdet *
                p->data.birimFiyat;

            cout << p->data.ad
                 << " "
                 << p->data.soyad
                 << " -> "
                 << p->data.borcAdet
                 << " damacana = "
                 << tutar
                 << " TL"
                 << endl;

            toplam += tutar;
            borcluVar = 1;
        }

        p = p->link;
    }

    if (borcluVar == 0) {
        cout << "Borçlu müþteri bulunmamaktadýr.\n";
    }
    else {
        cout << "\nToplam Borç: "
             << toplam
             << " TL"
             << endl;
    }
}

// LÝSTEYÝ TEMÝZLE


void freeList(node*& list) {
    while (list != NULL) {
        node* sil = list;
        list = list->link;
        delete sil;
    }
}

// MENÜ

void menuYazdir() {
    cout << "\n*** HAZIR SU STOK MÜÞTERÝ TAKÝP SÝSTEMÝ ***";
    cout << "\n1- Kayýt Ekle";
    cout << "\n2- Kayýtlarý Listele";
    cout << "\n3- Kayýt Ara";
    cout << "\n4- Kayýt Güncelle";
    cout << "\n5- Kayýt Sil";
    cout << "\n6- Dosyaya Aktar";
    cout << "\n7- Dosyadan Al";
    cout << "\n8- Borç Raporu";
    cout << "\n0- Çýkýþ";
}

// ANA PROGRAM

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Turkish");

    int secim;

    do {
        menuYazdir();

        secim = tamSayiAl("\n\nSeçiminiz: ");

        switch (secim) {
            case 1:
                kayitEkle();
                break;

            case 2:
                kayitListele();
                break;

            case 3:
                kayitAra();
                break;

            case 4:
                kayitGuncelle();
                break;

            case 5:
                kayitSil();
                break;

            case 6:
                dosyayaAktar();
                break;

            case 7:
                dosyadanAl();
                break;

            case 8:
                borcRaporu();
                break;

            case 0:
                cout << "\nProgram kapatýldý.\n";
                break;

            default:
                cout << "\nHatalý seçim yaptýnýz. Lütfen menüdeki seçeneklerden birini giriniz.\n";
        }

    } while (secim != 0);

    freeList(list);

    return 0;
}
