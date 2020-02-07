#include <bst.hpp>

int main(){

    bst<int, int, std::less<int>> t{1,1,std::less<int>()};

    t.insert({1,36});
    t.insert({3,66});
    t.insert({2,54});

    std::cout<< t << std::endl;
    return 0;

}

