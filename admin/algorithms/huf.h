#pragma once
#include <string.h>

struct node {
	char data;
	int freq;
	node* left, * right;
};

node*  build_huf_tree(std::string str);
std::string write_encoded_ascii(std::string& encodedText);
void   create_tree_string(node* currentNode, int index, char* charset, int* freq, int& treeSize);

std::string huf_encode_string(node* root, std::string str);
std::string huf_decode_string(node* root, std::string str);
