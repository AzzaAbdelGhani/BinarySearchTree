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

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(const pair_type& x){
    
    if (head == nullptr)
    {
        head = new node_type(x, nullptr);
        return(std::make_pair<iterator(head),true>);
    }
    
    node_type* new_node = nullptr;  
    node_type* tmp = head ;
    
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
            //if the key is already exist 
             return(std::make_pair<iterator(),false>);
        }
        
    }
    tmp = new node_type(x, new_node);
    if (x.first < new_node->getValue().first)
    { 
        new_node->getLeft() = tmp; 
    }
    else
    {
        new_node->getRight() = tmp; 
    }
    return(std::make_pair<iterator(tmp),true>); 
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(pair_type&& x){
    
       if (head == nullptr)
    {
        head = new node_type(std::move(x), nullptr);
        return(std::make_pair<iterator(head),true>);
    }
    
    node_type* new_node = nullptr;  
    node_type* tmp = head ;
    
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
            //if the key is already exist 
             return(std::make_pair<iterator(),false>);
        }
        
    }
    tmp = new node_type(std::move(x), new_node);
    if (x.first < new_node->getValue().first)
    { 
        new_node->getLeft() = tmp; 
    }
    else
    {
        new_node->getRight() = tmp; 
    }
    return(std::make_pair<iterator(tmp),true>); 
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::find(const k& x) noexcept{
    
    auto it = iterator(head);

    while(it.getCurrent() != nullptr )
    {
        if(it.getCurrent().getValue().first < x)
        {
            it.getCurrent() = it.getCurrent()->getRight(); 
        }
        else if(it.getCurrent().getValue().first > x)
        {
            it.getCurrent() = it.getCurrent()->getLeft(); 
        }
        else
        {
            return(iterator(it));
        }
        
    }

    return end();
}
template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::find(const k& x) const{
        
    auto it = iterator(head);
    while(it.getCurrent() != nullptr )
    {
        if(it.getCurrent().getValue().first < x)
        {
            it.getCurrent() = it.getCurrent()->getRight(); 
        }
        else if(it.getCurrent().getValue().first > x)
        {
            it.getCurrent() = it.getCurrent()->getLeft(); 
        }
        else
        {
            return(iterator(it));
        }
        
    }

    return end();
}