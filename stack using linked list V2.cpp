

#include<iostream>
using namespace std;

struct node {
public:

	int value;
	node* next;

	node() {
		value = 0;
		next = nullptr;

	}

	node(int val, node* next) {
		value = val;
		this->next = next;
	}

};


class stack {

public:
	node* TOP;


	stack() {

		TOP = nullptr;

	}

	

	void push(int val) {
		node* temp = new node();
		temp->value = val;
		temp->next = TOP;
		TOP = temp;
		cout << "the node has been pushed successfully " << endl;
	}

	void pop() {
		if (TOP == nullptr) {
			cout << "stack underflow " << endl;

		}

		node* temp = TOP;
		TOP = TOP->next;
		delete temp;
		cout << "the element has been popped successfully " << endl;

	}


	int top()const {
		if (TOP == nullptr) {
			cout << "there is stack underflow " << endl;
			return -1;

		}

		return TOP->value;

	}


	int size()const {
		int count = 0;
		node* temp = TOP;
		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}

		return count;

	}


	void display() const {
		node* temp = TOP;
		while (temp != nullptr) {
			cout << "the value of is " << temp->value << " " << endl;
			temp = temp->next;
		}
	}



	friend bool operator==(const stack& lhs, const stack& rhs);
	friend bool operator!=(const stack& lhs, const stack& rhs);
	friend bool operator<(const stack& lhs, const stack& rhs);
	friend bool operator>(const stack& lhs, const stack& rhs);
	friend bool operator>=(const stack& lhs, const stack& rhs);
	friend void swap(stack& lhs, stack& rhs);
	

};


 bool operator==(const stack& lhs, const stack& rhs) {
	 if (lhs.size() != rhs.size()) {
		 return false;
	 }

	 node* temp1 = lhs.TOP;

	 node* temp2 = rhs.TOP;

	 while (temp1->next != nullptr && temp2 != nullptr) {
		 if (temp1->value != temp2->value) {
			 return false;
		 }

		 temp1 = temp1->next;
		 temp2 = temp2->next;

	 }

	 return true;
}

 bool operator!=(const stack& lhs, const stack& rhs) {
	 if (lhs.size() != rhs.size()) {
		 return true;

	 }

	 node* temp1 = lhs.TOP;
	 node* temp2 = rhs.TOP;

	 while (temp1->next != nullptr && temp2->next != nullptr) {
		 if (temp1->value != temp2->value) {
			 return true;
		 }
	 }
	 return false;


 }

 bool operator<(const stack& lhs, const stack& rhs) {
	 int min_size = lhs.size() < rhs.size() ? lhs.size() : rhs. size();

	 node* temp1 = lhs.TOP;
	 node* temp2 = rhs.TOP;


	 for (int i = 0; i < min_size; i++) {
		 if (temp1->value < temp2->value) {
			 return true;
		 }

		 else if (temp1->value > temp2->value) {
			 return false;
		 }

		 temp1 = temp1->next;
		 temp2 = temp2->next;
	 }

	 if (lhs.size() < lhs.size()) {
		 return true;
	}
}


 bool operator>(const stack& lhs, const stack& rhs) {
	 int min_size = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
	 node* temp1 = lhs.TOP;
	 node* temp2 = rhs.TOP;

	 for (int i = 0; i < min_size; i++) {
		 if (temp1->value > temp2->value) {
			 return true;

		 }

		 else if (temp1->value < temp2->value) {
			 return false;
		 }

		 temp1 = temp1->next;
		 temp2 = temp2->next;


	 }

	 return lhs.size() > rhs.size();
	
 }


 bool operator>=(const stack& lhs, const stack& rhs) {
	 return !(lhs < rhs);
 }

 void swap(stack& lhs, stack& rhs) {
	 node* temp = lhs.TOP;
	 lhs.TOP = rhs.TOP;
	 rhs.TOP = temp;
 }


int main() {
	stack s1;
	s1.push(15);
	s1.push(16);
	s1.push(17);


	stack s2;

	s2.push(15);
	s2.pop();
	s2.push(19);
	s2.push(18);
	s2.push(21);


	bool greater = s1 > s2;
	if (greater) {
		cout << "s1 is greater than s2 " << endl;

	}

	else {
		cout << "s2 is greater " << endl;
	}


	bool smaller = s1 < s2;

	if (smaller) {
		cout << "s1 is smaller than s2 " << endl;

	}
	else {
		cout << "s2 is smaller " << endl;
	}


	bool greaterORequal = s1 >= s2;

	if (greaterORequal) {
		cout << "s1 is greater than or equal to s2 " << endl;

	}

	else {
		cout << "it is not greater than or equal " << endl;
	}
	

	bool notEqual = s1 != s2;

	if (notEqual) {
		cout << "the both stack are not eqaul " << endl;


	}

	else {
		cout << "both the stacks are equal " << endl;
	}

	cout << "before swapping... " << endl;

	cout << "the stack1 is: " << endl;
	s1.display();

	cout << "the stack2 is: " << endl;
	s2.display();


	swap(s1, s2);

	cout << "after swapping.... " << endl;

	cout << "the stack1 is: " << endl;
	s1.display();

	cout << "the stack2 is: " << endl;
	s2.display();
}