#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

struct node {
	char data;
	int freq;
	node* left, * right;
};

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

// ordonarea heap-ului ; caracterul cu cea mai mica frecventa are o prioritate mai mare
struct comparison {
	bool operator()(node* left, node* right)
	{
		return left->freq > right->freq;
	}
};

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
void decode(node* root, int& counter, string str)
{
	if (root == nullptr)
	{
		return;
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << root->data;
		return;
	}
	counter++;
	if (str[counter] == '0')
		decode(root->left, counter, str);
	else
		decode(root->right, counter, str);
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

	cout << "Pentru sirul \"" << str << "\" ,codurile sunt : " << endl;
	for (auto it : HuffmanCodes)
	{
		cout << it.first << ' ' << it.second << endl;
	}
	cout << endl;

	string textToPrint = "";
	for (char ch : str)
	{
		encodedText += HuffmanCodes[ch];
		textToPrint += HuffmanCodes[ch];
		textToPrint += " ";
	}
	cout << "Encoded string: " << textToPrint << endl << endl;
}

void HuffmanDecode(node* root, string str)
{
	int index = -1;
	cout << "Decoded string is: ";
	while (index < (int)str.size() - 1)
	{
		decode(root, index, str);
	}
	cout << endl;
}

int main()
{
	string str = "Acest text este codificat Huffman.";
	string encodedString = "";
	node* root = buildHuffmanTree(str);
	HuffmanEncode(root, str, encodedString);
	HuffmanDecode(root, encodedString);
	return 0;
}