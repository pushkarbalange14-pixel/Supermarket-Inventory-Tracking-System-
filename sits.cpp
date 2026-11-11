#include <iostream> 
#include <fstream> 
#include <iomanip> 
using namespace std; 
 
class Product { 
public: 
 int id, quantity; 
 string name; 
 double price; 
 
 void input() { 
 cout << "Enter product ID: "; 
 cin >> id; 
 cout << "Enter name (no spaces): "; 
 cin >> name; 
 cout << "Enter quantity: "; 
 cin >> quantity; 
 cout << "Enter price: "; 
 cin >> price; 
 } 
 
 void display() { 
 cout << left << setw(8) << id 
 << setw(20) << name 
 << setw(10) << quantity 
 << fixed << setprecision(2) << price << '\n'; 
 } 
}; 
 
class Inventory { 
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
 while (count < 100 && 
 file >> products[count].id 
 >> products[count].name 
 >> products[count].quantity 
 >> products[count].price) { 
 count++; 
 }
11
 
 file.close(); 
 } 
 
 void saveToFile() { 
 ofstream file(filename); 
 
 for (int i = 0; i < count; i++) 
 file << products[i].id << ' ' 
 << products[i].name << ' ' 
 << products[i].quantity << ' ' 
 << products[i].price << '\n'; 
 
 file.close(); 
 } 
 
 int findProduct(int id) { 
 for (int i = 0; i < count; i++) 
 if (products[i].id == id) 
 return i; 
 
 return -1; 
 } 
 
 void addProduct() { 
 if (count == 100) { 
 cout << "Inventory is full!\n"; 
 return; 
 } 
 
 Product p; 
 p.input(); 
 
 if (findProduct(p.id) != -1) { 
 cout << "Product ID already exists!\n"; 
 return; 
 } 
 
 if (p.quantity < 0 || p.price < 0) { 
 cout << "Invalid quantity or price!\n"; 
 return; 
 } 
 
 products[count++] = p; 
 saveToFile(); 
 cout << "Product added successfully!\n"; 
 } 
 
 void displayProducts() { 
 cout << "\nID Name Quantity Price\n"; 
 cout << "---------------------------------------------\n"; 
 
 for (int i = 0; i < count; i++) 
 products[i].display();

if (count == 0) 
 cout << "Inventory is empty.\n"; 
 } 
 
 void searchProduct() { 
 int id; 
 cout << "Enter product ID: "; 
 cin >> id; 
 
 int i = findProduct(id); 
 
 if (i != -1) 
 products[i].display(); 
 else 
 cout << "Product not found!\n"; 
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
 
 products[i].quantity = quantity; 
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
 
 for (int j = i; j < count - 1; j++)

products[j] = products[j + 1]; 
 
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
