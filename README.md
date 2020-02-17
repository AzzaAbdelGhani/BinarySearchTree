# Advanced Programming Exam

A binary search tree implementation, written in c++14 for the Advanced Programming Exam of DSSC Course 2019/20


In this project we implemented a templated Binary Search Tree (BST) in C++ and we benchmarked it against the `std::map` implementation. In the directory there are two main files: one to actually use our BST, and the other to test the performance. In order compile and run them, we wrote a MakeFile thanks to which you can run the commands `make` and `./bst`, for the tree, and `make benchmark` and `./benchmark` for the testing.

### Concepts
In our implementation we have three templated classes: one for the tree, one for the node and one for the iterator. Here a short description of them:

##### Binary Search Tree
```c++
template <typename k, typename v, typename c = std::less<k> >
class bst{
    using node_type = node<std::pair<const k,v> >;
    c op;
    std::unique_ptr<node_type> head;
}
```
This class represents the concept of BST and it is templated on the key, on the value and on the comparison operator. The class has just a pointer to the head of the tree and a compare operator (that is `std::less` by default).

##### Node
```c++
template <typename T>
class node {
    T value;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    node* parent;
}
```
This class represents the concept of node, in which we have the value of it and the pointers to the childern and the parent. The only template that we have is on the value.

##### Iterator
```c++
template <typename node_type, typename T>
class _iterator {
    node_type* current;
}
```
This last class allows us to iterate through the BST without extern any implemetation detail about his structure. The iterator is templated on the type of the node and on the value of it and it saves only a pointer to the current node.

### Important choices
There were important choices that we had to take at the beginning of the implementation:

- First of all we decided to separate all the classes. This because they are templated and we want to generalize them as much as possible. For example, the BST class has templates on k,v and c, but we want the concept of node to be templated on just its value, that could be of whatever type, and we do not care about details concerning our specific implemenation of the BST. This would allow us to use the node class for another type of tree. Another reason it is the fact that we are avoiding to write too many templates in every implementation of the functions outside the classes.

- Another important choice was deciding the type of the pointers involved. In our opinion, the two children and the head could have been either unique or shared pointers, because in that way we do not have to worry about deleting them. We will never have two pointers to the same child or to the same head, therefore we chose unique. Instead, we decided to use a raw pointer to the parent, because it will be pointed from at least two other pointers. We could use a shared-pointer too, but we would have had problems when deleting nodes.




### Functions

##### Insert

```c++
std::pair<iterator, bool> insert(const pair_type& x);
std::pair<iterator, bool> insert(pair_type&& x);
```
They are used to insert a new node. The function returns a pair of an iterator (pointing to the node) and a bool. The bool is true if a new node has been allocated, false otherwise (i.e., the key was already present in the tree). 


##### Emplace

```c++
template< class... Types >
std::pair<iterator,bool> emplace(Types&&... args);
```
Inserts a new element into the container constructed in-place with the given args, By invoking the insert() function with argument of pair type.

##### Clear

```c++
void clear();
```
Clear the content of the tree by `reset` the head pointer.

##### Begin

```c++
iterator begin();
const_iterator begin() const;
const_iterator cbegin() const;
```

Checks if the head is a null pointer (the tree is empty), return an iterator pointing to null. Otherwise, it returns an iterator to the left-most node of the head . 

##### End

```c++
iterator end();
const_iterator end() const;
const_iterator cend() const;
```

Return an iterator to one-past the last element.

##### Find

```c++
iterator find(const key_type& x);
const_iterator find(const key_type& x) const;
```
Find a given key by traversing the tree: if the key is larger than the current node's key, it will seek on the right, otherwise on left. If the key is already present, it returns an iterator to the proper node, `end()` otherwise.

##### Balance

```c++
void balance();
```

Balance the tree by copying the values of the tree into a vector, the copy process will be in ascending order, in other words, start from the begin of the tree to the end. Then, clear the tree, and restart building it by recursively dividing the vector into two halves and inserting the middle value of the vector. 

##### Subscripting operator

```c++
value_type& operator[](const key_type& x);
value_type& operator[](key_type&& x);
```

Returns a reference to the value that is mapped to a key equivalent to `x` by calling find() function, and performing an insertion with a default value if such key does not already exist.

##### Put-to operator

```c++
friend
std::ostream& operator<<(std::ostream& os, const bst& x);
```
Here, we return a reference to ostream object that contains all values of the nodes from the begin() of the tree to the end().

##### Copy and move

The copy semantics perform a deep-copy: for copy constructor copy the head of the right side tree to the head of left side tree, and for copy assignment, we clear the tree and then copy the head of the left side tree.
Meanwhile, for the move constructor and assignment, we've just put them equal to the `default`.

##### Erase

```c++
void erase(const key_type& x);
```

Removes the element (if one exists) with the key equivalent to the given key. it will check the state of the node: it could be a full node, so having right and left children, or it could have just one child either on right or left, a leaf otherwise.
