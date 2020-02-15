#include <bst.hpp>

int main(){
/*
    //Constructor with head
    //bst<int, int, std::less<int>> t{std::less<int>()};
    bst<int, int, std::less<int>> t{1,1,std::less<int>()};

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

    std::cout << "Sartori" << std::endl;
    std::cout<< sartori << std::endl;

    std::cout << sartori[3] << std::endl;
    //std::cout << sartori[60] << std::endl;
    //std::cout<< sartori << std::endl;

    //Copy constructor test-case
    bst<int, int, std::less<int>> sartoriBis{sartori};
    std::cout << "Sartori bis" << std::endl;
    std::cout<< sartoriBis << std::endl;
    sartoriBis.isThere(8);

    sartoriBis.insert({5,5});
    std::cout << "SartoriBis after insert on sartoriBis" << std::endl;
    std::cout<< sartoriBis << std::endl;

    std::cout << "Sartori after insert on sartoriBis" << std::endl;
    std::cout<< sartori << std::endl;

    //Clear test

    std::cout << "t after t.clear()" << std::endl;
    t.clear();
    std::cout<< t << std::endl;

    //Copy assignment test

    std::cout << "sartoriBis after sartoriBis = sartori " << std::endl;
    sartoriBis = sartori;
    std::cout << sartoriBis << std::endl;

    //Move constructor test

    std::cout << "sartoriTris after sartoriTris{std::move(sartoriBis)}" << std::endl;
    bst<int,int,std::less<int>> sartoriTris{std::move(sartoriBis)};
    std::cout << sartoriTris << std::endl;
    
    std::cout << "sartoriBis after sartoriTris{std::move(sartoriBis)} ? " << std::endl;
    std::cout << sartoriBis << std::endl;

    //Move assignment test

    std::cout << "sartoriBis after sartoriBis = std::move(sartoriTris)" << std::endl;
    sartoriBis = std::move(sartoriTris);
    std::cout << sartoriBis << std::endl;
    
    std::cout << "sartoriTris after sartoriBis = std::move(sartoriTris) ? " << std::endl;
    std::cout << sartoriTris << std::endl;


    std::cout << "Testing the Erase Function :" << std::endl;
    std::cout << "Testing the deletion of thr root in all cases : " << std::endl;
    bst<int, int, std::less<int>> t1{std::less<int>()};
    std::cout << "delete the root that has only a left child : " << std::endl;
    t1.insert({8,8});
    t1.insert({3,3});
    t1.draw();
    t1.erase(8);
    t1.draw(); 
    bst<int, int, std::less<int>> t2{std::less<int>()};
    std::cout << "delete the root that has only a right child : " << std::endl;
    t2.insert({8,8});
    t2.insert({10,10});
    t2.draw();
    t2.erase(8);
    t2.draw();
    bst<int, int, std::less<int>> t3{std::less<int>()};
    std::cout << "delete the root that has right and left childs : " << std::endl;
    t3.insert({8,8});
    t3.insert({10,10});
    t3.insert({3,3});
    t3.draw();
    t3.erase(8);
    t3.draw();
    bst<int, int, std::less<int>> sartoriE{8,8,std::less<int>()};
    sartoriE.insert({3,3});
    sartoriE.insert({6,6});
    sartoriE.insert({1,1});
    sartoriE.insert({10,10});
    sartoriE.insert({7,7});
    sartoriE.insert({14,14});
    sartoriE.insert({4,4});
    sartoriE.insert({13,13});
    sartoriE.draw();
    sartoriE.erase(8);
    sartoriE.draw();
    sartoriE.erase(20);
    sartoriE.erase(3);
    sartoriE.draw();
    sartoriE.erase(14);
    sartoriE.draw();
    sartoriE.erase(10);
    sartoriE.draw();
    sartoriE.erase(1);
    sartoriE.draw();
    sartoriE.erase(7);
    sartoriE.draw();






    //Emplace test

    std::cout << "sartoriBis after emplace of (20,20)" << std::endl;
    sartoriBis.emplace(20,20);
    std::cout << sartoriBis << std::endl;

    std::cout << "sartoriBis after emplace of (13,13): already has it and should not insert" << std::endl;
    sartoriBis.emplace(13,13);
    std::cout << sartoriBis << std::endl;

    std::cout << "sartoriBis after emplace of (std::make_pair(21,21)): should be inserted" << std::endl;
    sartoriBis.emplace(std::make_pair(21,21));
    std::cout << sartoriBis << std::endl; 

    //getters Test: we try to see what we can achieve with actually returning a reference with begin

    //uselessVariable actually does not modify anything BUT it seems it is storing a value
    //since it will still be alive even when the tree is dead
    
    auto uselessVariable = *(sartoriBis.begin());
    (*(sartoriBis.begin())).second = 10;
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
    uselessVariable.second = 3;
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;

    std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;
    std::cout << "sartoriBis BOOM!" << std::endl;

    sartoriBis.clear();

    //actually uselessVariableKey is still alive! Even though sartoriBis is clearly not
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
    std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;

    //Balance test
    std::cout << "Imbalance sartori bst" << std::endl;
    sartori.draw();
    sartori.balance();
    std::cout << "Balance sartori bst" << std::endl;
    sartori.draw();
    




    //TODO: for debugging purposes, let's just stick with key=value (just like Alberto)
    //TODO: Should we just have one big try catch block in our main?
    try{
        //Constructor with head
        bst<int, int, std::less<int>> t{1,1,std::less<int>()};
        t.insert({3,3});
        t.insert({6,6});
        std::cout << t << std::endl;

        //Constructor without head: insert should create the head: WORKS
        bst<int, int, std::less<int>> abba{1,1,std::less<int>()};
        abba.insert({2,2});
        std::cout<< abba << std::endl;

*/
        //Construct S.A.R.T.O.R.I. (Something abstract related to our recursive implementation)
        bst<int, int, std::less<int>> sartori{8,8,std::less<int>()};
        sartori.insert({3,3});
        sartori.insert({6,6});
        sartori.insert({1,1});
        sartori.insert({10,10});
        sartori.insert({7,7});
        sartori.insert({14,14});
        sartori.insert({4,4});
        sartori.insert({13,13});
        sartori.insertOrUpdate({13,13});

        std::cout << "Sartori" << std::endl;
        sartori.draw();
/*
        std::cout << sartori[9] << std::endl;
        //std::cout << sartori[60] << std::endl;
        //std::cout<< sartori << std::endl;

        //Copy constructor test-case
        bst<int, int, std::less<int>> sartoriBis{sartori};
        std::cout << "Sartori bis" << std::endl;
        std::cout<< sartoriBis << std::endl;
        sartoriBis.isThere(8);

        sartoriBis.insert({5,5});
        std::cout << "SartoriBis after insert on sartoriBis" << std::endl;
        std::cout<< sartoriBis << std::endl;

        std::cout << "Sartori after insert on sartoriBis" << std::endl;
        std::cout<< sartori << std::endl;

        //Clear test
        std::cout << "t after t.clear()" << std::endl;
        t.clear();
        std::cout<< t << std::endl;

        //Copy assignment test
        std::cout << "sartoriBis after sartoriBis = sartori " << std::endl;
        sartoriBis = sartori;
        std::cout << sartoriBis << std::endl;

        //Move constructor test

        std::cout << "sartoriTris after sartoriTris{std::move(sartoriBis)}" << std::endl;
        bst<int,int,std::less<int>> sartoriTris{std::move(sartoriBis)};
        std::cout << sartoriTris << std::endl;
        
        std::cout << "sartoriBis after sartoriTris{std::move(sartoriBis)} ? " << std::endl;
        std::cout << sartoriBis << std::endl;

        //Move assignment test

        std::cout << "sartoriBis after sartoriBis = std::move(sartoriTris)" << std::endl;
        sartoriBis = std::move(sartoriTris);
        std::cout << sartoriBis << std::endl;
        
        std::cout << "sartoriTris after sartoriBis = std::move(sartoriTris) ? " << std::endl;
        std::cout << sartoriTris << std::endl;

        //Emplace test

        std::cout << "sartoriBis after emplace of (20,20)" << std::endl;
        sartoriBis.emplace(20,20);
        std::cout << sartoriBis << std::endl;

        std::cout << "sartoriBis after emplace of (13,13): already has it and should not insert" << std::endl;
        sartoriBis.emplace(13,13);
        std::cout << sartoriBis << std::endl;

        std::cout << "sartoriBis after emplace of (std::make_pair(21,21)): should be inserted" << std::endl;
        sartoriBis.emplace(std::make_pair(21,21));
        std::cout << sartoriBis << std::endl;    

        //getters Test: we try to see what we can achieve with actually returning a reference with begin

        //uselessVariable actually does not modify anything BUT it seems it is storing a value
        //since it will still be alive even when the tree is dead
        
        // auto uselessVariable = *(sartoriBis.begin());
        // (*(sartoriBis.begin())).second = 10;
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
        // uselessVariable.second = 3;
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;

        // std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;
        // std::cout << "sartoriBis BOOM!" << std::endl;

        // sartoriBis.clear();

        // //actually uselessVariableKey is still alive! Even though sartoriBis is clearly not
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
        // std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;

        // Let's build the upside-down tree!

        bst<int, int, std::greater<int>> irotras{8,8,std::greater<int>()};
        irotras.insert({3,3});
        irotras.insert({6,6});
        irotras.insert({1,1});
        irotras.insert({10,10});
        irotras.insert({7,7});
        irotras.insert({14,14});
        irotras.insert({4,4});
        irotras.insert({13,13});

        std::cout << "irotras" << std::endl;
        std::cout<< irotras << std::endl;

    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception occured" << std::endl;
        return 2;
    }

*/
    return 0;
    
}


