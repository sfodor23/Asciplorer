#include <iostream>
#include <string>
#include "../Libraries/FastNoiseLite.h"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/GenerationConstants.hpp"
#include "../ProgramMethods/CoreMapMethods.hpp"
#include "../ProgramMethods/MiscMethods.hpp"
#include "../ProgramMethods/ArrayGenerationMethods.hpp"
#include "../ProgramMethods/InputMethods.hpp"
#include <cmath>
#include <ctime>
using namespace std;

int main() {
    int XDimension;
    int YDimension;

    InitializeRandomSeed();

    cout << "****NATIONAL CONQUEST****";
    cout << "Before Round Begins, Presets Must Be Selected";

    InputDimensions(XDimension, YDimension);

    Map<float> TopographyMap(XDimension, YDimension);
    Map<string> CombinedMap(XDimension, YDimension);
    Map<double> TemperatureMap(XDimension, YDimension);
    Map<double> PrecipitationMap(XDimension, YDimension);
    Map<string> SiteMap(XDimension, YDimension);

    TopographyMapArrayValueGeneration(TopographyMap);
    TemperatureMapArrayValueGeneration(TemperatureMap, TopographyMap);
    PrecipitationMapArrayValueGeneration(PrecipitationMap, TopographyMap);
    CombinedMapArrayValueGeneration(TopographyMap, CombinedMap, PrecipitationMap, TemperatureMap);

    CombinedMap.PrintMap();

    return 0;
}