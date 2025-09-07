#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include "../RealTimeStatistics/RealTimeStatistics.hpp"
#include "../ProgramMethods/ArrayGenerationMethods.hpp"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/LineStyles.hpp"

using namespace std;
using namespace LineStyles;

void TargetTypeCalculation(Map<string>& BiomeMap, Map<string>& CombinedMap) {
    string TargetBiomeValue = BiomeMap.MapArray[CurrentStatistics.TargetCoordinate[1]][CurrentStatistics.TargetCoordinate[0]];
    string TargetSettlementValue = CombinedMap.MapArray[CurrentStatistics.TargetCoordinate[1]][CurrentStatistics.TargetCoordinate[0]];

    CurrentStatistics.TargetBiomeType = "Unknown";

    if (TargetBiomeValue == CurrentStatistics.Forest) {
        CurrentStatistics.TargetBiomeType = "Forest";
    }
    else if (TargetBiomeValue == CurrentStatistics.Rainforest) {
        CurrentStatistics.TargetBiomeType = "Rainforest";
    }
    else if (TargetBiomeValue == CurrentStatistics.Desert) {
        CurrentStatistics.TargetBiomeType = "Desert";
    }
    else if (TargetBiomeValue == CurrentStatistics.Boreal) {
        CurrentStatistics.TargetBiomeType = "Boreal";
    }
    else if (TargetBiomeValue == CurrentStatistics.Tundra) {
        CurrentStatistics.TargetBiomeType = "Tundra";
    }
    else if (TargetBiomeValue == CurrentStatistics.Mountain) {
        CurrentStatistics.TargetBiomeType = "Mountain";
    }
    else if (TargetBiomeValue == CurrentStatistics.IceCappedMountain) {
        CurrentStatistics.TargetBiomeType = "Ice Capped Mountain";
    }

    CurrentStatistics.TargetSettlementType = "None";

    if (TargetSettlementValue == CurrentStatistics.Village) {
        CurrentStatistics.TargetSettlementType = "Village";
    }
    else if (TargetSettlementValue == CurrentStatistics.Town) {
        CurrentStatistics.TargetSettlementType = "Town";
    }
    else if (TargetSettlementValue == CurrentStatistics.City) {
        CurrentStatistics.TargetSettlementType = "City";
    }
    else if (TargetSettlementValue == CurrentStatistics.Capital) {
        CurrentStatistics.TargetSettlementType = "Capital";
    }
    else if (TargetSettlementValue == CurrentStatistics.Megacity) {
        CurrentStatistics.TargetSettlementType = "Megacity";
    }
}

void CrewNumberThresholdCheck() {
    if (CurrentStatistics.Crew < 10) {
        CurrentStatistics.Crew = 10;
    }

    if (CurrentStatistics.Crew > 250) {
        CurrentStatistics.Crew = 250;
    }
}

void CalculateUntrackedStatistics(Map<string>& BiomeMap, Map<string>& CombinedMap) {
    TargetTypeCalculation(BiomeMap, CombinedMap);
    CrewNumberThresholdCheck();
}

void QueueWorldInformationPrints() {
    CurrentStatistics.PrintingLine[0] += GroupHeader;
    CurrentStatistics.PrintingLine[1] += "                     WORLD INFORMATION                        ";
    CurrentStatistics.PrintingLine[2] += GroupHeader;

    CurrentStatistics.PrintingLine[3] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[4] += "                  [ GENERAL INFORMATION ]                     ";
    CurrentStatistics.PrintingLine[5] += FormattedEmptyLine;

    string MapAreaText = "Map Area: " + to_string(CurrentStatistics.MapArea) + " Tiles (" + to_string(CurrentStatistics.MapDimensionX) + " Tiles by " + to_string(CurrentStatistics.MapDimensionY) + " Tiles)";
    int MapAreaTextSpaces = 62 - MapAreaText.length();
    CurrentStatistics.PrintingLine[6] += MapAreaText + string(max(0, MapAreaTextSpaces), ' ');

    string MapTypeText = "Map Generation Type: " + CurrentStatistics.MapType + " Map";
    int MapTypeTextSpaces = 62 - MapTypeText.length();
    CurrentStatistics.PrintingLine[7] += MapTypeText + string(max(0, MapTypeTextSpaces), ' ');

    string ClimateText = "Map Climate Type: " + CurrentStatistics.MapClimateType + " Climate";
    int ClimateTextSpaces = 62 - ClimateText.length();
    CurrentStatistics.PrintingLine[8] += ClimateText + string(max(0, ClimateTextSpaces), ' ');

    string StyleText = "Map Color Palette/Style: " + CurrentStatistics.MapStyle + " Style";
    int StyleTextSpaces = 62 - StyleText.length();
    CurrentStatistics.PrintingLine[9] += StyleText + string(max(0, StyleTextSpaces), ' ');

    string SeedText = "Map Seed: " + to_string(CurrentStatistics.TopographySeed);
    int SeedTextSpaces = 62 - SeedText.length();
    CurrentStatistics.PrintingLine[10] += SeedText + string(max(0, SeedTextSpaces), ' ');

    CurrentStatistics.PrintingLine[11] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[12] += "                   [ BIOME INFORMATION ]                      ";
    CurrentStatistics.PrintingLine[13] += FormattedEmptyLine;

    string basicCompText = "Basic World Composition:";
    int basicCompSpaces = 62 - basicCompText.length();
    CurrentStatistics.PrintingLine[14] += basicCompText + string(max(0, basicCompSpaces), ' ');
    
    string landText = to_string((double)CurrentStatistics.LandTileCount / CurrentStatistics.MapArea * 100) + "% Land (" + to_string(CurrentStatistics.LandTileCount) + " Tiles)";
    int landSpaces = 62 - landText.length();
    CurrentStatistics.PrintingLine[15] += landText + string(max(0, landSpaces), ' ');
    
    string waterText = to_string((double)(CurrentStatistics.MapArea - CurrentStatistics.LandTileCount) / CurrentStatistics.MapArea * 100) + "% Water (" + to_string(CurrentStatistics.MapArea - CurrentStatistics.LandTileCount) + " Tiles)";
    int waterSpaces = 62 - waterText.length();
    CurrentStatistics.PrintingLine[16] += waterText + string(max(0, waterSpaces), ' ');
    
    CurrentStatistics.PrintingLine[17] += FormattedEmptyLine;
    
    string advancedCompText = "Advanced World Composition:";
    int advancedCompSpaces = 62 - advancedCompText.length();
    CurrentStatistics.PrintingLine[18] += advancedCompText + string(max(0, advancedCompSpaces), ' ');
    
    string forestText = to_string((double)CurrentStatistics.ForestTileCount / CurrentStatistics.MapArea * 100) + "% Forest (" + to_string(CurrentStatistics.ForestTileCount) + " Tiles)";
    int forestSpaces = 62 - forestText.length();
    CurrentStatistics.PrintingLine[19] += forestText + string(max(0, forestSpaces), ' ');
    
    string rainforestText = to_string((double)CurrentStatistics.RainforestTileCount / CurrentStatistics.MapArea * 100) + "% Rainforest (" + to_string(CurrentStatistics.RainforestTileCount) + " Tiles)";
    int rainforestSpaces = 62 - rainforestText.length();
    CurrentStatistics.PrintingLine[20] += rainforestText + string(max(0, rainforestSpaces), ' ');
    
    string desertText = to_string((double)CurrentStatistics.DesertTileCount / CurrentStatistics.MapArea * 100) + "% Desert (" + to_string(CurrentStatistics.DesertTileCount) + " Tiles)";
    int desertSpaces = 62 - desertText.length();
    CurrentStatistics.PrintingLine[21] += desertText + string(max(0, desertSpaces), ' ');
    
    string borealText = to_string((double)CurrentStatistics.BorealTileCount / CurrentStatistics.MapArea * 100) + "% Boreal (" + to_string(CurrentStatistics.BorealTileCount) + " Tiles)";
    int borealSpaces = 62 - borealText.length();
    CurrentStatistics.PrintingLine[22] += borealText + string(max(0, borealSpaces), ' ');
    
    string tundraText = to_string((double)CurrentStatistics.TundraTileCount / CurrentStatistics.MapArea * 100) + "% Tundra (" + to_string(CurrentStatistics.TundraTileCount) + " Tiles)";
    int tundraSpaces = 62 - tundraText.length();
    CurrentStatistics.PrintingLine[23] += tundraText + string(max(0, tundraSpaces), ' ');
    
    string mountainText = to_string((double)CurrentStatistics.MountainTileCount / CurrentStatistics.MapArea * 100) + "% Mountain (" + to_string(CurrentStatistics.MountainTileCount) + " Tiles)";
    int mountainSpaces = 62 - mountainText.length();
    CurrentStatistics.PrintingLine[24] += mountainText + string(max(0, mountainSpaces), ' ');
    
    string iceMountainText = to_string((double)CurrentStatistics.IceCappedMountainTileCount / CurrentStatistics.MapArea * 100) + "% Ice Capped Mountain (" + to_string(CurrentStatistics.IceCappedMountainTileCount) + " Tiles)";
    int iceMountainSpaces = 62 - iceMountainText.length();
    CurrentStatistics.PrintingLine[25] += iceMountainText + string(max(0, iceMountainSpaces), ' ');
    
    CurrentStatistics.PrintingLine[26] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[27] += "                 [ SETTLEMENT INFORMATION ]                   ";
    CurrentStatistics.PrintingLine[28] += FormattedEmptyLine;
    
    int totalPopulation = CurrentStatistics.ForestTotalPopulation + CurrentStatistics.DesertTotalPopulation + CurrentStatistics.RainforestTotalPopulation + CurrentStatistics.BorealTotalPopulation + CurrentStatistics.TundraTotalPopulation + CurrentStatistics.MountainTotalPopulation + CurrentStatistics.IceCappedMountainTotalPopulation;
    string populationText = "Total Population: " + to_string(totalPopulation) + " People";
    int populationSpaces = 62 - populationText.length();
    CurrentStatistics.PrintingLine[29] += populationText + string(max(0, populationSpaces), ' ');
    
    string settlementCountText = "Settlement Count:";
    int settlementCountSpaces = 62 - settlementCountText.length();
    CurrentStatistics.PrintingLine[30] += settlementCountText + string(max(0, settlementCountSpaces), ' ');
    
    int totalVillages = CurrentStatistics.RainforestTotalVillages + CurrentStatistics.DesertTotalVillages + CurrentStatistics.ForestTotalVillages + CurrentStatistics.BorealTotalVillages + CurrentStatistics.TundraTotalVillages + CurrentStatistics.MountainTotalVillages + CurrentStatistics.IceCappedMountainTotalVillages;
    string villageText = to_string(totalVillages) + (totalVillages == 1 ? " Village" : " Villages");
    int villageSpaces = 62 - villageText.length();
    CurrentStatistics.PrintingLine[31] += villageText + string(max(0, villageSpaces), ' ');
    
    int totalTowns = CurrentStatistics.RainforestTotalTowns + CurrentStatistics.DesertTotalTowns + CurrentStatistics.ForestTotalTowns + CurrentStatistics.BorealTotalTowns + CurrentStatistics.TundraTotalTowns + CurrentStatistics.MountainTotalTowns + CurrentStatistics.IceCappedMountainTotalTowns;
    string townText = to_string(totalTowns) + (totalTowns == 1 ? " Town" : " Towns");
    int townSpaces = 62 - townText.length();
    CurrentStatistics.PrintingLine[32] += townText + string(max(0, townSpaces), ' ');
    
    int totalCities = CurrentStatistics.RainforestTotalCities + CurrentStatistics.DesertTotalCities + CurrentStatistics.ForestTotalCities + CurrentStatistics.BorealTotalCities + CurrentStatistics.TundraTotalCities + CurrentStatistics.MountainTotalCities + CurrentStatistics.IceCappedMountainTotalCities;
    string cityText = to_string(totalCities) + (totalCities == 1 ? " City" : " Cities");
    int citySpaces = 62 - cityText.length();
    CurrentStatistics.PrintingLine[33] += cityText + string(max(0, citySpaces), ' ');
    
    int totalCapitals = CurrentStatistics.RainforestTotalCapitals + CurrentStatistics.DesertTotalCapitals + CurrentStatistics.ForestTotalCapitals + CurrentStatistics.BorealTotalCapitals + CurrentStatistics.TundraTotalCapitals + CurrentStatistics.MountainTotalCapitals + CurrentStatistics.IceCappedMountainTotalCapitals;
    string capitalText = to_string(totalCapitals) + (totalCapitals == 1 ? " Capital" : " Capitals");
    int capitalSpaces = 62 - capitalText.length();
    CurrentStatistics.PrintingLine[34] += capitalText + string(max(0, capitalSpaces), ' ');
    
    int totalMegacities = CurrentStatistics.RainforestTotalMegacities + CurrentStatistics.DesertTotalMegacities + CurrentStatistics.ForestTotalMegacities + CurrentStatistics.BorealTotalMegacities + CurrentStatistics.TundraTotalMegacities + CurrentStatistics.MountainTotalMegacities + CurrentStatistics.IceCappedMountainTotalMegacities;
    string megacityText = to_string(totalMegacities) + (totalMegacities == 1 ? " Megacity" : " Megacities");
    int megacitySpaces = 62 - megacityText.length();
    CurrentStatistics.PrintingLine[35] += megacityText + string(max(0, megacitySpaces), ' ');
}

void QueueSimulationStatisticsPrints() {
    CurrentStatistics.PrintingLine[0] += GroupHeader;
    CurrentStatistics.PrintingLine[1] += "                    SIMULATION STATISTICS                     ";
    CurrentStatistics.PrintingLine[2] += GroupHeader;

    CurrentStatistics.PrintingLine[3] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[4] += "                   [ NAVIGATION STATISTICS ]                  ";
    CurrentStatistics.PrintingLine[5] += FormattedEmptyLine;
    
    CurrentStatistics.PrintingLine[6] += "Current Position: (" + to_string(CurrentStatistics.CurrentCoordinate[0]) + ", " + to_string(CurrentStatistics.CurrentCoordinate[1]) + ")";
    
    CurrentStatistics.PrintingLine[7] += "Target Coordinate: (" + to_string(CurrentStatistics.TargetCoordinate[0]) + ", " + to_string(CurrentStatistics.TargetCoordinate[1]) + ")";
    
    CurrentStatistics.PrintingLine[8] += "Distance To Target: " + to_string((int)sqrt(((abs(CurrentStatistics.TargetCoordinate[0] - CurrentStatistics.CurrentCoordinate[0])) * (abs(CurrentStatistics.TargetCoordinate[0] - CurrentStatistics.CurrentCoordinate[0]))) + ((abs(CurrentStatistics.TargetCoordinate[1] - CurrentStatistics.CurrentCoordinate[1])) * (abs(CurrentStatistics.TargetCoordinate[1] - CurrentStatistics.CurrentCoordinate[1]))))) + " Tiles";
    
    CurrentStatistics.PrintingLine[9] += "Target Type: " + CurrentStatistics.TargetBiomeType + " " + CurrentStatistics.TargetSettlementType;
    
    CurrentStatistics.PrintingLine[10] += "Targets Reached: " + to_string(CurrentStatistics.TargetsReached) + " Targets";
    
    CurrentStatistics.PrintingLine[11] += "Tiles Travelled: " + to_string(CurrentStatistics.TilesTravelled) + " Tiles";
    
    CurrentStatistics.PrintingLine[12] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[13] += "                    [ MONETARY STATISTICS ]                   ";
    CurrentStatistics.PrintingLine[14] += FormattedEmptyLine;
    
    if (CurrentStatistics.Doubloons >= 0) {
        CurrentStatistics.PrintingLine[15] += "Doubloons: " + to_string(CurrentStatistics.Doubloons) + " Doubloons";
    }
    if (CurrentStatistics.Doubloons < 0) {
        CurrentStatistics.PrintingLine[15] += "Doubloons: " + to_string(abs(CurrentStatistics.Doubloons)) + " Doubloons In Debt";
    }
    
    double doubloonsPerCapita = (CurrentStatistics.Crew > 0) ? 
    (double)CurrentStatistics.Doubloons / CurrentStatistics.Crew : 0.0;
    CurrentStatistics.PrintingLine[16] += "Doubloons Per Capita: " + to_string(doubloonsPerCapita) + " Doubloons";

    CurrentStatistics.PrintingLine[17] += FormattedEmptyLine;
    CurrentStatistics.PrintingLine[18] += "                   [ PERSONAGES STATISTICS ]                  ";
    CurrentStatistics.PrintingLine[19] += FormattedEmptyLine;
    
    CurrentStatistics.PrintingLine[20] += "Crew: " + to_string(CurrentStatistics.Crew) + " Crewmembers";

    string CaptainName;
    if (!CurrentStatistics.CurrentCaptain.empty()) {
        CaptainName = string(CurrentStatistics.CurrentCaptain.begin(), CurrentStatistics.CurrentCaptain.end());
    } else {
        CaptainName = "Unknown";
    }
    CurrentStatistics.PrintingLine[21] += "Captain: " + CaptainName;
}

