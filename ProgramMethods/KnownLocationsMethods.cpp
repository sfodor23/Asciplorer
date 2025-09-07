#include <iostream>

#include "KnownLocationsMethods.hpp"

CoordinateList::CoordinateList() {

}

CoordinateList::~CoordinateList() {
 
}

void CoordinateList::AddCoordinate(int x, int y) {
    Coordinates.push_back({x, y});
}

void CoordinateList::RemoveCoordinate(int x, int y) {
    for (auto it = Coordinates.begin(); it != Coordinates.end(); ++it) {
        if (it->first == x && it->second == y) {
            Coordinates.erase(it);
            return;
        }
    }
}

std::pair<int, int> CoordinateList::GetCoordinate(int index) const {
   if (index >= 0 && index < static_cast<int>(Coordinates.size())) {
        return Coordinates[index];
    } else {
        std::cout << "Error: Index " << index << " out of bounds!\n";
        return {-1, -1};
    }
}

int CoordinateList::GetSize() const {
    return static_cast<int>(Coordinates.size());
}