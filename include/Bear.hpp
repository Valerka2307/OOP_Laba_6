#pragma once
#include "NPC.hpp"

class Bear : public NPC {
  public:
    Bear(int x, int y, const std::string& name = "");
    Bear(std::istream &is);

    void print() override;
    std::string getTypeName() const override;

    bool is_bear() const override;

    BattleResult fight(std::shared_ptr<Robber> other) override;
    BattleResult fight(std::shared_ptr<Elf> other) override;
    BattleResult fight(std::shared_ptr<Bear> other) override;

    BattleResult accept_fight(std::shared_ptr<NPC>) override;
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bear &bear);
    ~Bear() override = default;
};