#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
    T* arr;           // Array to store stack elements
    int top;          // Index of the top element
    int capacity;     // Maximum capacity of the stack

public:
    // Constructor to initialize the stack with a given capacity
    Stack(int size) {
        arr = new T[size];
        capacity = size;
        top = -1;
    }


    Stack(const Stack<T>& other) {
        capacity = other.capacity;
        top = other.top;

        // Allocate new memory for the copied stack
        arr = new T[capacity];

        // Copy all elements from the other stack
        for (int i = 0; i <= top; ++i) {
            arr[i] = other.arr[i];
        }
    }

    // Destructor to free up memory
    ~Stack() {
        delete[] arr;
    }

    // Function to add an element to the stack
    void push(T value) {
        if (top == capacity - 1) {
            cout << "Stack overflow, cannot push " << value << endl;
            return;
        }
        arr[++top] = value;
    }

    // Function to remove the top element from the stack
    void pop() {
        if (isEmpty()) {
            cout << "Stack underflow, cannot pop" << endl;
            return;
        }
        --top;
    }

    // Function to return the top element of the stack
    T peek() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return T();  // Return default value of T
        }
        return arr[top];
    }

    // Function to check if the stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Function to get the current size of the stack
    int size() const {
        return top + 1;
    }

    // Overloaded comparison operators
    // Equality operator
    friend bool operator==(const Stack<T>& s1, const Stack<T>& s2) {
        if (s1.size() != s2.size())
            return false;
        for (int i = 0; i <= s1.top; i++) {
            if (s1.arr[i] != s2.arr[i])
                return false;
        }
        return true;
    }

    // Inequality operator
    friend bool operator!=(const Stack<T>& s1, const Stack<T>& s2) {
        return !(s1 == s2);
    }
    friend bool operator<(const Stack<T>& s1, const Stack<T>& s2) {
        int minSize = min(s1.size(), s2.size());
        for (int i = 0; i < minSize; ++i) {
            if (s1.arr[i] < s2.arr[i]) return true;
            if (s1.arr[i] > s2.arr[i]) return false;
        }
        return s1.size() < s2.size();  // If all elements are equal, the shorter stack is "less"
    }

    // Lexicographic greater-than operator
    
    friend bool operator>(const Stack<T>& s1, const Stack<T>& s2) {
        int minSize = min(s1.size(), s2.size());
        for (int i = 0; i < minSize; ++i) {
            if (s1.arr[i] > s2.arr[i]) return true;
            if (s1.arr[i] < s2.arr[i]) return false;
        }
        return s1.size() > s2.size();  // If all elements are equal, the longer stack is "greater"
    }


    Stack<T>& operator=(const Stack<T>& other) {
        if (this == &other) return *this;  // Self-assignment check

        delete[] arr;  // Delete the existing array to prevent memory leak

        // Copy capacity and top index
        capacity = other.capacity;
        top = other.top;

        // Allocate new memory and copy elements
        arr = new T[capacity];
        for (int i = 0; i <= top; ++i) {
            arr[i] = other.arr[i];
        }

        return *this;
    }
 
};

int main() {
    Stack<int> stack1(5);
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);

    Stack<int> stack2(5);
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);

    cout << "Stack 1 == Stack 2: " << (stack1 == stack2) << endl;
    cout << "Stack 1 != Stack 2: " << (stack1 != stack2) << endl;
    cout << "Stack 1 < Stack 2: " << (stack1 < stack2) << endl;
    cout << "Stack 1 > Stack 2: " << (stack1 > stack2) << endl;

    stack1.pop();
    cout << "After popping an element from Stack 1:" << endl;
    cout << "Stack 1 == Stack 2: " << (stack1 == stack2) << endl;

    return 0;
}
