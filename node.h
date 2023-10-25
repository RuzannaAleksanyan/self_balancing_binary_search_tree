#ifndef NODE
#define NODE

struct Node {
    Node(int& val) 
            : left{nullptr}, right{nullptr}, value{val}
    {
    }

    Node* left;
    Node* right;
    int value; 
};

#endif
