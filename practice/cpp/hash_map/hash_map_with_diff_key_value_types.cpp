// Copyright 2024 by Contributors
#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

template <typename key_type, typename value_type>
class Node {
 public:
    key_type key;
    value_type value;
    bool state;

    // Constructor
    Node(const key_type& key, value_type value) : key(key), value(value), state(true) {}

    // Defualt constructor
    Node() : key(key_type()), value(value_type()), state(true) {}

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Node<key_type, value_type>& node) {
        os << "Key: " << node.key << ", Value: " << node.value;
        return os;
    }

    void updateValue(const key_type& newKey, value_type newValue) {
        key = newKey;
        value = newValue;
        state = true;
    }

    bool empty() const {
        return !state;
    }
};

template <typename key_type, typename value_type>
class HashMap {
 private:
    double rehashSize;
    size_t size;
    size_t sizeAllNonNullptr;
    key_type defualtKey;
    value_type defualtValue;
    std::vector<Node<key_type, value_type>*> arr;

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
    size_t findEmptyIndex(const key_type& key) const {
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
    size_t findIndex(const key_type& key) const {
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

    void _add(const key_type& key, value_type value) {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        size_t i = 0;

        bool foundFirstDeleted = false;
        size_t firstDeleted = 0;

        while (arr[h1] != nullptr && i < arr.size()) {
            if (arr[h1]->key == key && arr[h1]->state) {
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
            arr[h1] = new Node<key_type, value_type>(key, value);
            sizeAllNonNullptr++;
        } else {
            arr[firstDeleted] = new Node<key_type, value_type>(key, value);
        }

        size++;
    }

    // Resize the hash table when it becomes too full
    void resize() {
        sizeAllNonNullptr = 0;
        size = 0;
        std::vector<Node<key_type, value_type>*> oldArr = arr;

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

        std::vector<Node<key_type, value_type>*> oldArr = arr;

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
        if constexpr (std::is_same<value_type, std::string>::value) {
            defualtValue = '\0';
        } else if constexpr (std::is_same<value_type, int>::value) {
            defualtValue = '\0';
        } else if constexpr (std::is_same<value_type, int64_t>::value) {
            defualtValue = '\0';
        }
    }

    // Set defualt key for constructor
    void setDefualtKey() {
        if constexpr (std::is_same<key_type, std::string>::value) {
            defualtKey = "nullptr";
        } else if constexpr (std::is_same<key_type, int>::value) {
            defualtKey = INT_MIN;
        } else if constexpr (std::is_same<key_type, int64_t>::value) {
            defualtKey = LONG_MIN;
        }
    }

    // Operator overloading
    value_type& operator[](const key_type& key) {
        size_t index = findIndex(key);
        if (arr[index] == nullptr) {
            arr[index] = new Node<key_type, value_type>(key, defualtValue);
            sizeAllNonNullptr++;
            size++;
        }
        return arr[index]->value;
    }

    // Comparison operator
    bool operator==(const HashMap& hashMap) const {
        return isEqual(hashMap);
    }

    // Comparison operator
    bool operator!=(const HashMap& hashMap) const {
        return !isEqual(hashMap);
    }

    // Operator output
    friend std::ostream& operator<<(std::ostream& os, const HashMap<key_type, value_type>& hashMap) {
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
    void put(const key_type& key, value_type value) {
        if (size + 1 > rehashSize * arr.size()) {
            resize();
        } else if (sizeAllNonNullptr > 2 * size) {
            rehash();
        }
        _add(key, value);
    }

    // Delete a key from the hash table
    void del(const key_type& key) {
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
    value_type get(const key_type& key) const {
        size_t index = findIndex(key);
        return (arr[index] == nullptr) ? defualtValue : arr[index]->value;
    }

    // Check if the current hash table is equal to another hash table
    bool isEqual(const HashMap<key_type, value_type>& other) const {
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

    // Destructor to free memory when the hash table is destroyed (unstable)
    ~HashMap() {
        for (Node<key_type, value_type>* node : arr) {
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

// Class for testing the HashMap
class Test {
 private:
    // Check if two strings are valid by comparing character frequencies
    bool isValid(std::string s, std::string t) {
        if (s.length() != t.length())
            return false;

        HashMap<std::string, int64_t> ls;
        HashMap<std::string, int64_t> lt;

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            std::string tempCharT(1, t[i]);
            ls.put(tempChar, 0);
            lt.put(tempCharT, 0);
        }

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            ls[tempChar]++;
        }

        for (size_t i = 0; i < t.length(); i++) {
            std::string tempCharT(1, t[i]);
            lt[tempCharT]++;
        }

        return ls.isEqual(lt);
    }

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
        std::string str1 = "555", str2 = "555";

        std::cout << "First string: " << str1 << std::endl;
        std::cout << "Second string: " << str2 << std::endl;

        std::cout << "Result: ";
        if (isValid(str1, str2)) {
            std::cout << "Correct" << std::endl;
        } else {
            std::cout << "Uncorrect" << std::endl;
        }
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
        HashMap<std::string, std::string> table;
        table["dog"] = "WOW";
        table["cat"] = "MEOW";
        std::cout << "key: sheep - value: " << table.get("sheep") << std::endl;
        std::cout << "key: 1234 - value: " << table.get("1234") << std::endl;
    }
};

int main() {
    Test test;
    test.test1();  // github test
    std::cout << "---------" << std::endl;
    test.test2();  // compare two string
    std::cout << "---------" << std::endl;
    test.test3();  // overtaking operator
    std::cout << "---------" << std::endl;
    test.test4();  // Pair <string, string> + uncorrect key
    std::cout << "---------" << std::endl;

    return 0;
}
