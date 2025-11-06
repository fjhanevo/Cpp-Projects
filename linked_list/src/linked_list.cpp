#include "linked_list.h"

LinkedList::~LinkedList()
{
    Node *tempNode{nullptr};
    // Loop through all nodes and delete them
    while (m_head != nullptr)
    {
        tempNode = m_head;
        m_head = m_head->next;
        delete tempNode;
    }
}

void LinkedList::pushFront(int value)
{
    // Allocate memory on the heap for a new Node object
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = m_head;
}

void LinkedList::popFront()
{
    // check if empty
    if (m_head == nullptr)
        return;

    Node *tempNode { m_head };

    // move head to the next node
    m_head = m_head->next;

    // delete the old head node
    delete tempNode;
}
