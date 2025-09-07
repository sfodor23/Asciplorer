#pragma once

#include <iostream>

#include "../RealTimeStatistics/RealTimeStatistics.hpp"

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
    void PrintMap(int LowerVisibilityBondX, int HigherVisibilityBondX, int LowerVisibilityBondY, int HigherVisibilityBondY);
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
void Map<T>::PrintMap(int LowerVisibilityBondX, int HigherVisibilityBondX, int LowerVisibilityBondY, int HigherVisibilityBondY) {
    int LineIndex = 0;

    for (int y = LowerVisibilityBondY; y < HigherVisibilityBondY; y++) {
        for (int x = LowerVisibilityBondX; x < HigherVisibilityBondX; x++) {
            CurrentStatistics.PrintingLine[LineIndex] += MapArray[y][x];
            CurrentStatistics.PrintingLine[LineIndex] += " ";
        }
        
        LineIndex++;
    }
}