//
// pch.cpp
//

#include "pch.h"

size_t getMemoryUsage() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	return pmc.PrivateUsage;
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(filter) = "ListTest*";
	return RUN_ALL_TESTS();
}