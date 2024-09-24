#pragma once

#include "interface/ListInterface.h"

template <typename T>
class SinglyLinkedList : public ListInterface<T> {
private:
	struct Node {
		T value; // 값을 저장할 수 있는 변수
		Node* next; // 다음 노드의 위치를 저장하는 변수

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
		// 소멸될 때, 모든 Node를 제거한다.
		clear();
	}

	/*
	* index에 element를 삽입한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual void insert(int index, T element) override {
		if (index < 0 || index > size) {
			throw std::out_of_range("Index out of range");
		}

		// 맨 앞과 맨 뒤는 각각 함수를 호출하고 끝낸다.
		if (index == 0) {
			pushFront(element);
			return;
		}
		else if (index == size) {
			pushBack(element);
			return;
		}

		/*
		*  [중간 삽입일 경우]
		*	== index 위치에다가 새로운 node를 넣어야한다.
		*	== target 뒤에다가 새로운 node를 넣는다. (target == 현재 index 위치의 "직전" node)
		*   == target과 target->next 사이에 넣는다.
		*	== target과 target->next의 연결관계를 재정의해줘야 한다.
		*/

		/*
		* 1) index 위치 직전에 있는 node를 가져온다.
		*/
		Node* prev = getNode(index - 1);
		Node* target = prev->next;

		/*
		* 2) 새로운 노드를 생성한다.
		*/
		Node* node = new Node(element);

		/*
		* 3) target과 새로운 노드의 관계를 맺는다.
		*/
		node->next = target; // node의 다음 노드는 target이 된다.

		/*
		* 4) target의 이전 노드와 새로운 노드의 관계를 맺는다.
		*/
		prev->next = node; // target의 prev 이후에 node가 들어간다.

		size = size + 1;

		return;
	}

	/*
	* index에 있는 element를 반환한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T get(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		Node* target = getNode(index);

		return target->value;
	}
	/*
	* index에 있는 element를 반환하고 삭제한다.
	* index가 유효하지 않다면, Error를 발생한다.
	*/
	virtual T pop(int index) override {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}

		T ret; // pop 대상 node는 지워져야하기 때문에 return할 수 있도록 따로 저장해둔다.

		/*
		* (point) 앞으로 돌아갈 수가 없기 때문에 pop 대상 직전 Node에서 처리해야한다.
		*/

		/*
		* head의 직전 Node는 없기 때문에 따로 처리한다.
		*/
		if (index == 0) {
			ret = head->value;
			Node* tmp = head; // head가 가르키고 있는 Node를 지우기 위해 잠시 저장한다.
			head = head->next; // 이제 head는 다음 Node가 된다.
			delete tmp; // 원래 맨 앞에 있던 Node는 지운다.
		}
		/*
		* 그 외는 직전 Node를 찾아서 처리한다.
		*/
		else {
			Node* prev = getNode(index - 1); // 직전 Node를 찾는다.
			Node* target = prev->next; // target이 pop해야할 node이다.
			ret = target->value; // value를 따로 저장해둔다.

			
			if (target == tail) { // target이 tail이라면 tail을 업데이트해줘야한다.
				tail = prev; // 가장 마지막 Node(tail)는 prev가 된다.
				prev->next = nullptr; // prev뒤에는 아무것도 없다.
			}
			else { // 나머지는 그냥 중간에 있을 때다.
				prev->next = target->next; // prev의 다음은 target이 아니라, target의 next가 된다.
			}

			delete target; // target은 이제 지우자.
		}

		size = size - 1;

		return ret;
	}
	/*
	* 모든 원소를 삭제한다.
	*/
	virtual void clear() override {
		/*
		* 앞에서부터 끝까지 모든 노드를 삭제한다. (head->tail)
		*/

		while (head != nullptr) {
			Node* temp = head->next; // head를 삭제하면, head의 다음 위치(next)도 사라지기 때문에 임시 저장한다.
			delete head; // 가장 맨 앞(head)를 지운다.
			head = temp; // 이제 그 다음(temp)이 가장 앞이 된다.

			// 언젠가 head가 nullptr이 된다. (tail->next는 nullptr이기 때문에)
			// 즉, tail까지 모두 지울때까지 반복한다. (while 사용)
		}

		/*
		* 초기 상태로 되돌린다.
		*/
		head = tail = nullptr; // head와 tail은 nullptr. (head는 이미 nullptr이긴 할테지만..)
		size = 0; // size는 0

		return;
	}
	/*
	* index에 있는 원소를 element로 수정한다.
	* index가 유효하지 않다면, Error를 발생한다.
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
	* 원소 개수를 반환한다.
	*/
	virtual int length() override {
		return size;
	}
	/*
	* 원소 개수를 반환한다.
	*/
	virtual bool isEmpty()override {
		return size == 0;
	}

	/*
	* element와 첫번째로 동일한 원소의 index를 반환한다.
	*/
	virtual int find(T element) override {
		// head부터 tail까지 탐색하면 된다!

		Node* current = head; // current는 앞에서부터 순회하는 진행요원이라고 생각하면 된다.
		int index = 0;

		// current != nullptr이 헷갈리면, (index < size) 로 바꿔도 된다.
		while (current != nullptr) {
			// 지금 보고 있는 node의 값이 찾으려는 값인가??
			if (current->value == element) {
				return index;
			}
			current = current->next; // 현재 Node는 봤으니까, 다음 노드로 가자.
			index = index + 1; // index도 하나씩 증가시키자.
			// 언젠가는 아무것도 없는 상태(nullptr)가 된다. (current가 tail의 다음이 되었다.)
			// -> head부터 tail까지 전부 다 순회했다.
		}

		return -1;
	}

	/*
	* 맨 앞에 element를 추가한다.
	*/
	virtual void pushFront(T element) override {
		Node* node = new Node(element); // 새롭게 추가될 node

		if (head == nullptr) {
			// 아무것도 없는 상황이니까, head, tail을 node로 바꿔준다.
			// 원소가 하나밖에 없다면, 맨 앞과 맨 뒤는 똑같은 Node다.
			head = tail = node;
		}
		else {
			// 가장 맨 앞(head)에 node를 연결해줘야 한다.
			node->next = head; // node가 가장 앞으로 가게되니까, node의 next가 지금의 head가 된다.
			head = node; // 이제 node가 가장 맨 앞(head)에 있다
		}

		size = size + 1;

		return;
	}

	/*
	* 맨 뒤에 element를 추가한다.
	*/
	virtual void pushBack(T element) override {
		Node* node = new Node(element); // 새롭게 추가될 node

		if (tail == nullptr) {
			// 아무것도 없는 상황이니까, head, tail을 node로 바꿔준다.
			// 원소가 하나밖에 없다면, 맨 앞과 맨 뒤는 똑같은 Node다.
			head = tail = node;
		}
		else {
			// 가장 맨 뒤(tail)에 node를 연결해줘야 한다.
			tail->next = node; // 현재 가장 뒤(tail)의 next가 node가 된다.
			tail = node; // 이제 node가 가장 맨 뒤(tail)에 있다
		}

		size = size + 1;

		return;
	}

private:
	int size;
	// 맨 앞과, 맨 뒤의 Node를 의미 (앞이랑 뒤에 있는 진행요원 느낌)
	Node* head;
	Node* tail;

	/*
	*  index위치에 있는 Node를 가져온다.
	*  맨 앞(head)에서 index 횟수만큼 next로 이동하면 된다.
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