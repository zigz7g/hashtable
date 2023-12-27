//#pragma once
//#include "Class.h"
//
//template <typename T>
//class Menu {
//public:
//    static void run() {
//        Stack<T> stack;
//        std::ostringstream str;
//
//        while (true) {
//            printMenu();
//            char choice;
//            std::cin >> choice;
//
//            switch (choice) {
//            case '1':
//                addItem(stack);
//                break;
//            case '2':
//                editItem(stack);
//                break;
//            case '3':
//                displayItems(stack,str);
//                break;
//            case '4':
//                deleteItem(stack);
//                break;
//            case '5':
//                saveToFile(stack);
//                break;
//            case '6':
//                loadFromFile(stack);
//                break;
//            case '7':
//                return;
//            default:
//                std::cout << "Invalid choice. Please try again." << std::endl;
//            }
//        }
//    }
//
//private:
//    static void printMenu() {
//        std::cout << "\nMenu:\n"
//            << "1. Add Item\n"
//            << "2. Edit Item\n"
//            << "3. Display Items\n"
//            << "4. Delete Item\n"
//            << "5. Save to File\n"
//            << "6. Load from File\n"
//            << "7. Exit\n"
//            << "Enter your choice: ";
//    }
//
//    static std::string addItem(Stack<T>& stack, std::ostringstream& out, std::ostringstream& in) {
//        T value;
//        out << "Enter value to add: ";
//        in >> value;
//        stack.push(value);
//        out << "Item added successfully." << std::endl;
//    }
//
//    static std::string editItem(Stack<T>& stack, std::ostringstream& out, std::ostringstream& in, std::ostringstream& err) {
//        if (stack.isEmpty()) {
//            out << "Stack is empty. Cannot edit item." << std::endl;
//            return;
//        }
//
//        out << "Enter new value: ";
//        T newValue;
//        in >> newValue;
//
//        try {
//            stack.peek() = newValue;
//            out << "Item edited successfully." << std::endl;
//        }
//        catch (const std::out_of_range& e) {
//            err << "Error: " << e.what() << std::endl;
//        }
//    }
//
//    static std::string displayItems(const Stack<T>& stack, std::ostringstream& out) {
//        if (stack.isEmpty()) {
//            out << "Stack is empty." << std::endl;
//            return out.str();
//        }
//
//        out << "Items in the stack: " << stack << std::endl;
//        return out.str();
//    }
//
//    static std::string deleteItem(Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
//        if (stack.isEmpty()) {
//            out << "Stack is empty. Cannot delete item." << std::endl;
//            return out;
//        }
//
//        try {
//            stack.pop();
//            out << "Item deleted successfully." << std::endl;
//            return out;
//        }
//        catch (const std::out_of_range& e) {
//             err << "Error: " << e.what() << std::endl;
//             return err;
//        }
//    }
//
//    static std::string saveToFile(const Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
//        std::ofstream outputFile("stack_data.txt");
//        if (!outputFile.is_open()) {
//            cerr << "Error opening file for writing." << std::endl;
//            return err;
//        }
//
//        outputFile << stack;
//        out << "Stack data saved to file." << std::endl;
//
//        outputFile.close();
//
//        return out;
//    }
//
//    static std::string loadFromFile(Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
//        std::ifstream inputFile("stack_data.txt");
//        if (!inputFile.is_open()) {
//            err << "Error opening file for reading." << std::endl;
//            return;
//        }
//
//        inputFile >> stack;
//        out << "Stack data loaded from file." << std::endl;
//
//        inputFile.close();
//
//        return out;
//    }
//};