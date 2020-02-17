# Advanced Programming Exam

A binary search tree implementation, written in c++14 for the Advanced Programming Exam of DSSC Course 2019/20


In this project we implemented a templated Binary Search Tree (BST) in c++ and we benchmarked it against the `std::map` implementation. In the directory there are two main files: one to actually use our BST, and the other to test the performance. In order compile and run them, we wrote a MakeFile thanks to which you can run the commands `make` and `./bst`, for the tree, and `make benchmark` and `./benchmark` for the testing.

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
This class represents the concept of node, in which we have the value of it and the poiters to the childern and the parent. The only template that we have is on the value.

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

- First of all we decided to separate all the classes. This because they are templated and we want to generalize them as much as possible. For example, the BST class has templates on k,v and c, but we want the concept of node to be templated on just his value, that could be of whatever type, and we do not care about details concerning our specific implemenation of the BST. This would allow us to use the node class for another type of tree. Another reason it is the fact that we are avoiding to write too many templates in every implementation of the functions outside the classes.

- Another imporant choice was deciding the type of the pointers involved. In our opinion, the two children and the head could have been either unique or shared pointers, becuase in that way we do not have to worry about deleting them. We will never have two pointers to the same child or to the same head, therefore we chose unique. Instead, we decided to use a raw pointer to the parent, because it will be pointed from at least two other pointers. We could use a shared-pointer too, but we would have had problems when deleting nodes.

