#include <bst.hpp>

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

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(const pair_type& x){
    node_type* new_node = nullptr;  
    node_type* tmp = head ;
    bool flag = false;
    if (head == nullptr)
    {
        head = node_type(x);
        flag = true;
        iterator M = iterator(head);
        return(std::pair<M,flag>);
    }
    while (tmp != nullptr)
    {
        new_node = tmp;
        if (x.first < tmp->getValue().first)
        {
            tmp = tmp->getLeft();
        }
        else if ((x.first > tmp->getValue().first))
        {
            tmp = tmp->getRight();
        }  
        else
        {
             iterator M = iterator();
             return(std::pair<M,flag>);
        }
        
    }
    tmp = node_type(x, new_node);
    flag = true;
    else if (x.first < new_node->getValue().first)
    { 
        new_node->getLeft() = tmp; 
    }
    else
    {
        new_node->getRight() = tmp; 
    }
  
    iterator M = iterator(new_node);
    return(std::pair<M,flag>); 
}
