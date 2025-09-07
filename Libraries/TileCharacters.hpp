#pragma once
#include <string>

namespace TileCharacters {
    // SPECIAL/SYSTEM TILES
    inline const std::string ErrorTile = "!";
    
    // PALETTE TILES
    //Normal Palette
    inline const std::string NormalWater = "\033[38;5;33m~\033[0m";          // Standard ocean blue
    inline const std::string NormalWarmWater = "\033[38;5;39m~\033[0m";      // Tropical cyan waters
    inline const std::string NormalIcyWater = "\033[38;5;117m~\033[0m";      // Arctic pale blue
    
    inline const std::string NormalGenericLand = "\033[38;5;34m■\033[0m";    // Natural forest green
    inline const std::string NormalMountain = "\033[38;5;8m▲\033[0m";        // Rocky dark gray
    inline const std::string NormalIceCappedMountain = "\033[38;5;15m▲\033[0m"; // Snow white peaks
    
    inline const std::string NormalTundra = "\033[38;5;15m■\033[0m";         // Frozen white expanse
    inline const std::string NormalBoreal = "\033[38;5;22m■\033[0m";         // Dense dark green forest
    inline const std::string NormalForest = "\033[38;5;28m■\033[0m";         // Temperate green woods
    inline const std::string NormalRainforest = "\033[38;5;40m■\033[0m";     // Lush bright green jungle
    inline const std::string NormalDesert = "\033[38;5;221m■\033[0m";        // Sandy yellow dunes
    
    inline const std::string NormalVillage = "\033[38;5;94m■\033[0m";        // Earthy brown hamlet
    inline const std::string NormalTown = "\033[38;5;166m■\033[0m";          // Orange brick community
    inline const std::string NormalCity = "\033[38;5;250m■\033[0m";          // Light gray urban center
    inline const std::string NormalCapital = "\033[38;5;242m■\033[0m";       // Dark gray seat of power
    inline const std::string NormalMegacity = "\033[38;5;226m■\033[0m";      // Golden sprawling metropolis

    //Arcane Palette
    inline const std::string ArcaneWater = "\033[38;5;63m~\033[0m";          // Deep mystical blue
    inline const std::string ArcaneWarmWater = "\033[38;5;69m~\033[0m";      // Enchanted purple-blue
    inline const std::string ArcaneIcyWater = "\033[38;5;153m~\033[0m";      // Frost magic blue
    
    inline const std::string ArcaneGenericLand = "\033[38;5;99m■\033[0m";    // Mystic purple
    inline const std::string ArcaneMountain = "\033[38;5;54m▲\033[0m";       // Dark sorcerer purple
    inline const std::string ArcaneIceCappedMountain = "\033[38;5;189m▲\033[0m"; // Crystal white-purple
    
    inline const std::string ArcaneTundra = "\033[38;5;147m■\033[0m";        // Ethereal light purple
    inline const std::string ArcaneBoreal = "\033[38;5;61m■\033[0m";         // Twilight blue-purple
    inline const std::string ArcaneForest = "\033[38;5;105m■\033[0m";        // Enchanted violet
    inline const std::string ArcaneRainforest = "\033[38;5;141m■\033[0m";    // Magical purple-green
    inline const std::string ArcaneDesert = "\033[38;5;228m■\033[0m";        // Golden arcane sands
    
    inline const std::string ArcaneVillage = "\033[38;5;177m■\033[0m";       // Amethyst settlement
    inline const std::string ArcaneTown = "\033[38;5;183m■\033[0m";          // Opal glow
    inline const std::string ArcaneCity = "\033[38;5;219m■\033[0m";          // Royal lavender
    inline const std::string ArcaneCapital = "\033[38;5;225m■\033[0m";       // Divine radiance
    inline const std::string ArcaneMegacity = "\033[38;5;229m■\033[0m";      // Pure golden light

    //Dull Palette
    inline const std::string DullWater = "\033[38;5;67m~\033[0m";            // Muted blue-gray
    inline const std::string DullWarmWater = "\033[38;5;73m~\033[0m";        // Dull teal-gray
    inline const std::string DullIcyWater = "\033[38;5;145m~\033[0m";        // Pale gray-blue
    
    inline const std::string DullGenericLand = "\033[38;5;65m■\033[0m";      // Muted green-gray
    inline const std::string DullMountain = "\033[38;5;235m▲\033[0m";        // Dark charcoal gray
    inline const std::string DullIceCappedMountain = "\033[38;5;251m▲\033[0m"; // Light gray
    
    inline const std::string DullTundra = "\033[38;5;249m■\033[0m";          // Off-white gray
    inline const std::string DullBoreal = "\033[38;5;236m■\033[0m";          // Dark gray-green
    inline const std::string DullForest = "\033[38;5;59m■\033[0m";           // Dull olive-gray
    inline const std::string DullRainforest = "\033[38;5;101m■\033[0m";      // Muted brown-green
    inline const std::string DullDesert = "\033[38;5;143m■\033[0m";          // Dusty brown-gray
    
    inline const std::string DullVillage = "\033[38;5;240m■\033[0m";         // Medium gray
    inline const std::string DullTown = "\033[38;5;244m■\033[0m";            // Light medium gray
    inline const std::string DullCity = "\033[38;5;247m■\033[0m";            // Lighter gray
    inline const std::string DullCapital = "\033[38;5;250m■\033[0m";         // Very light gray
    inline const std::string DullMegacity = "\033[38;5;253m■\033[0m";
}