//
//  BinarySearchTree.h
//  BinarySearchTree
//
//  Created by Ajayvir Dhaliwal on 11/29/17.
//  Copyright © 2017 Ajayvir Dhaliwal. All rights reserved.
//
#include <string>
#include <iostream>

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
namespace pic10b{
    class Tree {
    private:
        class node; // nested node class
        node *root; // the root of the tree
        void deleteTree(node*); // to recursively delete the tree
        void traverseInsert(node*); // to help with copying
        void swap(Tree& A, Tree& B); // swap two Trees
        int sz;
    public:
        class iterator; // nested iterator class
        Tree(); // default constructor for empty tree
        ~Tree(); // destructor
        Tree(const Tree&); // copy constructor
        Tree(Tree&&); // move constructor
        Tree& operator=(Tree); // assignment operators
        Tree::iterator find(const double& num);
        iterator begin() const; // iterator to begin position
        iterator end() const; // iterator to past-the-end position
        void insert(const  double&); // to add a value to the tree
        void erase(iterator); // to erase a value from the tree
        int size() const {return sz;};
    };
    class Tree::node {
        friend Tree; // tree member functions may search through nodes
        friend iterator; // to be able to advance by checking node values
    private:
        node(const double&); // constructor
        node *left, *right; // children
        ~node(){delete left, right;};
        double val; // data value stored
        node *parent;//parent
        bool insertNode(node* n); // member function for inserting node
    };
    class Tree::iterator {
        friend Tree; // to allow iterator modifications by Tree operations
    private:
        iterator(node*, const Tree*); // constructor
        node *curr; // current position
        const Tree *container; // holding container
    public:
        iterator &operator++(); // prefix ++
        iterator operator++(int); // postfix ++
        const double& operator*() const; // dereference operator
        const double* operator->() const { // arrow operator
            return & (curr->val);
        }
        bool operator==(const iterator& rhs) const; // comparisons
        bool operator!=(const iterator& rhs)const ;//nonmember function
    };
}// ending namespace brace



#endif /* BinarySearchTree_h */
