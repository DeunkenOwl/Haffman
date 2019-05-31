
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//узел дерева хаффмана
struct treeNode {
	vector<bool> code;
	char ch;
	treeNode* left = NULL;
	treeNode* right = NULL;
};
//функция добавления нового символа в дерево
void add_branch(treeNode *tree, treeNode *node, int pos = 0) {
	if (pos == node->code.size() - 1) {
		if (node->code[pos]) {
			tree->right = node;
		}
		else {
			tree->left = node;
		}
	}
	else {
		
		if (node->code[pos]) {
			if (tree->right == NULL)
				tree->right = new treeNode;
			add_branch(tree->right, node, pos + 1);
		}
		else {
			if (tree->left == NULL)
				tree->left = new treeNode;
			add_branch(tree->left, node, pos + 1);
		}
		
	}
		
}

int main()
{
	
	ifstream input("input", ios_base::in | ios_base::binary);
	//считывание кодировки
	unsigned char n1, n2, ch;
	vector<treeNode*> codes;
	//размер алфавита
	input >> n1;
	while (n1 > 0) {
		//длина кода символа
		input >> n2;
		treeNode *newNode = new treeNode;
		codes.push_back(newNode);
		newNode = NULL;
		while (n2 > 0) {
			input >> ch;
			if (ch == '0')
				codes[codes.size() - 1]->code.push_back(false);
			else
				codes[codes.size() - 1]->code.push_back(true);
			n2--;
		}
		input >> codes[codes.size() - 1]->ch;
		n1--;
	}

	//проверка правильности кодов
	for (int i = 0; i < codes.size(); i++) {
		for (int j = 0; j < codes[i]->code.size(); j++)
			cout << codes[i]->code[j];
		cout << codes[i]->ch << endl;
	}

	//создание дерева
	treeNode* hafTree = new treeNode;
	for (int i = 0; i < codes.size(); i++)
		add_branch(hafTree, codes[i]);
	codes.clear();

	//расшифровка в вывод
	ofstream output("output", ios_base::out | ios_base::trunc | ios_base::binary);
	treeNode* temp = hafTree;
	while (input >> ch) {
		//обходим дерево с каждым символом
		if (ch == '0')
			temp = temp->left;
		else
			temp = temp->right;

		//если нашли символ, то записываем его в файл
		if (temp->ch >= 0) {
			output << temp->ch;
			temp = hafTree;
		}
	}
	
	input.close();
	output.close();
	return 0;
}