#include "Game.hpp"
#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"
#include "Visitor.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <filesystem>

Game::Game() {
}

void Game::addObserver(std::shared_ptr<Observer> observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

bool Game::isValidPosition(int x, int y) const {
    return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

void Game::addNPC(NPCType type, int x, int y, const std::string& name) {
    if (!isValidPosition(x, y)) {
        std::cerr << "Error: Invalid position (" << x << ", " << y << "). Allowed range: 0-500." << std::endl;
        return;
    }
    
    auto npc = factory.createNPC(type, x, y);
    if (npc) {
        npc->setName(name);
        // Subscribe all observers
        for (const auto& observer : observers) {
            npc->subscribe(observer);
        }
        npcs.push_back(npc);
        std::cout << "NPC \"" << name << "\" added successfully." << std::endl;
    }
}

void Game::printAllNPCs() const {
    if (npcs.empty()) {
        std::cout << "No NPCs on the map." << std::endl;
        return;
    }
    
    std::cout << "\n=== Current NPCs ===" << std::endl;
    for (const auto& npc : npcs) {
        std::cout << npc->getTypeName() << " \"" << npc->getName() << "\": (" 
                  << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
    std::cout << "==================\n" << std::endl;
}

void Game::saveToFile(const std::string& filename) {
    std::string filepath = filename;
    if (!std::filesystem::path(filename).is_absolute()) {
        filepath = std::filesystem::current_path().parent_path().string() + "/" + filename;
    }
    
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << " for writing." << std::endl;
        return;
    }
    
    for (const auto& npc : npcs) {
        npc->save(file);
    }
    
    file.close();
    std::cout << "Saved " << npcs.size() << " NPCs to " << filepath << std::endl;
}

void Game::loadFromFile(const std::string& filename) {
    std::string filepath = filename;
    if (!std::filesystem::path(filename).is_absolute()) {
        filepath = std::filesystem::current_path().parent_path().string() + "/" + filename;
    }

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return;
    }

    npcs.clear();

    while (file.peek() != EOF) {
        auto npc = factory.loadNPC(file);
        
        if (npc) {
            // Subscribe all observers
            for (const auto& observer : observers) {
                npc->subscribe(observer);
            }
            npcs.push_back(npc);
        } else {
            break; // Stop on error
        }
    }

    file.close();
    std::cout << "Loaded " << npcs.size() << " NPCs from " << filepath << std::endl;
}


void Game::startBattle(size_t distance) {
    if (npcs.size() < 2) {
        std::cout << "Not enough NPCs to start a battle. At least 2 NPCs required." << std::endl;
        return;
    }
    
    std::cout << "\n=== Battle Mode Started (Distance: " << distance << " meters) ===" << std::endl;
    
    // Боевые раунды
    bool battles_occurred = true;
    
    while (battles_occurred && npcs.size() > 1) {
        battles_occurred = false;
        std::vector<bool> alive(npcs.size(), true);
        
        // Каждый NPC сражается с каждым другим в пределах дальности
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!alive[i]) continue;
            
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!alive[j]) continue;
                
                // Проверяем дальность между NPC
                if (npcs[i]->is_close(npcs[j], distance)) {
                    battles_occurred = true;
                    
                    // Выполняем бой: i-ый NPC атакует j-го
                    // accept_fight() возвращает результат для защитника
                    BattleResult result_for_j = npcs[i]->accept_fight(npcs[j]);
                    
                    if (result_for_j == Victory) {
                        // j победил, i мертв
                        alive[i] = false;
                    } else if (result_for_j == Defeat) {
                        // j проиграл, j мертв
                        alive[j] = false;
                    } else if (result_for_j == MutualDestruction) {
                        // оба погибают
                        alive[i] = false;
                        alive[j] = false;
                    }
                    // Если PeaceAndLove, оба остаются живы
                }
            }
        }
        
        // Собираем выживших
        std::vector<std::shared_ptr<NPC>> survivors;
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (alive[i]) {
                survivors.push_back(npcs[i]);
            }
        }
        
        npcs = survivors;
    }
    
    std::cout << "=== Battle Ended ===" << std::endl;
    printAllNPCs();
}

size_t Game::getNPCCount() const {
    return npcs.size();
}
