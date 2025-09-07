#pragma once

#include "../ProgramMethods/CoreMapMethods.hpp"
#include <iostream>

using namespace std;

void SetStartingCoordinate(Map<string>& CombinedMap);

void GiveTargetRewards(Map<string>& CombinedMap);

void SetTargetCoordinate(Map<string>& CombinedMap);

void PreviousCoordinateCleanup(Map<string>& CombinedMap);

void MovementCalculation(Map<string>& CombinedMap);