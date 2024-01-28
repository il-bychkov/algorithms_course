#include <iostream>
#include <vector>
#include <climits>

template <typename T, typename T2>
class Node {
public:
    T key;
    T2 value;
    bool state;

    // Constructor
    Node(const T& key, T2 value) : key(key), value(value), state(true) {}

    // Defualt constructor
    Node() : key(T()), value(T2()), state(true) {}

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Node<T, T2>& node) {
        os << "Key: " << node.key << ", Value: " << node.value;
        return os;
    }

    void updateValue(const T& newKey, T2 newValue) {
        key = newKey;
        value = newValue;
        state = true;
    }

    bool empty() const {
        return !state;
    }
};

template <typename T, typename T2>
class HashMap {
private:
    double rehashSize;
    size_t size;
    size_t sizeAllNonNullptr;
    T defualtKey;
    T2 defualtValue;
    std::vector<Node<T, T2>*> arr;

    // Hash function for generating indices based on a string key
    size_t hashGenerate(const std::string& string, size_t tableSize, size_t key) const {
        size_t hashResult = 0;
        for (char token : string) {
            hashResult = (key * hashResult + token) % tableSize;
        }
        hashResult = (hashResult * 2 + 1) % tableSize;
        return hashResult % tableSize;
    }

    // Hash function for generating indices based on an integer key
    size_t hashGenerate(const int64_t& string, size_t tableSize, size_t key) const {
        size_t hashResult = 0;
        for (char token : std::to_string(string)) {
            hashResult = (key * hashResult + token) % tableSize;
        }
        hashResult = (hashResult * 2 + 1) % tableSize;
        return hashResult % tableSize;
    }

    // First hash function using the current table size
    size_t hash1(const std::string& key) const {
        return hashGenerate(key, arr.size(), arr.size() - 1);
    }

    // First hash function using the current table size for integer keys
    size_t hash1(const int64_t& key) const {
        return hashGenerate(std::to_string(key), arr.size(), arr.size() - 1);
    }

    // Second hash function using the current table size
    size_t hash2(const std::string& key) const {
        return hashGenerate(key, arr.size(), arr.size() + 1);
    }

    // Second hash function using the current table size for integer keys
    size_t hash2(const int64_t& key) const {
        return hashGenerate(std::to_string(key), arr.size(), arr.size() + 1);
    }

    // Find an empty index for the given key using double hashing
    size_t findEmptyIndex(const T& key) const {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t i = 0;

        while (arr[h1] != nullptr && i < arr.size()) {
            if (!arr[h1]->state) {
                return h1;
            }
            h1 = (h1 + h2) % arr.size();
            ++i;
        }

        return h1;
    }

    // Get a index to put in the hash map
    size_t findIndex(const T& key) const {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t i = 0;

        while (arr[h1] != nullptr && i < arr.size()) {
            if (arr[h1]->key == key && arr[h1]->state) {
                return h1;
            }
            h1 = (h1 + h2) % arr.size();
            ++i;
        }
        return h1;
    }

    void _add(const T& key, T2 value) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        size_t i = 0;

        bool foundFirstDeleted = false;
        size_t firstDeleted = 0;

        while (arr[h1] != nullptr && i < arr.size()) {

            if (arr[h1]->key == key && arr[h1]->state) {
                //arr[h1]->value = value;
                return;
            }

            if (!arr[h1]->state && foundFirstDeleted == false) {
                firstDeleted = h1;
                foundFirstDeleted = true;
            }

            h1 = (h1 + h2) % arr.size();
            ++i;
        }

        if (foundFirstDeleted == false) {
            arr[h1] = new Node<T, T2>(key, value);
            sizeAllNonNullptr++;
        } else {
            arr[firstDeleted] = new Node<T, T2>(key, value);
        }

        size++;
    }

    // Resize the hash table when it becomes too full
    void resize() {
        sizeAllNonNullptr = 0;
        size = 0;
        std::vector<Node<T, T2>*> oldArr = arr;

        arr.clear();
        arr.resize(oldArr.size() * 2, nullptr);

        for (size_t i = 0; i < oldArr.size(); ++i) {
            if (oldArr[i] != nullptr) {
                if (oldArr[i]->state) {
                    _add(oldArr[i]->key, oldArr[i]->value);
                    delete oldArr[i];
                }
            }
        }
    }

    // Rehash the full hash table
    void rehash() {
        sizeAllNonNullptr = 0;
        size = 0;

        std::vector<Node<T, T2>*> oldArr = arr;

        arr.clear();
        arr.resize(oldArr.size(), nullptr);

        for (size_t i = 0; i < oldArr.size(); ++i) {
            if (oldArr[i] != nullptr) {
                if (oldArr[i]->state) {
                    _add(oldArr[i]->key, oldArr[i]->value);
                    delete oldArr[i]; 
                }
            }
        }
    }


public:
    // Constructor, set defualt values
    HashMap() : rehashSize(0.75), size(0), sizeAllNonNullptr(0) { 
        arr.resize(8, nullptr); 
        setDefualtKey();
        setDefualtValue();
    }

    // Set defualt value for constructor
    void setDefualtValue() {
        if constexpr (std::is_same<T2, std::string>::value) {
            defualtValue = "Value is undefinded";
        } else if constexpr (std::is_same<T2, int>::value) {
            defualtValue = INT_MIN;
        } else if constexpr (std::is_same<T2, int64_t>::value) {
            defualtValue = LONG_MIN;
        }
    }

    // Set defualt key for constructor
    void setDefualtKey() {
        if constexpr (std::is_same<T, std::string>::value) {
            defualtKey = "nullptr";
        } else if constexpr (std::is_same<T, int>::value) {
            defualtKey = INT_MIN;
        } else if constexpr (std::is_same<T, int64_t>::value) {
            defualtKey = LONG_MIN;
        }
    }
    
    // Operator overloading
    T2& operator[](const T& key) {
        size_t index = findIndex(key);
        if (arr[index] == nullptr) {
            arr[index] = new Node<T, T2>(key, defualtValue);
            sizeAllNonNullptr++;
            size++;
        }
        return arr[index]->value;
    }

    // += operator
    void operator+=(const T2& value) {
        operator[](defualtKey) += value;
    }

    // -= operator
    void operator-=(const T2& value) {
        operator[](defualtKey) -= value;
    }

    // Comparison operator
    bool operator==(const HashMap& hashMap) const {
        return isEqual(hashMap);
    }

    // Comparison operator
    bool operator!=(const HashMap& hashMap) const {
        return !isEqual(hashMap);
    }

    // Increment operator
    void operator++(int) {
        incrementValue(defualtKey);
    }

    // Decrement operator
    void operator--(int) {
        decrementValue(defualtKey);
    }

    // Operator output
    friend std::ostream& operator<<(std::ostream& os, const HashMap<T, T2>& hashMap) {
        for (size_t i = 0; i < hashMap.arr.size(); ++i) {
            os << "Index " << i << ": ";
            if (hashMap.arr[i] == nullptr || hashMap.arr[i]->empty()) {
                os << "nullptr\n";
            } else {
                os << *hashMap.arr[i] << "\n";
            }
        }
        return os;
    }

    // Insert a key-value pair into the hash table
    void put(const T& key, T2 value) {
        if (size + 1 > rehashSize * arr.size()) {
            //std::cout << "Work Resize!!!" << std::endl;
            resize();
        } else if (sizeAllNonNullptr > 2 * size) {
            //std::cout << "Work Rehash!!!" << std::endl;
            rehash();
        }
        _add(key, value);
    }

    // Insert a key initialization a zero value into the hash table
    void put(const T& key) {
        if (size + 1 > rehashSize * arr.size()) {
            resize();
        } else if (sizeAllNonNullptr > 2 * size) {
            rehash();
        }
        _add(key, 0);
    }

    // Delete a key from the hash table
    void del(const T& key) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t i = 0;

        while (arr[h1] != nullptr && i < arr.size()) {
            if (arr[h1]->key == key && arr[h1]->state) {
                delete arr[h1];
                arr[h1]->state = false;
                size--;
            }

            h1 = (h1 + h2) % arr.size();
            ++i;
        }
    }

    // Get the value associated with a key from the hash table
    T2 get(const T& key) const {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t i = 0;

        while (arr[h1] != nullptr && i < arr.size()) {
            if (arr[h1]->key == key && arr[h1]->state) {
                return arr[h1]->value;
            }
            h1 = (h1 + h2) % arr.size();
            ++i;
        }

        return defualtValue;
    }

    // Check if the current hash table is equal to another hash table
    bool isEqual(const HashMap<T, T2>& other) const {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == nullptr) {
                continue;
            }
            if (other.arr[i] == nullptr)
                return false;
            if (arr[i]->key != other.arr[i]->key || arr[i]->value != other.arr[i]->value) {
                return false;
            }
        }
        return true;
    }

    // Increment the value associated with a key
    void incrementValue(const T& key) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        if (arr[h1] == nullptr) {
            put(key, 1);
        } else if (arr[h1] != nullptr && arr[h1]->key == key) {
            arr[h1]->value++;
        } else {
            size_t i = 0;
            while (arr[h1] != nullptr && i < arr.size()) {
                if (arr[h1]->key == key) {
                    arr[h1]->value++;
                    return;
                }
                h1 = (h1 + h2) % arr.size();
                ++i;
            }
            put(key, 1);
        }
    }

    // Decrement the value associated with a key
    void decrementValue(const T& key) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        if (arr[h1] == nullptr) {
            put(key, 1);
        } else if (arr[h1] != nullptr && arr[h1]->key == key) {
            arr[h1]->value--;
        } else {
            size_t i = 0;
            while (arr[h1] != nullptr && i < arr.size()) {
                if (arr[h1]->key == key) {
                    arr[h1]->value--;
                    return;
                }
                h1 = (h1 + h2) % arr.size();
                ++i;
            }
            put(key, 1);
        }
    }

    // Destructor to free memory when the hash table is destroyed (unstable)
    ~HashMap() {
        for (Node<T, T2>* node : arr) {
            if (node != nullptr) {
                if (node->state) {
                    delete node;
                    size--;
                    sizeAllNonNullptr--;
                }
            }
        }
    }

    // Additional function
    void dump() const {
        std::cout << "------------" << std::endl;
        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << "Index " << i << ": ";
            if (arr[i] == nullptr || arr[i]->empty()) {
                std::cout << "nullptr\n";
            } else {
                std::cout << "Active Node\n";
                std::cout << "    Key: " << arr[i]->key << "\n";
                std::cout << "    Value: " << arr[i]->value << "\n";
            }
        }
    }
};

// Class for some solution 
class Solution {
public:
    // Check if two strings are valid by comparing character frequencies
    bool isValid(std::string s, std::string t) {
        if (s.length() != t.length())
            return false;

        HashMap<std::string, int64_t> ls;
        HashMap<std::string, int64_t> lt;

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            std::string tempCharT(1, t[i]);
            ls.put(tempChar);
            lt.put(tempCharT);
        }

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            ls.incrementValue(tempChar);
        }

        for (size_t i = 0; i < t.length(); i++) {
            std::string tempCharT(1, t[i]);
            lt.incrementValue(tempCharT);
        }

        return ls.isEqual(lt);
    }
};

// Class for testing the HashMap
class Test {
public:
    void test1() {
        std::cout << "Test 1 start" << std::endl;

        HashMap<std::string, int64_t> table;

        table.put("foo", 12);
        table.put("foo", 15);
        table.put("bar", 15);

        table.dump();

        table.del("bar");

        table.dump();

        table.put("bar", 78);

        table.dump();

        size_t valueToFind = table.get("foo");
        if (valueToFind != LONG_MIN) {
            std::cout << "Found value: " << valueToFind << "\n";
        } else {
            std::cout << "Key not found\n";
        }

        table.put("el0", 15);
        table.put("el1", 15);
        table.put("el2", 15);
        table.put("el3", 15);

        table.dump();

        table.put("el5", 15);

        table.dump();

        table.put("el4", 15);
        table.put("el6", 15);
        table.put("el7", 15);

        table.del("el0");
        table.del("el1");
        table.del("el2");
        table.del("el3");
        table.del("el4");
        table.del("el6");
        table.del("el7");

        table.put("new_new", 15);

        table.get("bar");

        table.dump();

        std::cout << "Test 1 end." << std::endl; 
    }

    void test2() {
        std::cout << "Test 2:\n" << std::endl;
        Solution solve;
        std::string str1 = "555", str2 = "555";

        std::cout << "First string: " << str1 << std::endl;
        std::cout << "Second string: " << str2 << std::endl;

        std::cout << "Result: ";
        if (solve.isValid(str1, str2)) std::cout << "Correct" << std::endl;
        else std::cout << "Uncorrect" << std::endl;
    }

    void test3() {
        std::cout << "Test 3:\n" << std::endl;
        HashMap<std::string, int64_t> table;
        HashMap<std::string, int64_t> table2;

        table["foo"] = 12;
        int64_t val = table["foo"];
        std::cout << "(table1)key foo : val = " << val << std::endl;
        table["foo"]++;
        table["foo"]+=1;
        table["foo"]--;
        std::cout << "(table1)key foo : val = " << table["foo"] << std::endl;

        table2["foo"] = 12;
        table2["foo"]++;
        table2["foo"]+=1;
        std::cout << "(table2)key foo : val = " << table2["foo"] << std::endl;

        std::string printEquals = (table == table2) ? "Equals" : "No equals";
        std::cout << "(table1)==(table2)? " << printEquals << std::endl;

        std::cout << "(table1)foo + (table2)foo = " << table["foo"] + table2["foo"] << std::endl;
    }

    void test4() {
        std::cout << "Test 4:\n" << std::endl;
        HashMap<int64_t, int64_t> table;
        for (int64_t i = 1; i < 11; i++) {
            table[i] = i;
        }
        std::cout << table << std::endl;
    }

    void test5() {
        std::cout << "Test 5:\n" << std::endl;
        HashMap<int, int> table;
        for (int i = 1; i < 11; i++) {
            table[i] = i;
        }
        std::cout << (table.get(1000) == INT_MIN) << std::endl;
        std::cout << table << std::endl;
    }

    void test6() {
        std::cout << "Test 6:\n" << std::endl;
        HashMap<std::string, std::string> table;
        table["dog"] = "WOW";
        table["cat"] = "MEOW";
        std::cout << table.get("sheep") << std::endl;
    }

};

int main() {
    Test test;
    test.test1(); //github test
    std::cout << "---------" << std::endl;
    test.test2(); //compare two string
    std::cout << "---------" << std::endl;
    test.test3(); //overtaking operator
    std::cout << "---------" << std::endl;
    test.test4(); //Pair <int64_t, int64_t>
    std::cout << "---------" << std::endl;
    test.test5(); //Pair <int, int> + uncorrect key
    std::cout << "---------" << std::endl;
    test.test6(); //Pair <string, string> + uncorrect key
    std::cout << "---------" << std::endl;
    return 0;
}