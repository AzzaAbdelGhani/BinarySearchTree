#include <bst.hpp>
#include <map>
#include <chrono>
#include <random>
#include <cmath>

//It would be nice to have a wrapper function handling times and their averages but it would
//probably be a little painful to generalise it

enum class method{ insert, emplace, find, erase};

template<class T>
void unbalancedRun(const unsigned int &n, const unsigned int &rep, T &object, const method &m);

template<class T>
void randomRun(const unsigned int &n, const unsigned int &rep, T &object, const method &m);

void balancedFind(const unsigned int &n, const unsigned int &rep, bst<int, int, std::less<int>> &object);


int main(){

    //Benchmark variables
    constexpr unsigned int N = 500;
    constexpr unsigned int reps = 20;

    //This code provides a benchmark of our class bst with respect to the standard library implementation
    //of map

    // bst<int, int, std::less<int>> bst1{std::less<int>()};
    // std::map<int, int> map1;
    using bst = bst<int, int, std::less<int>>;
    using map = std::map<int, int>;

    bst bst1{std::less<int>()};
    map map1;

    //Unbalanced insert 

    std::cout << N << " unbalanced inserts on bst" << std::endl;
    unbalancedRun<bst>(N, reps, bst1, method::insert);

    std::cout << N << " unbalanced inserts on map" << std::endl;
    unbalancedRun<map>(N, reps, map1, method::insert);

    // std::cout << N << " unbalanced emplaces on bst" << std::endl;
    // unbalancedRun<bst>(N, reps, bst1, method::emplace);

    // std::cout << N << " unbalanced emplaces on map" << std::endl;
    // unbalancedRun<map>(N, reps, map1, method::emplace);

    // std::cout << N << " unbalanced finds on bst" << std::endl;
    // unbalancedRun<bst>(N, reps, bst1, method::find);

    // std::cout << N << " unbalanced finds on map" << std::endl;
    // unbalancedRun<map>(N, reps, map1, method::find);

    // std::cout << N << " unbalanced erase on bst" << std::endl;
    // unbalancedRun<bst>(N, reps, bst1, method::erase);

    // std::cout << N << " unbalanced erase on map" << std::endl;
    // unbalancedRun<map>(N, reps, map1, method::erase);

    // //Random insert 

    // std::cout << N << " random inserts on bst" << std::endl;
    // randomRun<bst>(N, reps, bst1, method::insert);

    // std::cout << N << " random inserts on map" << std::endl;
    // randomRun<map>(N, reps, map1, method::insert);

    // std::cout << N << " random emplaces on bst" << std::endl;
    // randomRun<bst>(N, reps, bst1, method::emplace);

    // std::cout << N << " random emplaces on map" << std::endl;
    // randomRun<map>(N, reps, map1, method::emplace);

    // std::cout << N << " random finds on bst" << std::endl;
    // randomRun<bst>(N, reps, bst1, method::find);

    // std::cout << N << " random finds on map" << std::endl;
    // randomRun<map>(N, reps, map1, method::find);

    // std::cout << N << " random erase on bst" << std::endl;
    // randomRun<bst>(N, reps, bst1, method::erase);

    // std::cout << N << " random erase on map" << std::endl;
    // randomRun<map>(N, reps, map1, method::erase);

    // //We insert an unbalanced tree, balance it and then run find 

    // std::cout << N << " balanced inserts on bst" << std::endl;
    // unbalancedRun(N, reps, bst1, method::insert);

    // std::cout << N << " balanced finds on bst" << std::endl;
    // balancedFind(N, reps, bst1);

}

template<class T>
void unbalancedRun(const unsigned int &n, const unsigned int &rep, T &object, const method &m){

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double avg = 0;
    double avg_2 = 0;

    for(unsigned int i = 0; i < rep; ++i){

        begin = std::chrono::steady_clock::now();

        switch (m)
        {
            case method::insert:
                object.clear();
                for(unsigned int k = 0; k < n; ++k)
                    object.insert(std::make_pair(k,k));
                break;
            
            case method::emplace:
                object.clear();
                for(unsigned int k = 0; k < n; ++k)
                    object.emplace(k,k);
                break;
            
            case method::find:
                for(unsigned int k = 0; k < n; ++k)
                    object.find(k);
                break;

            default:
                break;
        }
            
        end = std::chrono::steady_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
        avg_2 += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()
                *std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
    }

    avg = static_cast<double>(avg)/rep;
    avg_2 = static_cast<double>(avg_2)/rep;
    auto std_dev = avg_2 - avg*avg;

    if(m == method::erase){
        begin = std::chrono::steady_clock::now();
        for(unsigned int k = 0; k < n; ++k){
            object.erase(k);
        }
        end = std::chrono::steady_clock::now();
        avg = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
        std_dev = 0;
    } 


    std::cout << "Average: " << avg << " (ms)" << std::endl;  
    std::cout << "Std Deviation: " << std_dev << " (ms)" << std::endl << std::endl;  
    
}

template<class T>
void randomRun(const unsigned int &n, const unsigned int &rep, T &object, const method &m){

    //Using the std uniform int distribution
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(1, n); //This way we might end up with duplicates numbers

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double avg = 0;
    double avg_2 = 0;

    for(unsigned int i = 0; i < rep; ++i){

        begin = std::chrono::steady_clock::now();

        switch (m)
        {
            case method::insert:
                object.clear();
                for(unsigned int k = 0; k < n; ++k){
                    auto tmp = dis(gen);
                    object.insert(std::make_pair(tmp,tmp));
                }
                break;
            
            case method::emplace:
                object.clear();
                for(unsigned int k = 0; k < n; ++k){
                    auto tmp = dis(gen);
                    object.emplace(tmp,tmp);
                }
                break;
            
            case method::find:
                for(unsigned int k = 0; k < n; ++k){
                    auto tmp = dis(gen);
                    object.find(tmp);
                }
                break;

            default:
                break;
        }
            
        end = std::chrono::steady_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
        avg_2 += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()
                *std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
    }

    avg = static_cast<double>(avg)/rep;
    avg_2 = static_cast<double>(avg_2)/rep;
    auto std_dev = avg_2 - avg*avg;

    
    if(m == method::erase){
        begin = std::chrono::steady_clock::now();
        for(unsigned int k = 0; k < n; ++k){
            auto tmp = dis(gen);
            object.erase(tmp);
        }
        end = std::chrono::steady_clock::now();
        avg = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
        std_dev = 0;
    } 

    std::cout << "Average: " << avg << " (ms)" << std::endl;  
    std::cout << "Std Deviation: " << std_dev << " (ms)" << std::endl << std::endl;  
    
}


void balancedFind(const unsigned int &n, const unsigned int &rep, bst<int, int, std::less<int>> &object){

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double avg = 0;
    double avg_2 = 0;
    object.balance();

    for(unsigned int i = 0; i < rep; ++i){

        begin = std::chrono::steady_clock::now();

        for(unsigned int k = 0; k < n; ++k)
            object.find(k);
            
        end = std::chrono::steady_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
        avg_2 += std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()
                *std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
    }

    avg = static_cast<double>(avg)/rep;
    avg_2 = static_cast<double>(avg_2)/rep;
    auto std_dev = avg_2 - avg*avg;

    std::cout << "Average: " << avg << " (ms)" << std::endl;  
    std::cout << "Std Deviation: " << std_dev << " (ms)" << std::endl << std::endl;  

}