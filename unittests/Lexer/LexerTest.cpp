#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"

TEST(ParserTest, t1)
{
    yyscan_t t;
    EXPECT_EQ(1, 1);
    EXPECT_EQ(true, true);
}

TEST(ParserTest, t2)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(false, true);
}