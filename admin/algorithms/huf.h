#pragma once
#include <string.h>

struct node {
	char data;
	int freq;
	node* left, * right;
};

node*  build_huf_tree(string str);
string write_encoded_ascii(string& encodedText);
void   create_tree_string(node* currentNode, int index, char* charset, int* freq, int& treeSize);

string huf_encode_string(node* root, string str);
string huf_dencode_string(node* root, string str);
