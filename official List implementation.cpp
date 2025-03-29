#include <iostream>

namespace cs211 {
    template <typename T>
    struct dnode
    {
        dnode<T>* next;
        dnode<T>* prev;
        T val;
    };
    template <typename T>
    class list
    {
    private:
        dnode<T>* Head;
        int n;

    public:
        list()
        {
            // Creating Dummy node
            Head = new dnode<T>;
            Head->next = this->Head;
            Head->prev = this->Head;
        }

		// Destructor
		~list()
		{
			dnode<T>* temp;
			temp = this->Head->next;
			while (temp != this->Head)
			{
				this->Head->next = temp->next;
				delete temp;
				temp = this->Head->next;
			}
			delete this->Head;
		} 




        // Push Back
        void push_back(const T& val)
        {
            dnode<T>* newnode;
            newnode = new dnode<T>;
            newnode->val = val;
            newnode->next = this->Head;
            newnode->prev = this->Head->prev;
            this->Head->prev->next = newnode;
            Head->prev = newnode;
            ++this->n;
        }
        // Push front
        void push_front(const T& val)
        {
            dnode<T>* newnode;
            newnode = new dnode<T>;
            if (Head->prev == Head)
            {
                newnode->val = val;
                newnode->prev = this->Head;
                newnode->next = this->Head;
                ++this->n;
            }
            else
            {
                newnode->val = val;
                newnode->next = this->Head->next;
                newnode->prev = this->Head;
                this->Head->next = newnode;
                ++this->n;
            }
        }
        bool empty()
        {
            if (this->Head->next == this->Head)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // Pop Back
        void pop_back()
        {
            if (empty())
            {
                throw(" list is empty ");
            }
            else
            {
                dnode<T>* temp;
                temp = this->Head->prev;
                temp->prev->next = this->Head;
                this->Head->prev = temp->prev;
                delete temp;
                --this->n;
            }
        }
        // pop front()
        void pop_front()
        {
            if (empty())
            {
                throw("list is empty ");
            }
            else
            {
                dnode<T>* temp;
                temp = this->Head->next;
                this->Head->next = temp->next;
                delete temp;
                --this->n;
                if (n == 0)
                {
                    this->Head->prev = this->Head;
                }
            }
        }
        void Display()
        {
            dnode<T>* temp;
            temp = new dnode<T>;
            temp = this->Head->next;

            while (temp != this->Head)
            {
                std::cout << temp->val << " ";
                temp = temp->next;
            }
        }


        class iterator
        {
        private:
            dnode<T>* ptr;

        public:
            friend list;

            // operator !=
            bool operator!=(const iterator& rhs) const
            {
                return this->ptr != rhs.ptr;
            }
            // operator ==
            bool operator==(const iterator& rhs) const
            {
                return this->ptr == rhs->ptr;
            }
            // pre increment
            iterator& operator++() // why reference?
            {
                this->ptr = this->ptr->next;
                return *this;
            }
            // post increment
            iterator operator++(int)
            {
                iterator old;
                old.ptr = this->ptr;
                this->ptr = this->ptr->next;
                return old;
            }
            // pre decrement
            iterator operator--()
            {
                return this->ptr->prev;
            }
            // post decrement
            iterator operator--(int)
            {
                iterator old;
                old.ptr = this->ptr;
                this->ptr = this->ptr->prev;
                return old;
            }
            // Dereference
            T& operator*()
            {
                return this->ptr->val;
            }
            //-> Arrow
            T* operator->()
            {
                return &(this->ptr->val);
            }
        };
        // begin
        iterator begin()
        {
            iterator temp;
            temp.ptr = this->Head->next;
            return temp;
        }
        // end
        iterator end()
        {
            iterator temp;
            temp.ptr = this->Head;
            return temp;
        }
        // insert
        iterator insert(iterator it, const T& val)
        {
            dnode<T>* pos;
            pos = it.ptr;
            if (pos == nullptr)
            {
                throw("invalid position ");
            }
            else
            {
                dnode<T>* newnode;
                newnode->val = val;
                newnode->next = pos;
                newnode->prev = pos->prev;
                pos->prev = newnode;
                pos->prev->next = newnode;
                ++this->n;
                it.ptr = newnode;
                return it;
            }
        }
        // erase
        iterator erase(iterator it)
        {
            dnode<T>* pos;
            pos = it.ptr;
            if (pos == nullptr)
            {
                throw("invalid pos");
            }

            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;
            it.ptr = pos->next;
            delete pos;
            --this->n;
            return it;
        }
        // unique
        void unique() {
            dnode<T>* current;
            current = this->Head->next;
            while (current->next != this->H) {
                if (current->data == current->next->data) {
                    dnode<T>* temp;
                    temp = current->next;
                    current->next = temp->next;
                    temp->next->prev = current;
                    delete temp;
                    this->n--;
                }
                current = current->next;
            }
        }
        //remove
        void remove(const T& val) {
            if (this->H->next->val == val) {
                dnode<T>* temp;
                temp = this->H->next;
                this->H->next = temp->next;
                temp->next->prev = this->H;
                delete temp;
                this->n--;
            }

            dnode<T>* current = this->Head->next;
            while (current != this->Head) {
                if (current->val == val) {
                    dnode<T>* temp = current;
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete temp; // Delete the node
                    this->n--;
                    return;
                }
                current = current->next;
            }
        }
        //splice After
        void splice_after(iterator it, const T& other)
        {
            dnode <T>* pos;
            pos = it.ptr;
            if (other.Head->next != other.Head)
            {
                pos->next = other.Head->next;
                other.Head->next->prev = pos;
                other.H->prev = pos->next->next;
                pos->next->prev = other.Head->prev;

                this->n += other.n;
                other.Head->next = other.Head;
                other.Head->prev = other.Head;
                other.n = 0;
            }

            else
            {
                std::cout << "list 2 is empty to perform splice after..\n";
            }
        }


    };
}


int main()
{
    cs211::list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_front(0);
    // l1.pop_front();
    l1.Display();
    typename cs211::list<int>::iterator it;
    it = l1.begin();
    l1.insert(it, 4);
    while (it != l1.end())
    {

        std::cout << *it << " ";
        ++it;
    }
    // std::cout<<std::endl;

    // it=l1.begin();

    // it=l1.erase(it);
    // while (it!=l1.end())
    // {
    //     std::cout<<*it<<" ";
    //     ++it;
    // }
    // std::cout<<std::endl;



}