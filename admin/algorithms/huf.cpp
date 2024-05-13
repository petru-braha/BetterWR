/**
#include <unordered_map>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include "huf.h"

using namespace std;

///build
struct comparison { // order my queue
	bool operator()(node* left, node* right)
	{
		return left->freq > right->freq;
	}
};

node* newNode(char character, int frequency)
{
	node* nod = new node;
	nod->data = character;
	nod->freq = frequency;
	nod->left = nullptr;
	nod->right = nullptr;
	return nod;
}

unordered_map<char, int> compute_frequencies(string str)
{
	unordered_map<char, int> freq;
	for (char ch : str)
		freq[ch]++;
	return freq;
}

priority_queue<node*, vector<node*>, comparison> create_queue(unordered_map<char, int> freq)
{
	priority_queue<node*, vector<node*>, comparison> q;
	for (auto it : freq)
		q.push(newNode(it.first, it.second));
	return q;
}

node* build_huf_tree(string str)
{
	unordered_map<char, int> freq_map = compute_frequencies(str);
	priority_queue<node*, vector<node*>, comparison> pr_queue = create_queue(freq_map);
	while (pr_queue.size() != 1)
	{
		// eliminam primele doua noduri cu frecventa cea mai mica din coada, urmand sa le folosim pentru a crea un nou nod
		// noul nod va fi parintele celor doua noduri eliminate, avand frecventa egala cu suma frecventelor fiilor acestuia
		// nodul creat va fi adaugat in final inapoi in coada

		node* left = pr_queue.top();
		pr_queue.pop();
		node* right = pr_queue.top();
		pr_queue.pop();

		int newNodeFrequency = left->freq + right->freq;
		node* p = newNode('$', newNodeFrequency);
		p->left = left;
		p->right = right;
		pr_queue.push(p);
	}
	node* root = pr_queue.top();
	return root;
}

///compress
string write_encoded_ascii(string& encodedText)
{
	// Convertim sirul binar in zecimal si scriem rezultatul in output file
	size_t encodedLength = encodedText.size();
	string asciiString = "";

	// Convert binary to decimal
	for (size_t i = 0; i < encodedLength; i += 8) {
		string byte = encodedText.substr(i, 8); // Luam fiecare 8-bit chunk
		while (byte.length() < 8)
			byte += "0";
		int decimalValue = stoi(byte, nullptr, 2); // Convert binary to decimal
		asciiString += (char)decimalValue;
	}

	return asciiString;
}

//stocarea informatiilor necesare reconstruirii arborelui Huffman
void create_tree_string(node* currentNode, int index, char* charset, int* freq, int& treeSize) {
	treeSize = max(treeSize, index);
	if (currentNode == nullptr)
	{
		charset[index] = 0;
		freq[index] = -1;
		return;
	}

	charset[index] = currentNode->data;
	freq[index] = currentNode->freq;

	create_tree_string(currentNode->left, index * 2, charset, freq, treeSize);
	create_tree_string(currentNode->right, index * 2 + 1, charset, freq, treeSize);
}

void encode(node* root, string str, unordered_map<char, string>& huffmanCodes)
{
	if (root == nullptr)
		return;

	if (root->left == nullptr && root->right == nullptr)
		huffmanCodes[root->data] = str;

	encode(root->left, str + "0", huffmanCodes);
	encode(root->right, str + "1", huffmanCodes);
}

string huf_encode_string(node* root, string str)
{
    string encoded_text = "";
	unordered_map<char, string> HuffmanCodes;
	encode(root, "", HuffmanCodes);
	for (char ch : str)
		encoded_text += HuffmanCodes[ch];
    return encoded_text;
}

///decompress
string ascii_to_binary(string& asciiString, int maxBytes)
{
	size_t asciiLength = asciiString.size();
	string binaryString = "";
	for (char c : asciiString) {
		binaryString += bitset<8>(c).to_string();
	}

	string str = binaryString.substr(0, maxBytes);
	return str;
}

// functie de reconstruire a arborelui Huffman, avand ca date de input continutul fisierului encodat
node* reconstructTree(int treeSize, int index, char* treeInfo, int* treeFreq)
{
	if (index > treeSize || treeFreq[index] < 0)
		return nullptr;

	node* newTreeNode = new node;
	newTreeNode->freq = treeFreq[index];
	newTreeNode->data = treeInfo[index];
	newTreeNode->left = reconstructTree(treeSize, index * 2, treeInfo, treeFreq);
	newTreeNode->right = reconstructTree(treeSize, index * 2 + 1, treeInfo, treeFreq);

	return newTreeNode;
}

void decode(node* root, int& counter, string str, string& decodedOutput)
{

	if (root == nullptr)
	{
		return;
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		decodedOutput+= root->data;
		return;
	}
	counter++;
	if (str[counter] == '0')
		decode(root->left, counter, str, decodedOutput);
	else
		decode(root->right, counter, str, decodedOutput);
}

string huf_dencode_string(node* root, string str)
{
    string decodedOutput = "";
	int index = -1;
	while (index < (int)str.size() - 1)
		decode(root, index, str, decodedOutput);
    return decodedOutput;
}

*/
