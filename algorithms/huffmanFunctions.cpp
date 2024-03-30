#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include "huffman.h"

using namespace std;	

// functie care creeaza un nod nou in arborele Hufmman (heap)
node* newNode(char character, int frequency)
{
	node* nod = new node;
	nod->data = character;
	nod->freq = frequency;
	nod->left = nullptr;
	nod->right = nullptr;

	return nod;
}

// traversarea arborelui Huffman si stocarea codurilor Huffman
void encode(node* root, string str, unordered_map<char, string>& huffmanCodes)
{
	if (root == nullptr)
	{
		return;
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		huffmanCodes[root->data] = str;
	}
	encode(root->left, str + "0", huffmanCodes);
	encode(root->right, str + "1", huffmanCodes);
}

// traversarea arborelui Huffman si decodarea sirului de coduri
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

// functie care numara de cate ori apare fiecare caracter si stocheaza aceste valori intr un map (hash table)
unordered_map<char, int> computeFrequencies(string str)
{
	unordered_map<char, int> freq;
	for (char ch : str)
	{
		freq[ch]++;
	}

	return freq;
}

// functie care creeaza o coada de prioritati si stocheaza in aceasta nodurile din arborele Huffman
priority_queue<node*, vector<node*>, comparison> createQueue(unordered_map<char, int>freq)
{
	priority_queue<node*, vector<node*>, comparison> q;
	for (auto it : freq)
	{
		q.push(newNode(it.first, it.second));
	}
	return q;
}

node* buildHuffmanTree(string str)
{
	unordered_map<char, int> freq_map = computeFrequencies(str);
	priority_queue<node*, vector<node*>, comparison> pr_queue = createQueue(freq_map);
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

void HuffmanEncode(node* root, string str, string& encodedText)
{
	unordered_map<char, string> HuffmanCodes;
	encode(root, "", HuffmanCodes);

	/*
	cout << "Pentru sirul \"" << str << "\" ,codurile sunt : " << endl;
	for (auto it : HuffmanCodes)
	{
		cout << it.first << ' ' << it.second << endl;
	}
	cout << endl;
	*/

	for (char ch : str)
	{
		encodedText += HuffmanCodes[ch];

	}
	//cout << "Encoded string: " << encodedText << endl << endl;
}

void HuffmanDecode(node* root, string str, string& decodedOutput)
{
	int index = -1;
	//cout << "Decoded string is: ";
	while (index < (int)str.size() - 1)
	{
		decode(root, index, str, decodedOutput);
	}
	//cout << endl;
}

string writeEncodedDataToFile(string& encodedText)
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

string ASCIIToBinary(string& asciiString, int maxBytes)
{
	size_t asciiLength = asciiString.size();
	string binaryString = "";
	for (char c : asciiString) {
		binaryString += bitset<8>(c).to_string();
	}
	
	string str = binaryString.substr(0, maxBytes);
	return str;
}

// functie pentru stocarea informatiilor necesare reconstruirii arborelui Huffman 
void createTreeString(node* currentNode, int index, char* charset, int* freq, int& treeSize) {
	treeSize = max(treeSize, index);
	if (currentNode == nullptr)
	{
		charset[index] = 0;
		freq[index] = -1;
		return;
	}

	charset[index] = currentNode->data;
	freq[index] = currentNode->freq;

	createTreeString(currentNode->left, index * 2, charset, freq, treeSize);
	createTreeString(currentNode->right, index * 2 + 1, charset, freq, treeSize);

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