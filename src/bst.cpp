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
    value=0;
    left=nullptr;
    right=nullptr;
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
    os << &n <<" value: " << n.value << " left: " << n.left << " right: " << n.right << std::endl;
    return os;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if (root == nullptr) {
        std::cout << "empty node" << std::endl;
        func(root);
        std::cout << "after empty node" << std::endl;
        std::cout << *get_root() << std::endl;

        return;
    }

    std::queue<BST::Node*> que;
    que.push(root);

    while (!que.empty()) {

        auto temp = que.front();
        que.pop();
        func(temp);

        std::cout << "bfs: " << std::endl;
        // auto a = temp->left;
        std::cout << temp->left << " ==left" << std::endl;
        std::cout << temp->right << " ==right" << std::endl;

        if (temp->left != nullptr) {
            std::cout << temp->left << "==new left" << std::endl;
            std::cout<<*temp->left << std::endl;
            que.push(temp->left);
        }
        if (temp->right != nullptr) {
            std::cout << temp->right << "==new right" << std::endl;
            std::cout<<*temp->right << std::endl;
            que.push(temp->right);
        }
        
    }
}

std::ostream& operator<<(std::ostream& os, BST& bst)
{
    // os << "0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0 " << std::endl;
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
        std::cout << temp->value << "===" << std::endl;

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

void asa(BST::Node*& node)
{
    int value = 10;
    std::cout << "1" << std::endl;
    if (node == nullptr) {
        BST::Node temp(value, nullptr, nullptr);
        node = &temp;
        std::cout << "consruction==" << std::endl;
        std::cout << *node << std::endl;
    }
    if (value > node->value && node->right == nullptr) {
        BST::Node temp(value, nullptr, nullptr);

        node->right = &temp;

        std::cout << "right==" << std::endl;
        std::cout << *node << std::endl;
        // return;
    } else if (value < node->value && node->left == nullptr) {
        BST::Node temp(value, nullptr, nullptr);

        node->left = &temp;

        std::cout << "left==" << std::endl;
        std::cout << *node << std::endl;
        // return;
    } else {
        std::cout << "double value" << std::endl;
    }
}

bool BST::add_node(int value)
{
    bool ans = false;

    bfs([ans, value](Node*& node) {
        // int value = 10;
        std::cout << "add node: " << std::endl;

        // if (node == nullptr || node->value == 0) {
        //     BST::Node* temp = new BST::Node(value, nullptr, nullptr);
        //     node = temp;
        //     std::cout << "consruction==" << std::endl;
        //     std::cout << *node << std::endl;
        //     return;
        // }
        if (value > node->value && node->right == nullptr) {
            BST::Node temp(value, nullptr, nullptr);

            node->right = &temp;

            std::cout << "right==" << std::endl;
            std::cout << *node << std::endl;
            std::cout << *node->right << std::endl;
            // return;
        } else if (value < node->value && node->left == nullptr) {
            BST::Node temp(value, nullptr, nullptr);

            node->left = &temp;

            std::cout << "left==" << std::endl;
            std::cout << *node << std::endl;
            // return;
        } else {
            std::cout << "double value" << std::endl;
        }
    });

    return ans;
}