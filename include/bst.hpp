#ifndef __bst_hpp
#define __bst_hpp

#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <vector>
#include <cmath>

template <typename T>
class node {
    T value;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    node* parent;

    public:
        node(const T &p): value{p}, parent{nullptr} {};
        node(T &&p): value{std::move(p)}, parent{nullptr} {};
        node(const T &p, node* n): value{p}, parent{n} {};
        node(T &&p, node* n): value{std::move(p)}, parent{n} {};
        // Explicit node copy constructor
        explicit node(const std::unique_ptr<node> &p, node* parent): value{p->value}{
            this->parent = parent;
            if(p->right)
                right = std::make_unique<node>(p->right, this);
            if(p->left)
                left = std::make_unique<node>(p->left, this);
        }
        
        using value_type = T;

        // getters
        T& getValue() { return value;}
        node* getLeft() const {return left.get();}
        node* getRight() const {return right.get();}
        node* getParent() const {return parent;}

        // setters
        void setLeft(node* x) { left.reset(x); }
        void setRight(node* x) { right.reset(x); }
        void setParent(node* x) { parent = x; }
        
        // release smart pointers
        node* releaseRight() {return right.release();}
        node* releaseLeft() {return left.release();}
};

template <typename node_type, typename T>
class _iterator {
    node_type* current;

    // private functions
    node_type* next() noexcept;
    node_type* previous() noexcept;

    public:
        _iterator() noexcept: current{nullptr} {};
        explicit _iterator(node_type* x) noexcept : current{x} {};
        
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category =std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        reference operator*() const noexcept { return(current->getValue()); }
        
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

        friend bool operator==(const _iterator& a, const _iterator& b) {
            return a.current == b.current;
        }

        friend bool operator!=(const _iterator& a, const _iterator& b) {
            return !(a == b);
        }

        // getter
        node_type* getCurrent() const {return current;}

        // setter
        void setCurrent(node_type* x) { current = x;}
};

template <typename k, typename v, typename c = std::less<k> >
class bst{
    using node_type = node<std::pair<const k,v> >;
    using pair_type = typename node_type::value_type;
    c op;
    std::unique_ptr<node_type> head;

    // private functions for tree balance
    void balanceRec(std::vector<pair_type> values, size_t n);
    int height(node_type* x) noexcept {return (x == nullptr) ? 0 : 1 + std::max(height(x->getLeft()), height(x->getRight()));};
    void drawRec(const std::string& prefix, node_type* x, bool isLeft) noexcept;

    public:
        bst(): op{c()}, head{nullptr} {};
        bst(c comp): op{comp}, head{nullptr} {};
        bst(k key, v value): op{c()}, head{ std::make_unique<node_type>(std::pair<k,v>(key,value))} {};
        bst(k key, v value, c comp): op{comp}, head{ std::make_unique<node_type>(std::pair<k,v>(key,value))} {};
        
        using iterator = _iterator<node_type, pair_type>;
        using const_iterator = _iterator<node_type, const pair_type>;

        std::pair<iterator, bool> insert(const pair_type& x);
        std::pair<iterator, bool> insert(pair_type&& x);

        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args) {return insert(pair_type(std::forward<Types>(args)...));}; 

        void clear() noexcept { if(head) {head.reset();} }; 

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept; 

        iterator end() noexcept {return iterator{nullptr};}
        const_iterator end() const noexcept { return const_iterator{nullptr};}
        const_iterator cend() const noexcept { return const_iterator{nullptr};}

        iterator find(const k& x) noexcept; 
        const_iterator find(const k& x) const noexcept; 

        void balance(); 
        //This function has been used to debug the balance function.
        bool isBalanced(node_type* x) noexcept; 

        v& operator[](const k& x) {
            auto it = find(x);
            if(it != end())
                return (*it).second;
            else {
                auto p = insert({x,v{}});
                return (*(p.first)).second;
            }
        }

        v& operator[](k&& x){
            auto it = find(x);
            if(it != end())
                return (*it).second;
            else {
                auto p = insert({std::move(x),v{}});
                return (*(p.first)).second;
            }
        }

        friend
        std::ostream& operator<<(std::ostream& os, const bst& x){
            auto it = x.begin(); //auto will be const_iterator
            while (it != x.end()) {
                os << (*it).second << " ";
                ++it;
            }
            return os;
        }

        void draw() {drawRec("",head.get(),false);};

        // copy semantic
        bst(const bst &b): op{b.op} { head = std::make_unique<node_type>(b.head,nullptr); } // copy constr
        
        bst& operator=(const bst& b){ // copy assignment
            this->clear();
            op = b.op;
            head = std::make_unique<node_type>(b.head,nullptr);
            return *this;
        } 

        // move semantic
        bst(bst&& b) noexcept = default; // move constr 
        bst& operator=(bst&& b) noexcept = default; //move assignment

        void erase(const k& x);
};


////////////////////////////////
/////                     //////
/////  ITERATOR FUNCTIONS //////
/////                     //////
////////////////////////////////

template <typename node_type, typename T>
node_type* _iterator<node_type,T>::next() noexcept {
    if(current->getRight() != nullptr) {
        current = current->getRight();
        while(current->getLeft() != nullptr)
            current = current->getLeft();
    } else {
        if(current->getParent() == nullptr) // if we are the head we are done
            return nullptr;
        while(current->getParent()->getLeft() != current){
                current = current->getParent();
                if(current->getParent() == nullptr)
                    return nullptr;
        }
        current = current->getParent();
    }
    return current;
}

///////////////////////////
/////                //////
/////  BST FUNCTIONS //////
/////                //////
///////////////////////////

//The first element of the bst is the leftmost element of the tree
template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::begin() noexcept {

    if(head == nullptr)
        return iterator(nullptr);
    
    auto it = iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;   
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::begin() const noexcept {

    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::cbegin() const noexcept{

    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(const pair_type& x){
    
    std::cout << "L-Val insert" << std::endl;

    if (head == nullptr){
        head = std::make_unique<node_type>(x, nullptr);;
        return(std::make_pair(iterator(head.get()),true));
    }
    
    node_type* new_node = nullptr;  
    auto tmp = head.get() ;
    
    while (tmp != nullptr){
        new_node = tmp;
        if (op(x.first,tmp->getValue().first))
            tmp = tmp->getLeft();
        else if (op(tmp->getValue().first, x.first))
            tmp = tmp->getRight();
        else
            return(std::make_pair(iterator(tmp),false)); //if the key is already exist 
    }

    tmp = new node_type(x, new_node);
    if (op(x.first,new_node->getValue().first))
        new_node->setLeft(tmp); 
    else
        new_node->setRight(tmp); 
     
    return(std::make_pair(iterator(tmp),true)); 
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(pair_type&& x){
    
    if (head == nullptr){
        head = std::make_unique<node_type>(std::move(x), nullptr);
        return(std::make_pair(iterator(head.get()),true));
    }
    
    node_type* new_node = nullptr;  
    auto tmp = head.get() ;
    
    while (tmp != nullptr){
        new_node = tmp;
        if (op(x.first,tmp->getValue().first))
            tmp = tmp->getLeft();
        else if (op(tmp->getValue().first,x.first))
            tmp = tmp->getRight();
        else 
             return(std::pair<iterator, bool> (iterator(tmp),false)); //if the key already exist
    }
    tmp = new node_type(std::move(x), new_node);
    if (op(x.first,new_node->getValue().first))
        new_node->setLeft(tmp); 
    else
        new_node->setRight(tmp);
    return(std::make_pair(iterator(tmp),true)); 
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::find(const k& x) noexcept{
    
    auto it = iterator(head.get());
    while(it.getCurrent() != nullptr ){
        auto node = it.getCurrent();
        if(op(node->getValue().first,x))
            it.setCurrent(node->getRight()); 
        else if(op(x,node->getValue().first))
            it.setCurrent(node->getLeft()); 
        else
            return(iterator(it)); 
    }
    return end();
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::find(const k& x) const noexcept{
        
    auto it = const_iterator(head.get());
    while(it.getCurrent() != nullptr ){
        auto node = it.getCurrent();
        if(op(node->getValue().first,x))
            it.setCurrent(node->getRight()); 
        else if(op(x,node->getValue().first))
            it.setCurrent(node->getLeft()); 
        else
            return(const_iterator(it)); 
    }
    return cend();
}

template <typename k, typename v, typename c>
void bst<k,v,c>::erase(const k& x){

    iterator p = find(x);

    if (p != end()){
        auto current = p.getCurrent();
        auto left = current->getLeft();
        auto right = current->getRight();
        auto parent = current->getParent();
           
        if(left && right) { // node with two children
            ++p;
            auto _current = p.getCurrent();
            auto _parent = _current->getParent();
            auto _right = _current->getRight();
            auto tmp = current->releaseLeft();
            _current->setLeft(tmp);
            tmp->setParent(_current);

            if(_parent == current) {
                auto tmp_next = _parent->releaseRight();
                if(head.get() == current) {
                    auto del_root = head.release();
                    head.reset(tmp_next);
                    delete del_root;
                } else if(parent->getLeft() == current) {
                    auto tmp_current = parent->releaseLeft();
                    parent->setLeft(tmp_next);
                    delete tmp_current;
                } else {
                    auto tmp_current = parent->releaseRight();
                    parent->setRight(tmp_next);
                    delete tmp_current;
                }
                tmp_next->setParent(parent);
            } else {
                auto tmp_next = _parent->releaseLeft();
                if(_right) {
                    auto tmp_right = _current->releaseRight();
                    _parent->setLeft(tmp_right);
                    tmp_right->setParent(_parent);
                }

                auto tmp_parent = current->releaseRight();
                tmp_next->setRight(tmp_parent);
                tmp_parent->setParent(tmp_next);
                
                if(head.get() == current) {
                    auto del_root = head.release();
                    head.reset(tmp_next);
                    delete del_root;
                } else if (parent->getLeft() == current) {
                    auto tmp_current = parent->releaseLeft();
                    parent->setLeft(tmp_next);
                    delete tmp_current;
                } else {
                    auto tmp_current = parent->releaseRight();
                    parent->setRight(tmp_next);
                    delete tmp_current;    
                }
                tmp_next->setParent(parent);  
            }
        } else if(!left && !right) { // leaf node  
             
            if(head.get() == current) {
                auto del_root = head.release();
                head.reset(nullptr);
                delete del_root;
            }
            else if(parent->getLeft() == current)
                parent->setLeft(nullptr);
            else
                parent->setRight(nullptr);
        } else if(left && !right) { // node with only left child
            
            left->setParent(parent);
            if(head.get() == current) {
                auto new_root = current->releaseLeft();
                auto del_root = head.release();
                head.reset(new_root);
                delete del_root;
            } else if(parent->getLeft() == current) {
                auto tmp = parent->releaseLeft();
                tmp->releaseLeft();
                parent->setLeft(left);  
                delete tmp;
            } else {
                auto tmp = parent->releaseRight();
                tmp->releaseLeft();
                parent->setRight(left);
                delete tmp;
            }      
        } else { // node with only right child 
            right->setParent(parent);
            if(head.get() == current) {
                auto new_root = current->releaseRight();
                auto del_root = head.release();
                head.reset(new_root);
                delete del_root;
            } else if(parent->getLeft() == current) {
                auto tmp = parent->releaseLeft();
                tmp->releaseRight();
                parent->setLeft(right);
                delete tmp;
            } else {
                auto tmp = parent->releaseRight();
                parent->setRight(right);
                tmp->releaseRight(); 
                delete tmp;
            }
        }
    }
    
}

template <typename k, typename v, typename c>
void bst<k,v,c>::balance() {

    //copying ordered values in a vector 
    std::vector<pair_type> values;
    auto it = cbegin();
    while(it.getCurrent() != nullptr){
        values.push_back((*it));
        it++;
    }
    clear(); //clear the bst
    balanceRec(values, values.size()); //re-built the balanced bst
}

template <typename k, typename v, typename c>
void bst<k,v,c>::balanceRec(std::vector<pair_type> values, size_t n) {
    if(n==1) {
        insert({values.at(0).first,values.at(0).second});
    } else if(n==2) {
        insert({values.at(0).first,values.at(0).second});
        insert({values.at(1).first,values.at(1).second});
    } else{
        int middle = (n % 2 == 0) ? (n/2)-1 : floor(n/2);
        insert({values.at(middle).first,values.at(middle).second});

        //create 2 sub-vectors
        auto firstLeft = values.begin();
        auto lastLeft = values.begin() + middle;
        auto firstRight = values.begin() + middle + 1;
        auto lastRight = values.end();
        std::vector<pair_type> leftValues(firstLeft,lastLeft);
        std::vector<pair_type> rightValues(firstRight,lastRight);
        balanceRec(leftValues, leftValues.size());
        balanceRec(rightValues, rightValues.size());
    }
}

template <typename k, typename v, typename c>
bool bst<k,v,c>::isBalanced(node_type* x) noexcept {
    if (x == nullptr) 
        return true; 
    
    int lh = height(x->getLeft()); 
    int rh = height(x->getRight()); 
  
    if(abs(lh - rh) <= 1 && isBalanced(x->getLeft()) && isBalanced(x->getRight())) 
        return true;
    return false;
}

template <typename k, typename v, typename c>
void bst<k,v,c>::drawRec(const std::string& prefix, node_type* x, bool isLeft) noexcept {
    if(x != nullptr){
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << x->getValue().second << std::endl;

        // enter the next tree level - left and right branch
        drawRec( prefix + (isLeft ? "│   " : "    "), x->getLeft(), true);
        drawRec( prefix + (isLeft ? "│   " : "    "), x->getRight(), false);
    }
}

#endif
