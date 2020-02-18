# Advanced Programming Exam

This is an implementation of a templated Binary Search Tree (BST) in C++14, benchmarked against the `std::map` implementation. In the repository you can find the directory include with the header file containing the definition of the BST (and also its implementation, see the section `Implementation choices`). You can also find two source files that can run the BST. In the `main.cc` there is a set of tests that covers all the possible cases of the BST functions. In the `benchmark.cc` you can find a comparison in between this implementation of BST and the one provided by the std library (`std::map`).

In order compile and run them, there is a Makefile in the directory which allows you to compile both files.
To compile and run the `main.cc` run `make` and `./bst`. To compile and run `benchmark.cc` run `make benchmark` and `./benchmark`.

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

### Implementation choices
There were important choices that had been taken at the beginning of the implementation:

- First of all we decided to separate all the classes. There are advantages and disadvantages with this choice. We want to do this because if the classes were nested inside the BST, we would have to repeat the templates of the BST class for every function implementation of the nested classes. This would also mean that if we changed the BST templates we would need to modify all these functions. Moreover, in this way, the Node class is reusable on different types of BSTs.
The main cons is that we are exposing the Iterator class as public, even though it is specific for our implemetation of the tree.

- Another important choice was deciding the type of the pointers involved. In our opinion, the two children and the head could have been either unique or raw pointers. We ended up in choosing unique pointers bacause they allow us not to care about deallocation of the memory, even if we realised that the erase function became more complicated, due to the reallocation of the pointers. Instead, we were forced to use a raw pointer for the parent, because every node is a child of some other node (except from the head), therefore it is not possible to use unique ones.

- We chose the iterator to be forward because the traversing of the tree is in order, therefore we do not need to go backward.

- The implementation of the structure is entirely written in the header file because we have to deal with templated functions. If the implementations were separated from the definitions, the complier would complain about undefined reference.

### Benchmark results




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
