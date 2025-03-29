// queue-sir-edition-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>






//using namespace std;

template<typename T>
class queue {
private:
	T* data;
	int head, tail, n, size1;

	template<typename U>
	friend bool operator==(const queue<U>& lhs, const queue<U>& rhs);
	template<typename U>
	friend bool operator<(const queue<U>& lhs, const queue<U>& rhs);

public:
	queue(const int s = 100) {
		size1 = s + 1;
		n = 0;
		head = 0;
		tail = 0;

		data = new T[size1];

	}


	bool empty()const {
		if (this->n == 0) {
			return true;

		}

		else {
			return false;
		}



	}


	~queue() {
		delete[]data;
	}

	int size2()const {
		return this->n;
	}


	void make_empty() {
		n = 0;
		head = tail;
	}


	T front()const {
		if (n==0) {
			throw("stack underflow ");
		}
		return this->data[(head + 1) % (size1)];

	}
	void swap(const queue<T>& other) {
		std::swap(this->head, other.head);
		std::swap(this->tail, other.tail);
		std::swap(this->n, other.n);
		std::swap(this->size1, other.size1);
		std::swap(this->data, other.data);
	}


	T back()const {
		if (n == 0) {
			throw("stack underflow ");

		}

		return data[tail];
	}


	void push(const T& val) {
		if (this->n == this->size1) {
			throw("stack overflow ");
		}

		tail = (tail + 1) % size1;
		data[tail] = val;
		++n;
	}



	void pop() {
		if (n == 0) {
			throw("stack underflow ");
			head = (head + 1) % size1;
			--n;
		}
	}
};

template<typename T>
bool operator==(const queue<T>& lhs, const queue<T>& rhs) {


	if (lhs.size2() != rhs.size2()) {
		return false;
	}

	int left_position = (lhs.head + 1) % lhs.size1;
	int right_position = (rhs.head + 1) % rhs.size1;

	for (int i = 0; i < lhs.size2(); i++) {
		if (lhs.data[left_position] != rhs.data[right_position]) {
			return false;
		}
		left_position = (left_position + 1) % lhs.size1;
		right_position = (right_position + 1) % rhs.size1;
	}

	return true;
}
                 

template<typename T>
bool operator<(const queue<T>& lhs, const queue<T>& rhs) {

	int left_position = (lhs.head + 1) % lhs.size1;
	int right_position = (lhs.head + 1) % lhs.size1;
	int i = 0;
	while (i < lhs.size2() && i < rhs.size2()) {
		if (lhs.data[left_position] < rhs.data[right_position]) {
			return true;
		}

		else if (lhs.data[left_position] > rhs.data[right_position]) {
			return false;
		}

		left_position = (left_position + 1) % lhs.size1;
		right_position = (right_position + 1) % rhs.size1;
		i++;
	}

	return lhs.size2() < rhs.size2();
}


int main() {

	queue<int>q;
	q.push(15);
	q.push(13);


	queue<int>q2;

	q2.push(16);
	q2.push(14);

	if (q == q2) {
		std::cout << "the queues are equal " << std::endl;


	}

	else {
		std::cout << "they are not equal " << std::endl;

	}

	if (q < q2) {
		std::cout << "first is smaller than second " << std::endl;
	}




}
