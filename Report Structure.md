## 1. Understand what your program actually is

Your program is a **console-based e‑commerce management system** with:

- **Two roles**: Admin and Customer (login system).
- **File persistence**: `settings.txt` and `products.txt` to store configuration and products.
- **Admin features**:
  - View/search products
  - Add/update/delete (deactivate) products
  - Edit system settings (login attempts, discount, credentials, etc.)
- **Customer features**:
  - View/search products
  - Add items to cart, update cart
  - View cart and checkout (discount applied, stock is updated)

This should be the core “story” of your report.

---

## 2. More detailed Table of Contents (you can copy & adapt)

You can use this as your Table of Contents and then fill each section:

1. **Introduction**
   
   1.1 Background of the Project  
   1.2 Problem Statement  
   1.3 Objectives  
   1.4 Scope and Limitations  

2. **System Overview**
   
   2.1 Description of the E‑Commerce Management System  
   2.2 User Roles (Admin and Customer)  
   2.3 High-Level Program Flow  

3. **System Design**
   
   3.1 Data Structures  
   &nbsp;&nbsp;&nbsp;&nbsp;3.1.1 `Product` Structure  
   &nbsp;&nbsp;&nbsp;&nbsp;3.1.2 `CartItem` Structure  
   &nbsp;&nbsp;&nbsp;&nbsp;3.1.3 Global Variables (`products`, `cart`, `maxAttempts`, `discountThreshold`, `discountRate`, usernames/passwords)  
   3.2 File Storage Design  
   &nbsp;&nbsp;&nbsp;&nbsp;3.2.1 `settings.txt` Format  
   &nbsp;&nbsp;&nbsp;&nbsp;3.2.2 `products.txt` Format  
   3.3 Input Validation Strategy  

4. **Function Descriptions**
   
   4.1 Input Handling Functions  
   &nbsp;&nbsp;&nbsp;&nbsp;4.1.1 `readInt()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.1.2 `readDouble()`  

   4.2 File Handling Functions  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.1 `loadSettingsFromFile()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.2 `editSettingsFile()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.3 `saveProductsToFile()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.4 `loadProductsFromFile()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.5 `generateProductsFile()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.2.6 `generateSettingsFile()`  

   4.3 Product Management  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.1 `findProductIndexById(int id)`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.2 `displayAllProducts()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.3 `searchProductByName()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.4 `addProduct()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.5 `updateProduct()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.6 `deleteProduct()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.3.7 `adminMenu()`  

   4.4 Cart and Checkout  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.1 `findCartItemIndexByProductId(int productId)`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.2 `addToCart()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.3 `updateCart()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.4 `viewCart(double &subtotal)`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.5 `checkout()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.4.6 `customerMenu()`  

   4.5 Login and Initialization  
   &nbsp;&nbsp;&nbsp;&nbsp;4.5.1 `login(bool &isAdmin)`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.5.2 `initialize()`  
   &nbsp;&nbsp;&nbsp;&nbsp;4.5.3 `main()`  

5. **Interaction Between Components**
   
   5.1 Program Start and Initialization Sequence  
   5.2 Admin Workflow  
   5.3 Customer Workflow  
   5.4 Data Persistence Across Runs  

6. **Testing and Results** (optional but recommended)
   
   6.1 Test Cases for Admin Features  
   6.2 Test Cases for Customer Features  
   6.3 Sample Screens / Output  

7. **Conclusion**
   
   7.1 Summary of Features Implemented  
   7.2 Challenges and Lessons Learned  
   7.3 Future Enhancements  

---

## 3. How to explain each function “and how it works”

For each significant function, you can follow this pattern:

1. **Name & Purpose**  
   - Example:  
     - `addProduct()` – Allows the admin to create a new product by entering its name, price, and stock, then saves it to the products list and file.

2. **Inputs / Parameters**  
   - If it takes parameters (e.g. `findProductIndexById(int id)`), explain what they mean.

3. **Output / Return Value**  
   - Example:  
     - `findProductIndexById` returns the index in the `products` array, or `-1` if not found.  
     - `login(bool &isAdmin)` returns `true` if login is successful, `false` otherwise, and sets `isAdmin` to indicate the role.

4. **Algorithm / Step-by-step logic**  
   Describe what the function does in order, in plain language:

   Example: `loadProductsFromFile()`  
   - Open `products.txt`.  
   - If the file doesn’t exist, print an error message and load default products into the `products` array.  
   - If it exists, read each line, split by `|`, convert strings to the correct data types (id, name, price, stock, active), store them into the `products` array and increase `productCount`.  
   - Return `true` if loaded from file, `false` if default products were used.

   Example: `checkout()`  
   - Check if the cart is empty; if yes, print a message and return.  
   - Call `viewCart(subtotal)` to display items and calculate subtotal.  
   - If `subtotal >= discountThreshold`, calculate discount using `discountRate`.  
   - Compute total = subtotal − discount, and display totals.  
   - Ask user if they want to proceed with payment.  
   - If yes:
     - Print “processing payment”, simulate success.  
     - Deduct quantities from product stock.  
     - Save products to file.  
     - Clear `cartItemCount`.  
   - If no: print “Checkout cancelled.”

5. **How it connects to other functions / the system**  
   - Example: `adminMenu()` repeatedly shows options and calls `displayAllProducts()`, `searchProductByName()`, `addProduct()`, etc.  
   - `initialize()` calls `loadSettingsFromFile()`, `loadProductsFromFile()`, `generateSettingsFile()`, `generateProductsFile()`.

If you do this level of explanation for each major function group, you will meet the requirement “functions in the code and explanation of the function and how they work”.

---

## 4. What to actually write in each main section

### 1. Background / Introduction
- Explain that online shopping is common and managing products and customer purchases is important.
- State that your project is a **simple console-based e‑commerce system** for learning purposes.
- Mention that it supports admins and customers, with login credentials configurable in `settings.txt`.

### 2. System Overview
- Briefly describe what each role can do:
  - Admin: manage inventory and system settings.
  - Customer: browse products, maintain a cart, and checkout.
- Provide a simple text diagram or explanation of the program flow:
  - `main()` → `initialize()` → `login()` → `adminMenu()` or `customerMenu()` → repeat or exit.

### 3. System Design
Describe data structures:
- `struct Product { int id; string name; double price; int stock; bool active; };`
- `struct CartItem { int productId; int quantity; };`
Explain that products and cart are stored globally:
- `Product products[maxProducts]; int productCount;`
- `CartItem cart[maxCartItems]; int cartItemCount;`
Explain configuration variables (`maxAttempts`, `discountThreshold`, `discountRate`, usernames, passwords).

Describe file formats:
- `settings.txt` lines like `key=value`.
- `products.txt` lines like `id|name|price|stock|active`.

Explain input validation:
- `readInt()` reads a line, tries to convert to `int`, returns `-2` on invalid input.
- `readDouble()` similarly for `double`, returns `-2` on invalid input.
- Many functions use loops to check for negative values or out-of-range values and re-prompt.

### 4. Function Explanations
Group them as above (input, file, product management, cart, login, menus), and for each:
- Give purpose
- Show prototype
- Explain logic in words
- Mention any important conditions (e.g. stock must not go below zero, discount applies only above threshold)

---
