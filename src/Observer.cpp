#include "Observer.hpp"
#include "NPC.hpp"
#include <filesystem>

std::shared_ptr<Observer> ObserverLog::get() {
    return std::make_shared<ObserverLog>();
}

void ObserverLog::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) {
    std::string log_path = std::filesystem::current_path().parent_path().string() + "/log.txt";
    std::ofstream log_file(log_path, std::ios_base::app);
    if (log_file.is_open()) {
        std::string outcome;
        if (result == 0) outcome = "Victory";
        else if (result == 1) outcome = "Defeat";
        else if (result == 2) outcome = "PeaceAndLove";
        else if (result == 3) outcome = "MutualDestruction";
        
        log_file << attacker->getTypeName() << " \"" << attacker->getName() << "\" (at " << attacker->getX() 
                 << "," << attacker->getY() << ") vs " << defender->getTypeName() << " \"" << defender->getName() 
                 << "\" (at " << defender->getX() << "," << defender->getY() << ") - " << outcome << std::endl;
        log_file.close();
    }
}

std::shared_ptr<Observer> ObserverOut::get() {
    return std::make_shared<ObserverOut>();
}

void ObserverOut::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) {
    std::string outcome;
    if (result == 0) outcome = "Victory";
    else if (result == 1) outcome = "Defeat";
    else if (result == 2) outcome = "PeaceAndLove";
    else if (result == 3) outcome = "MutualDestruction";
    
    std::cout << attacker->getTypeName() << " \"" << attacker->getName() << "\" (at " << attacker->getX() 
              << "," << attacker->getY() << ") vs " << defender->getTypeName() << " \"" << defender->getName() 
              << "\" (at " << defender->getX() << "," << defender->getY() << ") - " << outcome << std::endl;
} 
