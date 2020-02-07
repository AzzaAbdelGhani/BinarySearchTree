#include <bst.hpp>

template <typename node_type, typename T>
node_type* _iterator<node_type,T>::next() noexcept{
    if(current.getRight() != nullptr) {
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
    if(current.getLeft() != nullptr) {
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