#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Node.h"


template <typename T>
class Stack {
private:

    Node<T>* top;

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
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        Node<T>* temp = top;
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
        Node<T>* current = stack.top;
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
        Node<T>* current = stack.top;
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

   

    static std::string editItem(Stack<T>& stack, std::ostringstream& out, T newValue, std::ostringstream& err) {

        try {
            stack.peek() = newValue;
            out << "Item edited successfully." << std::endl;
            return out.str();
        }
        catch (const std::out_of_range& e) {
            err << "Error: " << e.what() << std::endl;
            return err.str();
        }
    }

    static std::string displayItems(const Stack<T>& stack, std::ostringstream& out) {
        if (stack.isEmpty()) {
            out << "Stack is empty." << std::endl;
            return out.str();
        }

        out << "Items in the stack: " << stack << std::endl;
        return out.str();
    }

    static std::string deleteItem(Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
        if (stack.isEmpty()) {
            out << "Stack is empty. Cannot delete item." << std::endl;
            return out.str();
        }

        try {
            stack.pop();
            out << "Item deleted successfully." << std::endl;
            return out.str();
        }
        catch (const std::out_of_range& e) {
            err << "Error: " << e.what() << std::endl;
            return err.str();
        }
    }

    static std::string saveToFile(const Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
        std::ofstream outputFile("stack_data.txt");
        if (!outputFile.is_open()) {
            err << "Error opening file for writing." << std::endl;
            return err.str();
        }

        outputFile << stack;
        out << "Stack data saved to file." << std::endl;

        outputFile.close();

        return out.str();
    }

    static std::string loadFromFile(Stack<T>& stack, std::ostringstream& out, std::ostringstream& err) {
        std::ifstream inputFile("stack_data.txt");
        if (!inputFile.is_open()) {
            err << "Error opening file for reading." << std::endl;
            return err.str();
        }

        inputFile >> stack;
        out << "Stack data loaded from file." << std::endl;

        inputFile.close();

        return out.str();
    }

};


