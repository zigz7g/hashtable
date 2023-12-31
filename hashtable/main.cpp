#include <iostream>
#include <string>
#include <limits>
#include "Test1.cpp"

template <typename T>
struct HashNode {
    int key;
    T value;
    HashNode* next;
    HashNode(int k, const T& v) : key(k), value(v), next(nullptr) {}
};


template <typename T>
class HashTable {
private:
    int tableSize;  
    HashNode<T>** table;

public:
    HashTable();
    explicit HashTable(int size);
    ~HashTable();

    void printAllElements() const;
    int getTableSize() const;
    void insert(int key, const T& value);
    bool remove(int key);

private:

    int hashFunction(int key) const;
};

int main() {
    setlocale(LC_ALL, "Russian");

    int tableSize;
    std::cout << "������� ������ �������: ";
    std::cin >> tableSize;

    HashTable<std::string> myHashTable(tableSize);

    while (true) {
        // ������� ����
        std::cout << "\n===== ���� =====\n";
        std::cout << "1. ��������/������������� �������\n";
        std::cout << "2. ������� �������\n";
        std::cout << "3. ������� ��� ��������\n";
        std::cout << "4. �����\n";
        std::cout << "�������� ��������: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // ����������/�������������� ��������
            int key;
            std::string value;

            std::cout << "������� ����: ";
            std::cin >> key;

            std::cout << "������� �������� ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, value);

            myHashTable.insert(key, value);

            std::cout << "������� ��������/��������������\n";
            break;
        }

        case 2: {
            // �������� ��������
            int key;
            std::cout << "������� ���� �������� ��� ��������: ";
            std::cin >> key;

            if (myHashTable.remove(key)) {
                std::cout << "������� ������� ������\n";
            }
            else {
                std::cout << "������� �� ������\n";
            }
            break;
        }

        case 3: {
            // ����� ���� ���������
            myHashTable.printAllElements();
            break;
        }

        case 4: {
            // ����� �� ���������
            return 0;
        }

        default:
            std::cout << "������������ �����, ���������� �����\n";
        }
    }

    return 0;
}

template <typename T>
HashTable<T>::HashTable() : tableSize(100), table(new HashNode<T>* [100]) {
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

template <typename T>
HashTable<T>::HashTable(int size) : tableSize(size) {
    if (size <= 0) {
        std::cerr << "������������ ������ �������. ������������ �������� �� ��������� (100).\n";
        tableSize = 100;
    }

    table = new HashNode<T>*[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < tableSize; ++i) {
        HashNode<T>* current = table[i];
        while (current != nullptr) {
            HashNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template <typename T>
void HashTable<T>::printAllElements() const {
    std::cout << "\n��� �������� �������:\n";

    for (int i = 0; i < tableSize; ++i) {
        HashNode<T>* current = table[i];
        while (current != nullptr) {
            std::cout << "����: " << current->key << ", ��������: " << current->value << "\n";
            current = current->next;
        }
    }
}

template <typename T>
int HashTable<T>::getTableSize() const {
    return tableSize;
}

template <typename T>
void HashTable<T>::insert(int key, const T& value) {
    int index = hashFunction(key);
    HashNode<T>* newNode = new HashNode<T>(key, value);
    HashNode<T>* current = table[index];
    HashNode<T>* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = newNode;
            }
            else {
                prev->next = newNode;
            }
            newNode->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }

    newNode->next = table[index];
    table[index] = newNode;
}

template <typename T>
bool HashTable<T>::remove(int key) {
    int index = hashFunction(key);
    HashNode<T>* current = table[index];
    HashNode<T>* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

template <typename T>
int HashTable<T>::hashFunction(int key) const {
    return key % tableSize;
}
