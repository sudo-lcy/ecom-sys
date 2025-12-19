# Online E-Commerce System for Small Businesses

Simple C++ console-based e-commerce system for course work.  
Features:
- Admin and Customer login
- Product array reading from/writing to a text file via file handling
- Display all avialable product
- Search product by name
- Shopping cart using array
- Checkout and simulated payment confirmation
- Simple receipt after checkout
- Loops, conditionals, modular functions, input validation

Repository layout
- /src
  - main.cpp         -> the main program
- /assets
  - markdown/*       -> Mermaid syntax codes
  - image/*          -> Flowchart images
- Makefile           -> build helper
- CMakeLists.txt     -> cross-platform build
- build.bat          -> Windows batch build
- build.ps1          -> PowerShell build
- .github/workflows/ci.yml -> CI to build on Linux/macos/windows
- .gitignore
- CONTRIBUTING.md

Build & run (Linux / macOS / WSL)
1. Clone the repo:
   git clone <repo-url>
2. Build with make:
   make
   or
   g++ -std=c++17 src/main.cpp -o ecommerce
3. Or use CMake (recommended cross-platform):
   mkdir build && cd build
   cmake ..
   cmake --build .
4. Run:
   ./ecommerce   (or ecommerce.exe on Windows)

Run instructions
- Open a terminal in the directory containing ecommerce
- Make sure products.txt exists in the same directory before running
- Do ./ecommerce to launch the program

Notes
- For Windows users without make/CMake installed, use build.bat or build.ps1 (requires g++ or MSVC).
- CI is configured to build with CMake on Linux, macOS and Windows.
