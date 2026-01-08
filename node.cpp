#include "header.hpp"


// Constructor for leaf nodes which sit at the ends
    node::node(char c, int f)
    {
        character = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }

// Constructor for internal nodes
    node::node(node* L, node* R){
        left = L;
        right = R;
        freq = L->freq + R->freq;
    }
