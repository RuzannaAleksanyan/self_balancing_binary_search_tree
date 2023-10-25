#include "self_balancing_binary_search_tree.h"

#include <queue>
#include <iostream>

// Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree() 
            : root{nullptr}
{
    balancing_tree(root);
}

// Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(int val) {
    root = new Node(val);
    balancing_tree(root);
}

// Copy Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(const self_balancing_binary_search_tree& other) {
    root = copy_tree(other.root);
}

// Copy assignment operator
self_balancing_binary_search_tree& self_balancing_binary_search_tree::operator=(const self_balancing_binary_search_tree& other) {
    if(this != &other) {
        destroy_tree(other.root);

        root = copy_tree(other.root);
    }

    return *this;
}

// Move Ctor
self_balancing_binary_search_tree::self_balancing_binary_search_tree(self_balancing_binary_search_tree&& other) {
    destroy_tree(root);
    root = other.root;
    other.root = nullptr;
}

// Move assignment operator
self_balancing_binary_search_tree& self_balancing_binary_search_tree::operator=(self_balancing_binary_search_tree&& other) {
    if(this != &other) {
        destroy_tree(root);
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
        return node; // Node not found
    }

    if (key < node->value) {
        node->left = delete_node(node->left, key);
    } else if (key > node->value) {
        node->right = delete_node(node->right, key);
    } else {
        // Node with the key found, perform deletion
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = (node->left) ? node->left : node->right;

            // If the node has one child or no child
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                // Node has one child, so copy the child's data to this node
                node->value = temp->value;
                node->left = node->right = nullptr;
            }

            delete temp;
        } else {
            // Node with two children: Get the in-order successor (smallest in the right subtree)
            Node* successor = get_min(node->right);

            // Copy the in-order successor's data to this node
            node->value = successor->value;

            // Delete the in-order successor
            node->right = delete_node(node->right, successor->value);
        }
    }

    // If the tree is empty after deletion, return
    if (node == nullptr) {
        return node;
    }

    // Rebalance the tree
    int balanceFactor = get_balancing_factor(node);

    // Left-Heavy
    if (balanceFactor > 1) {
        if (get_balancing_factor(node->left) >= 0) {
            // Left-Left imbalance, perform a right rotation (RR)
            node = rr_rotation(node);
        } else {
            // Left-Right imbalance, perform a left rotation on the left child
            // followed by a right rotation on the current node (LR)
            node->left = ll_rotation(node->left);
            node = rr_rotation(node);
        }
    }

    // Right-Heavy
    if (balanceFactor < -1) {
        if (get_balancing_factor(node->right) <= 0) {
            // Right-Right imbalance, perform a left rotation (LL)
            node = ll_rotation(node);
        } else {
            // Right-Left imbalance, perform a right rotation on the right child
            // followed by a left rotation on the current node (RL)
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
    return is_balanced(root);
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
        // First, balance the left subtree
        balancing_tree(node->left);

        // Then, balance the right subtree
        balancing_tree(node->right);

        // Calculate the balancing factor for the current node
        int balanceFactor = get_balancing_factor(node);

        // If the balance factor is greater than 1, it means the tree is left-heavy
        if (balanceFactor > 1) {
            // Determine if it's a left-left or left-right imbalance
            if (get_balancing_factor(node->left) >= 0) {
                // Left-Left imbalance, perform a right rotation (RR)
                node = rr_rotation(node);
            } else {
                // Left-Right imbalance, perform a left rotation on the left child
                // followed by a right rotation on the current node (LR)
                node->left = ll_rotation(node->left);
                node = rr_rotation(node);
            }
        }

        // If the balance factor is less than -1, it means the tree is right-heavy
        if (balanceFactor < -1) {
            // Determine if it's a right-right or right-left imbalance
            if (get_balancing_factor(node->right) <= 0) {
                // Right-Right imbalance, perform a left rotation (LL)
                node = ll_rotation(node);
            } else {
                // Right-Left imbalance, perform a right rotation on the right child
                // followed by a left rotation on the current node (RL)
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

// void self_balancing_binary_search_tree::print_root() {
//     std::cout << root->value << " ";
// }
