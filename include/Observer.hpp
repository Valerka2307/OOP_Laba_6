#pragma once

#include <iostream>
#include <fstream>
#include <memory>

class NPC;

// Base observer interface
class Observer {
  public:
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) = 0;
    virtual ~Observer() = default;
};

// Log observer - writes to file
class ObserverLog: public Observer {
  public:
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) override;
    static std::shared_ptr<Observer> get();
};

// Console observer - writes to stdout
class ObserverOut: public Observer {
  public:
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) override;
    static std::shared_ptr<Observer> get();
};