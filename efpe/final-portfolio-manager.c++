#include <bits/stdc++.h>
using namespace std;

// Class & Object: Definisi kelas Asset yang merepresentasikan sebuah aset dalam portofolio
class Asset
{
private:
    // Attribute/Property: Definisi atribut (properti) dari kelas Asset
    int id;
    string nama;
    string kategori;
    double harga;
    int kuantitas;

public:
    // Constructor: Menginisialisasi sebuah objek dari kelas Asset
    Asset(int id, string nama, string kategori, double harga, int kuantitas)
    {
        this->id = id;
        this->nama = nama;
        this->kategori = kategori;
        this->harga = harga;
        this->kuantitas = kuantitas;
    }

    // Setter & Getter: Menyediakan metode untuk mengatur dan mendapatkan nilai atribut
    int getId() const
    {
        return id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    string getNama() const
    {
        return nama;
    }

    void setNama(string nama)
    {
        this->nama = nama;
    }

    string getKategori() const
    {
        return kategori;
    }

    void setKategori(string kategori)
    {
        this->kategori = kategori;
    }

    double getHarga() const
    {
        return harga;
    }

    void setHarga(double harga)
    {
        this->harga = harga;
    }

    int getKuantitas() const
    {
        return kuantitas;
    }

    void setKuantitas(int kuantitas)
    {
        this->kuantitas = kuantitas;
    }

    // Method/Behavior: Definisi metode untuk menghitung nilai total aset
    virtual double getNilaiTotal() const
    {
        return harga * kuantitas;
    }
};

// Class GabunganSahamCrypto yang merupakan turunan dari kelas Asset
class GabunganSahamCrypto : public Asset
{
private:
    string ticker;

public:
    GabunganSahamCrypto(int id, string nama, string kategori, double harga, int kuantitas, string ticker)
        : Asset(id, nama, kategori, harga, kuantitas), ticker(ticker) {}

    string getTicker() const
    {
        return ticker;
    }

    void setTicker(string ticker)
    {
        this->ticker = ticker;
    }

    // Override metode getNilaiTotal dari kelas Asset
    double getNilaiTotal() const override
    {
        return Asset::getNilaiTotal();
    }
};

// Class & Object: Definisi kelas Portfolio yang merepresentasikan kumpulan aset
class Portfolio
{
private:
    // Attribute/Property: Definisi atribut (properti) dari kelas Portfolio
    vector<Asset*> assets;

public:
    // Encapsulation: Membungkus data dan metode dalam kelas dengan kontrol akses
    // Access Modifier, Visibility: Menggunakan kata kunci private dan public untuk mengontrol akses ke anggota kelas
    // Method/Behavior: Definisi metode untuk mengelola portofolio
    void tambahAsset(Asset *asset)
    {
        bool ditemukan = false;
        for (auto &p : assets)
        {
            if (p->getId() == asset->getId())
            {
                cout << "Id sudah ada." << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan)
        {
            assets.push_back(asset);
            cout << "Asset berhasil ditambahkan." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void hapusAsset(int id)
    {
        bool ditemukan = false;
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if ((*i)->getId() == id)
            {
                delete *i; // Menghapus memori yang dialokasikan
                assets.erase(i);
                ditemukan = true;
                cout << "Asset berhasil dihapus." << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        if (!ditemukan)
        {
            cout << "Id tidak ada." << endl;
        }
    }

    Asset *cariAsset(int id)
    {
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if ((*i)->getId() == id)
            {
                return *i;
            }
        }
        return nullptr;
    }

    void perbaruiAsset(int id, string nama, string kategori, double harga, int kuantitas, string ticker)
{
    bool ditemukan = false;
    for (auto i = assets.begin(); i != assets.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            // Jika kategori baru adalah "saham" atau "crypto", dan aset yang sedang diperbarui bukan GabunganSahamCrypto
            if ((kategori == "saham" || kategori == "crypto") && typeid(**i) != typeid(GabunganSahamCrypto))
            {
                // Hapus aset yang lama dari memori
                delete *i;
                // Buat aset baru dengan GabunganSahamCrypto
                *i = new GabunganSahamCrypto(id, nama, kategori, harga, kuantitas, ticker);
            }
            else if ((kategori != "saham" && kategori != "crypto") && typeid(**i) == typeid(GabunganSahamCrypto))
            {
                // Jika kategori baru bukan "saham" atau "crypto", dan aset yang sedang diperbarui adalah GabunganSahamCrypto
                // Hapus aset yang lama dari memori
                delete *i;
                // Buat aset baru tanpa menggunakan GabunganSahamCrypto
                *i = new Asset(id, nama, kategori, harga, kuantitas);
            }
            else // Jika kategori baru tidak "saham" atau "crypto", atau aset yang diperbarui sudah GabunganSahamCrypto
            {
                (*i)->setNama(nama);
                (*i)->setKategori(kategori);
                (*i)->setHarga(harga);
                (*i)->setKuantitas(kuantitas);

                // Jika aset yang ingin diperbarui adalah GabunganSahamCrypto, perbarui juga ticker
                GabunganSahamCrypto* gabunganAsset = dynamic_cast<GabunganSahamCrypto*>(*i);
                if (gabunganAsset != nullptr)
                {
                    gabunganAsset->setTicker(ticker);
                }
            }

            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "ID tidak ada." << endl;
    }
}


    void cetakAsset() const
{
    double totalNilaiPortofolio = 0.0;
    for (auto i = assets.begin(); i != assets.end(); i++)
    {
        cout << "ID : " << (*i)->getId() << endl;
        cout << "Nama : " << (*i)->getNama() << endl;
        cout << "Kategori : " << (*i)->getKategori() << endl;
        cout << "Harga : $ " << (*i)->getHarga() << endl;
        cout << "Kuantitas : " << (*i)->getKuantitas() << endl;
        double nilaiTotal = (*i)->getNilaiTotal();
        cout << "Nilai Total : $ " << nilaiTotal << endl;
        
        // Cek apakah aset adalah GabunganSahamCrypto
        GabunganSahamCrypto *gabunganAsset = dynamic_cast<GabunganSahamCrypto *>(*i);
        if (gabunganAsset != nullptr)
        {
            cout << "Ticker : " << gabunganAsset->getTicker() << endl;
        }
        
        cout << "-----------------------------------------------------------" << endl;
        totalNilaiPortofolio += nilaiTotal;
    }
    cout << "Nilai Portofolio: $ " << totalNilaiPortofolio << endl;
    cout << "-----------------------------------------------------------" << endl;
}


    void simpanPortofolioKeFile(const string& filename)
    {
        ofstream file(filename, ios::out); // Mengubah menjadi overwrite file
        for (int i = 0; i < assets.size(); i++)
        {
            Asset *p = assets[i];
            if (GabunganSahamCrypto* gabunganAsset = dynamic_cast<GabunganSahamCrypto*>(p))
            {
                file << p->getId() << "," << p->getNama() << "," << p->getKategori() << "," << p->getHarga() << "," << p->getKuantitas() << "," << gabunganAsset->getTicker() << endl;
            }
            else
            {
                file << p->getId() << "," << p->getNama() << "," << p->getKategori() << "," << p->getHarga() << "," << p->getKuantitas() << endl;
            }
        }
        file.close();
    }

    void loadPortfolioFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        assets.clear(); // Clear existing assets before loading new ones

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string idStr, name, category, priceStr, quantityStr, ticker;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);
            int quantity = stoi(quantityStr);

            if (getline(ss, ticker, ','))
            {
                assets.push_back(new GabunganSahamCrypto(id, name, category, price, quantity, ticker));
            }
            else
            {
                assets.push_back(new Asset(id, name, category, price, quantity));
            }
        }

        cout << "Portfolio loaded from file." << endl;
        file.close();
    }

    ~Portfolio()
    {
        for (auto asset : assets)
        {
            delete asset; // Menghapus memori yang dialokasikan untuk setiap asset
        }
    }
};

// Polymorphism: Menggunakan pointer atau referensi kelas dasar
void cetakNilaiTotalAsset(const Asset &asset)
{
    cout << "Nilai Total: $ " << asset.getNilaiTotal() << endl;
}

bool getIntInput(int &input)
{
    cin >> input;
    if (cin.fail())
    {
        cin.clear(); // Membersihkan error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input tidak valid
        cout << "Masukkan input yang benar." << endl;
        return false;
    }
    return true;
}

bool getDoubleInput(double &input)
{
    cin >> input;
    if (cin.fail())
    {
        cin.clear(); // Membersihkan error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input tidak valid
        cout << "Masukkan input yang benar." << endl;
        return false;
    }
    return true;
}

int main()
{
    Portfolio portfolio;
    cout << "-----------------------------------------------------------" << endl;
    cout << "--------------Sistem Manajemen Portofolio -----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Selamat Datang! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char pilihan;
    do
    {
        cout << "Silakan pilih opsi:" << endl;
        cout << "1. Tambah aset" << endl;
        cout << "2. Hapus aset" << endl;
        cout << "3. Cari aset" << endl;
        cout << "4. Perbarui aset" << endl;
        cout << "5. Lihat semua aset" << endl;
        cout << "6. Simpan portofolio ke file" << endl;
        cout << "7. Load portofolio dari file" << endl;
        cout << "Q. Keluar" << endl;
        cin >> pilihan;
        cin.ignore(); // Untuk membersihkan karakter newline dari buffer input

        switch (pilihan)
        {
        case '1':
        {
            int id;
            string nama, kategori, ticker;
            double harga;
            int kuantitas;

            cout << "Masukkan ID: ";
            while (!getIntInput(id));

            cout << "Masukkan nama aset: ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan kategori aset: ";
            getline(cin, kategori);

            cout << "Masukkan harga aset: $ ";
            while (!getDoubleInput(harga));

            cout << "Masukkan kuantitas aset: ";
            while (!getIntInput(kuantitas));

            transform(kategori.begin(), kategori.end(), kategori.begin(), ::tolower);

            if (kategori == "saham" || kategori == "crypto")
            {
                cout << "Masukkan ticker aset: ";
                cin.ignore();
                getline(cin, ticker);
                Asset *asset = new GabunganSahamCrypto(id, nama, kategori, harga, kuantitas, ticker);
                portfolio.tambahAsset(asset);
            }
            else
            {
                Asset *asset = new Asset(id, nama, kategori, harga, kuantitas);
                portfolio.tambahAsset(asset);
            }
            break;
        }

        case '2':
        {
            int id;
            cout << "Masukkan ID aset: ";
            while (!getIntInput(id));
            portfolio.hapusAsset(id);
            break;
        }

        case '3':
        {
            int id;
            cout << "Masukkan ID aset: ";
            while (!getIntInput(id));
            Asset *asset = portfolio.cariAsset(id);
            if (asset)
            {
                cout << "Nama: " << asset->getNama() << endl;
                cout << "Kategori: " << asset->getKategori() << endl;
                cout << "Harga: $ " << asset->getHarga() << endl;
                cout << "Kuantitas: " << asset->getKuantitas() << endl;
                cout << "Nilai Total: $ " << asset->getNilaiTotal() << endl;

                if (GabunganSahamCrypto* gabunganAsset = dynamic_cast<GabunganSahamCrypto*>(asset))
                {
                    cout << "Ticker: " << gabunganAsset->getTicker() << endl;
                }

                cout << "-----------------------------------------------------------" << endl;
            }
            else
            {
                cout << "Aset tidak ditemukan." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }

        case '4':
{
    // Pilih opsi perbarui aset
    // Tambahkan logika perbarui aset
    int id;
    string nama, kategori, ticker;
    double harga;
    int kuantitas;

    cout << "Masukkan ID aset: ";
    cin >> id;

    cout << "Masukkan nama aset baru: ";
    cin.ignore();
    getline(cin, nama);

    cout << "Masukkan kategori aset baru: ";
    getline(cin, kategori);

    cout << "Masukkan harga aset baru: $ ";
    cin >> harga;

    cout << "Masukkan kuantitas aset baru: ";
    cin >> kuantitas;

    // Mengubah kategori menjadi lowercase
    transform(kategori.begin(), kategori.end(), kategori.begin(), ::tolower);

    if (kategori == "saham" || kategori == "crypto")
    {
        cout << "Masukkan ticker baru (opsional): ";
        cin.ignore();
        getline(cin, ticker);
    }

    // Memanggil fungsi perbaruiAsset yang telah diperbarui
    portfolio.perbaruiAsset(id, nama, kategori, harga, kuantitas, ticker);
    cout << "Aset berhasil diperbarui." << endl;
    cout << "-----------------------------------------------------------" << endl;
    break;
}



        case '5':
            portfolio.cetakAsset();
            break;

        case '6':
        {
            string filename;
            cout << "Masukkan nama file untuk menyimpan portofolio: ";
            cin.ignore();
            getline(cin, filename);
            portfolio.simpanPortofolioKeFile(filename);
            break;
        }

        case '7':
        {
            string filename;
            cout << "Masukkan nama file untuk load portofolio: ";
            cin.ignore();
            getline(cin, filename);
            portfolio.loadPortfolioFromFile(filename);
            break;
        }

        case 'Q':
        case 'q':
            cout << "Terima kasih, sampai jumpa, semoga bebas dari perbudakan fiat!" << endl;
            break;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 'Q' && pilihan != 'q');

    return 0;
}
