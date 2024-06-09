#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
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

// Inheritance: Definisi kelas turunan dari Asset
class Saham : public Asset
{
private:
    string ticker;

public:
    Saham(int id, string nama, string kategori, double harga, int kuantitas, string ticker)
        : Asset(id, nama, kategori, harga, kuantitas), ticker(ticker) {}

    // Overriding: Menimpa metode getNilaiTotal untuk menambahkan logika spesifik saham
    double getNilaiTotal() const override
    {
        return getHarga() * getKuantitas(); // Contoh sederhana; bisa termasuk logika lebih kompleks
    }

    string getTicker() const
    {
        return ticker;
    }

    void setTicker(string ticker)
    {
        this->ticker = ticker;
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

    void perbaruiAsset(int id, string nama, string kategori, double harga, int kuantitas)
    {
        bool ditemukan = false;
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if ((*i)->getId() == id)
            {
                (*i)->setNama(nama);
                (*i)->setKategori(kategori);
                (*i)->setHarga(harga);
                (*i)->setKuantitas(kuantitas);
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
            file << p->getId() << "," << p->getNama() << "," << p->getKategori() << "," << p->getHarga() << "," << p->getKuantitas() << endl;
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
            string idStr, name, category, priceStr, quantityStr;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');

            int id = stoi(idStr);
            double price = stod(priceStr);
            int quantity = stoi(quantityStr);

            // Determine asset type based on category (assuming saham for 'saham', else regular asset)
            if (category == "saham")
            {
                string ticker;
                getline(ss, ticker, ',');
                assets.push_back(new Saham(id, name, category, price, quantity, ticker));
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

            if (kategori == "saham") {
                cout << "Masukkan ticker saham: ";
                getline(cin, ticker);
                Saham *saham = new Saham(id, nama, kategori, harga, kuantitas, ticker);
                portfolio.tambahAsset(saham);
            } else {
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
            int id;
            string nama, kategori;
            double harga;
            int kuantitas;

            cout << "Masukkan ID aset: ";
            while (!getIntInput(id));

            cout << "Masukkan nama aset baru: ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan kategori aset baru: ";
            getline(cin, kategori);

            cout << "Masukkan harga aset baru: $ ";
            while (!getDoubleInput(harga));

            cout << "Masukkan kuantitas aset baru: ";
            while (!getIntInput(kuantitas));

            portfolio.perbaruiAsset(id, nama, kategori, harga, kuantitas);
            cout << "Aset berhasil diperbarui." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }

        case '5':
        {
            portfolio.cetakAsset();
            break;
        }
        case '6':
        {
            portfolio.simpanPortofolioKeFile("portfolio.csv");
            cout << "Portofolio berhasil disimpan ke file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '7':
        {
            portfolio.loadPortfolioFromFile("portfolio.csv");
            cout << "Portofolio berhasil dimuat dari file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
            }
        case 'q':
        case 'Q':
            cout << "Terima kasih, sampai jumpa!" << endl;
            cout << "-----------------------------------------------------------" << endl;
            return 0;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            cout << "-----------------------------------------------------------" << endl;
         break;
        }
    } while (true);

    return 0;
}
