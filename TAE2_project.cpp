#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <limits>
using namespace std;

class Menu
{
    int itemCode;
    char itemName[50], category[30];
    float price;

public:

    void addItem()
    {
        ofstream fout("menu.dat", ios::app | ios::binary);

        cout << "\nEnter Item Code: ";
        cin >> itemCode;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Item Name: ";
        cin.getline(itemName, 50);

        cout << "Enter Category: ";
        cin.getline(category, 30);

        cout << "Enter Price: Rs.";
        cin >> price;

        fout.write((char*)this, sizeof(*this));
        fout.close();

        cout << "\nItem Added Successfully!";
    }

    void viewMenu()
    {
        ifstream fin("menu.dat", ios::binary);
        Menu m;
        int count = 0;

        if (!fin)
        {
            cout << "\nNo Menu Items Found!";
            return;
        }

        cout << "\n";
        cout << "===============================================\n";
        cout << "              FOOD PARADISE\n";
        cout << "===============================================\n";

        cout << left << setw(10) << "Code"
             << setw(22) << "Item Name"
             << setw(16) << "Category"
             << "Price\n";

        cout << "-----------------------------------------------\n";

        while (fin.read((char*)&m, sizeof(m)))
        {
            cout << left << setw(10) << m.itemCode
                 << setw(22) << m.itemName
                 << setw(16) << m.category
                 << "Rs." << m.price << "\n";

            count++;
        }

        cout << "===============================================\n";

        if (count == 0)
            cout << "\nNo Items Available!";

        fin.close();
    }

    void updateItem()
    {
        ifstream fin("menu.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        Menu m;
        int code, flag = 0;

        if (!fin)
        {
            cout << "\nMenu File Not Found!";
            fout.close();
            return;
        }

        cout << "\nEnter Item Code to Update: ";
        cin >> code;

        while (fin.read((char*)&m, sizeof(m)))
        {
            if (m.itemCode == code)
            {
                flag = 1;

                cout << "\nEnter New Item Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(m.itemName, 50);

                cout << "Enter New Category: ";
                cin.getline(m.category, 30);

                cout << "Enter New Price: ";
                cin >> m.price;
            }

            fout.write((char*)&m, sizeof(m));
        }

        fin.close();
        fout.close();

        remove("menu.dat");
        rename("temp.dat", "menu.dat");

        if (flag)
            cout << "\nMenu Updated Successfully!";
        else
            cout << "\nItem Not Found!";
    }

    void deleteItem()
    {
        ifstream fin("menu.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        Menu m;
        int code, flag = 0;

        if (!fin)
        {
            cout << "\nNo Menu Records Found!";
            fout.close();
            return;
        }

        cout << "\nEnter Item Code to Delete: ";
        cin >> code;

        while (fin.read((char*)&m, sizeof(m)))
        {
            if (m.itemCode == code)
                flag = 1;
            else
                fout.write((char*)&m, sizeof(m));
        }

        fin.close();
        fout.close();

        remove("menu.dat");
        rename("temp.dat", "menu.dat");

        if (flag)
            cout << "\nItem Deleted Successfully!";
        else
            cout << "\nItem Not Found!";
    }

    void orderFood()
    {
        ifstream fin("menu.dat", ios::binary);
        Menu m;

        int code, quantity;
        int flag;
        float total = 0;

        if (!fin)
        {
            cout << "\nMenu Not Available!";
            return;
        }

        fin.close();

        char choice;

        cout << "\n========== CUSTOMER MENU ==========\n";

        do
        {
            viewMenu();

            cout << "\nEnter Item Code: ";
            cin >> code;

            cout << "Enter Quantity: ";
            cin >> quantity;

            fin.open("menu.dat", ios::binary);
            flag = 0;

            while (fin.read((char*)&m, sizeof(m)))
            {
                if (m.itemCode == code)
                {
                    flag = 1;

                    if (quantity <= 0)
                    {
                        cout << "\nInvalid Quantity!";
                        break;
                    }

                    float amount = m.price * quantity;

                    cout << "\nItem: " << m.itemName;
                    cout << "\nQuantity: " << quantity;
                    cout << "\nAmount: Rs." << amount;

                    total += amount;
                    break;
                }
            }

            fin.close();

            if (!flag)
                cout << "\nInvalid Item Code!";

            cout << "\n\nAdd More Items? (Y/N): ";
            cin >> choice;

        } while (choice == 'Y' || choice == 'y');

        cout << "\n";
        cout << "=================================\n";
        cout << "          FINAL BILL\n";
        cout << "=================================\n";
        cout << "Total Amount: Rs." << total << "\n";
        cout << "Thank You! Visit Again!\n";
        cout << "=================================\n";
    }
};

int main()
{
    Menu m;
    int choice;

    do
    {
        cout << "\n\n";
        cout << "====================================\n";
        cout << "         FOOD PARADISE\n";
        cout << "       RESTAURANT MENU SYSTEM\n";
        cout << "====================================\n";

        cout << "\n1. Admin Panel";
        cout << "\n2. Customer Panel";
        cout << "\n0. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int ch;

                do
                {
                    cout << "\n======= ADMIN PANEL =======";
                    cout << "\n1. Add Menu Item";
                    cout << "\n2. View Menu";
                    cout << "\n3. Update Menu Item";
                    cout << "\n4. Delete Menu Item";
                    cout << "\n0. Back";

                    cout << "\nEnter Choice: ";
                    cin >> ch;

                    switch (ch)
                    {
                        case 1: m.addItem(); break;
                        case 2: m.viewMenu(); break;
                        case 3: m.updateItem(); break;
                        case 4: m.deleteItem(); break;
                        case 0: cout << "\nBack to Main Menu"; break;
                        default: cout << "\nInvalid Choice!";
                    }

                } while (ch != 0);

                break;
            }

            case 2:
            {
                int ch;

                do
                {
                    cout << "\n======= CUSTOMER PANEL =======";
                    cout << "\n1. View Menu";
                    cout << "\n2. Order Food";
                    cout << "\n0. Back";

                    cout << "\nEnter Choice: ";
                    cin >> ch;

                    switch (ch)
                    {
                        case 1: m.viewMenu(); break;
                        case 2: m.orderFood(); break;
                        case 0: cout << "\nThank You!"; break;
                        default: cout << "\nInvalid Choice!";
                    }

                } while (ch != 0);

                break;
            }

            case 0:
                cout << "\nThank You! \nVisit Again!";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 0);

    return 0;
}
