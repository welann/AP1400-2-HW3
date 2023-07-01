#include "bst.h"
#include <ostream>

BST::Node::Node(int value, Node* left, Node* right)
    : value(value)
    , left(left)
    , right(right)
{
}
BST::Node::Node()
    : value(0)
    , left(nullptr)
    , right(nullptr)
{
}
BST::Node::Node(const Node& node)
{
    value = node.value;
    left = node.left;
    right = node.right;
}

bool BST::Node::operator<(int a) const
{
    return value < a;
}
bool BST::Node::operator<=(int a) const
{
    return value <= a;
}
bool BST::Node::operator>=(int a) const
{
    return value >= a;
}
bool BST::Node::operator>(int a) const
{
    return value > a;
}
bool BST::Node::operator==(int a) const
{
    return value == a;
}

std::ostream& operator<<(std::ostream& os, const BST::Node* n)
{
    os<<"value: "<<n->value<<" left: "<<n->left<<" right: "<<n->right<<std::endl;
    return os;
}
