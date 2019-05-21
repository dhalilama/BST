//
//  BinarySearchTreeImplementations.cpp
//  BinarySearchTree
//
//  Created by Ajayvir Dhaliwal on 11/29/17.
//  Copyright © 2017 Ajayvir Dhaliwal. All rights reserved.
//

#include <stdio.h>
#include "BinarySearchTree.h"
using namespace pic10b;
/* default constructor for empty tree*/
Tree::Tree(): root(nullptr), sz(0)
{
    
}
/* destructor */
Tree::~Tree()
{
   deleteTree(root);//invokes deleteTree recursive funciton on root
}
/* copy constructor */
Tree::Tree(const Tree& rhs) : root(nullptr), sz(rhs.sz) {
    traverseInsert(rhs.root); // calls a recursive function on nodes to copy
}
/*move constructor */
Tree::Tree(Tree&& rhs) : root(rhs.root), sz(rhs.sz) {
    rhs.root = nullptr;
}
/* assignment operator */
Tree& Tree::operator=(Tree that) {
    swap(*this, that);
    return *this;
}
/* node constructor */
Tree::node::node(const double& value): left(nullptr), right(nullptr),parent(nullptr), val(value)
{
    
}
/*a find member function returning the iterator to the node with a given value
 if found and otherwise returning the past-the-end iterator.*/
Tree::iterator Tree::find(const double& num)
{
    node* nRoot = root;
    if (nRoot->val == num) {//if the value of the node equals the input parameter
        return iterator(nRoot, this);
    }
    while (nRoot) {// while nRoot is not null
        if (nRoot->val > num) {
            if (nRoot->left == nullptr) { // if left child is null
                return end();
            } else {
                nRoot = nRoot->left;
            }
        }
        else {
            if (nRoot->right == nullptr) {// if right child is null
                return end();
            } else {
                nRoot = nRoot->right;
            }
        }
    }
    return iterator(nRoot, this);   //return current iterator
}
/* swap function for swapping two trees, used in assignment operator */
void Tree::swap(Tree& A, Tree& B)
{
    std::swap(A.root,B.root);   //swap roots
    std::swap(A.sz,B.sz);   //swap sizes
}
/* returns iterator to the first node */
Tree::iterator Tree::begin() const { // return type requires scope
    if (root == nullptr) { // if root is null then tree empty
        return iterator(nullptr, this); // return iterator that is null
    }
    node *n = root; // start at the root
    while (n->left != nullptr) { // while we can still go left (to lower value)
        n = n->left; // go left
    }
    return iterator(n, this); // return iterator for node of smallest value
}
/* end iterator one “past the end” and should store null */
Tree::iterator Tree::end() const{
    return iterator(nullptr, this);
}
/* returns true if insertNode is succesful, returns false if insertNode is unsuccesful */
bool Tree::node::insertNode(node* newNode){
    if (val < newNode->val) { //sorts node to the right if it is less than current node
        if (right) {
            right->insertNode(newNode); //recurse on right child
        } else {
            right = newNode;
        }
    } else if (val > newNode->val) {    //sorts  val to left if it is greater than current node
        if (left) {
            left->insertNode(newNode);    //recurse implementation on left child
        } else {
            left = newNode;
        }
    } else {
        return false;
    }
    newNode->parent = this;
    return true;
}
/* insert member function accepting a double value and adding it to the
 tree */
void Tree::insert(const double& val) {
    if (!root) { // if the root is empty
        root = new node(val); // make a new node and set this to be root
    }
    else{ // otherwise
        node *n = new node(val); // create a new node
        bool test= root->insertNode(n);
        if(test==true)++sz;
        // and recursively pass it node to node until in place
        root->insertNode(n);
    }
    
}
/*  member function accepting an iterator and removing the node
 managed by the iterator from the tree */
void Tree::erase(iterator itr)
{
    node* curr = itr.curr; //declares variable curr of type node* and assigns it to the input paramter iterator's current node.
    if (curr == nullptr) {// if curr is null
        return;
    }
    
   
    if ((curr->left == nullptr) && (curr->right == nullptr)) {//if both children are null
        if (curr == curr->parent->left) {
            curr->parent->left = nullptr;
        } else {
            curr->parent->right = nullptr;
        }
        delete curr;
    }
  
    else if ((curr->left == nullptr) || (curr->right == nullptr)) {// if one child is null
        if (curr->left) {
            curr->left->parent = curr->parent;
            curr->parent->left = curr->left;
        } else {
            curr->right->parent = curr->parent;
            curr->parent->right = curr->right;
        }
        delete curr;
    }

    else {// neither child is null
        node* temp = curr->right;
        while (temp->left) {
            temp = temp->left;
        }
        curr->val = temp->val;
        if (temp->left) {
            temp->left->parent = temp->parent;
            temp->parent->left = temp->left;
            delete temp;
        } else if (temp->right) {
            temp->right->parent = temp->parent;
            temp->parent->left = temp->right;
            delete temp;
        } else {
            delete temp;
        }
    }
    --sz; //decreaes size
}
/* deletes every node in tree recursively */
void Tree::deleteTree(node* n)
{
    if (n->left) {
        deleteTree(n->left);
    }
    delete n;
    if (n->right) {
        deleteTree(n->right);
    }
}
/* helper member function that recursively helps break down binary search tree so insert function and copy constructor can be implemented */
void Tree::traverseInsert(node* n)
{
    if (n->left) {
        traverseInsert(n->left);    //recursive call on left child
    }
    insert(n->val);
    if (n->right) {
        traverseInsert(n->right);   //recursive call on right child
    }
}

Tree::iterator::iterator(node* n, const Tree* A) : curr(n), container(A)//iterator constructor
{
    
}
/*******
 operators 
 ******/
/* prefix increment operator */
Tree::iterator& Tree::iterator::operator++()
{
    if (curr == nullptr) {
        curr = container->root;
        if (curr == nullptr) {
            throw std::out_of_range("Tree empty");
        }
        
    } else if (curr->right) {
        curr = curr->right;
        while (curr->left) {
            curr = curr->left;
        }
    } else if (curr->right == nullptr) {
        node* p = curr->parent;
        while (p && curr == p->right) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}
/* postfix increment operator */
Tree::iterator Tree::iterator::operator++(int)
{
    iterator copy(*this);   //make a copy of the current iterator
    ++(*this);
    return copy;    //return the copy
}

/* dereference operator */
const double& Tree::iterator::operator*() const
{
    return this->curr->val;
}

// comparison operatpr

//comparison operator for equality
bool Tree::iterator::operator==(const iterator& rhs) const
{
    return ((curr == rhs.curr) && (container == rhs.container));//checks for current nodes and current containers and see if they are equal, returns true if they are
}

bool Tree::iterator::operator!=(const Tree::iterator& rhs) const
{
    return !(*this == rhs); //return true of this iterator and rhs are not equal
}
