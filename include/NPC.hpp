#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include <set>
#include <math.h>
#include "Observer.hpp"
#include "Visitor.hpp"

class NPC;
class Robber;
class Elf;
class Bear;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NPCType {
    Unknown,
    RobberType,
    ElfType,
    BearType
};

class NPC : public std::enable_shared_from_this<NPC>, BattleVisitor {
protected:
    std::string name;
    NPCType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<Observer>> observers;
 public:
    NPC(NPCType t, int _x, int _y, const std::string& _name = "");
    NPC(NPCType t, std::istream &is);

    void subscribe(std::shared_ptr<Observer>observer );
    void fight_notify(const std::shared_ptr<NPC> defender, int result);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;
    
    std::string getName() const;
    void setName(const std::string& _name);
    int getX() const { return x; }
    int getY() const { return y; }
    NPCType getType() const { return type; }
    virtual std::string getTypeName() const = 0;

    virtual BattleResult accept_fight(std::shared_ptr<NPC>) = 0;

    virtual bool is_robber() const;
    virtual bool is_elf() const;
    virtual bool is_bear() const ;

    virtual BattleResult fight(std::shared_ptr<Robber> other) = 0;
    virtual BattleResult fight(std::shared_ptr<Elf> other) = 0;
    virtual BattleResult fight(std::shared_ptr<Bear> other) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream &os);
    virtual ~NPC() = default;

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};