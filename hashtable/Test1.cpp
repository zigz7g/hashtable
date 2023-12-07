#include "gtest/gtest.h"
#include "main.cpp"

TEST(HashTableTest, InsertAndSearch) {
    HashTable<int> hashTable(100);
    hashTable.insert(42, 100);
    HashNode<int>* result = hashTable.search(42);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 100);
}

TEST(HashTableTest, Remove) {
    HashTable<std::string> hashTable(100);
    hashTable.insert(42, "TestValue");
    hashTable.remove(42);
    HashNode<std::string>* result = hashTable.search(42);
    EXPECT_EQ(result, nullptr);
}
