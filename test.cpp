#include "self_balancing_binary_search_tree.h"
#include <iostream>

int main() {
    self_balancing_binary_search_tree avl;

    // Insert values into the tree
    avl.insert(70);
    avl.insert(90);
    avl.insert(80);
    avl.insert(50);
    avl.insert(60);
    avl.insert(40);
    avl.insert(30);
    avl.insert(20);
    avl.insert(95);

    // Print the tree in different traversal orders
    std::cout << "Inorder traversal: ";
    avl.inorder();
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    avl.preorder();
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    avl.postorder();
    std::cout << std::endl;

    std::cout << "Level-order traversal: ";
    avl.level_order();
    std::cout << std::endl;

    std::cout << "BFS traversal: ";
    avl.bfs();
    std::cout << std::endl;

    std::cout << "DFS traversal: ";
    avl.dfs();
    std::cout << std::endl;
    
    // Test get_balancing_factor
    int balance_factor = avl.get_balancing_factor(avl.get_root());
    std::cout << "Balancing factor of the root node: " << balance_factor << std::endl;

    // Search for values in the tree
    int search_value = 30;
    if (avl.search(search_value)) {
        std::cout << search_value << " found in the tree." << std::endl;
    } else {
        std::cout << search_value << " not found in the tree." << std::endl;
    }

    // Get the minimum and maximum values in the tree
    int min_val = avl.get_min();
    int max_val = avl.get_max();
    int hight_val = avl.get_height();
    std::cout << "Minimum value in the tree: " << min_val << std::endl;
    std::cout << "Maximum value in the tree: " << max_val << std::endl;
    std::cout << "Hight value in the tree: " << hight_val << std::endl;

    // Delete a node from the tree
    int delete_value = 30;
    avl.delete_node(delete_value);
    std::cout << "Deleted " << delete_value << " from the tree." << std::endl;

    // Print the tree after deletion
    std::cout << "Inorder traversal after deletion: ";
    avl.inorder();
    std::cout << std::endl;

    // Check if the tree is balanced
    if (avl.balancing_factor()) {
        std::cout << "The tree is balanced." << std::endl;
    } else {
        std::cout << "The tree is not balanced." << std::endl;
    }

    return 0;
}
