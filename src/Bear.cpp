#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"
#include "Visitor.hpp"

Bear::Bear(int x, int y, const std::string& name) : NPC(BearType, x, y, name) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

void Bear::print() {
    std::cout << "Bear \"" << name << "\": " << *this;
}

std::string Bear::getTypeName() const {
    return "Bear";
}

void Bear::save(std::ostream &os) {
    NPC::save(os);
}
bool Bear::is_bear() const { return true; }

BattleResult Bear::fight(std::shared_ptr<Robber> other) {
    fight_notify(other, PeaceAndLove);
    return PeaceAndLove;
}
BattleResult Bear::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, Victory);
    return Victory;
}
BattleResult Bear::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, PeaceAndLove);
    return PeaceAndLove;
}

BattleResult Bear::accept_fight(std::shared_ptr<NPC> other) {
    return other->fight(std::dynamic_pointer_cast<Bear>(shared_from_this()));
}

std::ostream &operator<<(std::ostream &os, Bear &bear) {
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}