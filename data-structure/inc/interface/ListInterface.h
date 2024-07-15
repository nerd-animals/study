#pragma once

template <typename T>
class ListInterface {
public:
	using value_type = T;
	
	virtual ~ListInterface() = default;

	/*
	* index에 element를 삽입한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void insert(int index, T element) = 0;

	/*
	* index에 있는 element를 반환한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T get(int index) = 0;

	/*
	* index에 있는 element를 반환하고 삭제한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T pop(int index) = 0;

	/*
	* 모든 원소를 삭제한다.
	*/
	virtual void clear() = 0;

	/*
	* index에 있는 원소를 element로 수정한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void set(int index, T element) = 0;

	/*
	* 원소 개수를 반환한다.
	*/
	virtual int length() = 0;

	/*
	* 원소 개수를 반환한다.
	*/
	virtual bool isEmpty() = 0;

	/*
	* element와 첫번째로 동일한 원소의 index를 반환한다.
	*/
	virtual int find(T element) = 0;

	/*
	* 맨 앞에 element를 추가한다.
	*/
	virtual void pushFront(T element) = 0;

	/*
	* 맨 뒤에 element를 추가한다.
	*/
	virtual void pushBack(T element) = 0;
};