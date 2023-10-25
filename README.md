# Self-Balancing Binary Search Tree (AVL Tree) Implementation
This project provides a C++ implementation of a self-balancing binary search tree, specifically an AVL tree. AVL trees are a type of binary search tree that automatically maintains balance, ensuring efficient search, insert, and delete operations.
## Table of Contents

- [Features](#features)
- [Usage](#usage)
- [API](#api)
- [Implementation Details](#Implementation_Details)
- [Testing](#Testing)

## Features

- Implementation of a self-balancing binary search tree (AVL tree).
- Supports searching, insertion, and deletion of elements.
- Provides tree traversal methods (preorder, inorder, postorder, and level order).
- Performs single and double rotations to maintain tree balance.
- Checks and reports the balancing factor of the tree.

# Usage
To use this AVL implementation in your C++ project, follow these steps:
- Include the necessary header files in your code.
- Create an instance of the self_balancing_binary_search_tree class, and perform various operations such as insertion, deletion, and searching in the tree.
- Run your program to interact with the AVL.

# API
Class: self_balancing_binary_search_tree
Constructors
- self_balancing_binary_search_tree(): Create an empty AVL tree.
- self_balancing_binary_search_tree(int val): Create an AVL tree with a root node containing the given value.
Public Methods
- bool search(int val): Search for a value in the tree.
- void insert(int val): Insert a value into the tree.
- void delete_node(int key): Delete a node with the given key.
- int get_min(): Get the minimum value in the tree.
- int get_max(): Get the maximum value in the tree.
- int get_height(): Get the height of the tree.
- void preorder(): Perform a preorder traversal of the tree.
- void inorder(): Perform an inorder traversal of the tree.
- void postorder(): Perform a postorder traversal of the tree.
- void level_order(): Perform a level-order traversal of the tree.
- bool balancing_factor(): Check if the tree is balanced.
- void ll_rotation(): Perform a left-left (LL) rotation.
- void rr_rotation(): Perform a right-right (RR) rotation.
- int get_balancing_factor(Node* node): Get the balancing factor of a node.
- void print_root(): Print the value of the root node.

# Implementation_Details
- node.hpp: Defines the node template struct, which represents a node in the binary search tree. It has left and right child pointers and a value of type T.
- self_balancing_binary_search_tree.h: Contains the self_balancing_binary_search_tree class definition, which represents the AVL. It includes member functions for various tree operations such as insertion, deletion, traversal (inorder, preorder, postorder, and level-order), and finding the minimum, maximum, and height of the tree.
- self_balancing_binary_search_tree.cpp: Provides the implementation for the member functions of the self_balancing_binary_search_tree class.

# Testing
The test.cpp file demonstrates how to use the self_balancing_binary_search_tree class by creating a AVL, performing various operations, and printing the tree in different traversal orders.
