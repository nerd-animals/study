#pragma once

#include "interface/ListInterface.h"

template <typename T>
class SequentialList : public ListInterface<T> {
public:
	/*
	* ������ : Class�� ó�� ������ �� ������
	* - Python: __init__()
	*/
	SequentialList() {
		max_size = 128;
		arr = new T[max_size]();
		size = 0;
	}

	/*
	* �Ҹ��� : Class�� ������ �� ������
	* - Python: __del__()
	*/
	~SequentialList() override {
		delete arr;
	}

	/*
	* index�� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void insert(int index, T element) {
		if (index < 0 || index > size) {
			throw std::out_of_range("Index out of range");
		}
		if (size == max_size) {
			increase();
		}
		// index ~ size-1 ���������� ��ĭ��!
		std::memcpy(&arr[index + 1], &arr[index], sizeof(T) * (size - index)); // ����) memmove ����ؾ���!

		arr[index] = element;
		size = size + 1;
	}

	/*
	* index�� �ִ� element�� ��ȯ�Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T get(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		return arr[index];
	}

	/*
	* index�� �ִ� element�� ��ȯ�ϰ� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T pop(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		T ret = arr[index];

		// index+1 ~ size-1
		std::memcpy(&arr[index], &arr[index + 1], sizeof(T) * (size - index - 1)); // ����) memmove ����ؾ���!

		size = size - 1;
		return ret;
	}

	/*
	* ��� ���Ҹ� �����Ѵ�.
	*/
	virtual void clear() override {
		size = 0;
	}

	/*
	* index�� �ִ� ���Ҹ� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void set(int index, T element) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		arr[index] = element;
	}

	/*
	* ���� ������ ��ȯ�Ѵ�.
	*/
	virtual int length() override {
		return size;
	}

	/*
	* ���� ������ ��ȯ�Ѵ�.
	*/
	virtual bool isEmpty()  override {
		return size == 0 ? true : false;
	}

	/*
	* element�� ù��°�� ������ ������ index�� ��ȯ�Ѵ�.
	* ��, ������ ���Ұ� ���ٸ� -1�� ��ȯ�Ѵ�.
	*/
	virtual int find(T element) override {
		for (int i = 0; i < size; i++) {
			if (arr[i] == element) {
				return i;
			}
		}

		return -1;
	}

	/*
	* �� �տ� element�� �߰��Ѵ�.
	*/
	virtual void pushFront(T element) override {
		insert(0, element);
	}

	/*
	* �� �ڿ� element�� �߰��Ѵ�.
	*/
	virtual void pushBack(T element) override {
		insert(size, element);
	}

private:
	T* arr;
	int size, max_size;

	/*
	* �迭�� ũ�⸦ Ű���!! 2��� Ű���!!
	* �׸��� ������ �ִ� ���Ҹ� ���ο� �迭�� �����Ѵ�.
	*/
	void increase() {
		T* tmp = new T[2 * max_size]();

		std::memcpy(tmp, arr, sizeof(T) * max_size);

		delete arr;
		arr = tmp;

		max_size = 2 * max_size;
	}
};