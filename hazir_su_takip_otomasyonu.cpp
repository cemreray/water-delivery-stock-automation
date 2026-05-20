#include <iostream>
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

void kayitEkle() {
    node* yeninode = newnode();

    yeninode->data.id = sonrakiID++;

    cout << "\n========== YENÝ MÜÞTERÝ EKLE ==========\n";

    cout << "Ad: ";
    cin >> yeninode->data.ad;

    cout << "Soyad: ";
    cin >> yeninode->data.soyad;

    cout << "Telefon: ";
    cin >> yeninode->data.telefon;

    cin.ignore();

    cout << "Adres: ";
    cin.getline(yeninode->data.adres, 100);

    cout << "Stok Adedi: ";
    cin >> yeninode->data.stokAdet;

    cout << "Borçlu Damacana Adedi: ";
    cin >> yeninode->data.borcAdet;

    cout << "Birim Fiyat: ";
    cin >> yeninode->data.birimFiyat;

    addlast(yeninode, list);

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

void kayitAra() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int arananID;

    cout << "\nAranacak müþteri ID: ";
    cin >> arananID;

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

void kayitGuncelle() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int id;

    cout << "\nGüncellenecek müþteri ID: ";
    cin >> id;

    node* bulunan = locate(id, list);

    if (bulunan == NULL) {
        cout << "\nKayýt bulunamadý.\n";
        return;
    }

    cout << "\n========== KAYIT GÜNCELLE ==========\n";

    cout << "Yeni Ad: ";
    cin >> bulunan->data.ad;

    cout << "Yeni Soyad: ";
    cin >> bulunan->data.soyad;

    cout << "Yeni Telefon: ";
    cin >> bulunan->data.telefon;

    cin.ignore();

    cout << "Yeni Adres: ";
    cin.getline(bulunan->data.adres, 100);

    cout << "Yeni Stok Adedi: ";
    cin >> bulunan->data.stokAdet;

    cout << "Yeni Borçlu Damacana Adedi: ";
    cin >> bulunan->data.borcAdet;

    cout << "Yeni Birim Fiyat: ";
    cin >> bulunan->data.birimFiyat;

    cout << "\nKayýt baþarýyla güncellendi.\n";
}

void kayitSil() {
    if (list == NULL) {
        cout << "\nListe boþ.\n";
        return;
    }

    int id;

    cout << "\nSilinecek müþteri ID: ";
    cin >> id;

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

void menuYazdir() {
    cout << "\n*** HAZIR SU STOK MÜÞTERÝ TAKÝP SÝSTEMÝ ***";
    cout << "\n1- Kayýt Ekle";
    cout << "\n2- Kayýtlarý Listele";
    cout << "\n3- Kayýt Ara";
    cout << "\n4- Kayýt Güncelle";
    cout << "\n5- Kayýt Sil";
    cout << "\n0- Çýkýþ";
    cout << "\n\nSeçiminiz: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Turkish");

    int secim;

    do {
        menuYazdir();
        cin >> secim;

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

            case 0:
                cout << "\nProgram kapatýldý.\n";
                break;

            default:
                cout << "\nHatalý seçim yaptýnýz.\n";
        }

    } while (secim != 0);

    return 0;
}
