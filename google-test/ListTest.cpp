#include "pch.h"
#include "../data-structure/inc/SequentialList.h"

/*
* Test하고 싶은 대상
* 아래 ListTest Class의 typename T로 들어간다.
*/ 
using TestType = ::testing::Types<SequentialList<char>, SequentialList<int>>;

template<typename T>
class ListTest : public testing::Test {
public:
	using ValueType = typename T::value_type;
	
	ListInterface<ValueType>* _list;

	/*
	* 각 테스트가 시작할 때 수행되는 로직
	*/
	void SetUp() override {
		_list = new T();
	}

	/*
	* 각 테스트가 종료될 때 수행되는 로직
	*/
	void TearDown() override {
		delete _list;
	}
};

/*
* ListTest의 type에 TestType을 넣는다.
*/
TYPED_TEST_CASE(ListTest, TestType);

TYPED_TEST(ListTest, first_test) {
	// 테스트 
	EXPECT_EQ(1, 1);
}

TYPED_TEST(ListTest, second_test) {
	// 테스트 
	EXPECT_EQ(1, 1);
}