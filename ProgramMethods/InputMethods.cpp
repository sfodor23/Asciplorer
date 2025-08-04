#include "InputMethods.hpp"
#include "../Libraries/GenerationConstants.hpp"
#include <iostream>

using namespace std;
using namespace GenerationConstants;

void InputDimensions(int& XDimension, int& YDimension) {
    char MapSizeSelection;
    int Success = false;

    cout << "\nSelect Map Size of [S]mall (" << SmallMapSizeX << " * " << SmallMapSizeY << ") or [L]arge (" << LargeMapSizeX << " * " << LargeMapSizeY << "): ";
    
    while (Success == false) {
        cin >> MapSizeSelection;

        switch(MapSizeSelection) {
            case 'S':
                XDimension = SmallMapSizeX;
                YDimension = SmallMapSizeY;
                Success = true;
                break;
            case 's':
                XDimension = SmallMapSizeX;
                YDimension = SmallMapSizeY;
                Success = true;
                break;    
            case 'L':
                XDimension = LargeMapSizeX;
                YDimension = LargeMapSizeY;
                Success = true;
                break;       
            case 'l':
                XDimension = LargeMapSizeX;
                YDimension = LargeMapSizeY;
                Success = true;
                break;
            default:
                cout << "\nInvalid Reponse! Input the letter S or L to Select Map Size: ";
                break;
        }
    }
}