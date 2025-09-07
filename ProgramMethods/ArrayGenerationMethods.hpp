#pragma once

#include "CoreMapMethods.hpp"

#include <string>

void TopographyMapArrayValueGeneration(Map<float>& TopographyMap);

void BiomeMapArrayValueGeneration(Map<float>& TopographyMap, Map<std::string>& BiomeMap, Map<double>& PrecipitationMap, Map<double>& TemperatureMap);

void TemperatureMapArrayValueGeneration(Map<double>& TemperatureMap, Map<float>& TopographyMap);

void PrecipitationMapArrayValueGeneration(Map<double>& PrecipitationMap, Map<float>& TopographyMap);

void SiteMapArrayValueGeneration(Map<std::string>& SiteMap);

void CombinedMapArrayValueGeneration(Map<std::string>& CombinedMap, Map<std::string>& SiteMap, Map<std::string>& BiomeMap);