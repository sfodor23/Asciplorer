#pragma once

#include <iostream>

template <typename T>
class Map {
public:
    int XDimension;
    int YDimension;
    double XMidPoint;
    double YMidPoint;
    T** MapArray = nullptr;

    Map(int XDimension, int YDimension);
    
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    ~Map();

    void GenerateMapArray();
    void ManualMapArrayDeletion();
    void PrintMap();
};

template <typename T>
Map<T>::Map(int XDimension, int YDimension) {
    this->XDimension = XDimension;
    this->YDimension = YDimension;
    this->XMidPoint = (XDimension/2) - 1;
    this->YMidPoint = (YDimension/2) - 1;
    GenerateMapArray();
}

template <typename T>
Map<T>::~Map() {
    if (MapArray != nullptr) {
        for (int y = 0; y < YDimension; y++) {
            delete[] MapArray[y];
        }
        delete[] MapArray;
        MapArray = nullptr;
    }
}

template <typename T>
void Map<T>::GenerateMapArray() {
    ManualMapArrayDeletion();

    MapArray = new T * [YDimension];

    for (int y = 0; y < YDimension; y++) {
        MapArray[y] = new T [XDimension];
    }

    for (int y = 0; y < YDimension; y++) {
        for (int x = 0; x < XDimension; x++) {
            MapArray[y][x] = T();
        }
    }
}

template <typename T>
void Map<T>::ManualMapArrayDeletion() {
    if (MapArray != nullptr) {
        for (int y = 0; y < YDimension; y++) {
            delete[] MapArray[y];
        }
        delete[] MapArray;
        MapArray = nullptr;
    }
}

template <typename T>
void Map<T>::PrintMap() {
    std::cout << "\n";
        
    int CurrentFirstDigit = 0;
        
    for (int x = 0; x < XDimension; x++) {
        if ((x + 1) % 10 == 0) {
            CurrentFirstDigit = (x + 1)/10;
        }
        if (CurrentFirstDigit == 0) {
            std::cout << "  ";
        }
        else {
            std::cout << CurrentFirstDigit << " ";
        }
    }

    std::cout << "\n";
        
    for (int x = 0; x < XDimension; x++) {
        std::cout << (x + 1) % 10 << " ";
    }
        
    std::cout << "\n";
        
    for (int x = 0; x < XDimension; x++) {
        std::cout << "_ ";
    } 
        
    std::cout << "\n\n";
        
    for (int y = 0; y < YDimension; y++) {
        for (int x = 0; x < XDimension; x++) {
            std::cout << MapArray[y][x] << " ";
        }
        std::cout << " |" << y + 1 << "\n";
    }
}