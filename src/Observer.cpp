#include "Observer.hpp"
#include "NPC.hpp"
#include <filesystem>

void ObserverLog::update(int value) {
    std::string log_path = std::filesystem::current_path().parent_path().string() + "/log.txt";
    std::ofstream log_file(log_path, std::ios_base::app);
    if (log_file.is_open()) {
        log_file << "Value updated to: " << value << std::endl;
        log_file.close();
    }
}

std::shared_ptr<Observer> ObserverLog::get() {
    return std::make_shared<ObserverLog>();
}

void ObserverLog::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) {
    std::string log_path = std::filesystem::current_path().parent_path().string() + "/log.txt";
    std::ofstream log_file(log_path, std::ios_base::app);
    if (log_file.is_open()) {
        std::string attacker_type, defender_type, outcome;
        if (attacker->is_robber()) attacker_type = "Robber";
        else if (attacker->is_elf()) attacker_type = "Elf";
        else if (attacker->is_bear()) attacker_type = "Bear";
        
        if (defender->is_robber()) defender_type = "Robber";
        else if (defender->is_elf()) defender_type = "Elf";
        else if (defender->is_bear()) defender_type = "Bear";
        
        if (result == 0) outcome = "Victory"; // Victory
        else if (result == 1) outcome = "Defeat"; // Defeat
        else if (result == 2) outcome = "PeaceAndLove"; // PeaceAndLove
        else if (result == 3) outcome = "MutualDestruction"; // MutualDestruction
        
        log_file << attacker_type << " \"" << attacker->getName() << "\" (at " << attacker->getX() 
                 << "," << attacker->getY() << ") vs " << defender_type << " \"" << defender->getName() 
                 << "\" (at " << defender->getX() << "," << defender->getY() << ") - " << outcome << std::endl;
        log_file.close();
    }
}

void ObserverOut::update(int value) {
    std::cout << "Value updated to: " << value << std::endl;
}

std::shared_ptr<Observer> ObserverOut::get() {
    return std::make_shared<ObserverOut>();
}

void ObserverOut::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) {
    std::string attacker_type, defender_type, outcome;
    if (attacker->is_robber()) attacker_type = "Robber";
    else if (attacker->is_elf()) attacker_type = "Elf";
    else if (attacker->is_bear()) attacker_type = "Bear";
    
    if (defender->is_robber()) defender_type = "Robber";
    else if (defender->is_elf()) defender_type = "Elf";
    else if (defender->is_bear()) defender_type = "Bear";
    
    if (result == 0) outcome = "Victory"; // Victory
    else if (result == 1) outcome = "Defeat"; // Defeat
    else if (result == 2) outcome = "PeaceAndLove"; // PeaceAndLove
    else if (result == 3) outcome = "MutualDestruction"; // MutualDestruction
    
    std::cout << attacker_type << " \"" << attacker->getName() << "\" (at " << attacker->getX() 
              << "," << attacker->getY() << ") vs " << defender_type << " \"" << defender->getName() 
              << "\" (at " << defender->getX() << "," << defender->getY() << ") - " << outcome << std::endl;
}
