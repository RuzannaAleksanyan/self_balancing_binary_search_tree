#include "self_balancing_binary_search_tree.h"

#include <queue>
#include <iostream>

// Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree() 
            : root{nullptr} {
    balancing_tree(root);
}

// Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(int val) {
    root = new Node(val);
    balancing_tree(root);
}

// Copy Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(
            const self_balancing_binary_search_tree& other) {
    root = copy_tree(other.root);
}

// Copy assignment operator
self_balancing_binary_search_tree& self_balancing_binary_search_tree::operator=(
            const self_balancing_binary_search_tree& other) {
    if(this != &other) {
        destroy_tree(this->root);

        root = copy_tree(other.root);
    }

    return *this;
}

// Move Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(
            self_balancing_binary_search_tree&& other) {
    destroy_tree(this->root);
    root = other.root;
    other.root = nullptr;
}

// Move assignment operator
self_balancing_binary_search_tree& self_balancing_binary_search_tree::operator=(
            self_balancing_binary_search_tree&& other) {
    if(this != &other) {
        destroy_tree(this->root);
        root = other.root;
        other.root = nullptr;
    }

    return *this;
}

// Dtor
self_balancing_binary_search_tree::~self_balancing_binary_search_tree() {
    destroy_tree(root);
}

bool self_balancing_binary_search_tree::search(Node* node, int val) {
    if(!node) {
        return false;
    }

    if(node->value == val) {
        return true;
    } else if(node->value < val) {
        return search(node->right, val);
    } else {
        return search(node->left, val);
    }
}

bool self_balancing_binary_search_tree::search(int val) {
    if(!root) {
        return false;
    }

    return search(root, val);
}

void self_balancing_binary_search_tree::destroy_tree(Node* root) {
    if(root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        delete root;
    }
}

Node* self_balancing_binary_search_tree::copy_tree(Node* root) {
    if(!root) {
        return nullptr;
    }

    Node* new_node = new Node(root->value);
    new_node->left = copy_tree(root->left);
    new_node->right = copy_tree(root->right);

    return new_node;
}

Node* self_balancing_binary_search_tree::get_min(Node* node) {
    if(!node->left) {
        return node;
    }

    return get_min(node->left);
}

int self_balancing_binary_search_tree::get_min() {
    Node* tmp = get_min(root);
    return tmp->value;
}

int self_balancing_binary_search_tree::get_max(Node* node) {
    if(!node->right) {
        return node->value;
    }

    return get_max(node->right);
}

int self_balancing_binary_search_tree::get_max() {
    return get_max(root);
}

int self_balancing_binary_search_tree::get_height(Node* node) {
    if(!node) {
        return -1;
    }

    int left_hight = get_height(node->left);
    int right_hight = get_height(node->right);

    return (left_hight > right_hight) ? (left_hight + 1) : (right_hight + 1);
}

int self_balancing_binary_search_tree::get_height() {
    return get_height(root);
}

Node* self_balancing_binary_search_tree::insert(Node* node, int val) {
    if(!node) {
        Node* tmp = new Node(val);
        return tmp;
    }

    if(val < node->value) {
        node->left = insert(node->left, val);
    } else if(val > node->value) {
        node->right = insert(node->right, val);
    }

    return node;
}

void self_balancing_binary_search_tree::insert(int val) {
    root = insert(root, val);
    balancing_tree(root);
}

Node* self_balancing_binary_search_tree::delete_node(Node* node, int key) {
    if (node == nullptr) {
        return node; 
    }

    if (key < node->value) {
        node->left = delete_node(node->left, key);
    } else if (key > node->value) {
        node->right = delete_node(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = (node->left) ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                node->value = temp->value;
                node->left = node->right = nullptr;
            }

            delete temp;
        } else {
            Node* successor = get_min(node->right);

            node->value = successor->value;

            node->right = delete_node(node->right, successor->value);
        }
    }

    if (node == nullptr) {
        return node;
    }

    int balanceFactor = get_balancing_factor(node);

    // Left-Heavy
    if (balanceFactor > 1) {
        if (get_balancing_factor(node->left) >= 0) {
            node = rr_rotation(node);
        } else {
            node->left = ll_rotation(node->left);
            node = rr_rotation(node);
        }
    }

    // Right-Heavy
    if (balanceFactor < -1) {
        if (get_balancing_factor(node->right) <= 0) {
            node = ll_rotation(node);
        } else {
            node->right = rr_rotation(node->right);
            node = ll_rotation(node);
        }
    }

    return node;
}

void self_balancing_binary_search_tree::delete_node(int key) {
    root = delete_node(root, key);
    balancing_tree(root);
}

void self_balancing_binary_search_tree::preorder(Node* node) const {
    if(!node) {
        return;
    }

    std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

void self_balancing_binary_search_tree::preorder() const {
    preorder(root);
}

void self_balancing_binary_search_tree::inorder(Node* node) const {
    if(!node) {
        return;
    }

    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
}

void self_balancing_binary_search_tree::inorder() const {
    inorder(root);
}

void self_balancing_binary_search_tree::postorder(Node* node) const {
    if(!node) {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " ";
}

void self_balancing_binary_search_tree::postorder() const {
    postorder(root);
}

void self_balancing_binary_search_tree::level_order() const {
    if(!root) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* current = q.front();
        q.pop();

        std::cout << current->value << " ";

        if(current->left) {
            q.push(current->left);
        }

        if(current->right) {
            q.push(current->right);
        }
    }
}

int self_balancing_binary_search_tree::balancing_factor(Node* node) {
    if (!node) {
        return 0; 
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return left_height - right_height;
}

bool self_balancing_binary_search_tree::balancing_factor() {
    return balancing_factor(root);
}

bool self_balancing_binary_search_tree::is_balanced(Node* node) {
    if (node == nullptr) {
        return true;
    }

    int balance = balancing_factor(node);
    if (abs(balance) > 1) {
        return false; 
    }

    return is_balanced(node->left) && is_balanced(node->right);
}

void self_balancing_binary_search_tree::balancing_tree(Node* &node) {
    if (node) {
        balancing_tree(node->left);

        balancing_tree(node->right);

        int balanceFactor = get_balancing_factor(node);

        if (balanceFactor > 1) {
            if (get_balancing_factor(node->left) >= 0) {
                node = rr_rotation(node);
            } else {
                node->left = ll_rotation(node->left);
                node = rr_rotation(node);
            }
        }

        if (balanceFactor < -1) {
            if (get_balancing_factor(node->right) <= 0) {
                node = ll_rotation(node);
            } else {
                node->right = rr_rotation(node->right);
                node = ll_rotation(node);
            }
        }
    }
}

Node* self_balancing_binary_search_tree::get_root() {
    return root;
}

int self_balancing_binary_search_tree::get_balancing_factor(Node* node) {
    return get_height(node->left) - get_height(node->right);
}

Node* self_balancing_binary_search_tree::ll_rotation(Node* node) {
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

Node* self_balancing_binary_search_tree::rr_rotation(Node* node) {
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

void self_balancing_binary_search_tree::bfs() {
    level_order();
}

void self_balancing_binary_search_tree::dfs() {
    preorder();
}