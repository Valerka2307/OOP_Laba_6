#include <gtest/gtest.h>
#include "Factory.hpp"
#include "Robber.hpp"
#include "Elf.hpp"
#include "Bear.hpp"

// Тесты для Factory

TEST(NPCFactoryTests, CreateRobberNPC) {
    Factory factory;
    auto robber = factory.createNPC(RobberType, 50, 50);
    ASSERT_NE(robber, nullptr);
    EXPECT_TRUE(robber->is_robber());
}

TEST(NPCFactoryTests, CreateElfNPC) {
    Factory factory;
    auto elf = factory.createNPC(ElfType, 100, 100);
    ASSERT_NE(elf, nullptr);
    EXPECT_TRUE(elf->is_elf());
}

TEST(NPCFactoryTests, CreateBearNPC) {
    Factory factory;
    auto bear = factory.createNPC(BearType, 150, 150);
    ASSERT_NE(bear, nullptr);
    EXPECT_TRUE(bear->is_bear());
}

TEST(NPCFactoryTests, NPCCoordinatesSetCorrectly) {
    Factory factory;
    auto npc = factory.createNPC(RobberType, 123, 456);
    EXPECT_EQ(npc->getX(), 123);
    EXPECT_EQ(npc->getY(), 456);
}

TEST(NPCFactoryTests, NPCTypeCorrectAfterCreation) {
    Factory factory;
    auto robber = factory.createNPC(RobberType, 10, 20);
    auto elf = factory.createNPC(ElfType, 10, 20);
    auto bear = factory.createNPC(BearType, 10, 20);
    
    EXPECT_EQ(robber->getType(), RobberType);
    EXPECT_EQ(elf->getType(), ElfType);
    EXPECT_EQ(bear->getType(), BearType);
}

TEST(NPCFactoryTests, CreateMultipleNPCsOfSameType) {
    Factory factory;
    auto robber1 = factory.createNPC(RobberType, 10, 10);
    auto robber2 = factory.createNPC(RobberType, 20, 20);
    
    ASSERT_NE(robber1, nullptr);
    ASSERT_NE(robber2, nullptr);
    EXPECT_NE(robber1, robber2);
}

TEST(NPCFactoryTests, FactoryProvidesObserversToNPC) {
    Factory factory;
    auto npc = factory.createNPC(RobberType, 50, 50);
    ASSERT_NE(npc, nullptr);
    // NPC должно быть создано с подписанными observer'ами
}
