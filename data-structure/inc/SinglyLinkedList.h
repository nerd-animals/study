#pragma once

#include "interface/ListInterface.h"

template <typename T>
class SinglyLinkedList : public ListInterface<T> {
public:
	SinglyLinkedList() {}
	~SinglyLinkedList() {}
};