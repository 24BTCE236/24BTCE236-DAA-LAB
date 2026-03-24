#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

// A Huffman tree node
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode *left, *right;

    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparison object to be used to order the priority queue (min-heap)
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // Min-heap based on frequency
    }
};

// Function to generate Huffman codes by traversing the tree
void generateCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr)
        return;

    // Found a leaf node
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
        return;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Main function to build the Huffman tree and generate codes
void buildHuffmanTree(string text) {
    // 1. Calculate character frequencies
    map<char, unsigned> frequencies;
    for (char character : text) {
        frequencies[character]++;
    }

    // 2. Create a min-priority queue and add all leaf nodes
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (auto const& [character, freq] : frequencies) {
        pq.push(new HuffmanNode(character, freq));
    }

    // 3. Build the tree by repeatedly extracting two min-freq nodes
    while (pq.size() != 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Create a new internal node with combined frequency
        HuffmanNode* parent = new HuffmanNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    // 4. Generate codes from the root of the single remaining tree
    HuffmanNode* root = pq.top();
    map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Output the generated Huffman codes
    cout << "Huffman Codes generated:\n";
    cout << "Char | Freq | Code\n";
    cout << "------------------\n";
    for (auto const& [character, code] : huffmanCodes) {
        cout << setw(4) << character << " | " << setw(4) << frequencies[character] << " | " << code << "\n";
    }

    // (Optional) Implement actual encoding and decoding here...
}

int main() {
    string input_text = "this is an example of huffman coding";
    cout << "Original text: " << input_text << "\n\n";
    buildHuffmanTree(input_text);
    return 0;
}
