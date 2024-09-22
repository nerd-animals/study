#pragma once

#include "interface/ListInterface.h"

template <typename T>
class DoublyLinkedList : public ListInterface<T> {
private:
	struct Node {
		T value; // ���� ������ �� �ִ� ����
		Node* prev; // ���� ����� ��ġ�� �����ϴ� ����
		Node* next; // ���� ����� ��ġ�� �����ϴ� ����

		Node(T v) {
			value = v;
			prev = next = nullptr;
		}
	};

public:
	DoublyLinkedList() {
		size = 0;
		head = tail = nullptr;
	}

	~DoublyLinkedList() override {
		// �Ҹ�� ��, ��� Node�� �����Ѵ�.
		clear();
	}

	/*
	* index�� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void insert(int index, T element) override {
		if (index < 0 || index > size) {
			throw std::out_of_range("Index out of range");
		}		

		// �� �հ� �� �ڴ� ���� �Լ��� ȣ���ϰ� ������.
		if (index == 0) {
			pushFront(element);
			return;
		}
		else if (index == size) {
			pushBack(element);
			return;
		}

		/*
		*  [�߰� ������ ���]
		*	== index ��ġ���ٰ� ���ο� node�� �־���Ѵ�.
		*	== target �տ��ٰ� ���ο� node�� �ִ´�. (target == ���� index ��ġ�� �ִ� node)
		*	== target�� target�� prev ���̿� ���ο� node�� �ִ´�.
		*	== target�� target->prev�� ������踦 ����������� �Ѵ�.
		*/

		/*
		* 1) index ��ġ�� �ִ� node�� �����´�.
		*/
		Node* target = getNode(index);

		/*
		* 2) ���ο� ��带 �����Ѵ�.
		*/
		Node* node = new Node(element);

		/*
		* 3) target�� prev�� ���ο� ����� ���踦 �δ´�.
		*/
		target->prev->next = node; // target�� ���� ����� ������ node�� �ȴ�. (������ target�̾��� ���̴�.)
		node->prev = target->prev; // node�� ���� ��尡 target�� prev�� �ȴ�.

		// 4) target�� ���ο� ����� ���踦 �δ´�.
		target->prev = node; // ���� target�� ���� ���� node�� �ȴ�.
		node->next = target; // node�� ���� ���� target�� �ȴ�.

		size = size + 1;

		return;
	}

	/*
	* index�� �ִ� element�� ��ȯ�Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T get(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		Node* target = getNode(index);

		return target->value;
	}
	/*
	* index�� �ִ� element�� ��ȯ�ϰ� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual T pop(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}

		/*
		* 1) target�� value�� ã�´�.
		* target node�� ����Ŵϱ� value�� �ӽ� �����Ѵ�.
		* ret: return�� value
		*/
		Node* target = getNode(index);
		T ret = target->value;

		/*
		* 2) target�� ��/�� ���� ���踦 �������Ѵ�.
		* 
		*    target�� �����ϰ� �ִ� ���� ������ ���� ������Ʈ ���ص��ȴ�. (������ �����ҰŴϱ�)
		*/

		// target�� head�̸鼭 tail�̸�?
		if (target == head && target == tail) {
			//   ���Ұ� �ϳ��ۿ� ���� ����̱� ������ �� �� �ƹ��͵� �������� �ʵ��� �Ѵ�.
			head = tail = nullptr;
		}
		// target�� ���� �� ��(head)�̶��?
		else if (target == head) {
			head = target->next; // ���� target�� ������ head�� �ȴ�.
			head->prev = nullptr; // ������ �� ���̵Ǿ����� ���� ���(target)�� ������ ���ش�.
		}
		// target�� ���� �� ��(tail)�̶��?
		else if (target == tail) {
			tail = target->prev; // target�� ���� Node�� tail�� �ȴ�.
			tail->next = nullptr; // �� �ڴϱ� target�� ���� �ִ� next�� ������ �����.
		}
		// target�� �߰��� �ִٸ�??
		else {
			target->prev->next = target->next; // target�� ���� Node�� �ٶ󺸴� ���� ���� target�� ���� ��尡 �ȴ�.
			target->next->prev = target->prev; // target�� ���� Node�� �ٶ󺸴� ���� ���� target�� ���� ��尡 �ȴ�.
		}

		/*
		* 3) target�� �����ϰ� size�� 1�� ���δ�.
		*/
		delete target;
		size = size - 1;

		return ret;
	}
	/*
	* ��� ���Ҹ� �����Ѵ�.
	*/
	virtual void clear() override {
		/*
		* �տ������� ������ ��� ��带 �����Ѵ�. (head->tail)
		*/

		while (head != nullptr) {
			Node* temp = head->next; // head�� �����ϸ�, head�� ���� ��ġ(next)�� ������� ������ �ӽ� �����Ѵ�.
			delete head; // ���� �� ��(head)�� �����.
			head = temp; // ���� �� ����(temp)�� ���� ���� �ȴ�.

			// ������ head�� nullptr�� �ȴ�. (tail->next�� nullptr�̱� ������)
			// ��, tail���� ��� ���ﶧ���� �ݺ��Ѵ�. (while ���)
		}

		/*
		* �ʱ� ���·� �ǵ�����.
		*/
		head = tail = nullptr; // head�� tail�� nullptr. (head�� �̹� nullptr�̱� ��������..)
		size = 0; // size�� 0

		return;
	}
	/*
	* index�� �ִ� ���Ҹ� element�� �����Ѵ�.
	* index�� ��ȿ���� �ʴٸ�, Error�� �߻��Ѵ�.
	*/
	virtual void set(int index, T element) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}

		Node* target = getNode(index);
		target->value = element;
		return;
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
	virtual bool isEmpty()override {
		return size == 0;
	}

	/*
	* element�� ù��°�� ������ ������ index�� ��ȯ�Ѵ�.
	*/
	virtual int find(T element) override {
		// head���� tail���� Ž���ϸ� �ȴ�!

		Node* current = head; // current�� �տ������� ��ȸ�ϴ� �������̶�� �����ϸ� �ȴ�.
		int index = 0;

		// current != nullptr�� �򰥸���, (index < size) �� �ٲ㵵 �ȴ�.
		while (current != nullptr) { 
			// ���� ���� �ִ� node�� ���� ã������ ���ΰ�??
			if (current->value == element) {
				return index;
			}
			current = current->next; // ���� Node�� �����ϱ�, ���� ���� ����.
			index = index + 1; // index�� �ϳ��� ������Ű��.
			// �������� �ƹ��͵� ���� ����(nullptr)�� �ȴ�. (current�� tail�� ������ �Ǿ���.)
			// -> head���� tail���� ���� �� ��ȸ�ߴ�.
		}

		return -1;
	}

	/*
	* �� �տ� element�� �߰��Ѵ�.
	*/
	virtual void pushFront(T element) override {
		Node* node = new Node(element); // ���Ӱ� �߰��� node

		if (head == nullptr) {
			// �ƹ��͵� ���� ��Ȳ�̴ϱ�, head, tail�� node�� �ٲ��ش�.
			// ���Ұ� �ϳ��ۿ� ���ٸ�, �� �հ� �� �ڴ� �Ȱ��� Node��.
			head = tail = node;
		}
		else {
			// ���� �� ��(head)�� node�� ��������� �Ѵ�.
			head->prev = node; // ���� ���� ��(head)�� prev�� node�� �ȴ�.
			node->next = head; // node�� ���� ������ ���ԵǴϱ�, node�� next�� ������ head�� �ȴ�.
			head = node; // ���� node�� ���� �� ��(head)�� �ִ�
		}

		size = size + 1;

		return;
	}

	/*
	* �� �ڿ� element�� �߰��Ѵ�.
	*/
	virtual void pushBack(T element) override {
		Node* node = new Node(element); // ���Ӱ� �߰��� node

		if (tail == nullptr) {
			// �ƹ��͵� ���� ��Ȳ�̴ϱ�, head, tail�� node�� �ٲ��ش�.
			// ���Ұ� �ϳ��ۿ� ���ٸ�, �� �հ� �� �ڴ� �Ȱ��� Node��.
			head = tail = node;
		}
		else {
			// ���� �� ��(tail)�� node�� ��������� �Ѵ�.
			tail->next = node; // ���� ���� ��(tail)�� next�� node�� �ȴ�.
			node->prev = tail; // node�� ���� ������ ���ԵǴϱ�, node�� prev�� ������ tail�� �ȴ�.
			tail = node; // ���� node�� ���� �� ��(tail)�� �ִ�
		}

		size = size + 1;

		return;
	}

private:
	int size;
	// �� �հ�, �� ���� Node�� �ǹ� (���̶� �ڿ� �ִ� ������ ����)
	Node* head; 
	Node* tail;

	/*
	*  index��ġ�� �ִ� Node�� �����´�.
	*  �� ��(head)���� index Ƚ����ŭ next�� �̵��ϸ� �ȴ�.
	*/
	Node* getNode(int index) {
		int cnt = 0;
		Node* target = head;
		while (cnt < index) {
			target = target->next;
			cnt = cnt + 1;
		}
		return target;
	}
};