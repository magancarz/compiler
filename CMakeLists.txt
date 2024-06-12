cmake_minimum_required(VERSION 3.28)
project(Compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(LEXER_INPUT Source/Parser/lexer.l)
set(PARSER_INPUT Source/Parser/parser.ypp)

set(LEXER_OUTPUT ${CMAKE_BINARY_DIR}/lexer.cpp)
set(PARSER_OUTPUT ${CMAKE_BINARY_DIR}/parser.tab.cpp)
set(PARSER_HEADER ${CMAKE_BINARY_DIR}/parser.tab.hpp)

FLEX_TARGET(Lexer ${LEXER_INPUT} ${LEXER_OUTPUT})
BISON_TARGET(Parser ${PARSER_INPUT} ${PARSER_OUTPUT} COMPILE_FLAGS --defines=${PARSER_HEADER})

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_executable(SimpleCompiler main.cpp)
target_sources(SimpleCompiler PRIVATE ${LEXER_OUTPUT} ${PARSER_OUTPUT})
target_include_directories(SimpleCompiler PUBLIC Source)

add_subdirectory(Source)

target_link_libraries(SimpleCompiler ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

include(CTest)
enable_testing()
add_subdirectory(ThirdParty/gtest)

if(BUILD_TESTING)
    file(GLOB_RECURSE SOURCES
            Source/*.cpp
            Source/*.h)
    add_executable(SimpleCompiler-Tests ${SOURCES})
    target_sources(SimpleCompiler-Tests PRIVATE ${LEXER_OUTPUT} ${PARSER_OUTPUT})

    target_link_libraries(SimpleCompiler-Tests PRIVATE GTest::gtest_main)
    target_link_libraries(SimpleCompiler-Tests PRIVATE GTest::gmock)
    target_link_libraries(SimpleCompiler-Tests PRIVATE ${FLEX_LIBRARIES} ${BISON_LIBRARIES})
    target_include_directories(SimpleCompiler-Tests PRIVATE Source)
    target_include_directories(SimpleCompiler-Tests PRIVATE Tests)

    include(GoogleTest)
    add_test(NAME SimpleCompiler-Tests COMMAND SimpleCompiler-Tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    add_subdirectory(Tests)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
