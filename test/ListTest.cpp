#include "pch.h"
#include "../data-structure/inc/SequentialList.h"

using TestType = ::testing::Types<SequentialList<int>>;

template<typename T>
class ListTest : public testing::Test {
public:
	using ValueType = typename T::value_type;
	
	ListInterface<ValueType>* _list;

	void SetUp() override {
		_list = new T();
	}

	void TearDown() override {}
};

TYPED_TEST_CASE(ListTest, TestType);

TYPED_TEST(ListTest, first) {
	using ValueType = typename TypeParam::value_type;
	
	EXPECT_GE(1, 1);
}