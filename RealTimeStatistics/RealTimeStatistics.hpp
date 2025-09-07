#pragma once

#include <iostream>

using namespace std;

class CoordinateList;

#define DECLARE_BIOME_SETTLEMENTS(biome) \
    int biome##TotalVillages = 0; \
    int biome##TotalTowns = 0; \
    int biome##TotalCities = 0; \
    int biome##TotalCapitals = 0; \
    int biome##TotalMegacities = 0;

struct SimulationStatistics {
    // ================================================================================
    //                                GAME CONFIGURATION
    // ================================================================================
    
    // Display Settings
    int RefreshRate = 100;

    // Map Generation Parameters
    int MapArea;
    int MapDimensionX;
    int MapDimensionY;
    double TopographyFrequency = 0.03f;
    int TopographyLayers = 10;
    double TopographySpreadiness = 1.85f;
    double TopographyLayerGain = 0.6f;

    // Map Information
    std::string MapStyle;
    std::string MapType;
    std::string MapClimateType;

    // Random Generation Seeds
    int MapSeedCount = 25000;
    int TopographySeed = 537;

    // Climate Configuration
    double AverageTemperature = 9;
    double LatitudeTemperatureVariation = 21;
    double LatitudeShift = 0;

    // ================================================================================
    //                                 PLAYER STATE
    // ================================================================================
    
    // Player Position & Movement
    int StartingCoordinate[2];
    int CurrentCoordinate[2];
    int TargetCoordinate[2];
    int PreviousCoordinate[2];
    string PreviousCoordinateState;
    
    // Player Resources & Crew
    int Doubloons = 100;
    int Crew = 100;
    wstring CurrentCaptain = L"John Smith";
    
    // Player Progress Tracking
    int TilesTravelled = 0;
    int TargetsReached = 0;
    string TargetBiomeType;
    string TargetSettlementType;

    // Player Visual Representation
    std::string Player = "\033[38;5;255m⚉\033[0m";

    // ================================================================================
    //                                WORLD STATISTICS
    // ================================================================================
    
    // Terrain Tile Counts
    int LandTileCount = 0;
    int RainforestTileCount = 0;
    int DesertTileCount = 0;
    int ForestTileCount = 0;
    int BorealTileCount = 0;
    int TundraTileCount = 0;
    int MountainTileCount = 0;
    int IceCappedMountainTileCount = 0;

    // Population Statistics by Biome
    int RainforestTotalPopulation = 0;
    int ForestTotalPopulation = 0;
    int BorealTotalPopulation = 0;
    int TundraTotalPopulation = 0;
    int DesertTotalPopulation = 0;
    int MountainTotalPopulation = 0;
    int IceCappedMountainTotalPopulation = 0;

    // ================================================================================
    //                              SETTLEMENT SYSTEM
    // ================================================================================
    
    // Settlement Distribution Percentages
    double VillagePercentage = 0.45;
    double TownPercentage = 0.35;
    double CityPercentage = 0.14;
    double CapitalPercentage = 0.05;
    double MegacityPercentage = 0.01;

    // Settlement Counts by Biome Type
    DECLARE_BIOME_SETTLEMENTS(Rainforest)
    DECLARE_BIOME_SETTLEMENTS(Desert)
    DECLARE_BIOME_SETTLEMENTS(Forest)
    DECLARE_BIOME_SETTLEMENTS(Boreal)
    DECLARE_BIOME_SETTLEMENTS(Tundra)
    DECLARE_BIOME_SETTLEMENTS(Mountain)
    DECLARE_BIOME_SETTLEMENTS(IceCappedMountain)

    // ================================================================================
    //                               VISUAL PALETTES
    // ================================================================================
    
    // Water Tiles
    std::string Water = "\033[38;5;33m~\033[0m";
    std::string WarmWater = "\033[38;5;39m~\033[0m";
    std::string IcyWater = "\033[38;5;117m~\033[0m";
    
    // Terrain Tiles
    std::string GenericLand = "\033[38;5;34m■\033[0m";
    std::string Mountain = "\033[38;5;8m▲\033[0m"; 
    std::string IceCappedMountain = "\033[38;5;15m▲\033[0m";
    
    // Biome Tiles
    std::string Tundra = "\033[38;5;15m■\033[0m";
    std::string Boreal = "\033[38;5;22m■\033[0m";
    std::string Forest = "\033[38;5;28m■\033[0m";
    std::string Rainforest = "\033[38;5;40m■\033[0m";
    std::string Desert = "\033[38;5;221m■\033[0m";
    
    // Settlement Tiles
    std::string Village = "\033[38;5;94m■\033[0m";
    std::string Town = "\033[38;5;166m■\033[0m";
    std::string City = "\033[38;5;250m■\033[0m";
    std::string Capital = "\033[38;5;242m■\033[0m";
    std::string Megacity = "\033[38;5;226m■\033[0m";

    // ================================================================================
    //                              COORDINATE MANAGEMENT
    // ================================================================================
    
    // Coordinate Lists for World Generation
    CoordinateList* LandCoordinates;
    CoordinateList* ForestCoordinates;
    CoordinateList* RainforestCoordinates;
    CoordinateList* DesertCoordinates;  
    CoordinateList* BorealCoordinates;
    CoordinateList* TundraCoordinates;
    CoordinateList* MountainCoordinates;
    CoordinateList* IceCappedMountainCoordinates;
    CoordinateList* SettlementCoordinates;

    // ================================================================================
    //                                DISPLAY OUTPUT
    // ================================================================================
    
    // Output Buffer for Statistics Display
    string PrintingLine[64];

    // ================================================================================
    //                           CONSTRUCTOR & DESTRUCTOR
    // ================================================================================
    
    SimulationStatistics();
    ~SimulationStatistics();
};

#undef DECLARE_BIOME_SETTLEMENTS

extern SimulationStatistics CurrentStatistics;