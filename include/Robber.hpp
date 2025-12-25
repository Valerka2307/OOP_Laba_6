#pragma once
#include "NPC.hpp"

class Robber : public NPC {
  public:
    Robber(int x, int y, const std::string& name = "");
    Robber(std::istream &is);

    void print() override;
    std::string getTypeName() const override;

    bool is_robber() const override;

    BattleResult fight(std::shared_ptr<Robber> other) override;
    BattleResult fight(std::shared_ptr<Elf> other) override;
    BattleResult fight(std::shared_ptr<Bear> other) override;
    
    BattleResult accept_fight(std::shared_ptr<NPC>) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Robber &robber);
    ~Robber() override = default;
};