#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    T& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        return top->data;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack) {
        Node* current = stack.top;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Stack& stack) {
        T value;
        is >> value;
        stack.push(value);
        return is;
    }

    friend std::ofstream& operator<<(std::ofstream& ofs, const Stack& stack) {
        Node* current = stack.top;
        while (current != nullptr) {
            ofs << current->data << " ";
            current = current->next;
        }
        return ofs;
    }

    friend std::ifstream& operator>>(std::ifstream& ifs, Stack& stack) {
        T value;
        while (ifs >> value) {
            stack.push(value);
        }
        return ifs;
    }

    friend std::istringstream& operator>>(std::istringstream& iss, Stack& stack) {
        T value;
        while (iss >> value) {
            stack.push(value);
        }
        return iss;
    }

    friend std::ostringstream& operator<<(std::ostringstream& oss, const Stack& stack) {
        Node* current = stack.top;
        while (current != nullptr) {
            oss << current->data << " ";
            current = current->next;
        }
        return oss;
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* start) : current(start) {}

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        T& operator*() const {
            return current->data;
        }
    };

    Iterator begin() const {
        return Iterator(top);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

template <typename T>
class Menu {
public:
    static void run() {
        Stack<T> stack;

        while (true) {
            printMenu();
            char choice;
            std::cin >> choice;

            switch (choice) {
            case '1':
                addItem(stack);
                break;
            case '2':
                editItem(stack);
                break;
            case '3':
                displayItems(stack);
                break;
            case '4':
                deleteItem(stack);
                break;
            case '5':
                saveToFile(stack);
                break;
            case '6':
                loadFromFile(stack);
                break;
            case '7':
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

private:
    static void printMenu() {
        std::cout << "\nMenu:\n"
            << "1. Add Item\n"
            << "2. Edit Item\n"
            << "3. Display Items\n"
            << "4. Delete Item\n"
            << "5. Save to File\n"
            << "6. Load from File\n"
            << "7. Exit\n"
            << "Enter your choice: ";
    }

    static void addItem(Stack<T>& stack) {
        T value;
        std::cout << "Enter value to add: ";
        std::cin >> value;
        stack.push(value);
        std::cout << "Item added successfully." << std::endl;
    }

    static void editItem(Stack<T>& stack) {
        if (stack.isEmpty()) {
            std::cout << "Stack is empty. Cannot edit item." << std::endl;
            return;
        }

        std::cout << "Enter new value: ";
        T newValue;
        std::cin >> newValue;

        try {
            stack.peek() = newValue;
            std::cout << "Item edited successfully." << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    static void displayItems(const Stack<T>& stack) {
        if (stack.isEmpty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }

        std::cout << "Items in the stack: " << stack << std::endl;
    }

    static void deleteItem(Stack<T>& stack) {
        if (stack.isEmpty()) {
            std::cout << "Stack is empty. Cannot delete item." << std::endl;
            return;
        }

        try {
            stack.pop();
            std::cout << "Item deleted successfully." << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    static void saveToFile(const Stack<T>& stack) {
        std::ofstream outputFile("stack_data.txt");
        if (!outputFile.is_open()) {
            std::cerr << "Error opening file for writing." << std::endl;
            return;
        }

        outputFile << stack;
        std::cout << "Stack data saved to file." << std::endl;

        outputFile.close();
    }

    static void loadFromFile(Stack<T>& stack) {
        std::ifstream inputFile("stack_data.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file for reading." << std::endl;
            return;
        }

        inputFile >> stack;
        std::cout << "Stack data loaded from file." << std::endl;

        inputFile.close();
    }
};

int main() {
    Menu<int>::run();

    return 0;
}
