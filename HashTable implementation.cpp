#include <iostream>
#include <stdexcept> // For std::runtime_error
const int FREE = -1;
const int DEL = -2;

template <typename T>
int hash_div(T k, int m) {
    return k % m; // Hash function using modulo
}

template <typename T>
class hash_double {
    T* table; // Pointer to the hash table
    int m;    // Table size
    int n;    // Number of elements in the table

public:
    hash_double(int s = 17) {
        m = s;
        table = new T[m];
        this->n = 0;

        // Initialize the hash table with FREE
        for (int i = 0; i < m; i++) {
            table[i] = FREE;
        }
    }

    // void insert(const T &val) {
    //     if (n >= m) {
    //         throw std::runtime_error("Hash table full");
    //     }

    //     int h, idx, h2;
    //     h = hash_div(val, m);
    //     h2 = hash_div(val, m - 2);
    //     for (int i = 0; i < m; i++) {
    //         idx = (h + i * (h2 + 1)) % m;
    //         if (table[idx] == FREE || table[idx] == DEL) {
    //             table[idx] = val;
    //             n++;
    //             return;
    //         }
    //     }
    //     throw std::runtime_error("Hash table full");
    // }


    void insert(const T& val) {
        if (n >= m) {
            throw std::runtime_error("Hash table full");
        }
        //formula for quad probing -- > idx=(h+i*i)%m;
         //formula for linear probing -- > idx=(h+i)%m;
        int h, idx, h2;
        h = hash_div(val, m);
        h2 = hash_div(val, m - 1); // Ensure secondary hash produces a coprime step size
        for (int i = 0; i < m; i++) {
            idx = (h + i * h2) % m; // Updated probing formula
            if (table[idx] == FREE || table[idx] == DEL) {
                table[idx] = val;
                n++;
                return;
            }
        }
        throw std::runtime_error("Hash table full");
    }

    bool find(T& val) {
        int h, idx, h2;
        h = hash_div(val, m);
        h2 = hash_div(val, m - 1);
        for (int i = 0; i < m; i++) {
            idx = (h + i * h2) % m;
            if (table[idx] == val) {
                return true;
            }
            if (table[idx] == FREE) {
                return false; // Stop searching if an empty slot is encountered
            }
        }
        return false;
    }

    void erase(const T& val) {
        int h, idx, h2;
        h = hash_div(val, m);
        h2 = hash_div(val, m - 1);
        for (int i = 0; i < m; i++) {
            idx = (h + i * h2) % m;
            if (table[idx] == val) {
                table[idx] = DEL;
                n--;
                return;
            }
            if (table[idx] == FREE) {
                throw std::runtime_error("Value not found");
            }
        }
        throw std::runtime_error("Value not found");
    }

    void display() {
        for (int i = 0; i < this->m; i++) {
            if (table[i] != FREE && table[i] != DEL) {
                std::cout << i << " ----> " << table[i] << std::endl;
            }
            else {
                std::cout << i << " ----> empty" << std::endl;
            }
        }
    }

    ~hash_double() {
        delete[] table; // Free dynamically allocated memory
    }
};

int main() {
    try {
        hash_double<int> t(9); // Create a hash table with size 9

        t.insert(20);
        t.insert(35);
        t.insert(47);
        t.insert(18);
        t.insert(9);
        t.insert(2);
        t.insert(12);
        t.display();
        t.erase(9);
        t.erase(2);
        t.erase(12);
        std::cout << "after erasing elements " << std::endl;
        t.display();

        int val;
        while (true) {
            std::cout << "Enter a value to search: ";
            std::cin >> val;
            bool found = t.find(val);
            if (found) {
                std::cout << val << " found" << std::endl;
            }
            else {
                std::cout << val << " not found" << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
