#pragma once

#include "interface/ListInterface.h"

template <typename T>
class SinglyLinkedList : public ListInterface<T> {
private:
	struct Node {
		T value; // ���� ������ �� �ִ� ����
		Node* next; // ���� ����� ��ġ�� �����ϴ� ����

		Node(T v) {
			value = v;
			next = nullptr;
		}
	};

public:
	SinglyLinkedList() {
		size = 0;
		head = tail = nullptr;
	}

	~SinglyLinkedList() override {
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
		*	== target �ڿ��ٰ� ���ο� node�� �ִ´�. (target == ���� index ��ġ�� "����" node)
		*   == target�� target->next ���̿� �ִ´�.
		*	== target�� target->next�� ������踦 ����������� �Ѵ�.
		*/

		/*
		* 1) index ��ġ ������ �ִ� node�� �����´�.
		*/
		Node* prev = getNode(index - 1);
		Node* target = prev->next;

		/*
		* 2) ���ο� ��带 �����Ѵ�.
		*/
		Node* node = new Node(element);

		/*
		* 3) target�� ���ο� ����� ���踦 �δ´�.
		*/
		node->next = target; // node�� ���� ���� target�� �ȴ�.

		/*
		* 4) target�� ���� ���� ���ο� ����� ���踦 �δ´�.
		*/
		prev->next = node; // target�� prev ���Ŀ� node�� ����.

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

		T ret; // pop ��� node�� ���������ϱ� ������ return�� �� �ֵ��� ���� �����صд�.

		/*
		* (point) ������ ���ư� ���� ���� ������ pop ��� ���� Node���� ó���ؾ��Ѵ�.
		*/

		/*
		* head�� ���� Node�� ���� ������ ���� ó���Ѵ�.
		*/
		if (index == 0) {
			ret = head->value;
			Node* tmp = head; // head�� ����Ű�� �ִ� Node�� ����� ���� ��� �����Ѵ�.
			head = head->next; // ���� head�� ���� Node�� �ȴ�.
			delete tmp; // ���� �� �տ� �ִ� Node�� �����.
		}
		/*
		* �� �ܴ� ���� Node�� ã�Ƽ� ó���Ѵ�.
		*/
		else {
			Node* prev = getNode(index - 1); // ���� Node�� ã�´�.
			Node* target = prev->next; // target�� pop�ؾ��� node�̴�.
			ret = target->value; // value�� ���� �����صд�.

			
			if (target == tail) { // target�� tail�̶�� tail�� ������Ʈ������Ѵ�.
				tail = prev; // ���� ������ Node(tail)�� prev�� �ȴ�.
				prev->next = nullptr; // prev�ڿ��� �ƹ��͵� ����.
			}
			else { // �������� �׳� �߰��� ���� ����.
				prev->next = target->next; // prev�� ������ target�� �ƴ϶�, target�� next�� �ȴ�.
			}

			delete target; // target�� ���� ������.
		}

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