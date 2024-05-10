

#include "lib.h"

#include <gtest/gtest.h>


TEST(test_valid_version, test_valid_version)
{
    ASSERT_LE(version(), 100);
    ASSERT_NE(version(), 1);
}
