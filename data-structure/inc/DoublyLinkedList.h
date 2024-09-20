#pragma once

#include "interface/ListInterface.h"

template <typename T>
class DoublyLinkedList : public ListInterface<T> {
public:
	DoublyLinkedList() {}
	~DoublyLinkedList() override {}

	/*
	* index에 element를 삽입한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void insert(int index, T element) override {
		return;
	}

	/*
	* index에 있는 element를 반환한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T get(int index) override {
		return T();
	}
	/*
	* index에 있는 element를 반환하고 삭제한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T pop(int index) override {
		return T();
	}
	/*
	* 모든 원소를 삭제한다.
	*/
	virtual void clear() override {
		return;
	}
	/*
	* index에 있는 원소를 element로 수정한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void set(int index, T element) override {
		return;
	}
	/*
	* 원소 개수를 반환한다.
	*/
	virtual int length() override {
		return 0;
	}
	/*
	* 원소 개수를 반환한다.
	*/
	virtual bool isEmpty()override {
		return true;
	}

	/*
	* element와 첫번째로 동일한 원소의 index를 반환한다.
	*/
	virtual int find(T element) override {
		return 0;
	}

	/*
	* 맨 앞에 element를 추가한다.
	*/
	virtual void pushFront(T element) override {
		return;
	}

	/*
	* 맨 뒤에 element를 추가한다.
	*/
	virtual void pushBack(T element) override {
		return;
	}
};