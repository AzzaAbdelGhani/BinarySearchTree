#include <bst.hpp>
#include <map>
#include<chrono>

int main(){

    //Benchmark variables
    constexpr unsigned int N = 5000;

    //This code provides a benchmark of our class bst with respect to the standard library implementation
    //of map

    bst<int, int, std::less<int>> bst1{std::less<int>()};
    std::map<int, int> map1;
    
    //Unbalanced insert 

    std::cout << N << " unbalanced inserts on bst" << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        bst1.insert(std::make_pair(i,i));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  

    std::cout << N << " unbalanced inserts on map" << std::endl;
     begin = std::chrono::steady_clock::now();
    for(unsigned int i = 0; i < N; ++i){
        map1.insert(std::make_pair(i,i));
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


}

