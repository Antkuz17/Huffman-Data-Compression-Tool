#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "header.hpp"

int main () {
    std::cout << "Enter a sentence" << std::endl;

    // This stores all our nodes
    std::vector<node*> nodes;

    // String holding our word
    std::string word;

    std::cin >> word;

    // Hashmap for counting the frequency of letters
    // Hashmaps are iterable in c++ so this is already fire
    std::unordered_map<char, int> counter;

    // We assume that we will have only generic charaters so no crazy odd characters
    for (char x : word) {
        counter[x]++;
    }

    // Debugging print function
    for (const auto& pair : counter) {
    std::cout << pair.first << " " << pair.second << std::endl;
    }

    // Now we have all the frequency data in a hashmap
    for (const auto& pair : counter) {
        node* leafNode = new node(pair.first, pair.second);
        nodes.push_back(leafNode);
    }
    int lowestIndex = -1;
    int secondLowestIndex = -1;

    // This is where we build the tree
    // We keep going till there is only one node left since that is the root
    while(nodes.size() > 1){

        // Tracks the lowest current frequencies
        lowestIndex = -1;
        secondLowestIndex = -1;

        // Here we loop and find lowest, should be using priority queue instead for 0 n log n time but for now its okay
        for(int i{0}; i < nodes.size(); i++){
            // If we are just starting to search or we found a new lowest
            if(lowestIndex == -1 || nodes[i]->getFreq() < nodes[lowestIndex]->getFreq()){
                lowestIndex = i;
            }
        }

        for(int i{0}; i < nodes.size(); i++){    
            if (i != lowestIndex && (secondLowestIndex == -1 || nodes[i]->getFreq() < nodes[secondLowestIndex]->getFreq())){
                secondLowestIndex = i;
            }
        }

        // Now we have the two lowest frequencies, we create a new internal node
        node* internalNode = new node(nodes[lowestIndex], nodes[secondLowestIndex]);
        nodes.push_back(internalNode);

        // Depending on the order, we erase in a differnt order to conserve position
        if(lowestIndex < secondLowestIndex){
            nodes.erase(nodes.begin() + secondLowestIndex);
            nodes.erase(nodes.begin() + lowestIndex);
        }
        else{
            nodes.erase(nodes.begin() + lowestIndex);
            nodes.erase(nodes.begin() + secondLowestIndex);
        }
    
    }

    //g++ main.cpp node.cpp -o test.exe ; .\test.exe
    


    return 0;
}

