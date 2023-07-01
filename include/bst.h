#ifndef BST_H
#define BST_H
#include <functional>
#include <iostream>
#include <queue>

class BST {
public:
    class Node {
    public:
        Node(int value, Node* left=nullptr, Node* right=nullptr);
        Node();
        Node(const Node& node);

        bool operator<(int a) const;
        bool operator<=(int a) const;
        bool operator>(int a) const;
        bool operator>=(int a) const;
        bool operator==(int a) const;

        friend std::ostream& operator<<(std::ostream& os, const Node& n);

        int value;
        Node* left;
        Node* right;
    };

    BST()
    {
        root = new Node();
    }

    BST(BST& bst)
    {
        root = bst.root;
    }

    BST(BST&& bst)
    {
        root=std::move(bst.root);
    }

    ~BST()
    {
        std::vector<Node*> nodes;
        bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
        for (auto& node : nodes)
            delete node;
    }

    void operator++();
    void operator=(BST &bts);
    void operator=(BST &&bts);

    friend std::ostream& operator<<(std::ostream& os,  BST& bst);

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};

bool operator>(int a, BST::Node b);
bool operator>=(int a, BST::Node b);
bool operator<(int a, BST::Node b);
bool operator<=(int a, BST::Node b);
bool operator==(int a, BST::Node b);

#endif // BST_H