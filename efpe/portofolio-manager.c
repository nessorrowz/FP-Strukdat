#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Asset
{
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    Asset(int id, string name, string category, double price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }

    int getId() const
    {
        return id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    string getName() const
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getCategory() const
    {
        return category;
    }

    void setCategory(string category)
    {
        this->category = category;
    }

    double getPrice() const
    {
        return price;
    }

    void setPrice(double price)
    {
        this->price = price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }

    double getTotalValue() const
    {
        return price * quantity;
    }
};

class Portfolio
{
private:
    vector<Asset> assets;

public:
    void addAsset(Asset asset)
    {
        bool found = false;
        for (auto &p : assets)
        {
            if (p.getId() == asset.getId())
            {
                cout << "Id already exists." << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            assets.push_back(asset);
            cout << "Asset added successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void removeAsset(int id)
    {
        bool found = false;
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if (i->getId() == id)
            {
                assets.erase(i);
                found = true;
                cout << "Asset removed successfully." << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Id does not exist" << endl;
        }
    }

    Asset *findAsset(int id)
    {
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if (i->getId() == id)
            {
                return &(*i);
            }
        }
        return nullptr;
    }

    void updateAsset(int id, string name, string category, double price, int quantity)
    {
        bool found = false;
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            if (i->getId() == id)
            {
                i->setName(name);
                i->setCategory(category);
                i->setPrice(price);
                i->setQuantity(quantity);
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "ID does not exist." << endl;
        }
    }

    void printAsset() const
    {
        double totalPortfolioValue = 0.0;
        for (auto i = assets.begin(); i != assets.end(); i++)
        {
            cout << "ID : " << i->getId() << endl;
            cout << "Name : " << i->getName() << endl;
            cout << "Category : " << i->getCategory() << endl;
            cout << "Price : $" << i->getPrice() << endl;
            cout << "Quantity : " << i->getQuantity() << endl;
            double totalValue = i->getTotalValue();
            cout << "Total Value : $" << totalValue << endl;
            cout << "-----------------------------------------------------------" << endl;
            totalPortfolioValue += totalValue;
        }
        cout << "Portofolio Worth: $" << totalPortfolioValue << endl;
        cout << "-----------------------------------------------------------" << endl;
    }

    void savePortfolioToFile(string filename)
    {
        ofstream file;
        file.open(filename, ios::out | ios::app);
        for (int i = 0; i < assets.size(); i++)
        {
            Asset p = assets[i];
            file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << endl;
        }
        file.close();
    }

    void loadPortfolioFromFile(string filename)
    {
        ifstream file;
        file.open(filename);

        if (file.is_open())
        {
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

                Asset p(id, name, category, price, quantity);
                assets.push_back(p);
            }

            file.close();
        }
        else
        {
            cout << "Error: Could not open file " << filename << endl;
        }
    }
};

int main()
{
    Portfolio portfolio;
    cout << "-----------------------------------------------------------" << endl;
    cout << "--------------Portfolio Management System -----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welkamm! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char choice;
    do
    {
        cout << "Please choose an option:" << endl;
        cout << "1. Add an asset" << endl;
        cout << "2. Remove an asset" << endl;
        cout << "3. Find an asset" << endl;
        cout << "4. Update an asset" << endl;
        cout << "5. View all holdings" << endl;
        cout << "6. Save Portfolio to file" << endl;
        cout << "7. Load Portfolio from file" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter asset name: ";
            cin >> name;
            cout << "Enter asset category: ";
            cin >> category;
            cout << "Enter asset price: $ ";
            cin >> price;
            cout << "Enter asset quantity: ";
            cin >> quantity;
            Asset asset(id, name, category, price, quantity);
            portfolio.addAsset(asset);
            break;
        }

        case '2':
        {
            int id;
            cout << "Enter asset id: ";
            cin >> id;
            portfolio.removeAsset(id);
            break;
        }

        case '3':
        {
            int id;
            cout << "Enter asset id: ";
            cin >> id;
            Asset *asset = portfolio.findAsset(id);
            if (asset)
            {
                cout << "Name: " << asset->getName() << endl;
                cout << "Category: " << asset->getCategory() << endl;
                cout << "Price: $ " << asset->getPrice() << endl;
                cout << "Quantity: " << asset->getQuantity() << endl;
                cout << "Total Value: $ " << asset->getTotalValue() << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else
            {
                cout << "Asset not found." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }

        case '4':
        {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the asset id: ";
            cin >> id;
            cout << "Enter new asset name: ";
            cin >> name;
            cout << "Enter new asset category: ";
            cin >> category;
            cout << "Enter new asset price: $ ";
            cin >> price;
            cout << "Enter new asset quantity: ";
            cin >> quantity;
            portfolio.updateAsset(id, name, category, price, quantity);
            cout << "Asset updated successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }

        case '5':
        {
            portfolio.printAsset();
            break;
        }
        case '6':
        {
            portfolio.savePortfolioToFile("portfolio.csv");
            cout << "Portfolio saved to file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '7':
        {
            portfolio.loadPortfolioFromFile("portfolio.csv");
            cout << "Portfolio loaded from file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case 'q':
        case 'Q':
            cout << "Dadah, Salam Cuan!!!" << endl;
            cout << "-----------------------------------------------------------" << endl;
            return 0;

        default:
            cout << "Invalid Choice. Please try again" << endl;
            cout << "-----------------------------------------------------------" << endl;
         break;
        }
    } while (true);

    return 0;
}
