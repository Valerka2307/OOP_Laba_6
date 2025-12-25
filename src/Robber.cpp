#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"
#include "Visitor.hpp"

Robber::Robber(int x, int y, const std::string& name) : NPC(RobberType, x, y, name) {}
Robber::Robber(std::istream &is) : NPC(RobberType, is) {}

void Robber::print() {
    std::cout << "Robber \"" << name << "\": " << *this;
}

std::string Robber::getTypeName() const {
    return "Robber";
}

void Robber::save(std::ostream &os) {
    NPC::save(os);
}
bool Robber::is_robber() const { return true; }

BattleResult Robber::fight(std::shared_ptr<Robber> other) {
    fight_notify(other, MutualDestruction);
    return MutualDestruction;
}

BattleResult Robber::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, Defeat);
    return Defeat;
}

BattleResult Robber::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, PeaceAndLove);
    return PeaceAndLove;
}

BattleResult Robber::accept_fight(std::shared_ptr<NPC> other) {
    return other->fight(std::dynamic_pointer_cast<Robber>(shared_from_this()));
}

std::ostream &operator<<(std::ostream &os, Robber &robber) {
    os << "robber: " << *static_cast<NPC *>(&robber) << std::endl;
    return os;
}