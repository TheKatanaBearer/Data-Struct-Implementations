

#include<iostream>
using namespace std;


class node {
public:
	int data;
	node* next;

	node(int val) {
		data = val;
		next = nullptr;

	}
};


class queue {
private:
	node* front;
	node* rear;

public:
	queue() {
		front = nullptr;
		rear = nullptr;

	}


	~queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}

	bool isEmpty() {
		return front == nullptr;

	}

	void enqueue(int val) {
		node* newnode = new node(val);

		if (front==nullptr && rear==nullptr) {
			front = rear = newnode;

		}

		else {
			rear->next = newnode;
			rear = newnode;

		}

		cout << "Enqueued " << val << endl;

	}


	void dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty cannot dequeue " << endl;
			return;
		}

		node* temp = front;
		front = front->next;

		if (front == nullptr) {
			rear = nullptr;
			//the queue has become empty

		}

		cout << "dequeued the following data " << temp->next << endl;
		delete temp;



	}


	//function to get the front element of a queue

	int getfront() {
		if (isEmpty) {
			cout << "The queue is emptry we cant pick any front element " << endl;
			return -1;

		}

		return front->data;
	}

	//copy constructor

	queue(const queue& other) {
		this->front = nullptr;
		this->rear = nullptr;

		node* temp = other.front;

		while (temp != nullptr) {
			enqueue(temp->data);
			temp = temp->next;
		}

	}

	queue& operator=(const queue& other) {


		if (this != &other) {
			while (!isEmpty) {
				dequeue();
			}
		}
		node* temp = other.front;				
		while (temp != nullptr) {
			enqueue(temp->data);
			temp = temp->next;
		}

		return *this;
	}

	bool operator==(const queue& other) {
		node* temp1 = front;
		node* temp2 = other.front;

		while (temp1 != nullptr && temp2 != nullptr) {
			if (temp1->data != temp2->data) {
				return false;

			}

			temp1 = temp1->next;
			temp2 = temp2->next;

		}

		return(temp1 == nullptr && temp2 == nullptr);



	}







};

int main() {


}