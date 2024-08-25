#pragma once

#include "interface/ListInterface.h"

template <typename T>
class SequentialList : public ListInterface<T> {
public:
	/*
	* 생성자 : Class가 처음 생성될 때 동작함
	* - Python: __init__()
	*/
	SequentialList() {
		max_size = 128;
		arr = new T[max_size]();
		size = 0;
	}

	/*
	* 소멸자 : Class가 삭제될 때 동작함
	* - Python: __del__()
	*/
	~SequentialList() override {
		delete arr;
	}

	/*
	* index에 element를 삽입한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void insert(int index, T element) {
		if (index < 0 || index > size) {
			throw std::out_of_range("Index out of range");
		}
		if (size == max_size) {
			increase();
		}
		// index ~ size-1 오른쪽으로 한칸씩!
		std::memcpy(&arr[index + 1], &arr[index], sizeof(T) * (size - index)); // 주의) memmove 사용해야함!

		arr[index] = element;
		size = size + 1;
	}

	/*
	* index에 있는 element를 반환한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T get(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		return arr[index];
	}

	/*
	* index에 있는 element를 반환하고 삭제한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T pop(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		T ret = arr[index];

		// index+1 ~ size-1
		std::memcpy(&arr[index], &arr[index + 1], sizeof(T) * (size - index - 1)); // 주의) memmove 사용해야함!

		size = size - 1;
		return ret;
	}

	/*
	* 모든 원소를 삭제한다.
	*/
	virtual void clear() override {
		size = 0;
	}

	/*
	* index에 있는 원소를 element로 수정한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void set(int index, T element) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		arr[index] = element;
	}

	/*
	* 원소 개수를 반환한다.
	*/
	virtual int length() override {
		return size;
	}

	/*
	* 원소 개수를 반환한다.
	*/
	virtual bool isEmpty()  override {
		return size == 0 ? true : false;
	}

	/*
	* element와 첫번째로 동일한 원소의 index를 반환한다.
	* 단, 동일한 원소가 없다면 -1을 반환한다.
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
	* 맨 앞에 element를 추가한다.
	*/
	virtual void pushFront(T element) override {
		insert(0, element);
	}

	/*
	* 맨 뒤에 element를 추가한다.
	*/
	virtual void pushBack(T element) override {
		insert(size, element);
	}

private:
	T* arr;
	int size, max_size;

	/*
	* 배열의 크기를 키운다!! 2배로 키운다!!
	* 그리고 기존에 있던 원소를 새로운 배열로 복사한다.
	*/
	void increase() {
		T* tmp = new T[2 * max_size]();

		std::memcpy(tmp, arr, sizeof(T) * max_size);

		delete arr;
		arr = tmp;

		max_size = 2 * max_size;
	}
};