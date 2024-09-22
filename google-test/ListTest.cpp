#include "pch.h"
#include "../data-structure/inc/SequentialList.h"
#include "../data-structure/inc/DoublyLinkedList.h"
#include "../data-structure/inc/SinglyLinkedList.h"

/*
* Test하고 싶은 대상
* 아래 ListTest Class의 typename T로 들어간다.
*/ 
using TestType = ::testing::Types<SinglyLinkedList<int>>;

template<typename T>
class ListTest : public testing::Test {
public:
	using ValueType = typename T::value_type;

	const int TEST_SIZE = 100'000;
	
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

TYPED_TEST(ListTest, pushBack_n_length) {
	_list->pushBack(10);
	EXPECT_EQ(_list->length(), 1);
	EXPECT_EQ(_list->get(0), 10);
}

TYPED_TEST(ListTest, pushFront) {
	_list->pushFront(5);
	EXPECT_EQ(_list->length(), 1);
	EXPECT_EQ(_list->get(0), 5);
	_list->pushFront(3);
	EXPECT_EQ(_list->length(), 2);
	EXPECT_EQ(_list->get(0), 3);
	EXPECT_EQ(_list->get(1), 5);
}

TYPED_TEST(ListTest, insert) {
	_list->pushBack(10);
	_list->insert(1, 20);
	_list->insert(0, 5);
	EXPECT_EQ(_list->length(), 3);
	EXPECT_EQ(_list->get(0), 5);
	EXPECT_EQ(_list->get(1), 10);
	EXPECT_EQ(_list->get(2), 20);
}

TYPED_TEST(ListTest, get) {
	_list->pushBack(10);
	_list->pushBack(20);
	EXPECT_EQ(_list->get(0), 10);
	EXPECT_EQ(_list->get(1), 20);
}

TYPED_TEST(ListTest, set) {
	_list->pushBack(10);
	_list->set(0, 20);
	EXPECT_EQ(_list->get(0), 20);
}

TYPED_TEST(ListTest, find) {
	_list->pushBack(10);
	_list->pushBack(20);
	EXPECT_EQ(_list->find(10), 0);
	EXPECT_EQ(_list->find(20), 1);
	EXPECT_EQ(_list->find(30), -1);
}

TYPED_TEST(ListTest, pop) {
	_list->pushBack(10);
	_list->pushBack(20);
	_list->pushBack(30);
	_list->pushBack(40);
	_list->pushBack(50);
	EXPECT_EQ(_list->pop(4), 50);
	EXPECT_EQ(_list->length(), 4);
	EXPECT_EQ(_list->pop(2), 30);
	EXPECT_EQ(_list->length(), 3);
	EXPECT_EQ(_list->get(2), 40);
}

TYPED_TEST(ListTest, clear_n_isEmpty) {
	_list->pushBack(10);
	_list->pushBack(20);
	EXPECT_FALSE(_list->isEmpty());
	_list->clear();
	EXPECT_TRUE(_list->isEmpty());
	EXPECT_EQ(_list->length(), 0);
}

TYPED_TEST(ListTest, OutOfRange_Exceptions) {
	EXPECT_THROW(_list->get(0), std::out_of_range);
	EXPECT_THROW(_list->pop(0), std::out_of_range);
	EXPECT_THROW(_list->set(0, 1), std::out_of_range);
	EXPECT_THROW(_list->insert(1, 1), std::out_of_range);
	
	// negative index
	EXPECT_THROW(_list->get(-1), std::out_of_range);
	EXPECT_THROW(_list->pop(-1), std::out_of_range);
	EXPECT_THROW(_list->set(-1, 1), std::out_of_range);
	EXPECT_THROW(_list->insert(-1, 1), std::out_of_range);
}

//TYPED_TEST(ListTest, pushBack_Performance) {
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushBack(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//}
//
//TYPED_TEST(ListTest, pushFront_Performance) {
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushFront(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//}
//
//TYPED_TEST(ListTest, get_Performance) {
//	// get-set은 동작 방식이 거의 동일함
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushBack(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//
//	for (int i = 0; i < TEST_SIZE; i++) {
//		EXPECT_EQ(_list->get(i), i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//}
//
//TYPED_TEST(ListTest, pop_front_Performance) {
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushBack(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//
//	for (int i = 0; i < TEST_SIZE; i++) {
//		EXPECT_EQ(_list->pop(0), i);
//	}
//	EXPECT_EQ(_list->length(), 0);
//}
//
//TYPED_TEST(ListTest, pop_back_Performance) {
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushBack(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//
//	for (int i = TEST_SIZE - 1; i >= 0; i--) {
//		EXPECT_EQ(_list->pop(i), i);
//	}
//	EXPECT_EQ(_list->length(), 0);
//}
//
//TYPED_TEST(ListTest, find_Performance) {
//	for (int i = 0; i < TEST_SIZE; i++) {
//		_list->pushBack(i);
//	}
//	EXPECT_EQ(_list->length(), TEST_SIZE);
//
//	for (int i = TEST_SIZE - 1; i >= 0; i--) {
//		EXPECT_EQ(_list->find(i), i);
//	}
//
//	EXPECT_EQ(_list->find(TEST_SIZE), -1);
//}