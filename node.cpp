class node{
    private:
        node* left{nullptr};
        node* right{nullptr};
        char character{};
        int freq{0};
    public:

    // Constructor for leaf nodes which sit at the ends
        node(char c, int f)
        {
            character = c;
            freq = f;
        }

    // Constructor for internal nodes
        node(node* L, node* R){
            left = L;
            right = R;
            freq = L->freq + R->freq;
        }

}