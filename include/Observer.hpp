#pragma once

#include <iostream>
#include <fstream>
#include <memory>

class NPC;

class Observer {
  public:
    virtual void update(int value) = 0;
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) = 0;
    virtual ~Observer() = default;
};

class ObserverLog: public Observer {
  public:
    void update(int value) override;
    static std::shared_ptr<Observer> get();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) override;
};

class ObserverOut: public Observer {
  public:
    void update(int value) override;
    static std::shared_ptr<Observer> get();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, int result) override;
};