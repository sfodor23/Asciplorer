#pragma once

#include "CoreMapMethods.hpp"
#include <string>

void TopographyMapArrayValueGeneration(Map<float>& TopographyMap);

void CombinedMapArrayValueGeneration(Map<float>& TopographyMap, Map<std::string>& CombinedMap, Map<double>& PrecipitationMap, Map<double>& TemperatureMap);

void TemperatureMapArrayValueGeneration(Map<double>& TemperatureMap, Map<float>& TopographyMap);

void PrecipitationMapArrayValueGeneration(Map<double>& PrecipitationMap, Map<float>& TopographyMap);