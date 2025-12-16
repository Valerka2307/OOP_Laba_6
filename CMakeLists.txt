cmake_minimum_required(VERSION 3.10)
project(OOP_NPC_Simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror=maybe-uninitialized")
endif()

# Source files library
add_library(${PROJECT_NAME}_lib
    src/NPC.cpp
    src/Bear.cpp
    src/Elf.cpp
    src/Robber.cpp
    src/Factory.cpp
    src/Observer.cpp
    src/Game.cpp
    src/DungeonEditor.cpp
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

# Main executable
add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME}_lib
)

# Testing
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Input tests
add_executable(input_tests
    tests/input_tests.cpp
)
target_link_libraries(input_tests
    PRIVATE ${PROJECT_NAME}_lib gtest gtest_main
)
add_test(NAME InputTests COMMAND input_tests)

# NPC Factory tests
add_executable(npc_factory_tests
    tests/npc_factory_tests.cpp
)
target_link_libraries(npc_factory_tests
    PRIVATE ${PROJECT_NAME}_lib gtest gtest_main
)
add_test(NAME NPCFactoryTests COMMAND npc_factory_tests)

# Output tests
add_executable(output_tests
    tests/output_tests.cpp
)
target_link_libraries(output_tests
    PRIVATE ${PROJECT_NAME}_lib gtest gtest_main
)
add_test(NAME OutputTests COMMAND output_tests)

# Fight logic tests
add_executable(fight_logic_tests
    tests/test_fight_logic.cpp
)
target_link_libraries(fight_logic_tests
    PRIVATE ${PROJECT_NAME}_lib gtest gtest_main
)
add_test(NAME FightLogicTests COMMAND fight_logic_tests)
