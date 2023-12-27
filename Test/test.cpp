#include "pch.h"
#include "C:\Users\windo\Desktop\уник\hashtable\hashtable\Class.h"
#include "C:\Users\windo\Desktop\уник\hashtable\hashtable\Node.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(StackTest, Push) {
    Stack<int> stack;

    stack.push(1);
    ASSERT_FALSE(stack.isEmpty());

}

TEST(StackTest, Pop) {
    Stack<int> stack;

    stack.push(1);
    ASSERT_EQ(stack.peek(), 1);

}

TEST(StackTest, Peek) {
    Stack<int> stack;

    ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, Edit) {
    Stack<std::string> stack;

    std::string value = "3", newValue = "5";
    std::ostringstream out, err;

    stack.push(value);
    std::string result = Stack<std::string>::editItem(stack, out, newValue, err);

    ASSERT_EQ(result, "Item edited successfully.\n");

}

TEST(StackTest, Display) {
    Stack<std::string> stack;

    std::string value = "3", newValue = "5";
    std::ostringstream out;
   
    stack.push(value);
    stack.push(newValue);
    std::string result = Stack<std::string>::displayItems(stack, out);
    ASSERT_EQ(result, "Items in the stack: 5 3 \n");

}

TEST(StackTest, Delete) {
    Stack<std::string> stack;

    std::string value = "3", newValue = "5";
    std::ostringstream out, err;

    stack.push(value);
    stack.push(newValue);
    std::string result = Stack<std::string>::deleteItem(stack, out, err);
    ASSERT_EQ(result, "Item deleted successfully.\n");
}

TEST(StackTest, SaveFromFile) {
    Stack<std::string> stack;

    std::ostringstream out, err;
    std::string value = "3", newValue = "5";
    stack.push(value);
    stack.push(newValue);
    std::string result = Stack<std::string>::saveToFile(stack, out, err);
    ASSERT_EQ(result, "Stack data saved to file.\n");

}

TEST(StackTest, LoadFromFile) {
    Stack<std::string> stack;

    std::ostringstream out, err;
    std::string value = "3", newValue = "5";
    stack.push(value);
    stack.push(newValue);
    std::string result = Stack<std::string>::loadFromFile(stack, out, err);
    ASSERT_EQ(result, "Stack data loaded from file.\n");
}


