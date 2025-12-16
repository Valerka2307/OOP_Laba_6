#include "Factory.hpp"


std::shared_ptr<NPC> Factory::loadNPC(std::istream& is) {
    int type_value;
    std::shared_ptr<NPC> character;
    if (!(is >> type_value)) {
        std::cerr << "Failed to read NPC type from stream" << std::endl;
        return nullptr;
    }
    
    NPCType type = static_cast<NPCType>(type_value);
    
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
            std::cerr << "INCORRECT INPUT: " << static_cast<int>(type) << std::endl;
            exit(EXIT_FAILURE);
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

    if (character) {
        character->subscribe(ObserverLog::get());
        character->subscribe(ObserverOut::get());
    }
    return character;
}
