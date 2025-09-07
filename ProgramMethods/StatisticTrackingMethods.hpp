#pragma once
#include <iostream>
#include "../ProgramMethods/ArrayGenerationMethods.hpp"

using namespace std;

void TargetTypeCalculation(Map<string>& BiomeMap, Map<string>& CombinedMap);

void CrewNumberThresholdCheck();

void CalculateUntrackedStatistics(Map<string>& BiomeMap, Map<string>& CombinedMap);

void QueueWorldInformationPrints();

void QueueSimulationStatisticsPrints();