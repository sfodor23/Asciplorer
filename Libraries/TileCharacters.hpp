#pragma once
#include <string>

namespace TileCharacters {
    inline const std::string GenericLand = "\033[32m■\033[0m";
    inline const std::string Forest = "\033[38;2;34;139;34m■\033[0m";
    inline const std::string Rainforest = "\033[38;2;16;199;36m■\033[0m";
    inline const std::string Boreal = "\033[38;2;8;90;21m■\033[0m";
    inline const std::string Water = "\033[38;2;66;156;208m~\033[0m";
    inline const std::string WarmWater = "\033[38;2;35;166;255m~\033[0m";
    inline const std::string IcyWater = "\033[38;2;117;183;252m~\033[0m";
    inline const std::string Mountain = "\033[90m▲\033[0m";
    inline const std::string IceCappedMountain = "\033[38;2;255;255;255m▲\033[0m";
    inline const std::string Tundra = "\033[38;2;255;255;255m■\033[0m";
    inline const std::string Desert = "\033[38;2;241;218;122m■\033[0m";
    inline const std::string ErrorTile = "!";
}