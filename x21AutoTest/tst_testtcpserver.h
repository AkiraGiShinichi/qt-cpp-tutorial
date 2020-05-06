#ifndef TST_TESTTCPSERVER_H
#define TST_TESTTCPSERVER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

//Below is the function wanted to test and 3 test cases(group of cases);
bool IsPrime(int n)
{
    return false;
}

TEST(IsPrimeTest, PositiveNumbers)
{
    EXPECT_FALSE(IsPrime(4));
    EXPECT_TRUE(IsPrime(5));
}

TEST(IsPrimeTest, NegativeNumbers)
{
    EXPECT_FALSE(IsPrime(-1));
    EXPECT_FALSE(IsPrime(-100));
}

TEST(IsPrimeTest, TrivialCases)
{
    EXPECT_FALSE(IsPrime(0));
    EXPECT_FALSE(IsPrime(1));
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
}

TEST(TestTcpServer, TestTcpServer)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}


#endif // TST_TESTTCPSERVER_H
