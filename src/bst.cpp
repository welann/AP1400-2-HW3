#include "bst.h"
#include <functional>
#include <iomanip>
#include <ostream>
#include <vector>

BST::Node::Node(int value, Node* left, Node* right)
    : value(value)
    , left(left)
    , right(right)
{
}
BST::Node::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
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

bool operator>(int a, BST::Node b)
{
    return b < a;
}
bool operator>=(int a, BST::Node b)
{
    return b <= a;
}
bool operator<(int a, BST::Node b)
{
    return b > a;
}
bool operator<=(int a, BST::Node b)
{
    return b >= a;
}
bool operator==(int a, BST::Node b)
{
    return b == a;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& n)
{
    os << &n << " value: " << n.value << " left: " << n.left << " right: " << n.right << std::endl;
    return os;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if (root == nullptr) {
        func(root);
        return;
    }

    std::queue<BST::Node*> que;
    que.push(root);

    while (!que.empty()) {

        auto temp = que.front();
        que.pop();
        func(temp);

        if (temp->left != nullptr) {
            que.push(temp->left);
        }
        if (temp->right != nullptr) {
            que.push(temp->right);
        }
    }
}

std::ostream& operator<<(std::ostream& os, BST& bst)
{
    os << std::string(80, '*') << std::endl;
    bst.bfs([&os](BST::Node*& node) {
        os << std::setiosflags(std::ios::left);
        os << std::setw(20) << node << "=> value:";
        os << std::setw(10) << node->value << "left:";
        os << std::setw(20) << node->left << "right:";
        os << std::setw(20) << node->right << std::endl;
    });
    os << std::string(80, '*') << std::endl;
    return os;
}

size_t BST::length()
{
    std::vector<int> ans;
    bfs([&ans](BST::Node*& node) { ans.push_back(node->value); });
    return ans.size();
}

bool BST::add_node(int value)
{
    bool ans = false;
    bool repeated = false;
    Node* pnode = root;

    while (!ans && !repeated) {
        if (pnode == nullptr) {
            root = new BST::Node(value, nullptr, nullptr);
            ans = true;
            break;
        }
        if (value < pnode->value) {
            if (pnode->left == nullptr) {
                pnode->left = new Node(value);
                ans = true;
            } else {
                pnode = pnode->left;
            }
        } else if (value > pnode->value) {
            if (pnode->right == nullptr) {
                pnode->right = new Node(value);
                ans = true;
            } else {
                pnode = pnode->right;
            }
        } else {
            repeated = true;
        }
    }

    return ans && !repeated;
}

BST::Node** BST::find_node(int value)
{
    static Node* result;
    bool find = false;
    bfs([value, &find](Node*& node) {
        if (node->value == value) {
            result = node;
            find = true;
        }
    });
    if (find) {
        return &result;

    } else {
        return nullptr;
    }
}

BST::Node** BST::find_parrent(int value)
{
    static Node* result;
    bool find = false;

    bfs([value, &find](Node*& node) {
        if (node->left != nullptr && node->left->value == value) {
            result = node;
            find = true;
        }
        if (node->right != nullptr && node->right->value == value) {
            result = node;
            find = true;
        }
    });
    if (find) {
        return &result;

    } else {
        return nullptr;
    }
}
BST::Node** BST::find_successor(int value)
{
    auto pnode = find_node(value);
    if (pnode == nullptr) {
        return nullptr;
    }
    if ((*pnode)->left == nullptr) {
        return nullptr;
    }

    *pnode = (*pnode)->left;
    while ((*pnode)->right != nullptr) {
        (*pnode) = (*pnode)->right;
    }
    return pnode;
}

bool BST::delete_node(int value)
{
    auto pnode = find_node(value);
    if (pnode == nullptr) {
        return false;
    }
    auto parent = find_parrent(value);

    if((*pnode)->left==nullptr){
        (*parent)->right = (*pnode)->right;
        return true;
    }
    if((*pnode)->right==nullptr){
        (*parent)->left = (*pnode)->left;
        return true;
    }
    if (parent == nullptr) {
        return false;
    }

    auto succ = find_successor(value);
    if (succ == nullptr) {
        if ((*parent)->right->value == value) {
            (*parent)->right = nullptr;

        } else {
            (*parent)->left = nullptr;
        }
        return true;
    }

    auto succ_parent = find_parrent((*succ)->value);
    (*pnode)->value = (*succ)->value;

    if ((*succ)->left != nullptr) {
        (*succ_parent)->right = (*succ)->left;
    }

    return true;
}
