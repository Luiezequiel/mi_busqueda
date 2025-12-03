@echo off
g++ -std=c++20 src/main.cpp src/FileHandler.cpp src/InvertedIndex.cpp src/SearchEngine.cpp -o mi_busqueda.exe
.\mi_busqueda.exe