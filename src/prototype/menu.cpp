#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

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

const int maxProducts = 100;
const int maxCartItems = 100;

Product products[maxProducts];
int productCount = 0;

CartItem cart[maxCartItems];
int cartItemCount = 0;

// ===================== Product Management ======================

int findProductIndexById(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].active && products[i].id == id)
            return i;
    }
    return -1;
}

void arrayProducts() {
    // Initialize at least 5 products
    products[0] = {1, "Phone Case",         2500.00, 10, true};
    products[1] = {2, "Airpods    ",        1200.00, 15, true};
    products[2] = {3, "ScreenProtector",    150.00, 25, true};
    products[3] = {4, "Phone Holder",       300.00, 20, true};
    products[4] = {5, "Powerbank",          80.00, 30, true};
    products[5] = {6, "Charging Cable",     50.00, 40, true};
    productCount = 6;
}

void displayAllProducts() {
    cout << "\n=== Product List ===\n";
    cout << "ID\tName\t\t\tPrice\tStock\n";
    cout << "---------------------------------------------\n";
    for (int i = 0; i < productCount; i++) {
        if (products[i].active) {
            cout << products[i].id << "\t" << products[i].name << "\t\t" << products[i].price << "\t" << products[i].stock << "\n";
        }
    }
}

void searchProductByName() {
    string key;
    cout << "\nEnter product name (or part of it) to search: ";
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
                cout << "ID: " << products[i].id
                     << " | Name: " << products[i].name
                     << " | Price: " << products[i].price
                     << " | Stock: " << products[i].stock << "\n";
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
    getline(cin, p.name);
    cout << "Enter product price: ";
    cin >> p.price;
    cout << "Enter product stock: ";
    cin >> p.stock;
    p.active = true;

    products[productCount++] = p;
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
    cout << "Product deleted (marked inactive).\n";
}

void adminMenu() {
    int choice;
    cout << "\n===== ADMIN MENU =====\n";
    cout << "1. View all products\n";
    cout << "2. Search product by name\n";
    cout << "3. Add new product\n";
    cout << "4. Update product\n";
    cout << "5. Delete product\n";
    cout << "0. Logout\n";
    do {
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

    cout << "ID\tName\t\tQty\tPrice\tTotal\n";
    cout << "-------------------------------------------------\n";
    for (int i = 0; i < cartItemCount; i++) {
        int productIndex = findProductIndexById(cart[i].productId);
        if (productIndex != -1) {
            double itemTotal = products[productIndex].price * cart[i].quantity;
            subtotal += itemTotal;
            cout << products[productIndex].id << "\t"
                 << products[productIndex].name << "\t\t"
                 << cart[i].quantity << "\t"
                 << products[productIndex].price << "\t"
                 << itemTotal << "\n";
        }
    }
    cout << "-------------------------------------------------\n";
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

        // Clear cart
        cartItemCount = 0;
    } else {
        cout << "Checkout cancelled.\n";
    }
}

void customerMenu() {
    int choice;
    cout << "\n===== CUSTOMER MENU =====\n";
    cout << "1. View all products\n";
    cout << "2. Search product by name\n";
    cout << "3. Add product to cart\n";
    cout << "4. View cart\n";
    cout << "5. Checkout\n";
    cout << "0. Logout\n";
    do {
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