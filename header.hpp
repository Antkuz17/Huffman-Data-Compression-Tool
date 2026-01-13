#include <string>
#include <fstream>


class node{
    
    private:
        node* left;
        node* right;
        char character;
        int freq;
        std::string code{};
        
    public:
        node(char c, int f); 
        node(node* L, node* R); 
        char getChar(){return character;};
        int getFreq(){return freq;}; 
        node* getLeft(){return left;};
        node* getRight(){return right;};
        void setCode(std::string c){code = c;};
        std::string getCode(){return code;};
};

void preOrder(node* root, std::string codeCurrent);
void writeJSON(node* root, std::ofstream& outfile, int indent = 0);

