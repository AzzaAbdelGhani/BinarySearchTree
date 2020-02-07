#include <bst.hpp>

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
        while(current->getParent()->getValue().first < current->getValue().first){// TODO:
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
        while(current->getParent()->getValue().first > current->getValue().first){// TODO:
            current = current->getParent();
            if(current->getParent() == nullptr)
                return nullptr;
        }
    }
    return current;
}

//The first element of the bst is the leftmost element of the tree
template <typename k, typename v, typename c>
bst<k,v,c>::iterator bst<k,v,c>::begin(){

    it = iterator(head);
    while( it.current->getLeft() != nullptr)
        it.current = it.current->getLeft()
    
    return it;
    
}

template <typename k, typename v, typename c>
bst<k,v,c>::iterator bst<k,v,c>::begin(){

    auto it = iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft()
    
    return it;
    
}


template <typename k, typename v, typename c>
bst<k,v,c>::iterator bst<k,v,c>::begin(){

    auto it = iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft()
    
    return it;   
}

template <typename k, typename v, typename c>
bst<k,v,c>::const_iterator bst<k,v,c>::begin() const{

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft()
    
    return it;
}

template <typename k, typename v, typename c>
bst<k,v,c>::const_iterator bst<k,v,c>::cbegin() const{

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.getCurrent() = it.getCurrent()->getLeft()
    
    return it;
}