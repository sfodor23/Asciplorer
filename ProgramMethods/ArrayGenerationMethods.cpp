#include "ArrayGenerationMethods.hpp"
#include "CoreMapMethods.hpp"
#include "MiscMethods.hpp"
#include "../Libraries/FastNoiseLite.h"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/GenerationConstants.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;
using namespace GenerationConstants;
using namespace TileCharacters;

void TopographyMapArrayValueGeneration(Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(RandomNumberGenerator(5000));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.03f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(10);
    noise.SetFractalLacunarity(1.85f);
    noise.SetFractalGain(0.6f);

    for (int y = 0; y < TopographyMap.YDimension; y++) {
        for (int x = 0; x < TopographyMap.XDimension; x++) {
            TopographyMap.MapArray[y][x] = noise.GetNoise((float)x, (float)y) * ElevationScaleFactor;
        }
    }
}

void CombinedMapArrayValueGeneration(Map<float>& TopographyMap, Map<string>& CombinedMap, Map<double>& PrecipitationMap, Map<double>& TemperatureMap) {
    auto BaseTerrainCalculation = [&](int y, int x) {
        char TileBaseTerrain = '0';

        if (TopographyMap.MapArray[y][x] < LandElevationRange[0]) {
            TileBaseTerrain = 'W';

            return TileBaseTerrain;
        }

        if (TopographyMap.MapArray[y][x] >= LandElevationRange[0] && TopographyMap.MapArray[y][x] < LandElevationRange[1]) {
            TileBaseTerrain = 'L';

            return TileBaseTerrain;
        }

        if (TopographyMap.MapArray[y][x] >= LandElevationRange[1]) {
            TileBaseTerrain = 'M';

            return TileBaseTerrain;
        }

        return TileBaseTerrain;
    };

    auto BiomeCalculation = [&](int y, int x, char TileBaseTerrain) {
        switch(TileBaseTerrain) {
            case 'W':
                if (TemperatureMap.MapArray[y][x] >= WaterTemperatureRange[1]) {
                    CombinedMap.MapArray[y][x] = WarmWater;
                }
            
                else if (TemperatureMap.MapArray[y][x] >= WaterTemperatureRange[0] && TemperatureMap.MapArray[y][x] < WaterTemperatureRange[1]) {
                    CombinedMap.MapArray[y][x] = Water;
                }

                else if (TemperatureMap.MapArray[y][x] < WaterTemperatureRange[0]) {
                    CombinedMap.MapArray[y][x] = IcyWater;
                }
                
                else {
                    CombinedMap.MapArray[y][x] = ErrorTile;
                }

                break;

            case 'L':
                if (TemperatureMap.MapArray[y][x] >= RainforestTemperatureRange[0] && PrecipitationMap.MapArray[y][x] >= RainforestPrecipitationRange[0]) {
                    CombinedMap.MapArray[y][x] = Rainforest;
                }
                
                else if (TemperatureMap.MapArray[y][x] >= DesertTemperatureRange[0] && PrecipitationMap.MapArray[y][x] < DesertPrecipitationRange[1]) {
                    CombinedMap.MapArray[y][x] = Desert;
                }

                else if (TemperatureMap.MapArray[y][x] < ForestTemperatureRange[1] && TemperatureMap.MapArray[y][x] >= ForestTemperatureRange[0] && PrecipitationMap.MapArray[y][x] >= ForestPrecipitationRange[0] && PrecipitationMap.MapArray[y][x] < ForestPrecipitationRange[1]) {
                    CombinedMap.MapArray[y][x] = Forest;
                }

                else if (TemperatureMap.MapArray[y][x] < BorealTemperatureRange[1] && TemperatureMap.MapArray[y][x] >= BorealTemperatureRange[0]) {
                    CombinedMap.MapArray[y][x] = Boreal;
                }
            
                else if (TemperatureMap.MapArray[y][x] < TundraTemperatureRange[1]) {
                    CombinedMap.MapArray[y][x] = Tundra;
                }
                else {
                    CombinedMap.MapArray[y][x] = ErrorTile;
                    cout << "\n" << TemperatureMap.MapArray[y][x] << " C " << PrecipitationMap.MapArray[y][x] << " mm";
                }

                break;

            case 'M':
                if (TemperatureMap.MapArray[y][x] >= MountainTemperatureRange[0]) {
                    CombinedMap.MapArray[y][x] = Mountain;
                }

                else if (TemperatureMap.MapArray[y][x] < MountainTemperatureRange[0]) {
                    CombinedMap.MapArray[y][x] = IceCappedMountain;
                }
                else {
                    CombinedMap.MapArray[y][x] = ErrorTile;
                }

                break;
            
            default:
                cout << "If You Are Seeing This The Land Generator Broke";
                break;
        }
    };
    
    for (int y = 0; y < CombinedMap.YDimension; y++) {
        for (int x = 0; x < CombinedMap.XDimension; x++) {
           char TileBaseTerrain = BaseTerrainCalculation(y, x);
           BiomeCalculation(y, x, TileBaseTerrain);
        }
    }
}

void PrecipitationMapArrayValueGeneration(Map<double>& PrecipitationMap, Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(RandomNumberGenerator(5000));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(7);
    noise.SetFractalLacunarity(1.6f);
    noise.SetFractalGain(0.6f);
    
    auto LatitudeFactorCalculation = [&](int y) {
        double DistanceFromMidPoint = abs(y - PrecipitationMap.YMidPoint);
        double LatitudeDegree = (DistanceFromMidPoint / PrecipitationMap.YMidPoint) * 90;
        double LatitudePrecipitationFactor = 1;

        if (LatitudeDegree < 25.47) {
            LatitudePrecipitationFactor = ((250 * (cos((Pi/90) * LatitudeDegree)))) + 1000 + ((750 * (cos((Pi/25) * LatitudeDegree))));
        }

        if (LatitudeDegree >= 25.47) {
            LatitudePrecipitationFactor = (-250 * cos(((Pi/30) * LatitudeDegree) - 40.8)) + 660;
        }

        return LatitudePrecipitationFactor;
    };

    auto AltitudeFactorCalculation = [&](int y, int x) {
        double AltitudePrecipitationFactor = 1;
        
        if (TopographyMap.MapArray[y][x] > 0 && TopographyMap.MapArray[y][x] < LandElevationRange[1]) {
            AltitudePrecipitationFactor = log((TopographyMap.MapArray[y][x] / 8000.0) + AltitudePrecipitationGain) / log(AltitudePrecipitationGain);
        }
        if (TopographyMap.MapArray[y][x] >= LandElevationRange[1]) {
            AltitudePrecipitationFactor = MountainPrecipitationMultiplier;
        }

        return AltitudePrecipitationFactor;
    };

    auto PerlinNoiseFactorCalculation = [&](int y, int x) {
        double PerlinNoisePrecipitationFactor = noise.GetNoise((float)x, (float)y) * PerlinNoisePrecipitationRange;
        return PerlinNoisePrecipitationFactor;
    };

    auto WindFactorCalculation = [&](int y, int x) {
        double DistanceFromMidPoint = abs(y - PrecipitationMap.YMidPoint);
        double LatitudeDegree = (DistanceFromMidPoint / PrecipitationMap.YMidPoint) * 90;
        double WindPrecipitationFactor = 1;

        if (LatitudeDegree < 30 || LatitudeDegree >= 60) {
            for (int offset = 1; offset <= 3; offset++) {
                if (x - offset >= 0) {
                    if (TopographyMap.MapArray[y][x - offset] >= LandElevationRange[1]) {
                        WindPrecipitationFactor = RainAmplifierMultiplier;
                        return WindPrecipitationFactor;
                    }
                }
            }
            
            for (int offset = 1; offset <= 3; offset++) {
                if (x + offset < TopographyMap.XDimension) {
                    if (TopographyMap.MapArray[y][x + offset] >= LandElevationRange[1]) {
                        WindPrecipitationFactor = RainShadowMultiplier;
                        return WindPrecipitationFactor;
                    }
                }
            }
        }

        if (LatitudeDegree >= 30 && LatitudeDegree < 60) {
            for (int offset = 1; offset <= 3; offset++) {
                if (x - offset >= 0) {
                    if (TopographyMap.MapArray[y][x - offset] >= LandElevationRange[1]) {
                        WindPrecipitationFactor = RainShadowMultiplier;
                        return WindPrecipitationFactor;
                    }
                }
            }

            for (int offset = 1; offset <= 3; offset++) {
                if (x + offset < TopographyMap.XDimension) {
                    if (TopographyMap.MapArray[y][x + offset] >= LandElevationRange[1]) {
                        WindPrecipitationFactor = RainAmplifierMultiplier;
                        return WindPrecipitationFactor;
                    }
                }
            }
        }

        return WindPrecipitationFactor;
    };

    for (int y = 0; y < PrecipitationMap.YDimension; y++) {
        double LatitudePrecipitationFactor = LatitudeFactorCalculation(y);

        for (int x = 0; x < PrecipitationMap.XDimension; x++) {
            double AltitudePrecipitationFactor = AltitudeFactorCalculation(y, x);
            double PerlinNoisePrecipitationFactor = PerlinNoiseFactorCalculation(y, x);
            double WindPrecipitationFactor = WindFactorCalculation(y, x);

            PrecipitationMap.MapArray[y][x] = ((LatitudePrecipitationFactor + PerlinNoisePrecipitationFactor) * AltitudePrecipitationFactor) * WindPrecipitationFactor;
        }
    }    
}

void TemperatureMapArrayValueGeneration(Map<double>& TemperatureMap, Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(RandomNumberGenerator(5000));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(7);
    noise.SetFractalLacunarity(1.6f);
    noise.SetFractalGain(0.6f);

    auto LatitudeFactorCalculation = [&](int y) {
        double DistanceFromMidPoint = abs(y - TemperatureMap.YMidPoint);
        double LatitudeDegree = (DistanceFromMidPoint / TemperatureMap.YMidPoint) * 90;
        double LatitudeTemperatureFactor = (LatitudeTemperatureVariation * (cos((Pi/90) * LatitudeDegree))) + AverageTemperature;

        return LatitudeTemperatureFactor;
    };
    
    auto AltitudeFactorCalculation = [&](int y, int x) {
        double AltitudeTemperatureFactor = 0;

         if (TopographyMap.MapArray[y][x] * ElevationScaleFactor > 0) {
                AltitudeTemperatureFactor = -1 * (ElevationTemperatureLose * (TopographyMap.MapArray[y][x]/1000));
         }

        return AltitudeTemperatureFactor;
    };

    auto PerlinNoiseFactorCalculation = [&](int y, int x) {
        double PerlinNoiseTemperatureFactor = noise.GetNoise((float)x, (float)y) * PerlinNoiseTemperatureRange;

        return PerlinNoiseTemperatureFactor;
    };

    for (int y = 0; y < TemperatureMap.YDimension; y++) {
        double LatitudeTemperatureFactor = LatitudeFactorCalculation(y);

        for (int x = 0; x < TemperatureMap.XDimension; x++) {
            double AltitudeTemperatureFactor = AltitudeFactorCalculation(y, x);
            double PerlinNoiseTemperatureFactor = PerlinNoiseFactorCalculation(y, x);
           
            TemperatureMap.MapArray[y][x] = LatitudeTemperatureFactor + AltitudeTemperatureFactor + PerlinNoiseTemperatureFactor;
        }
    }    
}