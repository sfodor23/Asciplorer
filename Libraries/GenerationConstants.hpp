#pragma once
#include <string>

namespace GenerationConstants {
    // MATHEMATICAL CONSTANTS (most fundamental)
    inline constexpr double Pi = 3.1415926535;
    
    // MAP SIZE CONSTANTS (core map dimensions)
    inline constexpr int SmallMapSizeX = 1000;
    inline constexpr int SmallMapSizeY = 500;
    inline constexpr int LargeMapSizeX = 2000;
    inline constexpr int LargeMapSizeY = 1000;
    
    // ELEVATION CONSTANTS (foundation for terrain)
    inline constexpr int ElevationScaleFactor = 8000;
    inline constexpr double LandElevationRange[2] = {0.0, 0.3 * ElevationScaleFactor};
    
    // TEMPERATURE CONSTANTS (base climate system)
    inline constexpr double ElevationTemperatureLose = 6.5;
    inline constexpr double PerlinNoiseTemperatureRange = 5;
    
    // PRECIPITATION CONSTANTS (water cycle system)
    inline constexpr double AltitudePrecipitationGain = 1.8;
    inline constexpr double MountainPrecipitationMultiplier = 0.85;
    inline constexpr double PerlinNoisePrecipitationRange = 500;
    inline constexpr double RainShadowMultiplier = 0.25;
    inline constexpr double RainAmplifierMultiplier = 1.5;
    
    // BIOME TEMPERATURE RANGES (grouped by biome type)
    inline constexpr double RainforestTemperatureRange[2] = {18, 10000};
    inline constexpr double ForestTemperatureRange[2] = {2, 10000};
    inline constexpr double DesertTemperatureRange[2] = {2, 10000};
    inline constexpr double BorealTemperatureRange[2] = {-8, 2};
    inline constexpr double TundraTemperatureRange[2] = {-10000, -8};
    inline constexpr double MountainTemperatureRange[2] = {-8, 10000};
    inline constexpr double WaterTemperatureRange[2] = {-1.5, 20};
    
    // BIOME PRECIPITATION RANGES (same biome order)
    inline constexpr double RainforestPrecipitationRange[2] = {1500, 10000};
    inline constexpr double ForestPrecipitationRange[2] = {500, 10000};
    inline constexpr double DesertPrecipitationRange[2] = {-10000, 500};
    inline constexpr double BorealPrecipitationRange[2] = {-10000, 10000};
    inline constexpr double TundraPrecipitationRange[2] = {-10000, 10000};
    
    // POPULATION DENSITY (settlement system, same biome order)
    inline constexpr int RainforestPopulationDensity = 100;
    inline constexpr int ForestPopulationDensity = 400;
    inline constexpr int DesertPopulationDensity = 150;
    inline constexpr int BorealPopulationDensity = 200;
    inline constexpr int TundraPopulationDensity = 10;
    inline constexpr int MountainPopulationDensity = 225;
    inline constexpr int IceCappedMountainPopulationDensity = 0;
}