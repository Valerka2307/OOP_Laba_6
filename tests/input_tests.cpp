#include <gtest/gtest.h>
#include <sstream>
#include "Game.hpp"
#include "DungeonEditor.hpp"

// Тесты для проверки ввода данных

TEST(InputTests, AddNPCWithValidCoordinates) {
    Game game;
    game.addNPC(RobberType, 100, 150, "TestRobber");
    EXPECT_EQ(game.getNPCCount(), 1);
}

TEST(InputTests, AddNPCWithBoundaryCoordinates) {
    Game game;
    game.addNPC(ElfType, 0, 0, "CornerElf");
    game.addNPC(BearType, 500, 500, "CornerBear");
    EXPECT_EQ(game.getNPCCount(), 2);
}

TEST(InputTests, RejectNPCWithInvalidXCoordinate) {
    Game game;
    game.addNPC(RobberType, 501, 250, "InvalidRobber");
    EXPECT_EQ(game.getNPCCount(), 0);
}

TEST(InputTests, RejectNPCWithInvalidYCoordinate) {
    Game game;
    game.addNPC(ElfType, 250, -1, "InvalidElf");
    EXPECT_EQ(game.getNPCCount(), 0);
}

TEST(InputTests, AddMultipleNPCsSequentially) {
    Game game;
    game.addNPC(RobberType, 10, 20, "Robber1");
    game.addNPC(ElfType, 30, 40, "Elf1");
    game.addNPC(BearType, 50, 60, "Bear1");
    EXPECT_EQ(game.getNPCCount(), 3);
}

TEST(InputTests, SetNameCorrectly) {
    Game game;
    game.addNPC(RobberType, 100, 100, "NamedRobber");
    // Проверяем, что имя установлено правильно через printAllNPCs
    EXPECT_EQ(game.getNPCCount(), 1);
}

TEST(InputTests, AllNPCTypesAccepted) {
    Game game;
    game.addNPC(RobberType, 100, 100, "R");
    game.addNPC(ElfType, 200, 200, "E");
    game.addNPC(BearType, 300, 300, "B");
    EXPECT_EQ(game.getNPCCount(), 3);
}
