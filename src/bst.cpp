#include <bst.hpp>

////////////////////////////////
/////                     //////
/////  ITERATOR FUNCTIONS //////
/////                     //////
////////////////////////////////


//Iterator functions
template <typename node_type, typename T>
node_type* _iterator<node_type,T>::next() noexcept{
    if(current->getRight() != nullptr) {
        current = current->getRight();

        while(current->getLeft() != nullptr)
            current = current->getLeft();
    } else {
        if(current->getParent() == nullptr){
            return nullptr;
        }
        // TODO: we would need to use a compare operator
        while(current->getParent()->getValue().first < current->getValue().first){
            current = current->getParent();
            if(current->getParent() == nullptr)
                return nullptr;
        }
    }
    return current;
}

template <typename node_type, typename T>
node_type* _iterator<node_type,T>::previous() noexcept{
    if(current->getLeft() != nullptr) {
        current = current->getLeft();

        while(current->getRight() != nullptr)
            current = current->getRight();
    } else {
        if(current->getParent() == nullptr){
            return nullptr;
        }
        // TODO: we would need to use a compare operator
        while(current->getParent()->getValue().first > current->getValue().first){
            current = current->getParent();
            if(current->getParent() == nullptr)
                return nullptr;
        }
    }
    return current;
}

///////////////////////////
/////                //////
/////  BST FUNCTIONS //////
/////                //////
///////////////////////////

template <typename k, typename v, typename c>
void bst<k,v,c>::clear() noexcept{

    //(Fra)TODO: I am confused, should this just call a node destructor?
    //Azza says: let's do a function that checks if a node is a leaf: then prune it!

        
}


//The first element of the bst is the leftmost element of the tree
template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::begin(){

    auto it = iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft();
    
    return it;   
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::begin() const{

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft();
    
    return it;
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::cbegin() const{

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft();
    
    return it;
}

