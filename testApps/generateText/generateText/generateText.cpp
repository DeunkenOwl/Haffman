

#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	//количество символов
	int n = 10000;
	ofstream output("input", ios_base::out | ios_base::trunc | ios_base::binary);
	char ch;
	for (int i = 0; i < n; i++) {
		ch = rand() % 94 + 33;
		output << ch;
	}
	return 0;
}
