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

void kayitEkle() {
    node* yeninode = newnode();

    yeninode->data.id = sonrakiID++;

    cout << "\n***** YENÝ MÜÞTERÝ EKLE *****\n";

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

void menuYazdir() {
    cout << "\n*** HAZIR SU STOK MÜÞTERÝ TAKÝP SÝSTEMÝ ***";
    cout << "\n1- Kayýt Ekle";
    cout << "\n2- Kayýtlarý Listele";
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

            case 0:
                cout << "\nProgram kapatýldý.\n";
                break;

            default:
                cout << "\nHatalý seçim yaptýnýz.\n";
        }

    } while (secim != 0);

    return 0;
}
