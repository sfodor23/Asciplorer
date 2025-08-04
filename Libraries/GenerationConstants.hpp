#pragma once
#include <string>

namespace GenerationConstants {
    inline constexpr int ElevationScaleFactor = 8000;
    inline constexpr double Pi = 3.1415926535;
    inline constexpr int SmallMapSizeX = 100;
    inline constexpr int SmallMapSizeY = 200;
    inline constexpr int LargeMapSizeX = 100;
    inline constexpr int LargeMapSizeY = 1000;
    inline constexpr double LandElevationRange[2] = {0.0, 0.3 * ElevationScaleFactor};
    inline constexpr double RainforestTemperatureRange[2] = {18, 10000};
    inline constexpr double RainforestPrecipitationRange[2] = {1500, 10000};
    inline constexpr double DesertTemperatureRange[2] = {2, 10000};
    inline constexpr double DesertPrecipitationRange[2] = {-10000, 500};
    inline constexpr double ForestTemperatureRange[2] = {2, 10000};
    inline constexpr double ForestPrecipitationRange[2] = {500, 10000};
    inline constexpr double BorealTemperatureRange[2] = {-8, 2};
    inline constexpr double BorealPrecipitationRange[2] = {-10000, 10000};
    inline constexpr double TundraTemperatureRange[2] = {-10000, -8};
    inline constexpr double TundraPrecipitationRange[2] = {-10000, 10000};
    inline constexpr double WaterTemperatureRange[2] = {-1.5, 20};
    inline constexpr double MountainTemperatureRange[2] = {-8, 10000};
    inline constexpr double ElevationTemperatureLose = 6.5;
    inline constexpr double AverageTemperature = 9;
    inline constexpr double LatitudeTemperatureVariation = 21;
    inline constexpr double PerlinNoiseTemperatureRange = 5;
    inline constexpr double AltitudePrecipitationGain = 1.8;
    inline constexpr double MountainPrecipitationMultiplier = 0.85;
    inline constexpr double PerlinNoisePrecipitationRange = 500;
    inline constexpr double RainShadowMultiplier = 0.25;
    inline constexpr double RainAmplifierMultiplier = 1.5;
}