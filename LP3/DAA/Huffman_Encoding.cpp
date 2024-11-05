#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
class Node
{
public:
    char data;
    int frequency;
    Node *left;
    Node *right;
    Node(char, int);
};
Node::Node(char data, int frequency)
{
    left = NULL;
    right = NULL;
    this->data = data;
    this->frequency = frequency;
}

struct Compare
{
    bool operator()(Node *left, Node *right)
    {
        return left->frequency > right->frequency;
    }
};
class Huffman
{
public:
    Node *root;
    unordered_map<char, string> huffmanCodes;
    void printCodes(Node *, const string &);
    Huffman();
    void buildTree(const string &);
    void encode(const string &);
};

void Huffman::printCodes(Node *node, const string &code)
{
    if (!node)
    {
        return;
    }
    if (!node->left && !node->right)
    {
        huffmanCodes[node->data] = code;
        cout << node->data << ": " << code << endl;
    }
    printCodes(node->left, code + "0");
    printCodes(node->right, code + "1");
}

Huffman::Huffman()
{
    root = NULL;
}

void Huffman::buildTree(const string &text)
{
    unordered_map<char, int> ump;
    for (char t : text)
    {
        ump[t]++;
    }
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (const auto &p : ump)
    {
        pq.push(new Node(p.first, p.second));
    }
    while (pq.size() > 1)
    {
        Node *l = pq.top();
        pq.pop();
        Node *r = pq.top();
        pq.pop();
        Node *newN = new Node('\0', l->frequency + r->frequency);
        newN->left = l;
        newN->right = r;
        pq.push(newN);
    }
    root = pq.top();
    printCodes(root, "");
}

void Huffman::encode(const string &text)
{
    if (!root)
    {
        cout << "Huffman Tree is not built yet.\n";
        return;
    }
    cout << "\nEncoded string: ";
    for (char ch : text)
    {
        cout << huffmanCodes[ch];
    }
    cout << endl;
}

int main()
{
    string text;
    cout << "Enter text to encode using Huffman Encoding: ";
    getline(cin, text);
    Huffman huffman;
    huffman.buildTree(text);
    huffman.encode(text);
    return 0;
}