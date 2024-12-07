#ifndef AVL
#define AVL

#include "node.h"

class self_balancing_binary_search_tree{
private:
    Node* root;

    bool search(Node* node, int val);
    void destroy_tree(Node* root);
    Node* copy_tree(Node* root);
    Node* get_min(Node* node);
    int get_max(Node* node);
    int get_height(Node* node);
    Node* insert(Node* node, int val);
    Node* delete_node(Node* node, int key);
    void preorder(Node* node) const;
    void inorder(Node* node) const;
    void postorder(Node* node) const;
    int balancing_factor(Node* node); 
    bool is_balanced(Node* node);
    Node* ll_rotation(Node* node);
    Node* rr_rotation(Node* node);
    void balancing_tree(Node*& node);

public:
    self_balancing_binary_search_tree();    
    self_balancing_binary_search_tree(int val); 

    self_balancing_binary_search_tree(const self_balancing_binary_search_tree& other);
    self_balancing_binary_search_tree& operator=(const self_balancing_binary_search_tree& other);

    self_balancing_binary_search_tree(self_balancing_binary_search_tree&& other);
    self_balancing_binary_search_tree& operator=(self_balancing_binary_search_tree&& other);

    ~self_balancing_binary_search_tree();

    Node* get_root();
    bool search(int val);
    int get_min();
    int get_max();
    int get_height();
    void insert(int val);   
    void delete_node(int key);
    void preorder() const;
    void inorder() const;
    void postorder() const;
    void level_order() const;
    bool balancing_factor();
    int get_balancing_factor(Node* node);

    void bfs();
    void dfs();
    // void print_root();  
};

#endif
