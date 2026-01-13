#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "header.hpp"
#include <fstream>

int main () {
    // This stores all our nodes
    std::vector<node*> nodes;

    // Json file to write the tree structure
    std::ofstream binTree("Output text\\huffman_tree.json");

    // Write the opening brace for the JSON object
    binTree << "{\n  \"huffman_tree\": ";

    // Opening the txt file
    std::ifstream inputfile("Input text\\text.txt");

    // String holding our word
    std::string word;

    // Temporary line holder
    std::string line;

    // File we will write to 
    std::ofstream outfile("Output text\\data.bin", std::ios::binary);

    // Hashmap for counting the frequency of letters
    // Hashmaps are iterable in c++ so this is already fire
    std::unordered_map<char, int> counter;

    // Total number of characters
    int numChars{0};

    // We assume that we will have only generic charaters so no crazy odd characters
    if (inputfile.is_open()) {
    while (std::getline(inputfile, line)) {
        word += line; // Append line to word
        for (char x : line) {

            // Only count standard ASCII characters
            if (x >= 0 && x <= 127) {
                word += x;
                numChars++;
                counter[x]++;
            }
        }
    }
        inputfile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
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
    preOrder(nodes[0], "");

    // At this point all the codes should be generated and stored in the nodes
    // Now we must just provide the conversion from original to encoded
    // I will also show the memory savings here
    std::string encodedString{""};
    for(char x: word){
        // Find its code
        for(node* n: leafNodes){
            if(n->getChar() == x){
                outfile.write(n->getCode().c_str(), n->getCode().size());
                encodedString += n->getCode();
                break;
            }
        }
    }

    //g++ main.cpp node.cpp -o test.exe ; .\test.exe

    writeJSON(nodes[0], binTree, 2);
    binTree << "\n}";
    binTree.close();

    outfile.close();
    
    return 0;
}

void preOrder(node* root, std::string codeCurrent){
    if(root == nullptr){
        return;
    }

    if(root->getLeft() == nullptr && root->getRight() == nullptr){
        root->setCode(codeCurrent);
    }

    preOrder(root->getLeft(), codeCurrent + "0");
    preOrder(root->getRight(), codeCurrent + "1");
}

void writeJSON(node* root, std::ofstream& outfile, int indent) {
    std::string indentation(indent, ' ');
    
    // Base case
    if (root == nullptr) {
        outfile << "null";
        return;
    }
    
    outfile << "{\n";
    // Write character
    if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        outfile << indentation << "  \"char\": \"" << root->getChar() << "\",\n";
    } else {
        outfile << indentation << "  \"char\": null,\n";
    }
    
    // Write frequency
    outfile << indentation << "  \"freq\": " << root->getFreq();
    
    // Write code if it's a leaf node
    if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        outfile << ",\n" << indentation << "  \"code\": \"" << root->getCode() << "\"";
    }
    
    // Write left child
    if (root->getLeft() != nullptr) {
        outfile << ",\n" << indentation << "  \"left\": ";
        writeJSON(root->getLeft(), outfile, indent + 2);
    }
    
    // Write right child
    if (root->getRight() != nullptr) {
        outfile << ",\n" << indentation << "  \"right\": ";
        writeJSON(root->getRight(), outfile, indent + 2);
    }
    
    outfile << "\n" << indentation << "}";
}

