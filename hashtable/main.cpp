#include <iostream>
#include <string>
#include <limits>

// Шаблон для хранения элемента таблицы
template <typename T>
struct HashNode {
    int key;
    T value;
    HashNode* next;
    HashNode(int k, const T& v) : key(k), value(v), next(nullptr) {}
};

// Шаблон для хеш-таблицы
template <typename T>
class HashTable {
private:
    int tableSize;  // Размер таблицы
    HashNode<T>** table;

public:
    HashTable() : tableSize(100), table(new HashNode<T>* [100]) {
        // Инициализация всех элементов массива nullptr
        for (int i = 0; i < tableSize; ++i) {
            table[i] = nullptr;
        }
    }

    explicit HashTable(int size) : tableSize(size) {
        if (size <= 0) {
            std::cerr << "Некорректный размер таблицы. Используется значение по умолчанию (100).\n";
            tableSize = 100;  // Используем значение по умолчанию
        }

        // Выделение памяти для массива ячеек таблицы
        table = new HashNode<T>*[tableSize];
        for (int i = 0; i < tableSize; ++i) {
            table[i] = nullptr;
        }
    }

    // Деструктор для освобождения выделенной памяти
    ~HashTable() {
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

    // Функция для вывода всех элементов из хеш-таблицы
    void printAllElements() const {
        std::cout << "\nВсе элементы таблицы:\n";

        for (int i = 0; i < tableSize; ++i) {
            HashNode<T>* current = table[i];
            while (current != nullptr) {
                std::cout << "Ключ: " << current->key << ", Значение: " << current->value << "\n";
                current = current->next;
            }
        }
    }

    // Получение размера таблицы
    int getTableSize() const {
        return tableSize;
    }

    // Вставка элемента в таблицу
   // Вставка элемента в таблицу
    void insert(int key, const T& value) {
        int index = hashFunction(key);
        HashNode<T>* newNode = new HashNode<T>(key, value);
        HashNode<T>* current = table[index];

        // Проверка наличия элемента с таким ключом
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

        // Вставка нового элемента
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Удаление элемента по ключу
    bool remove(int key) {
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
                return true;  // Элемент успешно удален
            }
            prev = current;
            current = current->next;
        }

        return false;  // Элемент не найден
    }

private:
    // Функция хеширования
    int hashFunction(int key) const {
        return key % tableSize;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    int tableSize;
    std::cout << "Введите размер таблицы: ";
    std::cin >> tableSize;

    HashTable<std::string> myHashTable(tableSize);

    while (true) {
        // Выводим меню
        std::cout << "\n===== Меню =====\n";
        std::cout << "1. Добавить/редактировать элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Вывести все элементы\n";
        std::cout << "4. Выйти\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Добавление/редактирование элемента
            int key;
            std::string value;

            std::cout << "Введите ключ: ";
            std::cin >> key;

            std::cout << "Введите значение ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, value);

            myHashTable.insert(key, value);

            std::cout << "Элемент добавлен/отредактирован\n";
            break;
        }

        case 2: {
            // Удаление элемента
            int key;
            std::cout << "Введите ключ элемента для удаления: ";
            std::cin >> key;

            if (myHashTable.remove(key)) {
                std::cout << "Элемент успешно удален\n";
            }
            else {
                std::cout << "Элемент не найден\n";
            }
            break;
        }

        case 3: {
            // Вывод всех элементов
            myHashTable.printAllElements();
            break;
        }

        case 4: {
            // Выход из программы
            return 0;
        }

        default:
            std::cout << "Некорректный выбор, попробуйте снова\n";
        }
    }

    return 0;
}
