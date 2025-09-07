#include "MiscMethods.hpp"

int RandomNumberGenerator(int Range) {
    return (rand() % Range) + 1;
}

int IndexedRandomNumberGenerator(int Range) {
    return (rand() % Range);
}

void InitializeRandomSeed() {
    srand(time(nullptr));
}