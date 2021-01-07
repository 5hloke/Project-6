#include "treap_bst.hpp"

#include <algorithm>
#include <stack>
#include <stdexcept>

// Default Constructor - Creates an empty treap
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() : root(nullptr)
{
	std::random_device rd;
	rndgen.seed(rd());
}

// Parameterized constructor - copies the passed treap as the parameter
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST& x) {
	
	if (x.root != nullptr) { // if the said treap is not empty
		root = nullptr; // set root to nullptr to start with
		copy(x.root); // copy the treap x 
	}
	else {
		root = nullptr; // if the said treap is empty then set root to nullptr
	}
}

// Copy assignment operator similar to the parameterized constructor 
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>& TreapBST<KeyType, ValueType>:: operator=(TreapBST x) {
	//std::swap(this, x);
	if (root != nullptr){ // if the current treap is not empty 
		clear(this->root); // clear the treap 
		copy(x.root); //  copy trap x to this->treap 
	}
	else {
		root = nullptr; // else set troot to nullptr to start with 
		copy(x.root); // copy treap x to this-> trap and then return *this
	}
	return *this; 
}

// Treap Destructor
template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType> :: ~TreapBST() {
	clear(root); // clear the treap and deallocate memory 
}

template <typename KeyType, typename ValueType>

bool TreapBST<KeyType, ValueType> ::empty() {

	return root == nullptr; // if the root == nullptr then the treap is empty and hence return true 
}

// Method to search for a given key and return the value in that particular node
template <typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType& key, bool& found) {
	return search(key, found, root); // Recursive method called to search for the key and return the data value
}

// Inserts a node into the treap with given key and data value
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType> ::insert(const KeyType& key, const ValueType& value) {
	insert(key, value, root); // Recursive method called to insert the node 
}

// Method to remove a node with a specific key 
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType> ::remove(const KeyType& key) {
	remove(key, root); // Recursive method called to remove the node with the specific key 
}

// Returns the height of the current treap
template <typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType> ::height() {
	return findHeight(root); // Recursive method to return the height of the urrent treap is called
}

// Method to rotate the tree right about a given node x
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType> ::rotateRight(Node<KeyType, ValueType>*& x) {
	Node<KeyType, ValueType>* node = x->childl; // get the left child of the node and and set it to new node pointer "node"
	x->childl = node->childr; // left child of x is equal to the right child of "node"
	node->childr = x; // Right child of "node" is equal to 
	x = node; // and  x is eaual to the node
}

// Method to rotate the tree left about a given node x
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType> ::rotateLeft(Node<KeyType, ValueType>*& x) {
	Node<KeyType, ValueType>* node = x->childr;// get the right child of the node and and set it to new node pointer "node"
	x->childr = node->childl; // right child of x is equal to he left child of "node"
	node->childl = x; // left child of node is equal to x 
	x = node; // x is equal to node 

}

// Recursive method to insert a new node
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType> ::insert(const KeyType& K, const ValueType& V, Node<KeyType, ValueType>*& node) {
	if (node == nullptr) { // if the current node is a terminal node then add a new node
		node = new Node<KeyType, ValueType>(K, V);
	}
	else if (K == node->key) { // if the key is being reinserted throw an error 
		throw std::logic_error("Same Key is being reinserted");
	}
	else if (K < node->key) { // if the key being entered is less than the key of the node 
		insert(K, V, node->childl); // then call insert and add the node as the left child
		if (node->childl->priority > node->priority) { // check if the priority of left child of node is higher than the priority of node
			rotateRight(node); // rotate the treap right about node 
		}
	}
	else if (K > node->key) { // if the key being enteres is greater than the key of the node 
		insert(K, V, node->childr); // then call insert and add the node as the right child
		if (node->childr->priority > node->priority) {// check if the priority of right child of node is higher than the priority of node
			rotateLeft(node); // rotate the treap left about the node 
		}
	}

}

// Recursive method to remove a node with a given key value 
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType& K, Node<KeyType, ValueType>*& node) {
	if (node != nullptr) { // if the given node is not the terminal node 
		if (K < node->key) { // check if the key we are looking for is less than the key of the node 
			remove(K, node->childl); // look in the left subtree
		}
		else if (K > node->key) { // check if the key we are looking for is greater than the key of the node 
			remove(K, node->childr); // look in the right subtree
		}
		else {
			if (node->childl == nullptr && node->childr == nullptr) { // if the node is a terminal node and has no children 
				delete node; // delete the node
				node = nullptr;
			}
			else if (node->childl == nullptr) { // if the node to be delted has a left child only
				Node<KeyType, ValueType>* temp = node; // set node to a temp pointer
				node = node->childr; // set the right child of the node equal to the node
				delete temp; // delete temp 
				//temp = nullptr;
			}
			else if (node->childr == nullptr) { // if the node to be dleted has a right child only 
				Node<KeyType, ValueType>* temp = node;// set node to a temp pointer
				node = node->childl; // set the left child of the node equal to the node
				delete temp;
				//temp = nullptr;
			}
			else
			{
				if (node->childl->priority < node->childr->priority) // if the node to be deleted has both children check which has the higher priority 
				{
					rotateLeft(node); // if right child has higher priority rotate left 
					remove(K, node->childl); // then look in the left subtree
				}
				else
				{
					rotateRight(node); // else reotate right 
					remove(K, node->childr); // then look in the right subtree
				}
			}
		}
	}
	else {
		throw std::logic_error("Removing from an empty treap"); // if the treap is empty throw a logic error
	}
}

//Recursive method to look for a given key in the treap 
template <typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType> ::search(const KeyType& K, bool& found, Node<KeyType, ValueType>*& node) {
	if (node == nullptr) { // if at the terminal node and the key has not been found
		found = false; // found is set to false
		return notfound; // a default ValueType has been returned 

	}
	if (node->key == K) { // if the key is found
		found = true; // found is set to true
		return node->data; // the data value in the node is returned
	}
	else {
		if (K < node->key) { // If the key we are looking for is less than the Key of the node
			return search(K, found, node->childl); // look in the left subtree
		}
		else {
			return search(K, found, node->childr); // else look in the right subtree
		}
	}
}

// Recursive method to find the height of the treap
template <typename KeyType, typename ValueType>
int TreapBST<KeyType, ValueType> ::findHeight(Node<KeyType, ValueType>*& node) {
	if (node == nullptr) { // if at the terminal node 
		return 0; // return 0 
	}
	else {
		int leftHeight = findHeight(node->childl); // find height of the left subtree of the node
		int rightHeight = findHeight(node->childr); // find height of the right subtree of the node
		if (leftHeight > rightHeight) { // check which height is greater
			return leftHeight + 1; // then return the greater height + 1
		}
		else {
			return rightHeight + 1;
		}

	}
}

// Recursive method to clear the entire treap
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::clear(Node<KeyType, ValueType>*& node) {
	if (node != nullptr) { // if not at the terminal node 
		clear(node->childl); // clear the left subtree of the node
		clear(node->childr); // clear the right subtree of the node 
		delete node; // delete the node 
	}
	node = nullptr;// set node to nullptr
}

// Recursive method to copy the given treap 
template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::copy(Node<KeyType, ValueType>* x) {
	
	if (x != nullptr) {
		insert(x->key, x->data); // insert the current node
		copy(x->childl); // copy the left subtree of the node
		copy(x->childr); // copy the right subtree of the node 
	}
	
}
