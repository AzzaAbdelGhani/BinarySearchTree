#include <bst.hpp>

int main(){
    try{ 
        std::cout << "Four trees built through all possibile ctor" << std::endl << std::endl;
        std::cout << "In general we are building trees with key = value" << std::endl << std::endl;

        std::cout << "Basic tree default ctor" << std::endl;
        std::cout << "insert function used" << std::endl;
        bst<int, int> tree;
        tree.insert({8,8});
        tree.insert({3,3});
        tree.insert({6,6});
        tree.insert({1,1});
        tree.insert({10,10});
        tree.insert({7,7});
        tree.insert({14,14});
        tree.insert({4,4});
        tree.insert({13,13});
        tree.draw();
        std::cout << std::endl;

        std::cout << "Students tree with only compare operator in the ctor" << std::endl;
        std::cout << "emplace function used with (k,v) or std::make_pair(k,v) " << std::endl;
        bst<std::string, std::string> studentsTree{std::less<std::string>()};
        studentsTree.emplace("Rossi","Rossi");
        studentsTree.emplace("Verdi","Verdi");
        studentsTree.emplace("Bianchi","Bianchi");
        studentsTree.emplace(std::make_pair("Solomita","Solomita"));
        studentsTree.emplace(std::make_pair("Brand","Brand"));
        studentsTree.emplace(std::make_pair("Abdalgh","Abdalgh"));
        studentsTree.draw();
        std::cout << std::endl;

        std::cout << "Cleared the basic tree. Now the tree is:" << std::endl;
        tree.clear();
        std::cout << tree << std::endl << std::endl;

        std::cout << "Basic tree with the head and the greater compare operator" << std::endl;
        std::cout << "[] operator used" << std::endl;
        bst<int, int, std::greater<int>> eert{8,8,std::greater<int>()};
        eert[3] = 3;
        eert[6] = 6;
        eert[1] = 1;
        eert[10] = 10;
        eert[7] = 7;
        eert[14] = 14;
        eert[4] = 4;
        eert[13] = 13;
        eert.draw();
        std::cout << std::endl;

        std::cout << "Another basic tree equal to the first one that I've just cleared" << std::endl;
        std::cout << "Ctor with all the parameters and insertOrUpdate function used in the last value" << std::endl;
        bst<int, int> treeBis{8,8,std::less<int>()};;
        treeBis.insert({3,3});
        treeBis.insert({6,6});
        treeBis.insert({1,1});
        treeBis.insert({10,10});
        treeBis.insert({7,7});
        treeBis.insert({14,14});
        treeBis.insert({4,4});
        treeBis.insert({13,13});
        if(!treeBis.insert({13,13}).second)
            treeBis[13]=13;
        treeBis.draw();
        std::cout << std::endl;

        std::cout << "Copy ctor unbalancedStudentsTree{studentsTree}" << std::endl;
        bst<std::string, std::string> unbalancedStudentsTree{studentsTree};
        std::cout << "Students tree: " << studentsTree << std::endl;
        std::cout << "Unbalanced students tree: " << unbalancedStudentsTree << std::endl << std::endl;
        std::cout << "Insert a value -> unbalancedStudentsTree.insert({'Scordo','Scordo'})" << std::endl;
        std::cout << "Now the tree is unbalanced" << std::endl;
        unbalancedStudentsTree.insert({"Scordo","Scordo"});
        std::cout << "Students tree: " << studentsTree << std::endl;
        std::cout << "Unbalanced students tree" << std::endl;
        unbalancedStudentsTree.draw();
        std::cout << std::endl;

        std::cout << "Using the balance function" << std::endl;
        unbalancedStudentsTree.balance();
        unbalancedStudentsTree.draw();
        std::cout << std::endl;

        std::cout << "Copy assignment tree = treeBis" << std::endl;
        tree = treeBis;
        std::cout << "tree: " << tree << std::endl;
        std::cout << "tree Bis: " << treeBis << std::endl;
        std::cout << "Insert a value -> tree.insert({15,15})" << std::endl;
        tree.insert({15,15});
        std::cout << "tree: " << tree << std::endl;
        std::cout << "tree Bis: " << treeBis << std::endl << std::endl;

        std::cout << "Move assignment tree = std::move(treeBis)" << std::endl;
        tree = std::move(treeBis);
        std::cout << "tree: " << tree << std::endl;
        std::cout << "tree Bis: " << treeBis << std::endl;
        std::cout << "Move assignment treeBis = std::move(basicTree)" << std::endl;
        treeBis = std::move(tree);
        std::cout << "tree: " << tree << std::endl;
        std::cout << "tree Bis: " << treeBis << std::endl << std::endl;

        std::cout << "Move ctor treeTris{std::move(treeBis)}" << std::endl;
        bst<int, int> treeTris{std::move(treeBis)};
        std::cout << "tree Tris: " << treeTris << std::endl;
        std::cout << "tree Bis: " << treeBis << std::endl << std::endl;


        std::cout << "Testing on treeTris the erase function in every possibile case (without considerung the root)" << std::endl;
        std::cout << "tree tris" << std::endl;
        treeTris.draw();
        std::cout << std::endl;
        std::cout << "Delete a key that does not exist -> treeTris.erase(20)" << std::endl;
        treeTris.erase(20);
        std::cout << std::endl;
        std::cout << "Delete a generic node with 2 children -> treeTris.erase(3)" << std::endl;
        treeTris.erase(3);
        treeTris.draw();
        std::cout << std::endl;
        std::cout << "Delete a generic node with only left child -> treeTris.erase(14)" << std::endl;
        treeTris.erase(14);
        treeTris.draw();
        std::cout << std::endl;
        std::cout << "Delete a generic node with only right child -> treeTris.erase(10)" << std::endl;
        treeTris.erase(10);
        treeTris.draw();
        std::cout << std::endl;
        std::cout << "Delete a generic leaf that is left child -> treeTris.erase(1)" << std::endl;
        treeTris.erase(1);
        treeTris.draw();
        std::cout << std::endl;
        std::cout << "Delete a generic leaf that is right child -> treeTris.erase(7)" << std::endl;
        treeTris.erase(7);
        treeTris.draw();
        std::cout << std::endl;

        std::cout << "Testing on a tree the erase function in every possibile root case" << std::endl;
        
        std::cout << "t1" << std::endl;
        bst<int, int> t1{8,8,std::less<int>()};
        t1.insert({3,3});
        t1.draw();
        std::cout << std::endl;

        std::cout << "Delete the root with left child -> t1.erase(8)" << std::endl;
        t1.erase(8);
        t1.draw();
        std::cout << std::endl;

        std::cout << "t2" << std::endl;
        bst<int, int> t2{8,8,std::less<int>()};
        t2.insert({10,10});
        t2.draw();
        std::cout << std::endl;

        std::cout << "Delete the root with right child -> t2.erase(8)" << std::endl;
        t2.erase(8);
        t2.draw();
        std::cout << std::endl;
        
        std::cout << "t3" << std::endl;
        bst<int, int> t3{8,8,std::less<int>()};
        t3.insert({3,3});
        t3.insert({10,10});
        t3.draw();
        std::cout << std::endl;

        std::cout << "Delete the root with 2 children -> t3.erase(8)" << std::endl;
        t3.erase(8);
        t3.draw();
        std::cout << std::endl;

        auto it = t3.find(3);
        (*it).second = 4;
        std::cout << (*it).second << std::endl;

    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception occured" << std::endl;
        return 2;
    }
    return 0;   
}


