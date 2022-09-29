#include <gtest/gtest.h>

#include "SortingMethods.h"

TEST(SwapTest, SwapIntegers)
{
  int a = 1;
  int b = 2;
  swap(&a, &b);
  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 1);
}

