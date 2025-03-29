#include <iostream>
#include <stdexcept>
template<typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;

   
    pair(): first(0), second("") {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}

    
    bool operator==(const pair& other) const {
        return first == other.first && second == other.second;
    }

    bool operator!=(const pair& other) const {
        return !(*this == other);
    }

    bool operator<(const pair& other) const {
        return (first < other.first);
    }
};

template<typename T1, typename T2>
pair<T1, T2> make_pair(const T1& a, const T2& b) {
    return pair<T1, T2>(a, b);
}

template <typename K, typename V>
struct tNode {
    pair<K, V> data;
    tNode* parent;
    tNode* left;
    tNode* right;
    bool is_Head;

    tNode() : parent(nullptr), left(nullptr), right(nullptr), is_Head(true) {}
};

template <typename K, typename V>
class map {
    tNode<K, V>* H; // Head node
    int n;          // Number of elements

public:



    //constructor
    map() {
        H = new tNode<K, V>;
        H->left = H;
        H->right = H;
        H->parent = H;
        n = 0;
    }


    //copy-constructor

    map(const map<K, V>& other) {
        H = new tNode<K, V>;
        H->left = H;
        H->right = H;
        H->parent = H;
        n = 0;
        for (auto it = other.begin(); it != other.end(); ++it) {
            insert(it->first, it->second);
        }
    }

    void insert(const K& key, const V& value) {
        tNode<K, V>* new_node = new tNode<K, V>;
        new_node->data = make_pair(key, value);
        new_node->left = H;
        new_node->right = H;

        if (n == 0) {
            new_node->parent = H;
            H->parent = new_node;
        }
        else {
            tNode<K, V>* current = H->parent;
            tNode<K, V>* parent = nullptr;

            //checking to see if the node that we want to insert already exists in the tree or not

            while (current != H) {
                parent = current;
                if (key == current->data.first) {
                    current->data.second = value;
                    delete new_node;
                    return;
                }
                else if (key < current->data.first) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }

            //from here i am inserting the node in the tree
            if (key < parent->data.first) {
                parent->left = new_node;
            }
            else {
                parent->right = new_node;
            }
            new_node->parent = parent;
        }
        n++;
    }



    void erase(const K& key) {
        tNode<K, V>* current = H->parent;
        tNode<K, V>* parent = H;

        //searching for the node that i want to delete and if i find it will break from the loop

        while (current != H) {
            if (key == current->data.first) {
                break;
            }
            parent = current;
            if (key < current->data.first) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (current == H) {
            std::cout << "The key isn't found" << std::endl;
            return;
            // in this case the node is not found so we simply returned from the statement
        }

        //now that our traversal is complete and we have found the node..then we will delete the node
        // deleting a leaf node
        if (current->left == H && current->right == H) {
            if (parent->left == current) {
                parent->left = H;
            }
            else {
                parent->right = H;
            }
            delete current;
        }


        //in this case the node that we have to delete has only one child node and that is the left node
        else if (current->left != H && current->right == H) {
            if (parent->left == current) {
                parent->left = current->left;
            }
            else {
                parent->right = current->left;
            }
            current->left->parent = parent;
            delete current;
        }

        //in this case the node that we have to delete has only one child and that is the right node 
        else if (current->left == H && current->right != H) {
            if (parent->left == current) {
                parent->left = current->right;
            }
            else {
                parent->right = current->right;
            }
            current->right->parent = parent;
            delete current;
        }

        //in this case the node that we have to delete has two children
        else {
            tNode<K, V>* successor = current->right;
            tNode<K, V>* successor_parent = current;
            while (successor->left != H) {
                successor_parent = successor;
                successor = successor->left;
            }
            current->data = successor->data;

            if (successor_parent->left == successor) {
                successor_parent->left = successor->right;
            }
            else {
                successor_parent->right = successor->right;
            }
            if (successor->right != H) {
                successor->right->parent = successor_parent;
            }
            delete successor;
        }
        n--;
    }



    class iterator {
        tNode<K, V>* ptr;
        friend class map<K, V>;

    public:
        iterator() : ptr(nullptr) {}
        iterator(tNode<K, V>* node) : ptr(node) {}

        iterator& operator++() {
            if (!ptr->right->is_Head) {
                ptr = ptr->right;
                while (!ptr->left->is_Head) {
                    ptr = ptr->left;
                }
            }
            else {
                tNode<K, V>* parent = ptr->parent;
                while (ptr == parent->right && !parent->is_Head) {
                    ptr = parent;
                    parent = parent->parent;
                }
                ptr = parent;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        pair<K, V> operator*() const {
            return ptr->data;
        }

        iterator& operator--() {
            tNode<K>* current = ptr;

            if (current->left->is_Head != true) {
                current = current->left;
                while (current->right->is_Head != true) {
                    current = current->right;                           //pre decrement
                }
                ptr = current;
            }
            else {
                tNode<K>* parent = current->parent;
                while (current == parent->left && parent->is_Head != true) {
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
            }
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;                                  //post decrement
            --(*this);
            return temp;
        }
    };

    //this will be called inside the clear function

    void clear_r(tNode<K, V>* current) {


        if (current == H) {
            return;
        }
        clear_r(current->left);
        clear_r(current->right);
        delete current;
    }

    void clear() {
        clear_r(H->parent);
        H->parent = H;
        H->left = H;
        H->right = H;
        n = 0;
    }

    iterator begin() const {
        tNode<K, V>* current = H->parent;
        if (current == H) {
            return iterator(H);
        }
        while (current->left != H) {
            current = current->left;
        }
        return iterator(current);
    }

    iterator end() const {
        return iterator(H);
    }


    iterator rbegin() const {
        tNode<K, V>* current = H->parent;
        if (current == H) {
            return iterator(H);
        }                                                       //iterator reverse begin
        while (current->right != H) {
            current = current->right;
        }
        return iterator(current);
    }


    iterator rend() const {                                     //iterator reverse end
        iterator it;
        it.ptr = this->H;
        return it;
    }

    //making the iterator function and setting its return type as iterator
    //placing it after the iterator implementation as it utlilized the iterator class

    iterator find(const K& key) const {
        tNode<K, V>* current = H->parent;
        while (current != H) {
            if (key == current->data.first) {
                return iterator(current);
            }
            else if (key < current->data.first) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return iterator(H); //this acts as end() function
    }

    //this throws an exception when the key is not found
    V& at(const K& key) {
        tNode<K, V>* current = H->parent;
        while (current != H) {
            if (key == current->data.first) {
                return current->data.second;

            }

            else if (key < current->data.first) {
                current = current->left;

            }

            else {
                current = current->right;
            }
        }

        throw std::out_of_range("Key not found");
    }

    //this inserts a default values when the key isnt found
    V& operator[](const K& key) {
        iterator it = find(key);
        if (it != end()) {
            return (*it).second;
        }
        else {
            V value;
            insert(key, value);
            return find(key).ptr->data.second;
        }
    }


    int count(const K& key)const {
        tNode<K, V>* current = H->parent;

        while (current != H) {

            if (key == current->data.first) {

                return -1;                                     //this function is used to check if the key is present or not in the map

            }

            else if (key < current->data.firt) {
                current = current->left;
            }

            else {
                current = current->right;
            }
        }
    }

    int size()const {
        reutrn n;
    }


    bool empty()const {
        return n == 0;
    }


    //the contain function is used to check if the key is present in the map or not..it also returns bool value

    bool contains(const K& key) const {
        tNode<K, V>* current = H->parent;

        while (current != H) {
            if (key == current->data.first) {
                return true;
            }
            else if (key < current->data.first) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }


    map& operator=(const map& other) {
        if (this == &other) {
            return *this;
        }

        clear();            //the current map is cleared....making it ready to store new vals

        for (auto it = other.begin(); it != other.end(); ++it) {
            insert(it->first, it->second);
        }
    }



        ~map() {
            /* while (H->parent != H) {
           erase(H->parent->data.first);
                 } */
            clear();
            delete H;


        }




    };





