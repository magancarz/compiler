#include "Memory/Memory.h"

#include "gtest/gtest.h"

TEST(MemoryTests, shouldAddVariableToMemory)
{
    // given
    Memory memory{};

    const std::string expected_variable_name{"dummy"};
    const unsigned long long expected_variable_value{10};

    // when
    memory.add_variable_to_memory(expected_variable_name, 10);

    // then
    EXPECT_TRUE(memory.check_if_variable_exists(expected_variable_name));
    EXPECT_EQ(memory.get_variable(expected_variable_name)->get_value(), expected_variable_value);
}

TEST(MemoryTests, shouldAddProcedureToMemory)
{
    // given
    Memory memory{};

    const std::string expected_variable_name{"dummy"};
    const std::string expected_procedure_name{"dummy"};

    // when
    memory.add_new_procedure();
    memory.add_procedure_variable_to_memory(expected_variable_name);
    memory.set_identifier_to_current_procedure(expected_procedure_name);
    memory.finish_procedure(0);

    // then
    EXPECT_TRUE(memory.check_if_procedure_exists(expected_procedure_name));
}
