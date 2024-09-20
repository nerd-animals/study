#pragma once

#include "interface/ListInterface.h"

template <typename T>
class DoublyLinkedList : public ListInterface<T> {
public:
	DoublyLinkedList() {}
	~DoublyLinkedList() override {}

	/*
	* index�� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void insert(int index, T element) override {
		return;
	}

	/*
	* index�� �ִ� element�� ��ȯ�Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T get(int index) override {
		return T();
	}
	/*
	* index�� �ִ� element�� ��ȯ�ϰ� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T pop(int index) override {
		return T();
	}
	/*
	* ��� ���Ҹ� �����Ѵ�.
	*/
	virtual void clear() override {
		return;
	}
	/*
	* index�� �ִ� ���Ҹ� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void set(int index, T element) override {
		return;
	}
	/*
	* ���� ������ ��ȯ�Ѵ�.
	*/
	virtual int length() override {
		return 0;
	}
	/*
	* ���� ������ ��ȯ�Ѵ�.
	*/
	virtual bool isEmpty()override {
		return true;
	}

	/*
	* element�� ù��°�� ������ ������ index�� ��ȯ�Ѵ�.
	*/
	virtual int find(T element) override {
		return 0;
	}

	/*
	* �� �տ� element�� �߰��Ѵ�.
	*/
	virtual void pushFront(T element) override {
		return;
	}

	/*
	* �� �ڿ� element�� �߰��Ѵ�.
	*/
	virtual void pushBack(T element) override {
		return;
	}
};