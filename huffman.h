#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

struct node {
	char data;
	int freq;
	node* left, * right;
};

// ordonarea heap-ului ; caracterul cu cea mai mica frecventa are o prioritate mai mare
struct comparison {
	bool operator()(node* left, node* right)
	{
		return left->freq > right->freq;
	}
};

node* newNode(char character, int frequency);
void encode(node* root, string str, unordered_map<char, string>& huffmanCodes);
void decode(node* root, int& counter, string str, string& decodedOutput);
unordered_map<char, int> computeFrequencies(string str);
priority_queue<node*, vector<node*>, comparison> createQueue(unordered_map<char, int>freq);
node* buildHuffmanTree(string str);
void HuffmanEncode(node* root, string str, string& encodedText);
void HuffmanDecode(node* root, string str, string& decodedOutput);
string writeEncodedDataToFile(string& encodedText);
string ASCIIToBinary(string& asciiString, int maxBytes);
void createTreeString(node* currentNode, int index, char* charset, int* freq, int& treeSize);
node* reconstructTree(int treeSize, int index, char* treeInfo, int* treeFreq);
