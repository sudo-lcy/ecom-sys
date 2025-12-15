#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// ===================== Global Data =========================

struct Product {
    int id;
    string name;
    double price;
    int stock;
    bool active;
};

struct CartItem {
    int productId;
    int quantity;
};

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

const string CUSTOMER_USERNAME = "user";
const string CUSTOMER_PASSWORD = "user123";

const int maxProducts = 100;
const int maxCartItems = 100;

Product products[maxProducts];
int productCount = 0;

CartItem cart[maxCartItems];
int cartItemCount = 0;

const string PRODUCTS_FILE = "products.txt";

// ===== Reading and writing products to text file via file handling ======

void saveProductsToFile() {
    ofstream out(PRODUCTS_FILE);
    if (!out) {
        cout << "Error: Unable to open " << PRODUCTS_FILE << " for writing.\n";
        return;
    }

    for (int i = 0; i < productCount; ++i) {
        // Save all products, including inactive ones, so IDs remain consistent.
        out << products[i].id << '|' << products[i].name << '|' << products[i].price << '|'
            << products[i].stock << '|' << (products[i].active ? 1 : 0) << '\n';
    }
}

void loadProductsFromFile() {
    ifstream in(PRODUCTS_FILE);
    string line;

    // This loop reads each line and store them as string
    while (getline(in, line) && productCount < maxProducts) {
        if (line.empty()) continue;

        stringstream ss(line);
        string part;
        Product p;

        // id
        if (!getline(ss, part, '|')) continue;
        p.id = stoi(part);  // This line converts string to integer

        // name
        if (!getline(ss, part, '|')) continue;
        p.name = part;

        // price
        if (!getline(ss, part, '|')) continue;
        p.price = stod(part); // This line converts string to double

        // stock
        if (!getline(ss, part, '|')) continue;
        p.stock = stoi(part); // This line converts string to integer

        // active
        if (!getline(ss, part, '|')) continue;
        p.active = (part == "1");

        products[productCount++] = p;
    }
}

// ===================== Product Management ======================

int findProductIndexById(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].active && products[i].id == id)
            return i;
    }
    return -1;
}

void displayAllProducts() {
    cout << "\n=== Product List ===\n";
    cout << "ID\tName\t\t\tPrice(RM)\tStock\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < productCount; i++) {
        if (products[i].active) {
            cout << products[i].id << "\t" << products[i].name << "\t\t"
                 << products[i].price << "\t\t" << products[i].stock << "\n";
        }
    }
}

void searchProductByName() {
    string key;
    cout << "\nEnter product name (or part of it) to search: ";
    cin.ignore();
    getline(cin, key);

    cout << "\n=== Search Results ===\n";
    bool found = false;
    for (int i = 0; i < productCount; i++) {
        string name = products[i].name, keyLower = key, nameLower = name;
        if (products[i].active) {
            for (int j = 0; j < (int)keyLower.size(); j++) {
                if (keyLower[j] >= 'A' && keyLower[j] <= 'Z')
                    keyLower[j] = keyLower[j] + ('a' - 'A');
            }
            for (int j = 0; j < (int)nameLower.size(); j++) {
                if (nameLower[j] >= 'A' && nameLower[j] <= 'Z')
                    nameLower[j] = nameLower[j] + ('a' - 'A');
            }

            if (nameLower.find(keyLower) != string::npos) {
                cout << "ID: " << products[i].id << " | Name: " << products[i].name
                     << " | Price: " << products[i].price << " | Stock: " << products[i].stock << "\n";
                found = true;
            }
        }
    }
    if (!found)
        cout << "No products matched your search.\n";
}

// ===================== Admin Specific Functions ================

void addProduct() {
    if (productCount >= maxProducts) {
        cout << "Cannot add more products. Maximum limit reached.\n";
        return;
    }
    Product p;
    p.id = productCount + 1;

    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter product price: ";
    cin >> p.price;
    cout << "Enter product stock: ";
    cin >> p.stock;
    p.active = true;

    products[productCount++] = p;
    saveProductsToFile();
    cout << "Product added successfully.\n";
}

void updateProduct() {
    int id, index, stock;
    double price;
    string name;

    cout << "\nEnter Product ID to update: ";
    cin >> id;
    index = findProductIndexById(id);
    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Updating product: " << products[index].name << "\n";
    cout << "Enter new name (leave blank to keep current): ";
    cin.ignore();
    getline(cin, name);

    if (name != "") {
        products[index].name = name;
    }

    cout << "Enter new price (-1 to keep current): ";
    cin >> price;
    if (price >= 0) {
        products[index].price = price;
    }

    cout << "Enter new stock (-1 to keep current): ";
    cin >> stock;
    if (stock >= 0) {
        products[index].stock = stock;
    }

    saveProductsToFile();
    cout << "Product updated successfully.\n";
}

void deleteProduct() {
    int id, index;
    cout << "\nEnter Product ID to delete: ";
    cin >> id;
    index = findProductIndexById(id);
    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    products[index].active = false;
    saveProductsToFile();
    cout << "Product deleted (marked inactive).\n";
}

void adminMenu() {
    int choice;
    do {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. View all products\n";
        cout << "2. Search product by name\n";
        cout << "3. Add new product\n";
        cout << "4. Update product\n";
        cout << "5. Delete product\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayAllProducts(); break;
            case 2: searchProductByName(); break;
            case 3: addProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 0: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

// ===================== Customer Specific Functions ============

int findCartItemIndexByProductId(int productId) {
    for (int i = 0; i < cartItemCount; i++) {
        if (cart[i].productId == productId) {
            return i; }
    }
    return -1;
}

void addToCart() {
    int id, productIndex, quantity, cartIndex;
    cout << "\nEnter Product ID to add to cart: ";
    cin >> id;
    productIndex = findProductIndexById(id);
    if (productIndex == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;
    if (quantity <= 0) {
        cout << "Quantity must be greater than 0.\n";
        return;
    }

    if (quantity > products[productIndex].stock) {
        cout << "Not enough stock. Available: " << products[productIndex].stock << "\n";
        return;
    }

    cartIndex = findCartItemIndexByProductId(id);
    if (cartIndex == -1) {
        if (cartItemCount >= maxCartItems) {
            cout << "Cart is full.\n";
            return;
        }
        cart[cartItemCount].productId = id;
        cart[cartItemCount].quantity = quantity;
        cartItemCount++;
    } else {
        if (cart[cartIndex].quantity + quantity > products[productIndex].stock) {
            cout << "Cannot add more than available stock. Current in cart: "
                 << cart[cartIndex].quantity
                 << ", Available: " << products[productIndex].stock << "\n";
            return;
        }
        cart[cartIndex].quantity += quantity;
    }

    cout << "Product added to cart.\n";
}

void viewCart() {
    double subtotal = 0.0;
    cout << "\n=== Shopping Cart ===\n";
    if (cartItemCount == 0) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "ID\tName\t\t\tQty\tPrice(RM)\tTotal(RM)\n";
    cout << "--------------------------------------------------------------------\n";
    for (int i = 0; i < cartItemCount; i++) {
        int productIndex = findProductIndexById(cart[i].productId);
        if (productIndex != -1) {
            double itemTotal = products[productIndex].price * cart[i].quantity;
            subtotal += itemTotal;
            cout << products[productIndex].id << "\t"
                 << products[productIndex].name << "\t\t"
                 << cart[i].quantity << "\t"
                 << products[productIndex].price << "\t\t"
                 << itemTotal << "\n";
        }
    }
    cout << "--------------------------------------------------------------------\n";
    cout << "Subtotal: " << subtotal << "\n";
}

// Calculate subtotal, discount, total
void calculateTotals(double &subtotal, double &discount, double &total) {
    subtotal = 0.0;
    for (int i = 0; i < cartItemCount; i++) {
        int productIndex = findProductIndexById(cart[i].productId);
        if (productIndex != -1) {
            subtotal += products[productIndex].price * cart[i].quantity;
        }
    }

    // Simple discount rule:
    // If subtotal >= 1000, 10% discount
    if (subtotal >= 1000) {
        discount = subtotal * 0.10;
    } else {
        discount = 0.0;
    }
    total = subtotal - discount;
}

void checkout() {
    if (cartItemCount == 0) {
        cout << "\nYour cart is empty. Add items before checkout.\n";
        return;
    }

    cout << "\n=== Order Summary ===\n";
    double subtotal, discount, total;
    calculateTotals(subtotal, discount, total);
    viewCart();
    cout << "Subtotal: " << subtotal << "\n";
    cout << "Discount: " << discount << "\n";
    cout << "Total: " << total << "\n";

    // Confirm checkout
    cout << "\nDo you want to proceed to payment? (y/n): ";
    char ans;
    cin >> ans;
    cin.ignore(10000, '\n');

    if (ans == 'y' || ans == 'Y') {
        // Simulate payment
        cout << "\nProcessing payment...\n";
        cout << "Payment successful! Thank you for your purchase.\n";

        // Reduce stock
        for (int i = 0; i < cartItemCount; i++) {
            int productIndex = findProductIndexById(cart[i].productId);
            if (productIndex != -1) {
                products[productIndex].stock -= cart[i].quantity;
                if (products[productIndex].stock < 0) {
                    products[productIndex].stock = 0;
                }
            }
        }

        // Persist updated stock
        saveProductsToFile();

        // Clear cart
        cartItemCount = 0;
    } else {
        cout << "Checkout cancelled.\n";
    }
}

void customerMenu() {
    int choice;
    do {
        cout << "\n===== CUSTOMER MENU =====\n";
        cout << "1. View all products\n";
        cout << "2. Search product by name\n";
        cout << "3. Add product to cart\n";
        cout << "4. View cart\n";
        cout << "5. Checkout\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayAllProducts(); break;
            case 2: searchProductByName(); break;
            case 3: addToCart(); break;
            case 4: viewCart(); break;
            case 5: checkout(); break;
            case 0: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

// ===================== Login System ============================

bool login(bool &isAdmin) 
{
    int role;
    string validity, username, password;
    cout << "===== LOGIN =====\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "0. Exit\n";

    do {
        cout << "Choose role: ";
        cin >> role;
        if (role < 0 || role > 2)
            cout << "Invalid role choice. Please try again.\n";
    } while (role < 0 || role > 2);

    cin.ignore();

    if (role == 1)
    {
        cout << "Admin login selected.\n";
        for ( int i = 0; i < 3; i++ ) 
        {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                cout << "Admin login successful.\n";
                validity = "valid";
                isAdmin = true;
                return true;
            } else {
                cout << "Invalid admin credentials. Please try again.\n";
                validity = "invalid";
            }
        }
    } 
    else if (role == 2)
    {
        cout << "Customer login selected.\n";
        for ( int i = 0; i < 3; i++ ) 
        {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            if (username == CUSTOMER_USERNAME && password == CUSTOMER_PASSWORD) {
                cout << "Customer login successful.\n";
                validity = "valid";
                isAdmin = false;
                return true;
            } else {
                cout << "Invalid customer credentials. Please try again.\n";
                validity = "invalid";
            }
        }
    }

    if (validity == "invalid") {
            cout << "Too many failed attempts.\n";
            return false;
    }
    
    return false;
}

// ===================== Main ====================================

int main() 
{
    bool isAdmin = false;
    char again;

    loadProductsFromFile();

    while (true) 
    {
        if (!login(isAdmin)) {
            cout << "\nGoodbye.\n";
            break;
        }

        if (isAdmin) {
            adminMenu();
        } else {
            customerMenu();
        }

        cout << "\nDo you want to login again? (y/n): ";
        cin >> again;
        
        if (again == 'n' || again == 'N') {
            cout << "Exiting system. Goodbye.\n";
            break;
        }
    }

    return 0;
}