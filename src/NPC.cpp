#include "NPC.hpp"

NPC::NPC(NPCType t, int _x, int _y, const std::string& _name) : type(t), x(_x), y(_y), name(_name) {}
NPC::NPC(NPCType t, std::istream &is) : type(t) {
    is >> x;
    is >> y;
    is.ignore();
    std::getline(is, name);
}

void NPC::subscribe(std::shared_ptr<Observer> observer) {
   observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, int result) {
    for (auto &o : observers)
        o->on_fight(shared_from_this(), defender, result);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

bool NPC::is_robber() const { return false; }
bool NPC::is_elf() const { return false; }
bool NPC::is_bear() const { return false; }

void NPC::save(std::ostream &os) {
    std::string type_str;
    if (type == RobberType) { type_str = "Robber"; }
    else if (type == ElfType) { type_str = "Elf"; }
    else if (type == BearType) { type_str = "Bear"; }
    else { type_str = "Unknown"; }
    
    os << type_str << " " << x << " " << y << " " << name << std::endl;
}

std::string NPC::getName() const {
    return name;
}

void NPC::setName(const std::string& _name) {
    name = _name;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}