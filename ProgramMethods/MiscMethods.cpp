#include "MiscMethods.hpp"

int RandomNumberGenerator(int Range) {
    return (rand() % Range) + 1;
}

void InitializeRandomSeed() {
    srand(time(nullptr));
}