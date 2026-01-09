# Huffman Data Encoder

Basic text compression using Huffman coding in C++. Builds a binary tree from character frequencies and assigns variable-length codes to compress data.

## How It Works

### Variable-Length Encoding
Unlike ASCII encoding which uses a fixed 8 bits for every character, Huffman coding uses variable-length codes. Characters that appear more frequently get shorter codes, while rare characters get longer codes. This is what enables compression.

### Algorithm Overview
Count the frequency of each character in the text, build a binary tree using a greedy algorithm that combines the two lowest-frequency nodes repeatedly, traverse the tree to assign binary codes (left = 0, right = 1), then encode the text using these codes.

### Example: Building the Tree

Let's say we have five letters with these frequencies:
```
a: 15%
b: 20%
c: 20%
d: 10%
e: 35%
```

After building the tree by repeatedly combining the two lowest frequencies, the final codes are:
```
d: 000
a: 001
e: 01
b: 10
c: 11
```

Notice how 'e' (35% frequency) gets a short 2-bit code, while 'd' (10% frequency) gets a longer 3-bit code.

## Performance

This is a very small set of test letters. Using standard English text, the difference becomes much more clear. I tested the algorithm by copying text from various online articles and found that on average, it achieved approximately 40% better space efficiency compared to standard ASCII encoding (which uses 8 bits per character).

## Implementation Notes

I know that a priority queue (min-heap) is more efficient than a vector for this algorithm. However, since this program only considers the English alphabet, common punctuation, and a few other characters, a vector works just as well. The dataset is small enough that the performance difference between O(n²) and O(n log n) is negligible for practical purposes.

## Note: This was a confusion I had when I first learned about this algorithm - why the codes can't be ambiguous

Because we use a binary tree where all characters are leaf nodes, there can never be ambiguity when decoding. 

For example, you'll never have a situation like:
```
a: 0
b: 1  
c: 01
```

If you received `010`, would that be "aba" or "ca"? This confusion cannot happen with Huffman coding because having `c: 01` would imply that 'c' is a child node of 'a', which is impossible since all characters are leaf nodes. No character's code can be a prefix of another character's code, making the encoding uniquely decodable.