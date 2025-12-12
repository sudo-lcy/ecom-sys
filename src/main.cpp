#include <iostream>
#include <string>
#include <iomanip>

// Simple e-commerce console app using arrays only.
// Conventions: maximum 5 products, cart capacity 20 items.

const int PRODUCT_COUNT = 5;
const int CART_CAPACITY = 20;

// Product data (arrays)
std::string productNames[PRODUCT_COUNT] = {
    "Classic Notebook",
    "Wireless Mouse",
    "Coffee Mug",
    "Standing Lamp",
    "Bluetooth Speaker"
};
double productPrices[PRODUCT_COUNT] = {9.99, 19.99, 7.50, 29.95, 45.00};
int productStock[PRODUCT_COUNT] = {10, 8, 15, 5, 3};

// Cart storage: store product indices and quantities
int cartProductIdx[CART_CAPACITY];
int cartQuantity[CART_CAPACITY];
int cartSize = 0;

// Helper: read integer with validation
int readInt(const std::string &prompt, int minVal, int maxVal) {
    while (true) {
        std::cout << prompt;
        int value;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (value < minVal || value > maxVal) {
            std::cout << "Please enter a number between " << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return value;
    }
}

// Display list of products
void showProducts() {
    std::cout << "\nAvailable products:\n";
    std::cout << std::left << std::setw(4) << "ID" << std::setw(25) << "Name" 
              << std::setw(8) << "Price" << std::setw(8) << "Stock" << "\n";
    for (int i = 0; i < PRODUCT_COUNT; ++i) {
        std::cout << std::left << std::setw(4) << i
                  << std::setw(25) << productNames[i]
                  << std::setw(8) << std::fixed << std::setprecision(2) << productPrices[i]
                  << std::setw(8) << productStock[i] << "\n";
    }
}

// View product details
void viewProductDetails() {
    int id = readInt("Enter product ID to view details (or -1 to cancel): ", -1, PRODUCT_COUNT - 1);
    if (id == -1) return;
    std::cout << "\nProduct details:\n";
    std::cout << "Name: " << productNames[id] << "\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << productPrices[id] << "\n";
    std::cout << "Available quantity: " << productStock[id] << "\n";
}

// Add product to cart
void addToCart() {
    if (cartSize >= CART_CAPACITY) {
        std::cout << "Cart is full. Cannot add more items.\n";
        return;
    }
    int id = readInt("Enter product ID to add to cart (or -1 to cancel): ", -1, PRODUCT_COUNT - 1);
    if (id == -1) return;
    if (productStock[id] == 0) {
        std::cout << "Sorry, that product is out of stock.\n";
        return;
    }
    int maxQty = productStock[id];
    int qty = readInt("Enter quantity: ", 1, maxQty);
    // If product already in cart, increase quantity
    for (int i = 0; i < cartSize; ++i) {
        if (cartProductIdx[i] == id) {
            if (cartQuantity[i] + qty > productStock[id]) {
                std::cout << "Cannot add that many. Only " << (productStock[id] - cartQuantity[i]) << " left available considering your cart.\n";
                return;
            }
            cartQuantity[i] += qty;
            std::cout << "Added " << qty << " to existing cart item.\n";
            return;
        }
    }
    // New cart entry
    cartProductIdx[cartSize] = id;
    cartQuantity[cartSize] = qty;
    ++cartSize;
    std::cout << "Added to cart.\n";
}

// Show cart and compute totals
double computeSubtotal() {
    double subtotal = 0.0;
    for (int i = 0; i < cartSize; ++i) {
        int idx = cartProductIdx[i];
        subtotal += productPrices[idx] * cartQuantity[i];
    }
    return subtotal;
}

void showCart() {
    if (cartSize == 0) {
        std::cout << "\nYour cart is empty.\n";
        return;
    }
    std::cout << "\nYour cart:\n";
    std::cout << std::left << std::setw(25) << "Item" << std::setw(8) << "Qty" << std::setw(10) << "Unit" << std::setw(10) << "Total\n";
    for (int i = 0; i < cartSize; ++i) {
        int idx = cartProductIdx[i];
        std::cout << std::left << std::setw(25) << productNames[idx]
                  << std::setw(8) << cartQuantity[i]
                  << std::setw(10) << std::fixed << std::setprecision(2) << productPrices[idx]
                  << std::setw(10) << productPrices[idx] * cartQuantity[i] << "\n";
    }
    double subtotal = computeSubtotal();
    double discount = 0.0;
    // Example discount rule: 10% off if subtotal >= $100
    if (subtotal >= 100.0) {
        discount = subtotal * 0.10;
    }
    double taxRate = 0.08; // 8%
    double tax = (subtotal - discount) * taxRate;
    double total = subtotal - discount + tax;

    std::cout << "\nSubtotal: $" << std::fixed << std::setprecision(2) << subtotal << "\n";
    if (discount > 0.0) {
        std::cout << "Discount: -$" << discount << " (10% off orders >= $100)\n";
    }
    std::cout << "Tax (8%): $" << tax << "\n";
    std::cout << "Total: $" << total << "\n";
}

// Checkout and confirm payment (simulation)
void checkout() {
    if (cartSize == 0) {
        std::cout << "Cart is empty. Add items before checkout.\n";
        return;
    }
    showCart();
    std::cout << "\nProceed to payment? (1 = yes, 0 = no): ";
    int choice;
    if (!(std::cin >> choice) || (choice != 0 && choice != 1)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid selection. Cancelling checkout.\n";
        return;
    }
    if (choice == 0) {
        std::cout << "Checkout cancelled.\n";
        return;
    }
    // Simulate stock deduction
    for (int i = 0; i < cartSize; ++i) {
        int idx = cartProductIdx[i];
        productStock[idx] -= cartQuantity[i];
    }
    // Simulated payment confirmation
    std::cout << "Processing payment...\n";
    std::cout << "Payment confirmed. Thank you for your purchase!\n";
    // Clear cart
    cartSize = 0;
}

// Main menu loop
void showMenu() {
    std::cout << "\n=== Small Biz E-Commerce ===\n";
    std::cout << "1) Show products\n";
    std::cout << "2) View product details\n";
    std::cout << "3) Add product to cart\n";
    std::cout << "4) View cart\n";
    std::cout << "5) Checkout\n";
    std::cout << "0) Exit\n";
}

int main() {
    while (true) {
        showMenu();
        int choice = readInt("Choose an option: ", 0, 5);
        switch (choice) {
            case 1:
                showProducts();
                break;
            case 2:
                viewProductDetails();
                break;
            case 3:
                showProducts();
                addToCart();
                break;
            case 4:
                showCart();
                break;
            case 5:
                checkout();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Unknown option.\n";
        }
    }
    return 0;
}
