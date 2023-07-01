#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>


int main(int argc, char** argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        BST bst {};
 
        std::cout<<"befer 10==="<<std::endl;
        std::cout<<*bst.get_root()<<" :root =="<<std::endl;

        std::cout<<"bst init: "<<bst<<std::endl;
        
        std::cout<<"10==="<<std::endl;
        bst.add_node(10);

        // std::cout<<"after 10==="<<std::endl;
        // std::cout<<*bst.get_root()<<" :root =="<<std::endl;

        // std::cout<<"20==="<<std::endl;
        // bst.add_node(20);

        // std::cout<<"after 20==="<<std::endl;
        // std::cout<<*bst.get_root()<<"=="<<std::endl;

        // std::cout<<"30==="<<std::endl;
        // bst.add_node(5);
        
        // std::cout<<"after 30==="<<std::endl;
        // std::cout<<*bst.get_root()<<"=="<<std::endl;

        // std::cout<<"size "<<bst.length()<<std::endl;

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}