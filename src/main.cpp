#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

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

const int maxProducts = 100;
const int maxCartItems = 100;

Product products[maxProducts];
int productCount = 0;

CartItem cart[maxCartItems];
int cartItemCount = 0;

string ADMIN_USERNAME, ADMIN_PASSWORD, CUSTOMER_USERNAME, CUSTOMER_PASSWORD;
int maxAttempts;
double discountThreshold, discountRate;

// ===================== Simple input validation function ====================

int readInt()
{
    string input;
    getline(cin, input);
    try {
        return stoi(input);
    } catch (const invalid_argument&) {
        return -2;  // Return -2 for invalid input
    }
}

int readDouble()
{
    string input;
    getline(cin, input);
    try {
        return stod(input);
    } catch (const invalid_argument&) {
        return -2;  // Return -2 for invalid input
    }
}

// ===== File handling: Load and Save Settings & Products =====

bool loadSettingsFromFile() {
    ifstream in("settings.txt");
    string line;

    if (!in) {
        cout << "Error: Unable to open settings.txt. Using default settings...\n";
        // Set default settings
        maxAttempts = 3;
        discountThreshold = 1000.0;
        discountRate = 0.10;
        ADMIN_USERNAME = "admin";
        ADMIN_PASSWORD = "admin123";
        CUSTOMER_USERNAME = "user";
        CUSTOMER_PASSWORD = "user123";
        return false;
    }

    while (getline(in, line)) {
        stringstream ss(line);
        string key, input;

        if (getline(ss, key, '=') && getline(ss, input)) {
            if (key == "maxAttempts") {
                maxAttempts = stoi(input);
            } else if (key == "discountThreshold") {
                discountThreshold = stod(input);
            } else if (key == "discountRate") {
                discountRate = stod(input);
            } else if (key == "adminUsername") {
                ADMIN_USERNAME = input;
            } else if (key == "adminPassword") {
                ADMIN_PASSWORD = input;
            } else if (key == "customerUsername") {
                CUSTOMER_USERNAME = input;
            } else if (key == "customerPassword") {
                CUSTOMER_PASSWORD = input;
            }
        }
    }
    return true;
}

void editSettingsFile() {
    int choice;
    
    do{
    cout << "\n======== Current Settings ========\n";
    cout << "1. Max Login Attempts: " << maxAttempts << "\n";
    cout << "2. Discount Threshold: " << discountThreshold << "\n";
    cout << "3. Discount Rate: " << discountRate << "\n";
    cout << "4. Admin Username: " << ADMIN_USERNAME << "\n";
    cout << "5. Admin Password: " << ADMIN_PASSWORD << "\n";
    cout << "6. Customer Username: " << CUSTOMER_USERNAME << "\n";
    cout << "7. Customer Password: " << CUSTOMER_PASSWORD << "\n";
    cout << "==================================\n";
    cout << "Enter the number of the setting you want to change (0 to exit): ";
    choice = readInt();

    switch (choice) {
        case 1:
            cout << "Enter new Max Login Attempts: ";
            maxAttempts = readInt();
            break;
        case 2:
            do{
                cout << "Enter new Discount Threshold: ";
                discountThreshold = readDouble();
                if (discountThreshold < 0)
                    cout << "Invalid Input. Please enter again.\n";
            } while (discountThreshold < 0);
            break;
        case 3:
            do{
                cout << "Enter new Discount Rate (e.g., 0.10 for 10%): ";
                discountRate = readDouble();
                if (discountRate < 0 || discountRate > 1)
                    cout << "Invalid Input. Please enter again.\n";
            } while (discountRate < 0 || discountRate > 1);
            break;
        case 4:
            cout << "Enter new Admin Username: ";
            getline(cin, ADMIN_USERNAME);
            break;
        case 5:
            cout << "Enter new Admin Password: ";
            getline(cin, ADMIN_PASSWORD);
            break;
        case 6:
            cout << "Enter new Customer Username: ";
            getline(cin, CUSTOMER_USERNAME);
            break;
        case 7:
            cout << "Enter new Customer Password: ";
            getline(cin, CUSTOMER_PASSWORD);
            break;
        case 0:
            cout << "Exiting settings edit.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    } while (choice != 0);

    // Write updated settings to file
    ofstream out("settings.txt");

    if (!out) {
        cout << "Error: Unable to open settings.txt for writing.\n";
        return;
    }

    out << "maxAttempts=" << maxAttempts << "\n";
    out << "discountThreshold=" << discountThreshold << "\n";
    out << "discountRate=" << discountRate << "\n";
    out << "adminUsername=" << ADMIN_USERNAME << "\n";
    out << "adminPassword=" << ADMIN_PASSWORD << "\n";
    out << "customerUsername=" << CUSTOMER_USERNAME << "\n";
    out << "customerPassword=" << CUSTOMER_PASSWORD << "\n";
}

void saveProductsToFile() {
    ofstream out("products.txt");
    if (!out) {
        cout << "Error: Unable to open products.txt for writing.\n";
        return;
    }

    for (int i = 0; i < productCount; ++i) {
        // Save all products, including inactive ones, so IDs remain consistent.
        out << products[i].id << '|' << products[i].name << '|' << products[i].price << '|'
            << products[i].stock << '|' << (products[i].active ? 1 : 0) << '\n';
    }
}

bool loadProductsFromFile() {
    ifstream in("products.txt");
    string line;

    if(!in) {
        cout << "Error: Unable to open products.txt. Using default product list...\n\n";
        products[0] = {1, "Phone Case",         35, 20, true};
        products[1] = {2, "Airpods    ",        90, 20, true};
        products[2] = {3, "ScreenProtector",    45, 20, true};
        products[3] = {4, "Phone Holder",       67, 20, true};
        products[4] = {5, "Powerbank",          110, 20, true};
        products[5] = {6, "Charging Cable",     30, 20, true};
        productCount = 6;
        return false;
    }

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
    return true;
}

void generateProductsFile() {
    ifstream prodIn("products.txt");
    if (!prodIn) {
        ofstream prodOut("products.txt");
        prodOut << "1|Phone Case|35|20|1\n";
        prodOut << "2|Airpods    |90|20|1\n";
        prodOut << "3|ScreenProtector|45|20|1\n";
        prodOut << "4|Phone Holder|67|20|1\n";
        prodOut << "5|Powerbank|110|20|1\n";
        prodOut << "6|Charging Cable|30|20|1\n";
        prodOut.close();
    }
    prodIn.close();
    cout << "products.txt generated successfully...\n\n";
}

void generateSettingsFile() {
    ifstream settingsIn("settings.txt");
    if (!settingsIn) {
        ofstream settingsOut("settings.txt");
        settingsOut << "maxAttempts=3\n";
        settingsOut << "discountThreshold=1000.0\n";
        settingsOut << "discountRate=0.10\n";
        settingsOut << "adminUsername=admin\n";
        settingsOut << "adminPassword=admin123\n";
        settingsOut << "customerUsername=user\n";
        settingsOut << "customerPassword=user123\n";
        settingsOut.close();
    }
    settingsIn.close();
    cout << "settings.txt generated successfully...\n\n";
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
    cout << "\n======================= Product List =======================\n";
    cout << "ID\tName\t\t\tPrice(RM)\tStock\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < productCount; i++) {
        if (products[i].active) {
            cout << products[i].id << "\t" << products[i].name << "\t\t"
                 << products[i].price << "\t\t" << products[i].stock << "\n";
        }
    }
    cout << "============================================================\n";
}

void searchProductByName() {
    string key;
    cout << "\nEnter product name (or part of it) to search: ";
    getline(cin, key);

    cout << "\n==================== Search Results ====================\n";
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
    if (!found){
        cout << "No products matched your search.\n";}
    
    cout << "=========================================================\n";
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

    do{
        cout << "Enter product price: ";
        p.price = readDouble();
        if (p.price < 0)
            cout << "Invalid Input. Please enter again.\n";
    } while (p.price < 0);
    
    do{
        cout << "Enter product stock: ";
        p.stock = readInt();
        if (p.stock < 0)
            cout << "Invalid input. Please enter again.\n";
    } while (p.stock < 0);
    
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
    id = readInt();
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

    do {
    cout << "Enter new price (-1 to keep current): ";
    price = readDouble();
    if (price < 0 && price != -1)
        cout << "Invalid input. Please enter again.\n";
    } while (price < 0 && price != -1);

    if (price >= 0) {
        products[index].price = price;
    }


    do {
    cout << "Enter new stock (-1 to keep current): ";
    stock = readInt();
    if (stock < 0 && stock != -1)
        cout << "Invalid input. Please enter again.\n";
    } while (stock < 0 && stock != -1);

    if (stock >= 0) {
        products[index].stock = stock;
    }

    saveProductsToFile();
    cout << "Product updated successfully.\n";
}

void deleteProduct() {
    int id, index;
    cout << "\nEnter Product ID to delete: ";
    id = readInt();
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
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. View all products\n";
        cout << "2. Search product by name\n";
        cout << "3. Add new product\n";
        cout << "4. Update product\n";
        cout << "5. Delete product\n";
        cout << "6. Edit system settings\n";
        cout << "0. Logout\n";
        cout << "===============================\n";
        cout << "Enter your choice: ";
        choice = readInt();

        switch (choice) {
            case 1: displayAllProducts(); break;
            case 2: searchProductByName(); break;
            case 3: addProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: editSettingsFile(); break;
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
    id = readInt();
    productIndex = findProductIndexById(id);
    if (productIndex == -1) {
        cout << "Product not found.\n";
        return;
    }

    do {
        cout << "Enter quantity: ";
        quantity = readInt();
        if (quantity <= 0) {
            cout << "Invalid input. Please try again.\n";
    }} while (quantity <= 0);

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

void updateCart() {
    int id, productIndex, cartIndex, quantity;

    cout << "\nEnter Cart Item ID to update: ";
    id = readInt();
    productIndex = findProductIndexById(id);
    cartIndex = findCartItemIndexByProductId(id);
    if (cartIndex == -1) {
        cout << "Item not found in cart.\n";
        return;
    }

    do {
    cout << "Enter new quantity: ";
    quantity = readInt();
    if (quantity < 0)
        cout << "Invalid input. Please enter again.\n";
    } while (quantity < 0);

    if (quantity > products[productIndex].stock) {
            cout << "Cannot add more than available stock. Current in cart: "
                 << cart[cartIndex].quantity
                 << ", Available: " << products[productIndex].stock << "\n";
            return;
    }
    
    cart[cartIndex].quantity = quantity;

    if (cart[cartIndex].quantity == 0) {
        // Remove item from cart
        for (int i = cartIndex; i < cartItemCount - 1; i++) {
            cart[i] = cart[i + 1];
        }
        cartItemCount--;
        cout << products[productIndex].name << " is removed from cart.\n";
        return;
    }

    cout << "Quantity for " << products[productIndex].name << " updated in cart.\n";
}

void viewCart(double &subtotal) {
    subtotal = 0.0;
    if (cartItemCount == 0) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "ID\tName\t\t\tQty\tPrice(RM)\tTotal(RM)\n";
    cout << "-------------------------------------------------------------------\n";
    for (int i = 0; i < cartItemCount; i++) {
        int productIndex = findProductIndexById(cart[i].productId);
        if (productIndex != -1 && cart[i].quantity > 0) {
            double itemTotal = products[productIndex].price * cart[i].quantity;
            subtotal += itemTotal;
            cout << products[productIndex].id << "\t"
                 << products[productIndex].name << "\t\t"
                 << cart[i].quantity << "\t"
                 << products[productIndex].price << "\t\t"
                 << itemTotal << "\n";
        }
    }
    cout << "-------------------------------------------------------------------\n";
    cout << "\t\t\t\t\tSubtotal: \t" << subtotal << "\n";
}

void checkout() {
    double subtotal, discount, total;
    char ans;

    if (cartItemCount == 0) {
        cout << "\nYour cart is empty. Add items before checkout.\n";
        return;
    }

    cout << "\n========================== Order Summary ==========================\n";
  
    viewCart(subtotal);

    if (subtotal >= discountThreshold) {
        discount = subtotal * discountRate;
    } else {
        discount = 0.0;
    }
    total = subtotal - discount;

    cout << "\t\t\t\t\tDiscount: \t" << discount << "\n";
    cout << "\t\t\t\t\tTotal: \t\t" << total << "\n";

    cout << "===================================================================\n";

    // Confirm checkout
    cout << "\nDo you want to proceed to payment?\n(Y/y to proceed, any other key to cancel): ";
    cin >> ans;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    double subtotal;
    do {
        cout << "\n======= CUSTOMER MENU =======\n";
        cout << "1. View all products\n";
        cout << "2. Search product by name\n";
        cout << "3. Add product to cart\n";
        cout << "4. Update cart item quantity\n";
        cout << "5. View cart\n";
        cout << "6. Checkout\n";
        cout << "0. Logout\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        choice = readInt();

        switch (choice) {
            case 1: displayAllProducts(); break;
            case 2: searchProductByName(); break;
            case 3: addToCart(); break;
            case 4: updateCart(); break;
            case 5: if (cartItemCount != 0){
                    cout << "\n========================== Shopping Cart ==========================\n";}
                    viewCart(subtotal); 
                    if (cartItemCount != 0){
                    cout << "===================================================================\n";}
                    break;
            case 6: checkout(); break;
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
    do {
        cout << "===== LOGIN =====\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "0. Exit\n";
        cout << "=================\n";
        cout << "Choose role: ";
        role = readInt();
        if (role < 0 || role > 2)
            cout << "\nInvalid role choice. Please try again.\n\n";
    } while (role < 0 || role > 2);

    if (role == 1)
    {
        cout << "Admin login selected.\n\n";
        for ( int i = 0; i < maxAttempts; i++ ) 
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
        cout << "Customer login selected.\n\n";
        for ( int i = 0; i < maxAttempts; i++ ) 
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

    if (validity == "invalid")
            cout << "Too many failed attempts.\n";
    return false;
}

void initialize(){
    cout << "Initializing E-Commerce Management System...\n";
    cout << "Loading settings and products data from external files...\n";

    bool settingsLoaded = loadSettingsFromFile();
    bool productsLoaded = loadProductsFromFile();

    if (settingsLoaded && productsLoaded) {
        cout << "Settings and products data loaded successfully...\n\n";
    }

    if (!settingsLoaded) {
        cout << "settings.txt not found. Generating default settings file...\n";
        generateSettingsFile();
    }

    if (!productsLoaded) {
        cout << "products.txt not found. Generating default products file...\n";
        generateProductsFile();
    }

cout << R"(              ▄▄                            
              ██                            
██   ██ ▄█▀█▄ ██ ▄████ ▄███▄ ███▄███▄ ▄█▀█▄ 
██ █ ██ ██▄█▀ ██ ██    ██ ██ ██ ██ ██ ██▄█▀ 
 ██▀██  ▀█▄▄▄ ██ ▀████ ▀███▀ ██ ██ ██ ▀█▄▄▄                                  
)" << endl;

cout << "How to use the system:\n";
cout << "1. Login as Admin or Customer using the default credentials if settings.txt was just generated.\n";
cout << "2. Admin can manage products and edit system settings.\n";
cout << "3. Customer can browse products, manage cart, and checkout.\n";
cout << "4. products.txt and settings.txt are used to persist data across sessions.\n";
cout << "5. id|name|price|stock|active format is used in products.txt for each product.\n";
cout << "6. Enjoy using the E-Commerce Management System!\n\n";

cout << "Github Repository: https://github.com/elseawhy/ecom-sys\n\n";
}

// ===================== Main ====================================

int main() 
{
    bool isAdmin = false;
    char again;

    initialize();

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

        cout << "\nDo you want to login again?\n(N/n to exit, any other key to continue): ";
        cin >> again;
        cout << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (again == 'n' || again == 'N') {
            cout << "Exiting system. Goodbye.\n";
            break;
        }
    }

    return 0;
}