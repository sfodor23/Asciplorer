#include <iostream>
#include <string>
#include "FastNoiseLite.h"
using namespace std;
namespace TiCh {
    string Land = "\033[32m■\033[0m";
    string Water = "\033[34m~\033[0m";
    string Mountain = "\033[90m▲\033[0m";
}


template <typename T>
class Map {
    public:
    int XDimension;
    int YDimension;
    T** MapArray = nullptr;

    Map(int XDimension, int YDimension) {
        this->XDimension = XDimension;
        this->YDimension = YDimension;
        GenerateMapArray();
    };

    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    ~Map() {
        if (MapArray != nullptr) {
            for (int y = 0; y < YDimension; y++) {
                delete[] MapArray[y];
            }

            delete[] MapArray;

            MapArray = nullptr;
        }
    }

    void GenerateMapArray() {
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

    void ManualMapArrayDeletion() {
        if (MapArray != nullptr) {
            for (int y = 0; y < YDimension; y++) {
                delete[] MapArray[y];
            }

            delete[] MapArray;

            MapArray = nullptr;
        }
    }

    void PrintMap() {
        cout << "\n";
            
        int CurrentFirstDigit = 0;
            
        for (int x = 0; x < XDimension; x++) {
            if ((x + 1) % 10 == 0) {
                CurrentFirstDigit = (x + 1)/10;
            }
            if (CurrentFirstDigit == 0) {
                cout << "  ";
            }
            else {
                cout << CurrentFirstDigit << " ";
            }
        }

        cout << "\n";
            
        for (int x = 0; x < XDimension; x++) {
            cout << (x + 1) % 10 << " ";
        }
            
        cout << "\n";
            
        for (int x = 0; x < XDimension; x++) {
            cout << "_ ";
        } 
            
        cout << "\n\n";
            
        for (int y = 0; y < YDimension; y++) {
            for (int x = 0; x < XDimension; x++) {
                cout << MapArray[y][x] << " ";
            }
            cout << " |" << y + 1 << "\n";
        }
    }
};

int RandomNumberGenerator(int Range) {
    int GeneratedNumber = (rand() % Range) + 1;

    return GeneratedNumber;
}

void InputDimensions(int& XDimension, int& YDimension) {
    char MapSizeSelection;
    int Success = false;

    cout << "\nSelect Map Size of [S]mall (50 by 25) or [L]arge (100 x 50): ";
    
    while (Success == false) {
        cin >> MapSizeSelection;

        switch(MapSizeSelection) {
            case 'S':
                XDimension = 50;
                YDimension = 25;
                Success = true;
                break;
            case 's':
                XDimension = 50;
                YDimension = 25;
                Success = true;
                break;    
            case 'L':
                XDimension = 100;
                YDimension = 50;
                Success = true;
                break;       
            case 'l':
                XDimension = 100;
                YDimension = 50;
                Success = true;
                break;
            default:
                cout << "\nInvalid Reponse! Input the letter S or L to Select Map Size: ";
                break;
        }
    }
}

void TopographyMapArrayValueGeneration(Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(RandomNumberGenerator(5000));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(7);
    noise.SetFractalLacunarity(1.6f);
    noise.SetFractalGain(0.6f);

    for (int y = 0; y < TopographyMap.YDimension; y++) {
        for (int x = 0; x < TopographyMap.XDimension; x++) {
            TopographyMap.MapArray[y][x] = noise.GetNoise((float)x, (float)y);
        }
    }
}

void CombinedMapArrayValueGeneration(Map<float>& TopographyMap, Map<string>& CombinedMap) {
    for (int y = 0; y < CombinedMap.YDimension; y++) {
        for (int x = 0; x < CombinedMap.XDimension; x++) {
            if (TopographyMap.MapArray[y][x] >= 0.06 && TopographyMap.MapArray[y][x] < 0.3) {
                CombinedMap.MapArray[y][x] = TiCh::Land;
            }
            if (TopographyMap.MapArray[y][x] > 0.3) {
                CombinedMap.MapArray[y][x] = TiCh::Mountain;
            }
            if (TopographyMap.MapArray[y][x] < 0.06) {
                CombinedMap.MapArray[y][x] = TiCh::Water;
            }
        }
    }
}

int main() {
    int XDimension;
    int YDimension;

    srand(time(NULL));

    cout << "****NATIONAL CONQUEST****";
    cout << "Before Round Begins, Presets Must Be Selected";

    InputDimensions(XDimension, YDimension);

    Map<float> TopographyMap(XDimension, YDimension);
    Map<string> CombinedMap(XDimension, YDimension);

    TopographyMapArrayValueGeneration(TopographyMap);
    CombinedMapArrayValueGeneration(TopographyMap, CombinedMap);

    CombinedMap.PrintMap();

    return 0;
}