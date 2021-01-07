#ifndef TREAP_BST_HPP
#define TREAP_BST_HPP

#include <random>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "abstract_bst.hpp"

template <typename KeyType, typename ValueType>
class TreapBST : public AbstractBST<KeyType, ValueType>
{
public:
    /** Default contructor. */
    TreapBST();

    /** Copy constructor. */
    TreapBST(const TreapBST &x);

    /** Copy-assignment. */
    TreapBST &operator=(TreapBST x);

    /** Destructor. */
    ~TreapBST();

    bool empty();

    ValueType search(const KeyType &key, bool &found);

    void insert(const KeyType &key, const ValueType &value);

    void remove(const KeyType &key);

    /** Get the height of the treap. */
    std::size_t height();

private:
    /* Random number generator. */
    std::mt19937 rndgen;
    ValueType notfound;
    /* Node struct with key, data, random priority, and parent, left child, and right child pointers. */
    template <typename K, typename V>
    struct Node
    {
        K key;
        V data;
        std::mt19937::result_type priority;
        Node* parent;
        Node* childl; // Left Child 
        Node* childr; // Right Child 
        std::mt19937 rnd;

        Node(const K& k, const V& d, Node* p = nullptr) //, Node* p = nullptr
        : key(k)
        , data(d)
        , parent(p)
        , childl(nullptr)
        , childr(nullptr)
        {
            
            priority = rnd();

        }
    };
    Node<KeyType, ValueType>* root;
    // You may add private member variables/methods as needed.
    void rotateLeft(Node<KeyType, ValueType>* & x); // Method to rotate left
    void rotateRight(Node<KeyType, ValueType>* & x); // Method to rotate right
    void insert(const KeyType& K, const ValueType& V, Node<KeyType, ValueType>* &node); // Method to reccursively insert a node 
    void remove(const KeyType& K, Node<KeyType, ValueType>*& node); // method to reccursively remove a node
    ValueType search(const KeyType& K, bool& found, Node<KeyType, ValueType>*& node); // method to reccursively search a node
    int findHeight(Node<KeyType, ValueType>*& node); // Recursive method to find the height of the treap 
    void clear(Node<KeyType, ValueType>*& node); // Recursive method to clear the treap and deallocate memory 
    void copy( Node<KeyType, ValueType>* x); // Method to copy a treap
};

#include "treap_bst.txx"

#endif // TREAP_BST_HPP
