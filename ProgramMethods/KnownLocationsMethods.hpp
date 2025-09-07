#pragma once

#include <iostream>
#include <vector>
#include <utility>

class CoordinateList {
    public:
    CoordinateList();
    
    ~CoordinateList();
    
    CoordinateList(const CoordinateList& other) = delete;
    CoordinateList& operator=(const CoordinateList& other) = delete;

    void AddCoordinate(int x, int y);
    void RemoveCoordinate(int x, int y);
    std::pair<int, int> GetCoordinate(int index) const;
    int GetSize() const;

    private:
        std::vector<std::pair<int, int>> Coordinates;
};