#pragma once

struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
public:
    LinkedList() : m_head(nullptr) { }
    ~LinkedList();
    void pushFront(int value);
    void popFront();

private:
    Node* m_head{};
};
