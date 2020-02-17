





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
Find a given key by traversing the tree in order way, if the given key is larger than the current node, go to right, otherwise go left. If the key is present, returns an iterator to the proper node, `end()` otherwise.

##### Balance

```c++
void balance();
```

Balance the tree by copying the values of the tree to a vector, the copy process will be in ascending order, in other words, start from the begin of the tree to the end. Then, clear the tree, and restart building the tree by recursively dividing the vector into two halves and inserting the middle value of the vector. 

##### Subscripting operator


```c++
value_type& operator[](const key_type& x);
value_type& operator[](key_type&& x);
```

Returns a reference to the value that is mapped to a key equivalent to `x` by calling find() function, and performing an insertion wit a default value if such key does not already exist.

##### Put-to operator


```c++
friend
std::ostream& operator<<(std::ostream& os, const bst& x);
```
Here, we return a reference to ostream object that contains all values of the nodes from the begin() of the tree to the end().

##### Copy and move

The copy semantics perform a deep-copy, copy the head of the right side tree to the head of left side tree, and for copy assignment, we clear the tree and then copy the head of the left side tree.
Meanwhile, for the move constructor and assignmen, just equal them to `default`.

##### Erase

```c++
void erase(const key_type& x);
```

Removes the element (if one exists) with the key equivalent to key. Checking the state of the node, if it is a full node, has a right and left nodes, Or if it is a leaf node, Or a node have just one childe either on right or left. 
