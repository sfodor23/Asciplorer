#include <string>
#include <cmath>
#include <iostream>

#include "ArrayGenerationMethods.hpp"
#include "CoreMapMethods.hpp"
#include "MiscMethods.hpp"
#include "KnownLocationsMethods.hpp"

#include "../Libraries/FastNoiseLite.h"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/GenerationConstants.hpp"

#include "../RealTimeStatistics/RealTimeStatistics.hpp"

using namespace std;
using namespace GenerationConstants;

#define CALCULATE_SETTLEMENTS(biome) \
    CurrentStatistics.biome##TotalVillages = static_cast<int>((CurrentStatistics.biome##TotalPopulation * CurrentStatistics.VillagePercentage) / 10000); \
    CurrentStatistics.biome##TotalTowns = static_cast<int>((CurrentStatistics.biome##TotalPopulation * CurrentStatistics.TownPercentage) / 25000); \
    CurrentStatistics.biome##TotalCities = static_cast<int>((CurrentStatistics.biome##TotalPopulation * CurrentStatistics.CityPercentage) / 50000); \
    CurrentStatistics.biome##TotalCapitals = static_cast<int>((CurrentStatistics.biome##TotalPopulation * CurrentStatistics.CapitalPercentage) / 100000); \
    CurrentStatistics.biome##TotalMegacities = static_cast<int>((CurrentStatistics.biome##TotalPopulation * CurrentStatistics.MegacityPercentage) / 1000000);

#define PLACE_BIOME_SETTLEMENTS(biome) \
    if (CurrentStatistics.biome##Coordinates->GetSize() > 0) { \
        /* Place Villages */ \
        for (int i = 0; i < CurrentStatistics.biome##TotalVillages; i++) { \
            if (CurrentStatistics.biome##Coordinates->GetSize() == 0) break; \
            int Index = IndexedRandomNumberGenerator(CurrentStatistics.biome##Coordinates->GetSize()); \
            auto Coordinate = CurrentStatistics.biome##Coordinates->GetCoordinate(Index); \
            int x = Coordinate.first; \
            int y = Coordinate.second; \
            SiteMap.MapArray[y][x] = CurrentStatistics.Village; \
            CurrentStatistics.SettlementCoordinates->AddCoordinate(x, y); \
            CurrentStatistics.biome##Coordinates->RemoveCoordinate(x, y); \
        } \
        /* Place Towns */ \
        for (int i = 0; i < CurrentStatistics.biome##TotalTowns; i++) { \
            if (CurrentStatistics.biome##Coordinates->GetSize() == 0) break; \
            int Index = IndexedRandomNumberGenerator(CurrentStatistics.biome##Coordinates->GetSize()); \
            auto Coordinate = CurrentStatistics.biome##Coordinates->GetCoordinate(Index); \
            int x = Coordinate.first; \
            int y = Coordinate.second; \
            SiteMap.MapArray[y][x] = CurrentStatistics.Town; \
            CurrentStatistics.SettlementCoordinates->AddCoordinate(x, y); \
            CurrentStatistics.biome##Coordinates->RemoveCoordinate(x, y); \
        } \
        /* Place Cities */ \
        for (int i = 0; i < CurrentStatistics.biome##TotalCities; i++) { \
            if (CurrentStatistics.biome##Coordinates->GetSize() == 0) break; \
            int Index = IndexedRandomNumberGenerator(CurrentStatistics.biome##Coordinates->GetSize()); \
            auto Coordinate = CurrentStatistics.biome##Coordinates->GetCoordinate(Index); \
            int x = Coordinate.first; \
            int y = Coordinate.second; \
            SiteMap.MapArray[y][x] = CurrentStatistics.City; \
            CurrentStatistics.SettlementCoordinates->AddCoordinate(x, y); \
            CurrentStatistics.biome##Coordinates->RemoveCoordinate(x, y); \
        } \
        /* Place Capitals */ \
        for (int i = 0; i < CurrentStatistics.biome##TotalCapitals; i++) { \
            if (CurrentStatistics.biome##Coordinates->GetSize() == 0) break; \
            int Index = IndexedRandomNumberGenerator(CurrentStatistics.biome##Coordinates->GetSize()); \
            auto Coordinate = CurrentStatistics.biome##Coordinates->GetCoordinate(Index); \
            int x = Coordinate.first; \
            int y = Coordinate.second; \
            SiteMap.MapArray[y][x] = CurrentStatistics.Capital; \
            CurrentStatistics.SettlementCoordinates->AddCoordinate(x, y); \
            CurrentStatistics.biome##Coordinates->RemoveCoordinate(x, y); \
        } \
        /* Place Megacities */ \
        for (int i = 0; i < CurrentStatistics.biome##TotalMegacities; i++) { \
            if (CurrentStatistics.biome##Coordinates->GetSize() == 0) break; \
            int Index = IndexedRandomNumberGenerator(CurrentStatistics.biome##Coordinates->GetSize()); \
            auto Coordinate = CurrentStatistics.biome##Coordinates->GetCoordinate(Index); \
            int x = Coordinate.first; \
            int y = Coordinate.second; \
            SiteMap.MapArray[y][x] = CurrentStatistics.Megacity; \
            CurrentStatistics.SettlementCoordinates->AddCoordinate(x, y); \
            CurrentStatistics.biome##Coordinates->RemoveCoordinate(x, y); \
        } \
    }

void TopographyMapArrayValueGeneration(Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(CurrentStatistics.TopographySeed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(CurrentStatistics.TopographyFrequency);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(CurrentStatistics.TopographyLayers);
    noise.SetFractalLacunarity(CurrentStatistics.TopographySpreadiness);
    noise.SetFractalGain(CurrentStatistics.TopographyLayerGain);

    for (int y = 0; y < TopographyMap.YDimension; y++) {
        for (int x = 0; x < TopographyMap.XDimension; x++) {
            TopographyMap.MapArray[y][x] = noise.GetNoise((float)x, (float)y) * ElevationScaleFactor;
        }
    }
}

void BiomeMapArrayValueGeneration(Map<float>& TopographyMap, Map<string>& BiomeMap, Map<double>& PrecipitationMap, Map<double>& TemperatureMap) { 
    auto BaseTerrainCalculation = [&](int y, int x) {
        char TileBaseTerrain = '0';

        if (TopographyMap.MapArray[y][x] < LandElevationRange[0]) {
            TileBaseTerrain = 'W';

            return TileBaseTerrain;
        }

        if (TopographyMap.MapArray[y][x] >= LandElevationRange[0] && TopographyMap.MapArray[y][x] < LandElevationRange[1]) {
            TileBaseTerrain = 'L';

            CurrentStatistics.LandTileCount += 1;
            CurrentStatistics.LandCoordinates->AddCoordinate(x, y);

            return TileBaseTerrain;
        }

        if (TopographyMap.MapArray[y][x] >= LandElevationRange[1]) {
            TileBaseTerrain = 'M';

            CurrentStatistics.LandTileCount += 1;

            return TileBaseTerrain;
        }

        return TileBaseTerrain;
    };

    auto BiomeCalculation = [&](int y, int x, char TileBaseTerrain) {
        switch(TileBaseTerrain) {
            case 'W':
                if (TemperatureMap.MapArray[y][x] >= WaterTemperatureRange[1]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.WarmWater;
                }
            
                else if (TemperatureMap.MapArray[y][x] >= WaterTemperatureRange[0] && TemperatureMap.MapArray[y][x] < WaterTemperatureRange[1]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Water;
                }

                else if (TemperatureMap.MapArray[y][x] < WaterTemperatureRange[0]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.IcyWater;
                }
                
                else {
                    BiomeMap.MapArray[y][x] = TileCharacters::ErrorTile;
                }

                break;

            case 'L':
                if (TemperatureMap.MapArray[y][x] >= RainforestTemperatureRange[0] && PrecipitationMap.MapArray[y][x] >= RainforestPrecipitationRange[0]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Rainforest;
                    CurrentStatistics.RainforestTileCount += 1;
                    CurrentStatistics.RainforestCoordinates->AddCoordinate(x, y);
                }
                
                else if (TemperatureMap.MapArray[y][x] >= DesertTemperatureRange[0] && PrecipitationMap.MapArray[y][x] < DesertPrecipitationRange[1]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Desert;
                    CurrentStatistics.DesertTileCount += 1;
                    CurrentStatistics.DesertCoordinates->AddCoordinate(x, y);
                }

                else if (TemperatureMap.MapArray[y][x] < ForestTemperatureRange[1] && TemperatureMap.MapArray[y][x] >= ForestTemperatureRange[0] && PrecipitationMap.MapArray[y][x] >= ForestPrecipitationRange[0] && PrecipitationMap.MapArray[y][x] < ForestPrecipitationRange[1]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Forest;
                    CurrentStatistics.ForestTileCount += 1;
                    CurrentStatistics.ForestCoordinates->AddCoordinate(x, y);
                }

                else if (TemperatureMap.MapArray[y][x] < BorealTemperatureRange[1] && TemperatureMap.MapArray[y][x] >= BorealTemperatureRange[0]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Boreal;
                    CurrentStatistics.BorealTileCount += 1;
                    CurrentStatistics.BorealCoordinates->AddCoordinate(x, y);
                }
            
                else if (TemperatureMap.MapArray[y][x] < TundraTemperatureRange[1]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Tundra;
                    CurrentStatistics.TundraTileCount += 1;
                    CurrentStatistics.TundraCoordinates->AddCoordinate(x, y);
                }
                else {
                    BiomeMap.MapArray[y][x] = TileCharacters::ErrorTile;
                    cout << "\n" << TemperatureMap.MapArray[y][x] << " C " << PrecipitationMap.MapArray[y][x] << " mm";
                }

                break;

            case 'M':
                if (TemperatureMap.MapArray[y][x] >= MountainTemperatureRange[0]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.Mountain;
                    CurrentStatistics.MountainTileCount += 1;
                    CurrentStatistics.MountainCoordinates->AddCoordinate(x, y);
                }

                else if (TemperatureMap.MapArray[y][x] < MountainTemperatureRange[0]) {
                    BiomeMap.MapArray[y][x] = CurrentStatistics.IceCappedMountain;
                    CurrentStatistics.IceCappedMountainTileCount += 1;
                    CurrentStatistics.IceCappedMountainCoordinates->AddCoordinate(x, y);
                }
                else {
                    BiomeMap.MapArray[y][x] = TileCharacters::ErrorTile;
                }

                break;
            
            default:
                cout << "If You Are Seeing This The Land Generator Broke Itself Somehow";
                break;
        }
    };
    
    for (int y = 0; y < BiomeMap.YDimension; y++) {
        for (int x = 0; x < BiomeMap.XDimension; x++) {
           char TileBaseTerrain = BaseTerrainCalculation(y, x);
           BiomeCalculation(y, x, TileBaseTerrain);
        }
    }
}

void PrecipitationMapArrayValueGeneration(Map<double>& PrecipitationMap, Map<float>& TopographyMap) {
    FastNoiseLite noise;
    noise.SetSeed(RandomNumberGenerator(CurrentStatistics.MapSeedCount));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(7);
    noise.SetFractalLacunarity(1.6f);
    noise.SetFractalGain(0.6f);
    
    auto LatitudeFactorCalculation = [&](int y) {
        double LatitudeDegree = ((double)(y - PrecipitationMap.YMidPoint) / PrecipitationMap.YMidPoint) * 90.0;
        double LatitudePrecipitationFactor = 1;

        if (LatitudeDegree < (25.47 + CurrentStatistics.LatitudeShift) && LatitudeDegree > (-25.47 + CurrentStatistics.LatitudeShift)) {
            LatitudePrecipitationFactor = ((250 * (cos((Pi/90) * (LatitudeDegree - CurrentStatistics.LatitudeShift))))) + 1000 + ((750 * (cos((Pi/25) * (LatitudeDegree - CurrentStatistics.LatitudeShift)))));
        }

        if (LatitudeDegree >= (25.47 + CurrentStatistics.LatitudeShift) || LatitudeDegree <= (-25.47 + CurrentStatistics.LatitudeShift)) {
            LatitudePrecipitationFactor = (-250 * cos(((Pi/30) * (LatitudeDegree - CurrentStatistics.LatitudeShift)) - 40.8)) + 660;
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
        double LatitudeDegree = ((double)(y - PrecipitationMap.YMidPoint) / PrecipitationMap.YMidPoint) * 90.0;
        double WindPrecipitationFactor = 1;

        if ((LatitudeDegree < (30 + CurrentStatistics.LatitudeShift) || LatitudeDegree > (-30 + CurrentStatistics.LatitudeShift)) || (LatitudeDegree >= (60 + CurrentStatistics.LatitudeShift) || LatitudeDegree <= (-60 + CurrentStatistics.LatitudeShift))) {
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

        if ((LatitudeDegree >= (30 + CurrentStatistics.LatitudeShift) || LatitudeDegree <= (-30 + CurrentStatistics.LatitudeShift)) || (LatitudeDegree < (60 + CurrentStatistics.LatitudeShift) || LatitudeDegree > (-60 + CurrentStatistics.LatitudeShift))) {
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
    noise.SetSeed(RandomNumberGenerator(CurrentStatistics.MapSeedCount));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(7);
    noise.SetFractalLacunarity(1.6f);
    noise.SetFractalGain(0.6f);

    auto LatitudeFactorCalculation = [&](int y) {
        double LatitudeDegree = ((double)(y - TemperatureMap.YMidPoint) / TemperatureMap.YMidPoint) * 90.0;
        double LatitudeTemperatureFactor = (CurrentStatistics.LatitudeTemperatureVariation * (cos(((Pi/90) * LatitudeDegree) - ((Pi/90) * CurrentStatistics.LatitudeShift)))) + CurrentStatistics.AverageTemperature;
    
        return LatitudeTemperatureFactor;
    };
    
    auto AltitudeFactorCalculation = [&](int y, int x) {
        double AltitudeTemperatureFactor = 0;

         if (TopographyMap.MapArray[y][x] > 0) {
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

void SiteMapArrayValueGeneration(Map<string>& SiteMap) {
    CurrentStatistics.ForestTotalPopulation = CurrentStatistics.ForestTileCount * ForestPopulationDensity;
    CurrentStatistics.RainforestTotalPopulation = CurrentStatistics.RainforestTileCount * RainforestPopulationDensity;
    CurrentStatistics.DesertTotalPopulation = CurrentStatistics.DesertTileCount * DesertPopulationDensity;
    CurrentStatistics.BorealTotalPopulation = CurrentStatistics.BorealTileCount * BorealPopulationDensity;
    CurrentStatistics.TundraTotalPopulation = CurrentStatistics.TundraTileCount * TundraPopulationDensity;
    CurrentStatistics.MountainTotalPopulation = CurrentStatistics.MountainTileCount * MountainPopulationDensity;
    CurrentStatistics.IceCappedMountainTotalPopulation = CurrentStatistics.IceCappedMountainTileCount * IceCappedMountainPopulationDensity;

    CALCULATE_SETTLEMENTS(Forest)
    CALCULATE_SETTLEMENTS(Rainforest)
    CALCULATE_SETTLEMENTS(Desert)
    CALCULATE_SETTLEMENTS(Boreal)
    CALCULATE_SETTLEMENTS(Tundra)
    CALCULATE_SETTLEMENTS(Mountain)
    CALCULATE_SETTLEMENTS(IceCappedMountain)

    PLACE_BIOME_SETTLEMENTS(Forest)
    PLACE_BIOME_SETTLEMENTS(Rainforest)
    PLACE_BIOME_SETTLEMENTS(Desert)
    PLACE_BIOME_SETTLEMENTS(Boreal)
    PLACE_BIOME_SETTLEMENTS(Tundra) 
    PLACE_BIOME_SETTLEMENTS(Mountain)
    PLACE_BIOME_SETTLEMENTS(IceCappedMountain)
}

void CombinedMapArrayValueGeneration(Map<string>& CombinedMap, Map<string>& SiteMap, Map<string>& BiomeMap) {
    for (int y = 0; y < CombinedMap.YDimension; y++) {
        for (int x = 0; x < CombinedMap.XDimension; x++) {
            if (SiteMap.MapArray[y][x] == CurrentStatistics.Village) {
                CombinedMap.MapArray[y][x] = CurrentStatistics.Village;
            }

            else if (SiteMap.MapArray[y][x] == CurrentStatistics.Town) {
                CombinedMap.MapArray[y][x] = CurrentStatistics.Town;
            }

            else if (SiteMap.MapArray[y][x] == CurrentStatistics.City) {
                CombinedMap.MapArray[y][x] = CurrentStatistics.City;
            }

            else if (SiteMap.MapArray[y][x] == CurrentStatistics.Capital) {
                CombinedMap.MapArray[y][x] = CurrentStatistics.Capital;
            }

            else if (SiteMap.MapArray[y][x] == CurrentStatistics.Megacity) {
                CombinedMap.MapArray[y][x] = CurrentStatistics.Megacity;
            }

            else {
                CombinedMap.MapArray[y][x] = BiomeMap.MapArray[y][x];
            }
        }
    }
}

#undef CALCULATE_SETTLEMENTS
#undef PLACE_BIOME_SETTLEMENTS