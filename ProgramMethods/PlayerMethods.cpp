#include <iostream>
#include <cmath>

#include "CoreMapMethods.hpp"
#include "MiscMethods.hpp"
#include "KnownLocationsMethods.hpp"

#include "../RealTimeStatistics/RealTimeStatistics.hpp"

#include "../Libraries/GenerationConstants.hpp"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/NameGeneration/dasmig/namegen.hpp"


using namespace std;
using ng = dasmig::ng;

struct TileOption {
    int XDisplacement;
    int YDisplacement;
    string TerrainType;
};

void SetStartingCoordinate(Map<string>& CombinedMap) {
    CurrentStatistics.StartingCoordinate[0] = static_cast<int>((CombinedMap.XDimension - 1) * (0.25 + (RandomNumberGenerator(50) * 0.01)));
    CurrentStatistics.StartingCoordinate[1] = static_cast<int>((CombinedMap.YDimension - 1) * (0.25 + (RandomNumberGenerator(50) * 0.01)));

    CurrentStatistics.CurrentCoordinate[0] = CurrentStatistics.StartingCoordinate[0];
    CurrentStatistics.CurrentCoordinate[1] = CurrentStatistics.StartingCoordinate[1];
}

void GiveTargetRewards(Map<string>& CombinedMap) {
    string TargetSettlementValue = CombinedMap.MapArray[CurrentStatistics.TargetCoordinate[1]][CurrentStatistics.TargetCoordinate[0]];
        
    if (TargetSettlementValue == CurrentStatistics.Village) {
        CurrentStatistics.Doubloons += (RandomNumberGenerator(25) + 88);
        CurrentStatistics.Crew += (RandomNumberGenerator(4) + 13);
    }

    else if (TargetSettlementValue == CurrentStatistics.Town) {
        CurrentStatistics.Doubloons += (RandomNumberGenerator(50) + 225);
        CurrentStatistics.Crew += (RandomNumberGenerator(4) + 18);
    }
            
    else if (TargetSettlementValue == CurrentStatistics.City) {
        CurrentStatistics.Doubloons += (RandomNumberGenerator(100) + 450);
        CurrentStatistics.Crew += (RandomNumberGenerator(4) + 23);
    }
            
    else if (TargetSettlementValue == CurrentStatistics.Capital) {
        CurrentStatistics.Doubloons += (RandomNumberGenerator(200) + 900);
        CurrentStatistics.Crew += (RandomNumberGenerator(4) + 28);
    }
            
    else if (TargetSettlementValue == CurrentStatistics.Megacity) {
        CurrentStatistics.Doubloons += (RandomNumberGenerator(1000) + 4500);
        CurrentStatistics.Crew += (RandomNumberGenerator(4) + 33);
    }
}

void SetTargetCoordinate(Map<string>& CombinedMap) {
    if (CurrentStatistics.SettlementCoordinates->GetSize() == 0) {
        cout << "No settlements found! Cannot set target coordinate." << endl;
        return;
    }

    bool FoundTargetSettlement = false;

    for (int i = 400; i <= 10000 && FoundTargetSettlement == false; i += 400) {
        for (int j = 0; j < CurrentStatistics.SettlementCoordinates->GetSize() && FoundTargetSettlement == false; j++) {
            int RandomizedIndex = IndexedRandomNumberGenerator(CurrentStatistics.SettlementCoordinates->GetSize());
            pair<int, int> TargetCoordinatePlaceHolder = CurrentStatistics.SettlementCoordinates->GetCoordinate(RandomizedIndex);

            if (abs(TargetCoordinatePlaceHolder.first - CurrentStatistics.CurrentCoordinate[0]) < i && abs(TargetCoordinatePlaceHolder.second - CurrentStatistics.CurrentCoordinate[1]) < i) {
                CurrentStatistics.TargetCoordinate[0] = TargetCoordinatePlaceHolder.first;
                CurrentStatistics.TargetCoordinate[1] = TargetCoordinatePlaceHolder.second;
                FoundTargetSettlement = true;
            }
            
        }
    }
}

void PreviousCoordinateCleanup(Map<string>& CombinedMap) {
    CombinedMap.MapArray[CurrentStatistics.PreviousCoordinate[1]][CurrentStatistics.PreviousCoordinate[0]] = CurrentStatistics.PreviousCoordinateState;
}

void MovementCalculation(Map<string>& CombinedMap) {
    auto CalculateGeneralDirectionToTarget = [](Map<string>& CombinedMap, int& XMovement, int& YMovement) {
        if (CurrentStatistics.CurrentCoordinate[0] == CurrentStatistics.TargetCoordinate[0] && CurrentStatistics.CurrentCoordinate[1] == CurrentStatistics.TargetCoordinate[1]) {
            CurrentStatistics.TargetsReached += 1;

            GiveTargetRewards(CombinedMap);
            SetTargetCoordinate(CombinedMap);
        
            return;
        }
    
        if ((CurrentStatistics.TargetCoordinate[0] - CurrentStatistics.CurrentCoordinate[0]) > 0) {
            XMovement = 1;    
        }
        
        if ((CurrentStatistics.TargetCoordinate[0] - CurrentStatistics.CurrentCoordinate[0]) < 0) {
            XMovement = -1;
        }
        
        if ((CurrentStatistics.TargetCoordinate[0] - CurrentStatistics.CurrentCoordinate[0]) == 0) {
            XMovement = 0;
        }
    
        if ((CurrentStatistics.TargetCoordinate[1] - CurrentStatistics.CurrentCoordinate[1]) > 0) {
            YMovement = 1;
        }
    
        if ((CurrentStatistics.TargetCoordinate[1] - CurrentStatistics.CurrentCoordinate[1]) < 0) {
            YMovement = -1;
        }
    
        if ((CurrentStatistics.TargetCoordinate[1] - CurrentStatistics.CurrentCoordinate[1]) == 0) {
            YMovement = 0;
        }
    };

    auto LogPlausibleMovementTiles = [](Map<string>& CombinedMap, int& XMovement, int& YMovement, TileOption TileOptionTable[8], int& TileOptionsFilled) {
        for (int y = -1; y < 2; y++) {
            for (int x = -1; x < 2; x++) {
                if (x == 0 && y == 0) continue;

                bool isMovingTowardTarget = true;

                if (XMovement > 0 && x < 0) isMovingTowardTarget = false;
    
                if (XMovement < 0 && x > 0) isMovingTowardTarget = false;
        
                if (YMovement > 0 && y < 0) isMovingTowardTarget = false;
    
                if (YMovement < 0 && y > 0) isMovingTowardTarget = false;

                if (YMovement == 0 && y != 0) isMovingTowardTarget = false;

                if (XMovement == 0 && x != 0) isMovingTowardTarget = false;
        
                if (!isMovingTowardTarget) continue;

                if (CurrentStatistics.CurrentCoordinate[0] + x < 0 || 
                    CurrentStatistics.CurrentCoordinate[0] + x >= CombinedMap.XDimension || 
                    CurrentStatistics.CurrentCoordinate[1] + y < 0 || 
                    CurrentStatistics.CurrentCoordinate[1] + y >= CombinedMap.YDimension) {
                    continue;
                }

                if (CurrentStatistics.CurrentCoordinate[0] + x == CurrentStatistics.PreviousCoordinate[0] && CurrentStatistics.CurrentCoordinate[1] + y == CurrentStatistics.PreviousCoordinate[1]) {
                    continue;
                }

                TileOptionTable[TileOptionsFilled] = {x, y, CombinedMap.MapArray[CurrentStatistics.CurrentCoordinate[1] + y][CurrentStatistics.CurrentCoordinate[0] + x]};

                TileOptionsFilled += 1;
            }
        }
    };

    auto TileSelectionByPreference = [](int& TileOptionsFilled, TileOption TileOptionTable[8]) {
        bool TileSelected = false;

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Village ||
                TileOptionTable[i].TerrainType == CurrentStatistics.Town ||
                TileOptionTable[i].TerrainType == CurrentStatistics.City ||
                TileOptionTable[i].TerrainType == CurrentStatistics.Capital ||
                TileOptionTable[i].TerrainType == CurrentStatistics.Megacity) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Water || 
                TileOptionTable[i].TerrainType == CurrentStatistics.WarmWater || 
                TileOptionTable[i].TerrainType == CurrentStatistics.IcyWater) {
                if (RandomNumberGenerator(5) != 5 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Forest) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Rainforest || 
                TileOptionTable[i].TerrainType == CurrentStatistics.Desert || 
                TileOptionTable[i].TerrainType == CurrentStatistics.Boreal) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Tundra) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.Mountain) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }

        for (int i = 0; i < TileOptionsFilled && !TileSelected; i++) {
            if (TileOptionTable[i].TerrainType == CurrentStatistics.IceCappedMountain) {
                if (RandomNumberGenerator(7) != 7 || i == TileOptionsFilled - 1) {    
                    CurrentStatistics.CurrentCoordinate[0] += TileOptionTable[i].XDisplacement;
                    CurrentStatistics.CurrentCoordinate[1] += TileOptionTable[i].YDisplacement;
                    TileSelected = true;
                }
            }
        }
    };

    auto LogPreviousTileInformation = [](Map<string>& CombinedMap) {
        CurrentStatistics.PreviousCoordinate[0] = CurrentStatistics.CurrentCoordinate[0];
        CurrentStatistics.PreviousCoordinate[1] = CurrentStatistics.CurrentCoordinate[1];
        CurrentStatistics.PreviousCoordinateState = CombinedMap.MapArray[CurrentStatistics.CurrentCoordinate[1]][CurrentStatistics.CurrentCoordinate[0]];
    };

    auto CalculateStatisticLosses = []() {
        if (RandomNumberGenerator(4) == 4) {
            CurrentStatistics.Doubloons -= 1;
        }

        if (RandomNumberGenerator(17) == 17) {
            CurrentStatistics.Crew -= 1;
            if (RandomNumberGenerator(12) == 12) {
                ng::instance().load("../Libraries/NameGeneration/resources");
                CurrentStatistics.CurrentCaptain = ng::instance().get_name().append_surname();
            }
        }
    };

    int XMovement = 0;
    int YMovement = 0;
    int TileOptionsFilled = 0;
    TileOption TileOptionTable[8] = {
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"},
        {999, 999, "N/A"}
    };

    PreviousCoordinateCleanup(CombinedMap);

    CalculateGeneralDirectionToTarget(CombinedMap, XMovement, YMovement);

    LogPlausibleMovementTiles(CombinedMap, XMovement, YMovement, TileOptionTable, TileOptionsFilled);

    TileSelectionByPreference(TileOptionsFilled, TileOptionTable);

    LogPreviousTileInformation(CombinedMap);

    CombinedMap.MapArray[CurrentStatistics.CurrentCoordinate[1]][CurrentStatistics.CurrentCoordinate[0]] = CurrentStatistics.Player;

    CurrentStatistics.TilesTravelled += 1;

    CalculateStatisticLosses();
}