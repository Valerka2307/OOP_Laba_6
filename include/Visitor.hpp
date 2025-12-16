#pragma once

#include <memory>

class NPC;
class Robber;
class Elf;
class Bear;

enum BattleResult {
    Victory,
    Defeat,
    PeaceAndLove,
    MutualDestruction
};

class BattleVisitor {
  public:
    
    virtual BattleResult fight(std::shared_ptr<Robber>) = 0;
    virtual BattleResult fight(std::shared_ptr<Elf>) = 0;
    virtual BattleResult fight(std::shared_ptr<Bear>) = 0;

    virtual BattleResult accept_fight(std::shared_ptr<NPC>) = 0;
    virtual ~BattleVisitor() = default;
};