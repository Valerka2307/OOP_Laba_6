#include <gtest/gtest.h>
#include <sstream>
#include "Game.hpp"

// Тесты для вывода данных

TEST(OutputTests, PrintEmptyNPCList) {
    Game game;
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("No NPCs"), std::string::npos);
}

TEST(OutputTests, PrintSingleNPC) {
    Game game;
    game.addNPC(RobberType, 100, 100, "Bandit");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("Robber"), std::string::npos);
    EXPECT_NE(output.find("Bandit"), std::string::npos);
}

TEST(OutputTests, PrintMultipleNPCs) {
    Game game;
    game.addNPC(RobberType, 10, 10, "Robber1");
    game.addNPC(ElfType, 20, 20, "Elf1");
    game.addNPC(BearType, 30, 30, "Bear1");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("Robber1"), std::string::npos);
    EXPECT_NE(output.find("Elf1"), std::string::npos);
    EXPECT_NE(output.find("Bear1"), std::string::npos);
}

TEST(OutputTests, PrintNPCCoordinates) {
    Game game;
    game.addNPC(RobberType, 123, 456, "LocatedRobber");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("123"), std::string::npos);
    EXPECT_NE(output.find("456"), std::string::npos);
}

TEST(OutputTests, PrintNPCTypes) {
    Game game;
    game.addNPC(RobberType, 10, 10, "R");
    game.addNPC(ElfType, 20, 20, "E");
    game.addNPC(BearType, 30, 30, "B");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("Robber"), std::string::npos);
    EXPECT_NE(output.find("Elf"), std::string::npos);
    EXPECT_NE(output.find("Bear"), std::string::npos);
}

TEST(OutputTests, CorrectFormatting) {
    Game game;
    game.addNPC(RobberType, 100, 200, "TestNPC");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    game.printAllNPCs();
    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    // Проверяем, что формат содержит открывающую скобку
    EXPECT_NE(output.find("("), std::string::npos);
    EXPECT_NE(output.find(")"), std::string::npos);
    EXPECT_NE(output.find(","), std::string::npos);
}
