#include <gtest/gtest.h>

#include <limits>

int Sum(int a, int b)
{
	return a + b;
}

TEST(SumTestSuite, SumTest_Simple)
{
	EXPECT_EQ(Sum(2, 4), 6);
	EXPECT_EQ(Sum(2, 2), 4);
	EXPECT_EQ(Sum(-2, 4), 2);
}

TEST(SumTestSuite, SumTest_Zero)
{
	EXPECT_EQ(Sum(0, 0), 0);
	EXPECT_EQ(Sum(0, -0), 0);
}

TEST(SumTestSuite, SumTest_LargerNumbers)
{
	constexpr int maxInt = std::numeric_limits<int>::max();
	constexpr int minInt = std::numeric_limits<int>::min();

	EXPECT_EQ(Sum(maxInt, 1), minInt);
}