
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct hafmanTreeNode{
	int pot = 0;
	char ch;
	hafmanTreeNode* left;
	hafmanTreeNode* right;
};

struct transcr {
	vector<bool> code;
	char ch;
};

void getDictionary(hafmanTreeNode* node, vector<transcr> &dictionary, vector<bool> code, unsigned int pos = 0) {
	
	if (node->ch >= 0) {
		dictionary.resize(dictionary.size() + 1);
		dictionary[dictionary.size() - 1].code = code;
		dictionary[dictionary.size() - 1].ch = node->ch;
	}
	else {
		code.push_back(false);
		if (node->left != NULL)
			getDictionary(node->left, dictionary, code, pos + 1);
		code[pos] = true;
		if (node->right != NULL)
			getDictionary(node->right, dictionary, code, pos + 1);
	}
}

void insertionSort(vector<hafmanTreeNode*> &vec, unsigned int l, unsigned int r) {
	if (l == r)
		return;
	unsigned int m = ceil((l + r) / 2);
	insertionSort(vec, l, m);
	insertionSort(vec, m + 1, r);
	unsigned int i = l;
	unsigned int j = m + 1;
	vector<hafmanTreeNode*> temp;
	while (i <= m && j <= r) {
		if (vec[i]->pot > vec[j]->pot) {
			temp.push_back(vec[i]);
			i++;
		}
		else {
			temp.push_back(vec[j]);
			j++;
		}
	}
	while (i <= m) {
		temp.push_back(vec[i]);
		i++;
	}
	while (j <= r) {
		temp.push_back(vec[j]);
		j++;
	}
	i = 0;
	j = l;
	while (i < temp.size()) {
		vec[j] = temp[i];
		i++;
		j++;
	}
}


int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	vector<char> text;
	vector<unsigned int> chCount;
	char ch;
	while (!input.eof()) {
		input >> ch;
		if (ch >= chCount.size()) {
			chCount.resize(ch + 1);
		}
		chCount[ch]++;
		text.push_back(ch);
	}
	chCount[ch]--;
	text.erase(text.end() - 1);
	vector<hafmanTreeNode*> hafVec;
	for (int i = 0; i < chCount.size(); i++) {
		if (chCount[i] > 0) {
			hafmanTreeNode* node = new hafmanTreeNode;
			node->pot = chCount[i];
			node->ch = i;
			hafVec.push_back(node);
		}
	}
	
	insertionSort(hafVec, 0, hafVec.size() - 1);

	/*for (int i = 0; i < hafVec.size(); i++) {
		cout << hafVec[i]->pot << ' ';
	}
	cout << endl;*/
	unsigned int count;
	while (hafVec.size() > 1) {
		hafmanTreeNode* node = new hafmanTreeNode;
		node->left = hafVec[hafVec.size() - 1];
		node->right = hafVec[hafVec.size() - 2];
		hafVec.erase(hafVec.end() - 1);
		hafVec.erase(hafVec.end() - 1);
		node->pot = node->left->pot + node->right->pot;
		hafVec.push_back(node);
		node = NULL;
		count = hafVec.size() - 1;
		while (count > 0 && hafVec[count - 1]->pot < hafVec[count]->pot) {
			swap(hafVec[count - 1], hafVec[count]);
		}
	}
	vector<transcr> dictionary;
	vector<bool> code;
	getDictionary(hafVec[0], dictionary, code);
	for (int i = 0; i < dictionary.size(); i++) {
		for (int j = 0; j < dictionary[i].code.size(); j++) {
			if (dictionary[i].code[j] == true)
				cout << 1;
			else
				cout << 0;
		}
		cout << dictionary[i].ch << endl;
	}
	return 0;
}
