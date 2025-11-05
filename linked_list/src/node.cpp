#include "node.h"

Node* createNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = nullptr;

    return node;
}
