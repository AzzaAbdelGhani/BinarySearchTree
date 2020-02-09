#include <bst.hpp>

int main(){

    //Constructor with head
    //bst<int, int, std::less<int>> t{std::less<int>()};
    bst<int, int, std::less<int>> t{8,8,std::less<int>()};

    //TODO: for debugging purposes, let's just stick with key=value (just like Alberto)
    // t.insert({2,2});
    // t.insert({3,3});
    t.insert({3,3});
    t.insert({6,6});
    // std::cout<< t << std::endl;
    std::cout << t << std::endl;
    //t.isThere({9});

    // //Constructor without head: insert should create the head: WORKS
    // bst<int, int, std::less<int>> abba{1,1,std::less<int>()};
    // abba.insert({2,2});
    // std::cout<< abba << std::endl;

    // //Construct S.A.R.T.O.R.I. (Something abstract related to our recursive implementation)
    bst<int, int, std::less<int>> sartori{8,8,std::less<int>()};
    sartori.insert({3,3});
    sartori.insert({6,6});
    sartori.insert({1,1});
    sartori.insert({10,10});
    sartori.insert({7,7});
    sartori.insert({14,14});
    sartori.insert({4,4});
    sartori.insert({13,13});
    std::cout<< sartori << std::endl;

    std::cout << sartori[3] << std::endl;
    std::cout << sartori[60] << std::endl;
    std::cout<< sartori << std::endl;

    return 0;
}

