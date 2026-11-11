#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string>

using namespace std; 

// Abstract Base Class demonstrating Abstraction & enabling Polymorphism
class InventoryItem {
public:
    virtual void input() = 0;         // Pure virtual function
    virtual void display() const = 0; // Pure virtual function
    virtual ~InventoryItem() {}       // Virtual destructor
};

class Product : public InventoryItem {
private:
    int id;
    int quantity;
    string name;
    double price;

public:
    Product() : id(0), quantity(0), name(""), price(0.0) {}

    // Encapsulation: Getters and Setters
    int getId() const { return id; }
    int getQuantity() const { return quantity; }
    string getName() const { return name; }
    double getPrice() const { return price; }

    void setId(int i) { id = i; }
    void setQuantity(int q) { quantity = q; }
    void setName(const string& n) { name = n; }
    void setPrice(double p) { price = p; }

    void input() override {
        cout << "Enter product ID: ";
        cin >> id;
        cout << "Enter name (no spaces): ";
        cin >> name;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;
    }

    void display() const override {
        cout << left << setw(8) << id 
             << setw(20) << name 
             << setw(10) << quantity 
             << fixed << setprecision(2) << price << '\n';
    }
};

class Inventory {
private:
    Product products[100];
    int count;
    const string filename = "inventory.txt";

public:
    Inventory() {
        count = 0;
        loadFromFile();
    }

    void loadFromFile() {
        ifstream file(filename);
        count = 0;
        int id, qty;
        string nm;
        double pr;
        
        while (count < 100 && (file >> id >> nm >> qty >> pr)) {
            products[count].setId(id);
            products[count].setName(nm);
            products[count].setQuantity(qty);
            products[count].setPrice(pr);
            count++;
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (int i = 0; i < count; i++) {
            file << products[i].getId() << ' ' 
                 << products[i].getName() << ' ' 
                 << products[i].getQuantity() << ' ' 
                 << products[i].getPrice() << '\n';
        }
        file.close();
    }

    int findProduct(int id) const {
        for (int i = 0; i < count; i++) {
            if (products[i].getId() == id)
                return i;
        }
        return -1;
    }

    void addProduct() {
        if (count == 100) {
            cout << "Inventory is full!\n";
            return;
        }

        Product p;
        p.input();

        if (findProduct(p.getId()) != -1) {
            cout << "Product ID already exists!\n";
            return;
        }

        if (p.getQuantity() < 0 || p.getPrice() < 0) {
            cout << "Invalid quantity or price!\n";
            return;
        }

        products[count++] = p;
        saveToFile();
        cout << "Product added successfully!\n";
    }

    void displayProducts() const {
        cout << "\nID Name Quantity Price\n";
        cout << "---------------------------------------------\n";

        for (int i = 0; i < count; i++) {
            // Polymorphism: Using a base class pointer to invoke the derived class's display() method
            const InventoryItem* item = &products[i];
            item->display();
        }

        if (count == 0)
            cout << "Inventory is empty.\n";
    }

    void searchProduct() const {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        int i = findProduct(id);

        if (i != -1) {
            // Polymorphic call
            const InventoryItem* item = &products[i];
            item->display();
        } else {
            cout << "Product not found!\n";
        }
    }

    void updateQuantity() {
        int id, quantity;
        cout << "Enter product ID: ";
        cin >> id;

        int i = findProduct(id);

        if (i == -1) {
            cout << "Product not found!\n";
            return;
        }

        cout << "Enter new quantity: ";
        cin >> quantity;

        if (quantity < 0) {
            cout << "Invalid quantity!\n";
            return;
        }

        products[i].setQuantity(quantity);
        saveToFile();
        cout << "Quantity updated successfully!\n";
    }

    void removeProduct() {
        int id;
        cout << "Enter product ID: ";
        cin >> id;

        int i = findProduct(id);

        if (i == -1) {
            cout << "Product not found!\n";
            return;
        }

        for (int j = i; j < count - 1; j++) {
            products[j] = products[j + 1];
        }

        count--;
        saveToFile();
        cout << "Product removed successfully!\n";
    }
};

int main() {
    Inventory inv;
    int choice;

    do {
        cout << "\n===== SUPERMARKET INVENTORY =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Quantity\n";
        cout << "5. Remove Product\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inv.addProduct(); break;
            case 2: inv.displayProducts(); break;
            case 3: inv.searchProduct(); break;
            case 4: inv.updateQuantity(); break;
            case 5: inv.removeProduct(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
