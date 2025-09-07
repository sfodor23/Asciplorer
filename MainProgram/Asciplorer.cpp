#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include "../Libraries/FastNoiseLite.h"
#include "../Libraries/TileCharacters.hpp"
#include "../Libraries/GenerationConstants.hpp"
#include "../Libraries/LineStyles.hpp"
#include "../ProgramMethods/CoreMapMethods.hpp"
#include "../ProgramMethods/MiscMethods.hpp"
#include "../ProgramMethods/ArrayGenerationMethods.hpp"
#include "../ProgramMethods/InputMethods.hpp"
#include "../ProgramMethods/PlayerMethods.hpp"
#include "../RealTimeStatistics/RealTimeStatistics.hpp"
#include "../ProgramMethods/StatisticTrackingMethods.hpp"

using namespace std;
using namespace GenerationConstants;
using namespace LineStyles;

void MapGeneration(int& XDimension, int& YDimension, Map<float>& TopographyMap, Map<string>& BiomeMap, Map<double>& TemperatureMap, Map<double>& PrecipitationMap, Map<string>& SiteMap, Map<string>& CombinedMap) {
    TopographyMapArrayValueGeneration(TopographyMap);

    TemperatureMapArrayValueGeneration(TemperatureMap, TopographyMap);

    PrecipitationMapArrayValueGeneration(PrecipitationMap, TopographyMap);

    BiomeMapArrayValueGeneration(TopographyMap, BiomeMap, PrecipitationMap, TemperatureMap);
    
    SiteMapArrayValueGeneration(SiteMap);

    CombinedMapArrayValueGeneration(CombinedMap, SiteMap, BiomeMap);
}

void InputHandling(int& XDimension, int& YDimension) {
    InputDimensions(XDimension, YDimension);
    InputClimateType();
    InputMapType();
    InputSeed();
    InputMapPalette();
    InputPlayerIcon();
    InputRefreshRate();
}

void TurnProcessing(int& XDimension, int& YDimension, Map<float>& TopographyMap, Map<string>& BiomeMap, Map<double>& TemperatureMap, Map<double>& PrecipitationMap, Map<string>& SiteMap, Map<string>& CombinedMap) {
    auto GetTerminalSize = []() -> pair<int, int> {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return make_pair(width, height);
        #else
            struct winsize Window;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &Window);
            return make_pair(Window.ws_col, Window.ws_row);
        #endif
    };
    
    auto ClearScreen = []() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    };

    auto PrepareOutput = [](Map<string>& CombinedMap, Map<string>& BiomeMap, 
        int VisibilityBoundX[2], int VisibilityBoundY[2], int TerminalWidth) {
        for (int i = 0; i < 64; i++) {
            CurrentStatistics.PrintingLine[i] = "";
        }        

        CalculateUntrackedStatistics(BiomeMap, CombinedMap);
    
        QueueWorldInformationPrints();

        CombinedMap.PrintMap(VisibilityBoundX[0], VisibilityBoundX[1], VisibilityBoundY[0], VisibilityBoundY[1]);

        QueueSimulationStatisticsPrints();
    };

    auto PrintFinalOutput = [](int TerminalWidth) {
        cout << string(TerminalWidth, GrandHeaderCharacter) << endl;

        for (int i = 0; i < 36; i++) {
            cout << CurrentStatistics.PrintingLine[i] << endl;
        }
    
        cout << string(TerminalWidth, GrandHeaderCharacter) << endl;
    };

    ClearScreen();
    
    auto [TerminalWidth, TerminalHeight] = GetTerminalSize();

    MovementCalculation(CombinedMap);

    int VisibilityBoundX[2] = {0, 0};

    if (static_cast<int>((TerminalWidth - 124)/4) % 2 == 0) {
        VisibilityBoundX[0] = CurrentStatistics.CurrentCoordinate[0] - (static_cast<int>((TerminalWidth - 124)/4)) + 1;
        VisibilityBoundX[1] =  CurrentStatistics.CurrentCoordinate[0] + (static_cast<int>((TerminalWidth - 124)/4));
    }
    else {
        VisibilityBoundX[0] = CurrentStatistics.CurrentCoordinate[0] - (static_cast<int>((TerminalWidth - 124)/4)) + 1;
        VisibilityBoundX[1] =  CurrentStatistics.CurrentCoordinate[0] + (static_cast<int>((TerminalWidth - 124)/4));
    }

    int VisibilityBoundY[2] = {CurrentStatistics.CurrentCoordinate[1] - 18, CurrentStatistics.CurrentCoordinate[1] + 18};

    VisibilityBoundX[0] = max(0, VisibilityBoundX[0]);
    VisibilityBoundX[1] = min(XDimension - 1, VisibilityBoundX[1]);
    VisibilityBoundY[0] = max(0, VisibilityBoundY[0]);
    VisibilityBoundY[1] = min(YDimension - 1, VisibilityBoundY[1]);

    PrepareOutput(CombinedMap, BiomeMap, VisibilityBoundX, VisibilityBoundY, TerminalWidth);

    PrintFinalOutput(TerminalWidth);
}

int main() {
    int XDimension;
    int YDimension;

    InitializeRandomSeed();

    cout << "****ASCIPLORER****" << endl;
    cout << "Before simulation begins, presets/settings must be selected" << endl;

    InputHandling(XDimension, YDimension);

    cout << "Loading..." << endl;

    Map<float> TopographyMap(XDimension, YDimension);
    Map<string> BiomeMap(XDimension, YDimension);
    Map<double> TemperatureMap(XDimension, YDimension);
    Map<double> PrecipitationMap(XDimension, YDimension);
    Map<string> SiteMap(XDimension, YDimension);
    Map<string> CombinedMap(XDimension, YDimension);

    MapGeneration(XDimension, YDimension, TopographyMap, BiomeMap, TemperatureMap, PrecipitationMap, SiteMap, CombinedMap);

    SetStartingCoordinate(CombinedMap);
    SetTargetCoordinate(CombinedMap);

    while (true) {
        TurnProcessing(XDimension, YDimension, TopographyMap, BiomeMap, TemperatureMap, PrecipitationMap, SiteMap, CombinedMap);
        std::this_thread::sleep_for(std::chrono::milliseconds(CurrentStatistics.RefreshRate));
    }

    return 0;
}