
#ifndef ABSTRACT_BST_HPP
#define ABSTRACT_BST_HPP

template <typename KeyType, typename ValueType>
class AbstractBST
{
public:
    /* Determine if the tree is empty. */
    virtual bool empty() = 0;

    /** Search for key.
     If found is true, returns the value associated with that key.
     If found is false, returns a default constructed ValueType. */
    virtual ValueType search(const KeyType& key, bool& found) = 0;

    /* Insert value into the BST with unique key.
     thows std::logic_error if key is already in the tree. */
    virtual void insert(const KeyType& key, const ValueType& value) = 0;

    /* Remove value from the BST with key.
      Do nothing if there is no such key in the BST.
      throws std::logic_error if empty. */
    virtual void remove(const KeyType& key) = 0;
};

#endif // ABSTRACT_BST_HPP
