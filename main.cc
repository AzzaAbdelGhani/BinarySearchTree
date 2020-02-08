#include <bst.hpp>

int main(){

    bst<int, int, std::less<int>> t{1,1,std::less<int>()};


    //TODO: for debugging purposes, let's just stick with key=value (just like Alberto)
    t.insert({2,2});
    t.insert({3,3});
    t.insert({4,4});
    t.insert({6,5});
    // t.insert({3,66});
    // t.insert({2,54});

    std::cout<< t << std::endl;

    // bst<int, int, std::less<int>> st{std::less<int>()};

    // st.insert({1,36});

    // auto a = 1;
    // auto b = 5;

    // st.insert({a,b});

    return 0;

}

