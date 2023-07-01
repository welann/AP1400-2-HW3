#include "bst.h"
#include <functional>
#include <ostream>

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
    bst.bfs([&os](BST::Node*& node) {
        os << node << "       => value:" << node->value << "        left:" << node->left << "      right:" << node->right << std::endl;
    });
    return os;
}

size_t BST::length()
{
    if (root == nullptr) {
        return 0;
    }
    std::queue<BST::Node*> que, ans;
    que.push(root);
    ans.push(root);

    while (!que.empty()) {
        auto temp = que.front();
        que.pop();

        if (temp->left != nullptr) {
            que.push(temp->left);
            ans.push(temp->left);
        }
        if (temp->right != nullptr) {
            que.push(temp->right);
            ans.push(temp->left);
        }
    }
    return ans.size();
}

bool BST::add_node(int value)
{
    bool ans = false;

    bfs([&ans, value, this](Node*& node) {
        if (ans == false) {
            if (node == nullptr) {
                node = new BST::Node(value, nullptr, nullptr);
                ans = true;
                return;
            }
            //这里用来保证左边的数字都小于根元素，右边的数字都大于根元素
            if (node->value < root->value && value > root->value) {
                return;
            }
            if (node->value > root->value && value < root->value) {
                return;
            }

            if (value > node->value && node->right == nullptr) {

                node->right = new BST::Node(value, nullptr, nullptr);
                ans = true;

            } else if (value < node->value && node->left == nullptr) {

                node->left = new BST::Node(value, nullptr, nullptr);

                ans = true;
            }

        } else {
            // std::cout << "double value" << std::endl;
            return;
        }
    });

    return ans;
}