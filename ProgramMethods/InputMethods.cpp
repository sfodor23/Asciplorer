#include <iostream>
#include <vector>
#include <cctype>

#include "InputMethods.hpp"
#include "MiscMethods.hpp"

#include "../Libraries/GenerationConstants.hpp"
#include "../Libraries/TileCharacters.hpp"

#include "../RealTimeStatistics/RealTimeStatistics.hpp"

using namespace std;
using namespace GenerationConstants;
using namespace TileCharacters;

void InputRefreshRate() {
    auto InputCustomRefreshRate = []() {
        string CustomRefreshRate;

        cout << "Enter Custom Refresh Rate (milliseconds): ";

        cin >> CustomRefreshRate;

        try {
            int ConvertedCustomRefreshRate = stoi(CustomRefreshRate);

            if (ConvertedCustomRefreshRate <= 0) {
                cout << "Invalid input! Please enter an integer above zero" << endl;
                return false;
            }
            
            CurrentStatistics.RefreshRate = ConvertedCustomRefreshRate;

            cout << "Selected Custom Refresh Rate: " << ConvertedCustomRefreshRate << " Milliseconds" << endl;

            return true;
        }
        catch (const exception& e) {
            cout << "Invalid input! Please enter valid integers" << endl;
            return false;
        }
    };

    string RefreshRateSelection;
    bool Success = false;
    
    cout << "Select Default or Custom Refresh Rate: ";
    
    while (!Success) {
        cin >> RefreshRateSelection;

        for (char& c : RefreshRateSelection) {
            c = tolower(c);
        }

        if (RefreshRateSelection == "d" || RefreshRateSelection == "default") {
            CurrentStatistics.RefreshRate = 100;

            cout << "Selected Default Refresh Rate: " << "100"  << " Milliseconds" << endl;
            Success = true;
        }
        else if (RefreshRateSelection == "c" || RefreshRateSelection == "custom") {
            Success = InputCustomRefreshRate();
            if (!Success) {
                cout << "Try again. Enter 'd' or 'c': ";
            }
        }
        else {
            cout << "Invalid input! Please enter 'd', 'default', 'c', or 'custom': ";
        }
    }
}

void InputMapPalette() {
    string MapPaletteSelection;
    bool Success = false;

    cout << "Select Map Palette of Normal, Arcane, or Dull: ";
    
    while (!Success) {
        cin >> MapPaletteSelection;

        for (char& c : MapPaletteSelection) {
            c = tolower(c);
        }

        if (MapPaletteSelection == "n" || MapPaletteSelection == "normal") {
            CurrentStatistics.MapStyle = "Normal";

            CurrentStatistics.Water = NormalWater;
            CurrentStatistics.WarmWater = NormalWarmWater;
            CurrentStatistics.IcyWater = NormalIcyWater;
            
            CurrentStatistics.GenericLand = NormalGenericLand;
            CurrentStatistics.Mountain = NormalMountain;
            CurrentStatistics.IceCappedMountain = NormalIceCappedMountain;
            
            CurrentStatistics.Tundra = NormalTundra;
            CurrentStatistics.Boreal = NormalBoreal;
            CurrentStatistics.Forest = NormalForest;
            CurrentStatistics.Rainforest = NormalRainforest;
            CurrentStatistics.Desert = NormalDesert;
            
            CurrentStatistics.Village = NormalVillage;
            CurrentStatistics.Town = NormalTown;
            CurrentStatistics.City = NormalCity;
            CurrentStatistics.Capital = NormalCapital;
            CurrentStatistics.Megacity = NormalMegacity;

            cout << "Selected Normal Palette" << endl;
            cout << endl;
            Success = true;
        }
        else if (MapPaletteSelection == "a" || MapPaletteSelection == "arcane") {
            CurrentStatistics.MapStyle = "Arcane";

            CurrentStatistics.Water = ArcaneWater;
            CurrentStatistics.WarmWater = ArcaneWarmWater;
            CurrentStatistics.IcyWater = ArcaneIcyWater;
            
            CurrentStatistics.GenericLand = ArcaneGenericLand;
            CurrentStatistics.Mountain = ArcaneMountain;
            CurrentStatistics.IceCappedMountain = ArcaneIceCappedMountain;
            
            CurrentStatistics.Tundra = ArcaneTundra;
            CurrentStatistics.Boreal = ArcaneBoreal;
            CurrentStatistics.Forest = ArcaneForest;
            CurrentStatistics.Rainforest = ArcaneRainforest;
            CurrentStatistics.Desert = ArcaneDesert;
            
            CurrentStatistics.Village = ArcaneVillage;
            CurrentStatistics.Town = ArcaneTown;
            CurrentStatistics.City = ArcaneCity;
            CurrentStatistics.Capital = ArcaneCapital;
            CurrentStatistics.Megacity = ArcaneMegacity;
            
            cout << "Selected Arcane Palette" << endl;
            cout << endl;
            Success = true;
        }
        else if (MapPaletteSelection == "d" || MapPaletteSelection == "dull") {
            CurrentStatistics.MapStyle = "Dull";

            CurrentStatistics.Water = DullWater;
            CurrentStatistics.WarmWater = DullWarmWater;
            CurrentStatistics.IcyWater = DullIcyWater;
            
            CurrentStatistics.GenericLand = DullGenericLand;
            CurrentStatistics.Mountain = DullMountain;
            CurrentStatistics.IceCappedMountain = DullIceCappedMountain;
            
            CurrentStatistics.Tundra = DullTundra;
            CurrentStatistics.Boreal = DullBoreal;
            CurrentStatistics.Forest = DullForest;
            CurrentStatistics.Rainforest = DullRainforest;
            CurrentStatistics.Desert = DullDesert;
            
            CurrentStatistics.Village = DullVillage;
            CurrentStatistics.Town = DullTown;
            CurrentStatistics.City = DullCity;
            CurrentStatistics.Capital = DullCapital;
            CurrentStatistics.Megacity = DullMegacity;
            
            cout << "Selected Dull Palette" << endl;
            cout << endl;
            Success = true;
        }
        else {
            cout << "Invalid input! Please enter 'n', 'normal', 'a', 'arcane', 'd', or 'dull': ";
        }
    }
}

void InputPlayerIcon() {
    string PlayerIconSelection;
    bool Success = false;
    
    cout << "Colors: green(g), red(r), blue(b), yellow(y), purple(p), white(w), cyan(c), orange(o), pink(pi), lime(l)" << endl;
    cout << "Select Player Icon and Player Color in format CHARACTER/COLOR: ";
    
    while (!Success) {
        cin >> PlayerIconSelection;

        vector<size_t> slashPositions;
        for (size_t i = 0; i < PlayerIconSelection.length(); i++) {
            if (PlayerIconSelection[i] == '/') {
                slashPositions.push_back(i);
            }
        }

        if (slashPositions.size() != 1) {
            cout << "Invalid format! Please use CHARACTER/COLOR format (e.g., #/purple) (default character selectable): " << endl;
            continue;
        }

        try {
            string PlayerCharacter = PlayerIconSelection.substr(0, slashPositions[0]);
            string PlayerColor = PlayerIconSelection.substr(slashPositions[0] + 1);

            if (PlayerCharacter == "Default" || PlayerCharacter == "default" || PlayerCharacter == "D" || PlayerCharacter == "d") {
                PlayerCharacter = "⚉";
            }

            for (char& c : PlayerColor) {
                c = tolower(c);
            }
            
            if (PlayerColor == "green" || PlayerColor == "g") {
                CurrentStatistics.Player = "\033[38;5;10m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;10m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "red" || PlayerColor == "r") {
                CurrentStatistics.Player = "\033[38;5;196m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;196m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
        
            else if (PlayerColor == "blue" || PlayerColor == "b") {
                CurrentStatistics.Player = "\033[38;5;33m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;33m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "yellow" || PlayerColor == "y") {
                CurrentStatistics.Player = "\033[38;5;226m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;226m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "purple" || PlayerColor == "p") {
                CurrentStatistics.Player = "\033[38;5;129m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;129m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "white" || PlayerColor == "w") {
                CurrentStatistics.Player = "\033[38;5;15m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;15m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "cyan" || PlayerColor == "c") {
                CurrentStatistics.Player = "\033[38;5;51m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;51m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "orange" || PlayerColor == "o") {
                CurrentStatistics.Player = "\033[38;5;208m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;208m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "pink" || PlayerColor == "pi") {
                CurrentStatistics.Player = "\033[38;5;205m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;205m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }
            
            else if (PlayerColor == "lime" || PlayerColor == "l") {
                CurrentStatistics.Player = "\033[38;5;118m" + PlayerCharacter + "\033[0m";
                cout << "Selected " << "\033[38;5;118m" + PlayerCharacter + "\033[0m" << " As Player Character" << endl;
                cout << endl;
                Success = true;
            }

            else {
                cout << "Invalid color! Available colors:" << endl;
                cout << "green(g), red(r), blue(b), yellow(y), purple(p), white(w)" << endl;
                cout << "cyan(c), orange(o), pink(pi), lime(l)" << endl;
                Success = false;
            }
        }
        catch (const exception& e) {
            cout << "Invalid format! Please use CHARACTER/COLOR format (e.g., $/green)" << endl;
            Success = false;
        }
    }
}

void InputClimateType() {
    auto SetClimateType = [](double GeneralTemperature, double TemperatureVariation, double TemperatureShift, string ClimateTypeName) {
        CurrentStatistics.AverageTemperature = GeneralTemperature;
        CurrentStatistics.LatitudeTemperatureVariation = TemperatureVariation;
        CurrentStatistics.LatitudeShift = TemperatureShift;

        CurrentStatistics.MapClimateType = ClimateTypeName;
    
        cout << "Selected " << ClimateTypeName << " Climate Type" << endl;
        cout << endl;
    };
    
    auto InputCustomType = [&SetClimateType]() {
        string CustomClimateInput;

        cout << "Enter Custom Climate Average Temperature (def. of 9), Latitude Temperature Variation (def. of 21), and Latitude Temperature Shift (def. of 0) (format of CAT/LTV/LTS): ";

        cin >> CustomClimateInput;

        vector<size_t> slashPositions;
        for (size_t i = 0; i < CustomClimateInput.length(); i++) {
            if (CustomClimateInput[i] == '/') {
                slashPositions.push_back(i);
            }
        }

        if (slashPositions.size() != 2) {
            cout << "Invalid format! Please use CAT/LTV/LTS format (e.g., 9/21/0)" << endl;
            return false;
        }

        try {
            string GeneralTemperatureStr = CustomClimateInput.substr(0, slashPositions[0]);
            string TemperatureVariationStr = CustomClimateInput.substr(slashPositions[0] + 1, slashPositions[1] - slashPositions[0] - 1);
            string TemperatureShiftStr = CustomClimateInput.substr(slashPositions[1] + 1);
            
            double GeneralTemperature = stod(GeneralTemperatureStr);
            double TemperatureVariation = stod(TemperatureVariationStr);
            double TemperatureShift = stod(TemperatureShiftStr);
            
            if (TemperatureShift < -90 || TemperatureShift > 90) {
                cout << "Invalid Temperature Shift! Please enter a value between -90 and 90" << endl;
                return false;
            }
            
            SetClimateType(GeneralTemperature, TemperatureVariation, TemperatureShift, "Custom");
            return true;
        }
        catch (const exception& e) {
            cout << "Invalid format! Please use CAT/LTV/LTS format (e.g., 9/21/0)" << endl;
            return false;
        }
    };
    
    string ClimateTypeSelection;
    bool Success = false;

    cout << "Select Climate Type of Normal, Greenhouse, Freezing, or Custom: ";
    
    while (!Success) {
        cin >> ClimateTypeSelection;

        for (char& c : ClimateTypeSelection) {
            c = tolower(c);
        }

        if (ClimateTypeSelection == "n" || ClimateTypeSelection == "normal") {
            SetClimateType(9, 21, 0, "Normal");
            Success = true;
        }
        else if (ClimateTypeSelection == "g" || ClimateTypeSelection == "greenhouse") {
            SetClimateType(18, 15, 8, "Greenhouse");
            Success = true;
        }
        else if (ClimateTypeSelection == "f" || ClimateTypeSelection == "freezing") {
            SetClimateType(-5, 25, -12, "Freezing");
            Success = true;
        }
        else if (ClimateTypeSelection == "c" || ClimateTypeSelection == "custom") {
            Success = InputCustomType();
            if (!Success) {
                cout << "Try again. Enter 'n', 'g', 'f', or 'c': ";
            }
        }
        else {
            cout << "Invalid input! Please enter 'n', 'normal', 'g', 'greenhouse', 'f', 'freezing', 'c', or 'custom': ";
        }
    }
}

void InputSeed() {
    auto InputCustomSeed = []() {
        string CustomSeedSelection;

        cout << "Enter Custom Seed: ";

        cin >> CustomSeedSelection;

        try {
            int ConvertedCustomSeedSelection = stoi(CustomSeedSelection);

            if (ConvertedCustomSeedSelection <= 0) {
                cout << "Invalid input! Please enter an integer above zero" << endl;
                return false;
            }
            
            CurrentStatistics.TopographySeed = ConvertedCustomSeedSelection;

            cout << "Selected Custom Seed: " << ConvertedCustomSeedSelection << endl;
            cout << endl;

            return true;
        }
        catch (const exception& e) {
            cout << "Invalid input! Please enter valid integers" << endl;
            return false;
        }
    };

    string MapSeedSelection;
    bool Success = false;
    
    cout << "Select Random or Custom Map Seed: ";
    
    while (!Success) {
        cin >> MapSeedSelection;

        for (char& c : MapSeedSelection) {
            c = tolower(c);
        }

        if (MapSeedSelection == "r" || MapSeedSelection == "random") {
            int RandomSeed = RandomNumberGenerator(CurrentStatistics.MapSeedCount);
            CurrentStatistics.TopographySeed = RandomSeed;
            cout << "Selected Random Seed: " << RandomSeed << endl;
            cout << endl;
            Success = true;
        }
        else if (MapSeedSelection == "c" || MapSeedSelection == "custom") {
            Success = InputCustomSeed();
            if (!Success) {
                cout << "Try again. Enter 'r' or 'c': ";
            }
        }
        else {
            cout << "Invalid input! Please enter 'r', 'random', 'c', or 'custom': ";
        }
    }
}

void InputMapType() {
    auto SetMapType = [](double Frequency, int Layers, double Spreadiness, double LayerGain, string MapTypeName) {
        CurrentStatistics.TopographyFrequency = Frequency;
        CurrentStatistics.TopographyLayers = Layers;
        CurrentStatistics.TopographySpreadiness = Spreadiness;
        CurrentStatistics.TopographyLayerGain = LayerGain;

        CurrentStatistics.MapType = MapTypeName;
    
        cout << "Selected " << MapTypeName << " Map Type" << endl;
        cout << endl;
    };
    
    auto InputCustomType = [&SetMapType]() {
        string CustomTypeInput;

        cout << "Enter Custom Map Noise Frequency (def. of 0.03), Layer Count (def. of 10), Spreadiness (def. of 1.85), and Layer Gain (def. of 0.6) (Format of F/LC/S/LG): ";

        cin >> CustomTypeInput;

        vector<size_t> slashPositions;
        for (size_t i = 0; i < CustomTypeInput.length(); i++) {
            if (CustomTypeInput[i] == '/') {
                slashPositions.push_back(i);
            }
        }

        if (slashPositions.size() != 3) {
            cout << "Invalid format! Please use F/LC/S/LG format (e.g., 0.03/10/1.85/0.6)" << endl;
            return false;
        }

        try {
            string FrequencyStr = CustomTypeInput.substr(0, slashPositions[0]);
            string LayersStr = CustomTypeInput.substr(slashPositions[0] + 1, slashPositions[1] - slashPositions[0] - 1);
            string SpreadinessStr = CustomTypeInput.substr(slashPositions[1] + 1, slashPositions[2] - slashPositions[1] - 1);
            string LayerGainStr = CustomTypeInput.substr(slashPositions[2] + 1);
            
            double Frequency = stod(FrequencyStr);
            int Layers = stoi(LayersStr);
            double Spreadiness = stod(SpreadinessStr);
            double LayerGain = stod(LayerGainStr);
            
            if (Frequency < 0.01 || Frequency > 1.0) {
                cout << "Invalid frequency! Please enter a value between 0.01 and 1.0" << endl;
                return false;
            }
            
            if (Layers < 1 || Layers > 20) {
                cout << "Invalid layer count! Please enter a value between 1 and 20" << endl;
                return false;
            }
            
            if (Spreadiness < 0.1 || Spreadiness > 5.0) {
                cout << "Invalid spreadiness! Please enter a value between 0.1 and 5.0" << endl;
                return false;
            }
            
            if (LayerGain < 0.1 || LayerGain > 1.0) {
                cout << "Invalid layer gain! Please enter a value between 0.1 and 1.0" << endl;
                return false;
            }
            
            SetMapType(Frequency, Layers, Spreadiness, LayerGain, "Custom");
            return true;
        }
        catch (const exception& e) {
            cout << "Invalid input! Please enter valid numbers in F/LC/S/LG format (e.g., 0.03/10/1.85/0.6)" << endl;
            return false;
        }
    };
    
    string MapTypeSelection;
    bool Success = false;

    cout << "Select Map Type of Continental, Island, or Custom: ";
    
    while (!Success) {
        cin >> MapTypeSelection;

        for (char& c : MapTypeSelection) {
            c = tolower(c);
        }

        if (MapTypeSelection == "c" || MapTypeSelection == "continental") {
            SetMapType(0.03f, 10, 1.85f, 0.6f, "Continental");
            Success = true;
        }
        else if (MapTypeSelection == "i" || MapTypeSelection == "island") {
            SetMapType(0.1f, 10, 1.6f, 0.6f, "Island");
            Success = true;
        }
        else if (MapTypeSelection == "cu" || MapTypeSelection == "custom") {
            Success = InputCustomType();
            if (!Success) {
                cout << "Try again. Enter 'c', 'i', or 'cu': ";
            }
        }
        else {
            cout << "Invalid input! Please enter 'c', 'continental', 'i', 'island', 'cu', or 'custom': ";
        }
    }
}

void InputDimensions(int& XDimension, int& YDimension) {
    auto SetMapSize = [](int& XDimension, int& YDimension, int SizeX, int SizeY, string SizeName) {
        XDimension = SizeX;
        YDimension = SizeY;
        CurrentStatistics.MapDimensionX = SizeX;
        CurrentStatistics.MapDimensionY = SizeY;
        CurrentStatistics.MapArea = SizeX * SizeY;
        CurrentStatistics.StartingCoordinate[0] = SizeX / 2;
        CurrentStatistics.StartingCoordinate[1] = SizeY / 2;
    
        cout << "Selected " << SizeName << " Map Size " << "(" << SizeX << " by " << SizeY  << ")" << endl;
        cout << endl;
    };
    
    auto InputCustomSize = [&SetMapSize](int& XDimension, int& YDimension) {
        string CustomSizeInput;

        cout << "Enter Custom Map Size (In Form WIDTHxHEIGHT): ";

        cin >> CustomSizeInput;

        size_t XCharPosition = CustomSizeInput.find('x');

        if (XCharPosition == string::npos) {
            XCharPosition = CustomSizeInput.find('X');
        }
        
        if (XCharPosition == string::npos) {
            cout << "Invalid format! Please use WIDTHxHEIGHT format (e.g., 500x300)" << endl;
            return false;
        }

        try {
            string WidthStr = CustomSizeInput.substr(0, XCharPosition);
            string HeightStr = CustomSizeInput.substr(XCharPosition + 1);
            
            int Width = stoi(WidthStr);
            int Height = stoi(HeightStr);
            
            if (Width < 25 || Height < 25) {
                cout << "Map dimensions too small! Minimum size is 25x25" << endl;
                return false;
            }
            
            if (Width > 10000 || Height > 10000) {
                cout << "Map dimensions too large! Maximum size is 10000x10000" << endl;
                return false;
            }
            
            SetMapSize(XDimension, YDimension, Width, Height, "Custom");
            return true;
        }
        catch (const exception& e) {
            cout << "Invalid Input! Please enter valid integers (e.g., 500x300)" << endl;
            return false;
        }
    };
    
    string MapSizeSelection;
    bool Success = false;

    cout << "Select Map Size of Small (" << SmallMapSizeX << " * " << SmallMapSizeY << "), Large (" << LargeMapSizeX << " * " << LargeMapSizeY << "), or Custom: ";
    
    while (!Success) {
        cin >> MapSizeSelection;

        for (char& c : MapSizeSelection) {
            c = tolower(c);
        }

        if (MapSizeSelection == "s" || MapSizeSelection == "small") {
            SetMapSize(XDimension, YDimension, SmallMapSizeX, SmallMapSizeY, "Small");
            Success = true;
        }
        else if (MapSizeSelection == "l" || MapSizeSelection == "large") {
            SetMapSize(XDimension, YDimension, LargeMapSizeX, LargeMapSizeY, "Large");
            Success = true;
        }
        else if (MapSizeSelection == "c" || MapSizeSelection == "custom") {
            Success = InputCustomSize(XDimension, YDimension);
            if (!Success) {
                cout << "Try again. Enter 's', 'l', or 'c': ";
            }
        }
        else {
            cout << "Invalid input! Please enter 's', 'small', 'l', or 'large', 'c', or 'custom': ";
        }
    }
}