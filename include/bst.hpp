#ifndef __bst_hpp
#define __bst_hpp

#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>

template <typename T>
class node {
    T value;
    // TODO: For now we are going to use raw pointers, cause it's easier to traverse the tree
    node* left;
    node* right;
    node* parent; // root points to null pointer

    public:
        node(T p): value{p}, left{nullptr}, right{nullptr}, parent{nullptr} {};
        node(T p, node* n): value{p}, left{nullptr}, right{nullptr}, parent{n} {};
        //TODO: Move constructor, do we need it?
        //node(T &&p): value{std::move(p)}, left{nullptr}, right{nullptr}, parent{nullptr} {};
        ~node(){
            delete left;
            delete right;
        }
        using value_type = T;

        //getters
        //TODO: Should we return a value or a reference to the value? 
        T& getValue(){ return value;}
        node* getLeft() const {return left;}
        node* getRight() const {return right;}
        node* getParent() const {return parent;}

        //setters
        void setLeft(node* x) { left = x; }
        void setRight(node* x) { right = x; }
        void setParent(node* x) { parent = x; }
};

template <typename node_type, typename T>
class _iterator {
    node_type* current;
    node_type* next() noexcept;
    node_type* previous() noexcept;

    public:
        _iterator() noexcept: current{nullptr} {};
        explicit _iterator(node_type* x) noexcept : current{x} {};
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category =std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        reference operator*() const noexcept { return current->getValue(); }
        pointer operator->() const noexcept { return &(*(*this)); }

        _iterator& operator++() noexcept {  // pre increment
            current = next();
            return *this;
        }

        _iterator operator++(int) noexcept {
            _iterator tmp{current};
            ++(*this);
            return tmp;
        }

        _iterator& operator--() noexcept { //pre decrement
            current = previous();
            return *this;
        }

        _iterator operator--(int) noexcept {
            _iterator tmp{current};
            --(*this);
            return tmp;
        }

        friend bool operator==(const _iterator& a, const _iterator& b) {
            return a.current == b.current;
        }

        friend bool operator!=(const _iterator& a, const _iterator& b) {
            return !(a == b);
        }

        //getter
        node_type* getCurrent() const {return current;}

        //setter
        void setCurrent(node_type* x) { current = x;}
};

template <typename k, typename v, typename c = std::less<k> >
class bst{
    using node_type = node<std::pair<const k,v> >;
    c op = c();
    //TODO: Head for now is a raw pointer, same reason for left and right
    node_type* head;

    public:
        bst(c comp): op{comp}, head{nullptr} {};
        bst(k key, v value, c comp): op{comp}, head{new node_type(std::pair<k,v>(key,value))} {};
        ~bst() { delete head; }

        using pair_type = typename node_type::value_type;
        using iterator = _iterator<node_type, pair_type>;
        using const_iterator = _iterator<node_type, const pair_type>;

        std::pair<iterator, bool> insert(const pair_type& x);
        std::pair<iterator, bool> insert(pair_type&& x);

        // TODO: what if we have an odd number of args?? Possibly exception!
        // probably args should be pairs because in that way we can pass different types of k and v
        // ask SARTORIIII
        // TODO: if insert thorows an exception, should emplace throw it too?
        // TODO: to implement
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args); 

        //TODO: to implement
        void clear() noexcept; 

        //TODO: Shall these be noexcept?
        iterator begin();
        const_iterator begin() const;
        // TODO: maybe add cbegin () without const??
        const_iterator cbegin() const; 

        // TODO: think about const and noexcept here
        iterator end(){return iterator{nullptr};}
        const_iterator end() const{ return const_iterator{nullptr};}
        const_iterator cend() const { return const_iterator{nullptr};}

        //TODO: to implement
        iterator find(const k& x) noexcept; 

        //TODO: to implement
        const_iterator find(const k& x) const; 

        //TODO: to implement
        void balance(); 

        //TODO: to implement
        v& operator[](const k& x); 
        //TODO: to implement
        v& operator[](k& x); 

        friend
        std::ostream& operator<<(std::ostream& os, const bst& x){
            auto it = x.begin();
            //FIXED: could not convert ‘it’ to bool
            while (it != x.end()) {
                // os << it.getCurrent()->getValue().first << " ";
                os << (*it).second << " ";
                ++it;
            }
            return os;
        }

        // copy semantic
        //TODO: to implement
        bst(const bst& b); // copy constr 
        //TODO: to implement
        bst& operator=(const bst& b); //copy assign 

        // move semantic

        //TODO: to implement
        bst(const bst&& b) noexcept; // move constr 
        //TODO: to implement
        bst& operator=(const bst&& b) noexcept; //move assign 

        //TODO: to implement
        void erase(const k& x); 
};



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
        std::cout << "Current right value: " << current->getRight()->getValue().first << std::endl;
        while(current->getLeft() != nullptr)
            current = current->getLeft();
    } else {
        std::cout << "Hi I am on the else" << std::endl;
        if(current->getParent() == nullptr){
            return nullptr;
        }
        // TODO: we would need to use a compare operator
        while(current->getParent()->getValue().first < current->getValue().first){
            current = current->getParent();
            std::cout << "Current_Value: " << current->getValue().first << std::endl;
            if(current->getParent() == nullptr)
                //return nullptr;
                break;
        }

        current = current->getParent();
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

    if(head == nullptr)
        return iterator(nullptr);
    
    auto it = iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;   
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::begin() const{

    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::cbegin() const{

    //TODO: maybe just call begin here
    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head);
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(const pair_type& x){
    
    if (head == nullptr)
    {
        head = new node_type(x, nullptr);
        return(std::make_pair(iterator(head),true));
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
             return(std::make_pair(iterator(),false));
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
    return(std::make_pair(iterator(tmp),true)); 
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(pair_type&& x){
    
    if (head == nullptr)
    {
        //head = new node_type(std::move(x), nullptr);
        head = new node_type(std::move(x), nullptr);
        return(std::make_pair(iterator(head),true));
    }
    
    node_type* new_node = nullptr;  
    auto tmp = head ;
    
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
             return(std::pair<iterator, bool> (iterator(),false));
        }
        
    }
    tmp = new node_type(std::move(x), new_node);
    if (x.first < new_node->getValue().first)
    { 
        new_node->setLeft(tmp); 
    }
    else
    {
        new_node->setRight(tmp);
    }
    return(std::make_pair(iterator(tmp),true)); 
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
        
    auto it = const_iterator(head);
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
            return(const_iterator(it));
        }
        
    }

    return end();
}


#endif
