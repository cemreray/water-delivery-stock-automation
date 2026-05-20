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

void temizle() {
    cin.clear();
    cin.ignore(10000, '\n');
}

node* newnode() {
    node* yeninode = new node;
    yeninode->link = NULL;
    return yeninode;
}

node* last(node* list) {
    if (list != NULL) {
        while (list->link != NULL) {
            list = list->link;
        }
    }
    return list;
}

void addlast(node* yeninode, node*& list) {
    if (list == NULL) {
        list = yeninode;
    }
    else {
        last(list)->link = yeninode;
    }
}

void insertSorted(node* yeninode, node*& list) {
    node* p;
    node* q;

    if (list == NULL || yeninode->data.id < list->data.id) {
        yeninode->link = list;
        list = yeninode;
    }
    else {
        p = list;
        q = NULL;

        while (p != NULL && p->data.id < yeninode->data.id) {
            q = p;
            p = p->link;
        }

        q->link = yeninode;
        yeninode->link = p;
    }
}

node* locate(int arananID, node* list) {
    node* yer = NULL;

    while (list != NULL) {
        if (list->data.id == arananID) {
            yer = list;
            break;
        }
        list = list->link;
    }

    return yer;
}

node* telefonBul(char tel[], node* list) {
    node* yer = NULL;

    while (list != NULL) {
        if (strcmp(list->data.telefon, tel) == 0) {
            yer = list;
            break;
        }

        list = list->link;
    }

    return yer;
}

int adSoyadKontrol(char metin[]) {
    int i;

    if (strlen(metin) == 0) {
        return 0;
    }

    for (i = 0; metin[i] != '\0'; i++) {
        if (metin[i] >= '0' && metin[i] <= '9') {
            return 0;
        }

        if (metin[i] == '!' || metin[i] == '?' || metin[i] == '*' ||
            metin[i] == '/' || metin[i] == '+' || metin[i] == '=' ||
            metin[i] == '_' || metin[i] == '.' || metin[i] == ',' ||
            metin[i] == ';' || metin[i] == ':' || metin[i] == '@' ||
            metin[i] == '#') {
            return 0;
        }
    }

    return 1;
}

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

int bosKontrol(char metin[]) {
    if (strlen(metin) == 0) {
        return 0;
    }

    return 1;
}

void adSoyadAl(const char mesaj[], char alan[], int uzunluk) {
    do {
        cout << mesaj;
        cin.getline(alan, uzunluk);

        if (!adSoyadKontrol(alan)) {
            cout << "Hatalý giriþ! Rakam veya özel karakter girilemez.\n";
        }

    } while (!adSoyadKontrol(alan));
}

void telefonAl(const char mesaj[], char alan[], int uzunluk) {
    do {
        cout << mesaj;
        cin.getline(alan, uzunluk);

        if (!telefonKontrol(alan)) {
            cout << "Hatalý telefon! Telefon sadece rakamlardan oluþmalý ve 10-11 haneli olmalýdýr.\n";
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

void kayitEkle() {
    node* yeninode = newnode();

    yeninode->data.id = sonrakiID++;

    cout << "\n***** YENÝ MÜÞTERÝ EKLE *****\n";

    adSoyadAl("Ad: ", yeninode->data.ad, 30);
    adSoyadAl("Soyad: ", yeninode->data.soyad, 30);

    do {
        telefonAl("Telefon: ", yeninode->data.telefon, 20);

        if (telefonBul(yeninode->data.telefon, list) != NULL) {
            cout << "Bu telefon numarasý sistemde zaten kayýtlý!\n";
        }

    } while (telefonBul(yeninode->data.telefon, list) != NULL);

    adresAl("Adres: ", yeninode->data.adres, 100);

    yeninode->data.stokAdet = tamSayiAl("Stok Adedi: ");
    yeninode->data.borcAdet = tamSayiAl("Borçlu Damacana Adedi: ");
    yeninode->data.birimFiyat = ondalikSayiAl("Birim Fiyat: ");

    insertSorted(yeninode, list);

    cout << "\nKayýt baþarýyla eklendi. Müþteri ID: "
         << yeninode->data.id
         << endl;
}

void kayitListele() {
    node* p = list;

    if (p == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    cout << "\n***** MÜÞTERÝ LÝSTESÝ *****\n";

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
        cout << "\n***** KAYIT BULUNDU *****\n";
        cout << "ID: " << bulunan->data.id << endl;
        cout << "Ad Soyad: " << bulunan->data.ad << " " << bulunan->data.soyad << endl;
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

void telefonlaAra() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    char tel[20];

    telefonAl("\nAranacak telefon numarasý: ", tel, 20);

    node* bulunan = telefonBul(tel, list);

    if (bulunan == NULL) {
        cout << "\nBu telefon numarasýna ait kayýt bulunamadý.\n";
    }
    else {
        cout << "\n***** TELEFONLA KAYIT BULUNDU *****\n";
        cout << "ID: " << bulunan->data.id << endl;
        cout << "Ad Soyad: " << bulunan->data.ad << " " << bulunan->data.soyad << endl;
        cout << "Telefon: " << bulunan->data.telefon << endl;
        cout << "Adres: " << bulunan->data.adres << endl;
        cout << "Stok Adedi: " << bulunan->data.stokAdet << endl;
        cout << "Borçlu Damacana Adedi: " << bulunan->data.borcAdet << endl;
    }
}

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

    cout << "\n***** KAYIT GÜNCELLE *****\n";

    adSoyadAl("Yeni Ad: ", bulunan->data.ad, 30);
    adSoyadAl("Yeni Soyad: ", bulunan->data.soyad, 30);

    char yeniTelefon[20];

    do {
        telefonAl("Yeni Telefon: ", yeniTelefon, 20);

        node* telKaydi = telefonBul(yeniTelefon, list);

        if (telKaydi != NULL && telKaydi != bulunan) {
            cout << "Bu telefon numarasý baþka bir müþteriye kayýtlý!\n";
        }
        else {
            strcpy(bulunan->data.telefon, yeniTelefon);
            break;
        }

    } while (1);

    adresAl("Yeni Adres: ", bulunan->data.adres, 100);

    bulunan->data.stokAdet = tamSayiAl("Yeni Stok Adedi: ");
    bulunan->data.borcAdet = tamSayiAl("Yeni Borçlu Damacana Adedi: ");
    bulunan->data.birimFiyat = ondalikSayiAl("Yeni Birim Fiyat: ");

    cout << "\nKayýt baþarýyla güncellendi.\n";
}

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

void dosyayaAktar() {
    ofstream dosya("water_records.bin", ios::binary);

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

void dosyadanAl() {
    ifstream dosya("water_records.bin", ios::binary);

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

        insertSorted(yeninode, list);

        sayac++;
    }

    dosya.close();

    cout << "\n"
         << sayac
         << " kayýt binary dosyadan listeye aktarýldý.\n";
}

void borcRaporu() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    node* p = list;
    float toplam = 0;
    int borcluVar = 0;

    cout << "\n***** BORÇ RAPORU *****\n";

    while (p != NULL) {
        if (p->data.borcAdet > 0) {
            float tutar = p->data.borcAdet * p->data.birimFiyat;

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

int toplamMusteriSayisi() {
    node* p = list;
    int sayac = 0;

    while (p != NULL) {
        sayac++;
        p = p->link;
    }

    return sayac;
}

int toplamStokSayisi() {
    node* p = list;
    int toplam = 0;

    while (p != NULL) {
        toplam += p->data.stokAdet;
        p = p->link;
    }

    return toplam;
}

void borcsuzMusterileriListele() {
    node* p = list;
    int bulundu = 0;

    cout << "\n***** BORÇSUZ MÜÞTERÝLER *****\n";

    while (p != NULL) {
        if (p->data.borcAdet == 0) {
            cout << p->data.id
                 << " - "
                 << p->data.ad
                 << " "
                 << p->data.soyad
                 << endl;

            bulundu = 1;
        }

        p = p->link;
    }

    if (bulundu == 0) {
        cout << "Borçsuz müþteri bulunmamaktadýr.\n";
    }
}

void enBorcluMusteri() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    node* p = list;
    node* enBorclu = list;

    float borc;
    float enYuksekBorc;

    enYuksekBorc = list->data.borcAdet * list->data.birimFiyat;

    while (p != NULL) {
        borc = p->data.borcAdet * p->data.birimFiyat;

        if (borc > enYuksekBorc) {
            enYuksekBorc = borc;
            enBorclu = p;
        }

        p = p->link;
    }

    cout << "\n***** EN BORÇLU MÜÞTERÝ *****\n";
    cout << "ID: " << enBorclu->data.id << endl;
    cout << "Ad Soyad: " << enBorclu->data.ad << " " << enBorclu->data.soyad << endl;
    cout << "Telefon: " << enBorclu->data.telefon << endl;
    cout << "Borçlu Damacana: " << enBorclu->data.borcAdet << endl;
    cout << "Toplam Borç: " << enYuksekBorc << " TL\n";
}

void detayliRapor() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    cout << "\n***** DETAYLI RAPORLAR *****\n";
    cout << "Toplam Müþteri Sayýsý: " << toplamMusteriSayisi() << endl;
    cout << "Toplam Stok Adedi: " << toplamStokSayisi() << endl;

    borcRaporu();
    borcsuzMusterileriListele();
    enBorcluMusteri();
}

void freeList(node*& list) {
    while (list != NULL) {
        node* sil = list;
        list = list->link;
        delete sil;
    }
}

void menuYazdir() {
    cout << "\n***** HAZIR SU STOK MÜÞTERÝ TAKÝP SÝSTEMÝ *****";
    cout << "\n1- Kayýt Ekle";
    cout << "\n2- Kayýtlarý Listele";
    cout << "\n3- ID ile Kayýt Ara";
    cout << "\n4- Kayýt Güncelle";
    cout << "\n5- Kayýt Sil";
    cout << "\n6- Dosyaya Aktar";
    cout << "\n7- Dosyadan Al";
    cout << "\n8- Borç Raporu";
    cout << "\n9- Detaylý Raporlar";
    cout << "\n10- Telefonla Kayýt Ara";
    cout << "\n0- Çýkýþ";
}

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

            case 9:
                detayliRapor();
                break;

            case 10:
                telefonlaAra();
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
