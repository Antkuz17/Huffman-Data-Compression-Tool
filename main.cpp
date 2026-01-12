#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "header.hpp"
#include <fstream>

int main () {
    std::cout << "Enter a sentence" << std::endl;

    // This stores all our nodes
    std::vector<node*> nodes;

    // Opening the txt file
    std::ifstream inputfile("INPUT TEXT HERE\\text.txt");

    // String holding our word
    std::string word;

    // Temporary line holder
    std::string line;

    // Hashmap for counting the frequency of letters
    // Hashmaps are iterable in c++ so this is already fire
    std::unordered_map<char, int> counter;

    // Total number of characters
    int numChars{0};

    // We assume that we will have only generic charaters so no crazy odd characters
    if (inputfile.is_open()) {
    while (std::getline(inputfile, line)) {
        std::cout << line << std::endl;
    }
        inputfile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
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

    std::vector<node*> leafNodes = nodes;

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

        


        // Now the tree is built we can move to traversing it to generate codes
        // The way im doing is im gonna store every code in a hashmap with char as key and array as value

    
    }
    std::cout << "Nodes remaining: " << nodes.size() << std::endl;

    preOrder(nodes[0], "");

    // At this point all the codes should be generated and stored in the nodes
    // Now we must just provide the conversion from original to encoded
    // I will also show the memory savings here
    std::string encodedString{""};
    for(char x: word){
        // Find its code
        for(node* n: leafNodes){
            if(n->getChar() == x){
                encodedString += n->getCode();
                break;
            }
        }
    }
    std::cout << "Encoded string: " << encodedString << std::endl;
    std::cout << "Original size (in bits): " << word.length() * 8 << std::endl;
    std::cout << "Encoded size (in bits): " << encodedString.length() << std::endl;

    //g++ main.cpp node.cpp -o test.exe ; .\test.exe
    
    return 0;
}

void preOrder(node* root, std::string codeCurrent){
    if(root == nullptr){
        return;
    }

    if(root->getLeft() == nullptr && root->getRight() == nullptr){
        root->setCode(codeCurrent);
        std::cout << root->getChar() << ": " << root->getCode() << std::endl;
    }

    preOrder(root->getLeft(), codeCurrent + "0");
    preOrder(root->getRight(), codeCurrent + "1");
}

