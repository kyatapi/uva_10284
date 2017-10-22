#pragma once
#include <gtest\gtest.h>
#include <gmock\gmock.h>

inline void run_test(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();;
}

