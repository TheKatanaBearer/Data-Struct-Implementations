#include <iostream>

template <typename K>
struct tNode {
    K key;
    tNode* parent;
    tNode* left;
    tNode* right;
    bool is_Head;

    tNode() {
        is_Head = true;
        parent = left = right = nullptr;
    }
};

template <typename K>
class set {
    tNode<K>* H; // Head node
    int n;       // Number of elements

public:
    set() {
        H = new tNode<K>;
        H->left = H;
        H->right = H;
        H->parent = H;
        n = 0;
    }

    void insert(const K& key) {
        tNode<K>* new_node = new tNode<K>;
        new_node->key = key;
        new_node->left = H;
        new_node->right = H;

        if (n == 0) {
            new_node->parent = H;
            H->parent = new_node;
        }
        else {
            tNode<K>* current = H->parent;
            tNode<K>* parent = nullptr;

            while (current != H) {
                parent = current;
                if (key == current->key) {
                    delete new_node;
                    return;
                }
                else if (key < current->key) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }

            if (key < parent->key) {
                parent->left = new_node;
            }
            else {
                parent->right = new_node;
            }
            new_node->parent = parent;
        }
        n++;
    }

    bool find(const K& key) const {
        tNode<K>* current = H->parent;
        while (current != H) {
            if (key == current->key) {
                return true;
            }
            else if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;
    }

    class iterator {
        tNode<K>* ptr;
        friend class set<K>;

    public:                                                     //keep in mind that we do current=ptr because ptr is part of the class so we dont need to call any iterator object
        iterator() : ptr(nullptr) {}
        iterator(tNode<K>* node) : ptr(node) {}

        iterator& operator++() {                //we will start from the left most..the begin function will take us there
			                                    //we wil check if the node has a right node or not if it has then we will go to the right node and then to the left most node of that right node
			                                    //if the node does not have a right node then we will go to the parent node
            tNode<K>* current = ptr;

            if (current->right->is_Head != true) {
                current = current->right;
                while (current->left->is_Head != true) {
                    current = current->left;
                }
                ptr = current;
            }                       
            else {                                                              
                tNode<K>* parent = current->parent;                                                 
                while (current == parent->right && parent->is_Head != true) {
					                                                             //if the node is the right child of the parent then we will go to the parent node
																				 //and the parent node will move to the parent node
                                                                                
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
            }
            return *this;
        }


		iterator operator++(int) {
                                                                //*this is used to store the current state of the object
                                                                //in obj.setX(10) obj is the current state of the object
                                                                //*this is used when you need to retrn the current state of the object
                                                                 //*this is also used when you want to copy the current state of the object 
			iterator temp = *this;
			++(*this);                                          //post operator 
			                                                   
			return temp;
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


        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

		const K& operator*() const {                    //for -> operator it is the same as the * operator
            return ptr->key;
        }

        iterator rbegin() const {
            tNode<K>* current = H->parent;
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




    };
                                                                
                                                                                //see the utility of making the set class a friend class of 
	                                                                            //the iterator class...in case of empty tree the iterators ptr will point to H
                                                                                


    iterator begin() const {
        tNode<K>* current = H->parent; // Start at the root
        if (current == H) {           // Empty tree                                        
            return iterator(H);
		}                                                                                   //iterator begin
        while (current->left != H) {  // Traverse to the leftmost node
            current = current->left;
        }
        return iterator(current);     // Return iterator to the leftmost node
    }


    iterator end() const {
        iterator it;                                                                         //iterator end
        it.ptr = this->H; // End iterator points to the sentinel node
        return it;
    }


    

    void erase(const K& key) {
        tNode<K>* current = H->parent;
        tNode<K>* parent = H;

        while (current != H) {
            if (key == current->key) {
                break;
            }
            parent = current;
            if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (current == H) {
            std::cout << "The key isn't found" << std::endl;
            return;
        }

        if (current->left == H && current->right == H) {
            if (parent->left == current) {
                parent->left = H;
            }
            else {
                parent->right = H;
            }
            delete current;
        }
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
        else {
            tNode<K>* successor = current->right;
            tNode<K>* successor_parent = current;
            while (successor->left != H) {
                successor_parent = successor;
                successor = successor->left;
            }
            current->key = successor->key;

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

    //this is the contain function

    
    bool contains(const K& key) const {
        return find(key);



        //this is the destructor
        ~set() {
            while (H->parent != H) {
                erase(H->parent->key);
            }
            delete H;
        }

    }


};

int main() {
    set<int> s;

    // Insert elements
    s.insert(10);
    s.insert(5);
    s.insert(15);
    s.insert(3);
    s.insert(7);

    // Print all elements using iterator (forward traversal)
    std::cout << "Elements in the set (forward): ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Print all elements using iterator (reverse traversal)
    std::cout << "Elements in the set (reverse): ";
    auto it = s.end();
    --it; // Move to the last valid element
    while (it != s.end()) {
        std::cout << *it << " ";
        --it;
    }
    std::cout << std::endl;

    // Check for existence of elements
    std::cout << "Find 7: " << (s.find(7) ? "Found" : "Not Found") << std::endl;
    std::cout << "Find 20: " << (s.find(20) ? "Found" : "Not Found") << std::endl;

    // Erase an element
    std::cout << "Erasing 5..." << std::endl;
    s.erase(5);

    // Print all elements again (forward traversal)
    std::cout << "Elements in the set after erasing 5 (forward): ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}



//implement contain
