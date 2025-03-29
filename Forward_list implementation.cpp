
#include <iostream>
template <typename T>
struct node
{
    T data;
    node* next;
};

template <typename T>
class forward_list
{
    int size, n;
    node<T>* top;

public:
    forward_list(int s = 10)
    {
        size = s;
        n = 0;
        top = new node<T>;
        top = nullptr;
    }
    int SIZE()
    {
        return this->n;
    }
    void push_front(T d)
    {
        if (SIZE() >= this->size)
        {
            throw "stack overflow";
        }
        node<T>* temp;
        temp = new node<T>;
        temp->data = d;
        temp->next = this->top;
        this->top = temp;
        ++this->n;
        sort();
    }
    void push_at_pos(int data, int pos)
    {
        node<T>* temp = this->top;
        node<T>* ptr;
        ptr = new node<T>;
        ptr->data = data;
        ptr->next = nullptr;
        while ((pos - 1) > 1)
        {
            temp = temp->next;
            pos--;
        }
        ptr->next = temp->next;
        temp->next = ptr;
    }
    void pop()
    {
        if (this->top == nullptr)
        {
            throw "stack underflow";
        }
        node<T>* temp;
        temp = new node<T>;
        temp = this->top->next;
        delete this->top;
        top = temp;
        --this->n;
    }
    void pop_from(int val)
    {
        if (val > this->n || val < 0)
        {
            throw "cannot pop";
        }
        // std ::cout << this->n << std ::endl;
        if (val == 1)
        {
            pop();
        }
        else
        {
            node<T>* temp, * temp_prev;
            temp = new node<T>;
            temp = this->top;
            temp_prev = nullptr;
            int count = 1;
            while (count < val)
            {
                temp_prev = temp;
                temp = temp->next;
                count++;
            }
            temp_prev->next = temp->next;
            delete temp;
            --this->n;
        }
    }
    void sort()
    {
        node<T>* temp1, * temp2;
        temp1 = new node<T>;
        temp2 = new node<T>;
        temp1 = this->top;
        if (this->top == nullptr)
        {
            std::cout << " list is empty " << std::endl;
        }
        while (temp1 != nullptr)
        {
            temp2 = temp1->next;
            while (temp2 != nullptr)
            {
                if (temp1->data > temp2->data)
                {
                    std::swap(temp1->data, temp2->data);
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
    }
    void free()
    {
        node<T>* temp;
        temp = this->top;
        while (this->top != nullptr)
        {
            temp = temp->next;
            delete this->top;
            this->top = temp;
            --this->n;
        }
    }
    bool empty()
    {
        if (top == nullptr)
        {
            return 1;
        }
        return 0;
    }
    bool full()
    {
        if (SIZE() >= this->size)
        {
            return 1;
        }
        return 0;
    }

    void display()
    {
        if (this->top == nullptr)
        {
            std::cout << "list is empty" << std::endl;
        }
        node<T>* temp;
        temp = new node<T>;
        temp = this->top;
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    class iterator
    {
        node<T>* ptr;
        friend class forward_list<T>;

    public:
        iterator operator++(int)
        {
            iterator temp;
            temp.ptr = this->ptr;
            this->ptr = this->ptr->next;
            return temp;
        }
        iterator operator++()
        {
            iterator temp;
            temp.ptr = this->ptr->next;
            return temp;
        }
        bool operator!=(const iterator& rhs) const
        {
            return this->ptr != rhs.ptr;
        }
        bool operator==(const iterator& rhs) const
        {
            return this->ptr == rhs.ptr;
        }
        T operator*() const
        {
            return this->ptr->data;
        }
    };
    iterator begin() const
    {
        iterator it;
        it.ptr = this->top;
        return it;
    }
    iterator end() const
    {
        iterator it;
        it.ptr = nullptr;
        return it;
    }
    iterator iter_at(int pos)
    {
        iterator it;
        if (pos < 0 || pos > this->n)
        {
            throw "cannot set iterator";
        }
        else if (pos == 0)
        {
            it = begin();
        }
        else
        {
            node<T>* temp;
            temp = this->top;
            while (pos > 0)
            {
                temp = temp->next;
                pos--;
            }
            it.ptr = temp;
        }
        return it;
    }
    void insert_after(iterator it, const T& val)
    {
        node<T>* temp;
        temp = new node<T>;
        temp->data = val;
        temp->next = it.ptr->next;
        it.ptr->next = temp;
    }
    void erase_after(iterator it1, iterator it2)
    {
        if (it1.ptr == nullptr || it2.ptr == nullptr)
        {
            return;
        }
        node<T>* temp1, * temp2, * temp;
        temp1 = it1.ptr->next;
        temp2 = it2.ptr->next;
        while (temp1 != temp2)
        {
            temp = temp1;
            temp1 = temp1->next;
            delete temp;
        }
        it1.ptr->next = temp2;
    }
    void splice_after(iterator it, forward_list<T>& f)
    {

        node<T>* temp, * temp1, * temp2;
        temp = it.ptr;
        temp1 = f.top;
        temp2 = f.top;
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
        }
        temp2 = temp->next;
        temp->next = temp1;
        f.top = nullptr;
    }
};


int main()
{
    forward_list<int> f1, f2;
    f1.push_front(5);
    f1.push_front(4);
    f1.push_front(56);
    f1.push_front(2);
    f1.push_front(-1);
    f1.push_front(3);
    f1.display();
    f2.push_front(3);
    f2.push_front(2);
    f2.push_front(1);
    f2.display();
    forward_list<int> ::iterator it, it1;
    it = f1.begin();
    it = f1.iter_at(2);
    it1 = f1.iter_at(4);
    f1.insert_after(it, 7);
    f1.display();
    f1.erase_after(it, it1);
    f1.display();
    it = f1.iter_at(2);
    f1.splice_after(it, f2);
    f1.display();
}