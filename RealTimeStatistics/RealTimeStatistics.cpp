#include "RealTimeStatistics.hpp"
#include "../ProgramMethods/KnownLocationsMethods.hpp"

SimulationStatistics::SimulationStatistics() {
    LandCoordinates = new CoordinateList();
    ForestCoordinates = new CoordinateList();
    RainforestCoordinates = new CoordinateList();
    DesertCoordinates = new CoordinateList();
    BorealCoordinates = new CoordinateList();
    TundraCoordinates = new CoordinateList();
    MountainCoordinates = new CoordinateList();
    IceCappedMountainCoordinates = new CoordinateList();
    SettlementCoordinates = new CoordinateList();

    for (int i = 0; i < 64; i++) {
        PrintingLine[i] = "";
    }
}

SimulationStatistics::~SimulationStatistics() {
    delete LandCoordinates;
    delete ForestCoordinates;
    delete RainforestCoordinates;
    delete DesertCoordinates;
    delete BorealCoordinates;
    delete TundraCoordinates;
    delete MountainCoordinates;
    delete IceCappedMountainCoordinates;
    delete SettlementCoordinates;
}

SimulationStatistics CurrentStatistics;