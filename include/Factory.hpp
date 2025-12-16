#pragma once

#include "NPC.hpp"
#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp" 


class Factory {
  public:
    std::shared_ptr<NPC> loadNPC(std::istream& is);

    std::shared_ptr<NPC> createNPC(NPCType, size_t, size_t);
};