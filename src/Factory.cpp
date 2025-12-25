#include "Factory.hpp"
#include <map>

// Helper map for string to type conversion
static const std::map<std::string, NPCType> typeMap = {
    {"Robber", RobberType},
    {"Elf", ElfType},
    {"Bear", BearType}
};

std::shared_ptr<NPC> Factory::loadNPC(std::istream& is) {
    std::string token;
    int type_value = 0;
    
    if (!(is >> token)) {
        std::cerr << "Failed to read NPC type from stream" << std::endl;
        return nullptr;
    }
    
    // Try to find in string-to-type map first
    auto it = typeMap.find(token);
    if (it != typeMap.end()) {
        type_value = it->second;
    } else {
        // Try to parse as number
        try {
            type_value = std::stoi(token);
        } catch (...) {
            std::cerr << "INCORRECT INPUT: " << token << std::endl;
            return nullptr;
        }
    }
    
    NPCType type = static_cast<NPCType>(type_value);
    std::shared_ptr<NPC> character;
    
    switch (type) {
        case RobberType: {
            character =  std::make_shared<Robber>(is);
            break;
        }
        case ElfType: {
            character =  std::make_shared<Elf>(is);
            break;
        }
        case BearType: {
            character =  std::make_shared<Bear>(is);
            break;
        }
        default: {
            std::cerr << "INCORRECT INPUT: " << type_value << std::endl;
            return nullptr;
        }
    }
    return character;
}

std::shared_ptr<NPC> Factory::createNPC(NPCType type, size_t x, size_t y) {
    std::shared_ptr<NPC> character;

    switch (type) {
        case RobberType: {
            character =  std::make_shared<Robber>(x, y);
            break;
        }
        case ElfType: {
            character =  std::make_shared<Elf>(x, y);
            break;
        }
        case BearType: {
            character =  std::make_shared<Bear>(x, y);
            break;
        }
        default: {
            std::cerr << "INCORRECT INPUT: " << static_cast<int>(type) << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return character;
}
