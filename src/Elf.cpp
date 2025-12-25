#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"
#include "Visitor.hpp"

Elf::Elf(int x, int y, const std::string& name) : NPC(ElfType, x, y, name) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print() {
    std::cout << "Elf \"" << name << "\": " << *this;
}

std::string Elf::getTypeName() const {
    return "Elf";
}

void Elf::save(std::ostream &os) {
    NPC::save(os);
}
bool Elf::is_elf() const { return true; }

BattleResult Elf::fight(std::shared_ptr<Robber> other) {
    fight_notify(other, Victory);
    return Victory;
}

BattleResult Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, PeaceAndLove);
    return PeaceAndLove;
}

BattleResult Elf::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, Defeat);
    return Defeat;
}

BattleResult Elf::accept_fight(std::shared_ptr<NPC> other) {
    return other->fight(std::dynamic_pointer_cast<Elf>(shared_from_this()));
}

std::ostream &operator<<(std::ostream &os, Elf &elf) {
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}