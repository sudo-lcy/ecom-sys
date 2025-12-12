# Cross-platform Makefile (works with GNU make on Linux/macOS/WSL/MSYS2/MinGW, and with Windows if GNU make is installed)
CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall
SRC = src/main.cpp
OUT = ecommerce

# Detect Windows
ifeq ($(OS),Windows_NT)
  OUT_EXE := $(OUT).exe
  RM = del /Q
else
  OUT_EXE := $(OUT)
  RM = rm -f
endif

.PHONY: all build clean

all: build

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT_EXE)

clean:
	-$(RM) $(OUT_EXE)
