class node{
    
    private:
        node* left;
        node* right;
        char character;
        int freq;
    public:
        node(char c, int f); 
        node(node* L, node* R); 
        char getChar(){return character;};
        int getFreq(){return freq;}; 
};

