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
    // TODO: shared??
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
    node* parent; // root point to null pointer

    public:
        node(T p): value{p}, left{nullptr}, right{nullptr}, parent{nullptr} {};
        node(T p, node* n): value{p}, left{nullptr}, right{nullptr}, parent{n} {};
        ~node(){delete parent;}; // TODO: take care of shared pointers
        using value_type = T;

        //getters
        T getValue(){return value;}
        node* getLeft() const {return left;}
        node* getRight() const {return right;}
        node* getParent() const {return parent;}
};

template <typename node_type, typename T>
class _iterator {
    node_type* current;
    node_type* next() noexcept;
    node_type* previous() noexcept;

    public:
        explicit _iterator(node_type* x)noexcept : current{x} {};
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category =std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        reference operator*() const noexcept { return current->getValue(); }
        pointer operator->() const noexcept { return &(*(*this)); }

        _iterator& operator++() noexcept {  // pre increment
            current = next(); // TODO:
            return *this;
        }

        _iterator operator++(int) noexcept {
            _iterator tmp{current};
            ++(*this);
            return tmp;
        }

        _iterator& operator--() noexcept { //pre decrement
            current = previous(); // TODO:
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

        node_type* getCurrent() const {return current;}
};

template <typename k, typename v, typename c = std::less<k> >
class bst{
    using node_type = node<std::pair<const k,v> >;
    c op;
    std::unique_ptr<node_type> head;

    public:
        bst(c comp): op{comp} {};
        bst(k key, v value, c comp): head{std::make_unique<node_type>(node_type(std::pair<k,v>(key,value)))}, op{comp} {};

        
        using pair_type = typename node_type::value_type;
        using iterator = _iterator<node_type, pair_type>;
        using const_iterator = _iterator<node_type, const pair_type>;

        std::pair<iterator, bool> insert(const pair_type& x);
        std::pair<iterator, bool> insert(pair_type&& x);

        // TODO: what if we have an odd number of args?? Possibly exception!
        // probably args should be pairs because in that way we can pass different types of k and v
        // ask SARTORIIII

        // TODO: if insert thorows an exception, should emplace throw it too?
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args);

        void clear() noexcept;

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const; // TODO: maybe add cbegin () without const??

        // TODO: think about const and noexcept
        iterator end(){return iterator{nullptr}};
        const_iterator end() const{ return const_iterator{nullptr}};
        const_iterator cend() const { return const_iterator{nullptr}};

        iterator find(const k& x) noexcept;
        const_iterator find(const k& x) const;

        void balance();

        v& operator[](const k& x);
        v& operator[](k& x);

        friend
        std::ostream& operator<<(std::ostream& os, const bst& x){
            auto it = x.begin();
            while (it) {
                os << it.getCurrent() << " ";
                it++;
            }
            return os;
        }

        // copy semantic
        bst(const bst& b); // copy constr
        bst& operator=(const bst& b); //copy assign

        // move semantic
        bst(const bst&& b) noexcept; // move constr
        bst& operator=(const bst&& b) noexcept; //move assign

        void erase(const k& x);
};
#endif