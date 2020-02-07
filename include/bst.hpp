#ifndef __bst_hpp
#define __bst_hpp

#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>

template <typename k, typename v, typename c = std::less<k>>
class bst{
    c op;
    std::unique_ptr<node> head;

    public:
        bst(c comp): op{comp} {};
        bst(k key, v value, c comp): head{node(std::pair<k,v>(key,value))}, op{comp} {};

        using node_type = node<std::pair<const k,v>>;
        using pair_type = typename node_type::value_type;
        using iterator = _iterator<node_type, pair_type>;
        using const_iterator = _iterator<node_type, const pair_type>;

        std::pair<_iterator, bool> insert(const pair_type& x);
        std::pair<_iterator, bool> insert(pair_type&& x);

        // TODO: what if we have an odd number of args?? Possibly exception!
        // probably args should be pairs because in that way we can pass different types of k and v
        // ask SARTORIIII

        // TODO: if insert thorows an exception, should emplace throw it too?
        template<class... Types>
        std::pairs<_iterator,bool> emplace(Types&&... args);

        void clear() noexcept;

        iterator begin() ;
        const_iterator begin() const;
        const_iterator cbegin() const; // TODO: maybe add cbegin () without const??

        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        iterator find(const k& x) noexcept;
        const_iterator find(const k& x) const;

        void balance();

        v& operator[](const k& x);
        v& operator[](k& x);

        friend
        std::ostream& operator<<(std::ostream& os, const bst& x);

        // copy semantic
        bst(const bst& b); // copy constr
        bst& operator=(const bst& b); //copy assign

        // move semantic
        bst(const bst&& b) noexcept; // move constr
        bst& operator=(const bst&& b) noexcept; //move assign

        void erase(const k& x);
};

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
        ~node(){delete parent; ~left; ~right;}; // TODO: delete or delete[] ??
        using value_type = T;
};

template <typename node_type, typename T>
class _iterator {
    node_type* current;

    public:
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category =std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        reference operator*() const noexcept { return current->value; }
        pointer operator->() const noexcept { return &(*(*this)); }

        _iterator& operator++() noexcept {  // pre increment
            current = next(); // TODO:
            return *this;
        }

        //next
        // you check right. if it's not null, you find the minimun of the right subtree
        // otherwise go to patents unitl greater value

        //left
        // you check left. if it's not null, you find the maximum of the left subtree
        // otherwise go to patents unitl lower value

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
};

#endif