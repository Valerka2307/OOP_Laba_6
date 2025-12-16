#include <gtest/gtest.h>
#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"

// Тесты для логики боевой системы

TEST(FightLogicTests, RobberVsRobberMutualDestruction) {
    auto robber1 = std::make_shared<Robber>(10, 10, "R1");
    auto robber2 = std::make_shared<Robber>(10, 10, "R2");
    
    BattleResult result = robber1->accept_fight(robber2);
    EXPECT_EQ(result, MutualDestruction);
}

TEST(FightLogicTests, ElfVsElfPeace) {
    auto elf1 = std::make_shared<Elf>(20, 20, "E1");
    auto elf2 = std::make_shared<Elf>(20, 20, "E2");
    
    BattleResult result = elf1->accept_fight(elf2);
    EXPECT_EQ(result, PeaceAndLove);
}

TEST(FightLogicTests, BearVsBearPeace) {
    auto bear1 = std::make_shared<Bear>(30, 30, "B1");
    auto bear2 = std::make_shared<Bear>(30, 30, "B2");
    
    BattleResult result = bear1->accept_fight(bear2);
    EXPECT_EQ(result, PeaceAndLove);
}

TEST(FightLogicTests, ElfBeatsRobber) {
    auto elf = std::make_shared<Elf>(40, 40, "Elf");
    auto robber = std::make_shared<Robber>(40, 40, "Robber");
    
    BattleResult result = robber->accept_fight(elf);
    EXPECT_EQ(result, Victory);
}

TEST(FightLogicTests, BearBeatsElf) {
    auto bear = std::make_shared<Bear>(50, 50, "Bear");
    auto elf = std::make_shared<Elf>(50, 50, "Elf");
    
    BattleResult result = elf->accept_fight(bear);
    EXPECT_EQ(result, Victory);
}

TEST(FightLogicTests, RobberAndBearPeace) {
    auto robber = std::make_shared<Robber>(60, 60, "Robber");
    auto bear = std::make_shared<Bear>(60, 60, "Bear");
    
    BattleResult result = robber->accept_fight(bear);
    EXPECT_EQ(result, PeaceAndLove);
}

TEST(FightLogicTests, DoubleFightDispatch) {
    auto robber = std::make_shared<Robber>(70, 70, "R");
    auto elf = std::make_shared<Elf>(70, 70, "E");
    
    BattleResult result1 = robber->accept_fight(elf);
    BattleResult result2 = elf->accept_fight(robber);
    
    // Robber теряет, Elf выигрывает - проверяем связь
    EXPECT_EQ(result1, Victory);
    EXPECT_EQ(result2, Defeat);
}
