#include "pch.h"
#include "../data-structure/inc/SequentialList.h"

/*
* Test�ϰ� ���� ���
* �Ʒ� ListTest Class�� typename T�� ����.
*/ 
using TestType = ::testing::Types<SequentialList<char>, SequentialList<int>>;

template<typename T>
class ListTest : public testing::Test {
public:
	using ValueType = typename T::value_type;
	
	ListInterface<ValueType>* _list;

	/*
	* �� �׽�Ʈ�� ������ �� ����Ǵ� ����
	*/
	void SetUp() override {
		_list = new T();
	}

	/*
	* �� �׽�Ʈ�� ����� �� ����Ǵ� ����
	*/
	void TearDown() override {
		delete _list;
	}
};

/*
* ListTest�� type�� TestType�� �ִ´�.
*/
TYPED_TEST_CASE(ListTest, TestType);

TYPED_TEST(ListTest, first_test) {
	// �׽�Ʈ 
	EXPECT_EQ(1, 1);
}

TYPED_TEST(ListTest, second_test) {
	// �׽�Ʈ 
	EXPECT_EQ(1, 1);
}