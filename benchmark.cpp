#include <bst.hpp>
#include <map>
#include <chrono>
#include <random>

enum class method{ insert, find, emplace};

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


    std::cout << N << " finds on unbalanced bst" << std::endl;
    begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        bst1.find(i);
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  

    std::cout << N << " finds on map" << std::endl;
    begin = std::chrono::steady_clock::now();
    for(unsigned int i = 0; i < N; ++i){
        map1.find(i);
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


    //Clear the trees
    std::cout << "Clearing the trees" << std::endl;
    bst1.clear();
    map1.clear();





    //Clear the trees
    std::cout << "Clearing the trees" << std::endl;
    bst1.clear();
    map1.clear();


    //Inserting random numbers

    //Using the std uniform int distribution
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(1, N); //This way we might end up with duplicates numbers
    //so insert should just not put them in the bst

    std::cout << N << " random inserts bst" << std::endl;
    begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        auto tmp = dis(gen);
        bst1.insert(std::make_pair(tmp,tmp));
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


    std::cout << N << " random inserts map" << std::endl;
    begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        auto tmp = dis(gen);
        map1.insert(std::make_pair(tmp,tmp));
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


    //Random finds

    std::cout << N << " random finds bst" << std::endl;
    begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        auto tmp = dis(gen);
        bst1.find(tmp);
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


    std::cout << N << " random finds map" << std::endl;
    begin = std::chrono::steady_clock::now();

    for(unsigned int i = 0; i < N; ++i){
        auto tmp = dis(gen);
        map1.find(tmp);
    }

    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " (ms)" << std::endl;  


    //Clear the trees
    std::cout << "Clearing the trees" << std::endl;
    bst1.clear();
    map1.clear();

}

// template<class T>
// void run(T object, )