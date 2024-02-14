#include <iostream>
#include "Trie.h"
#include "Functions.h"
//#include "WordInput.h"
//#include <conio.h>
//#include <Windows.h>

string FileName;

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	TrieNode* root = new TrieNode();
	FileName = "Input.txt";


	FillingDictionary(root);

	StartDialog();

	MainCycle(root);

	delete root;

	return 0;
}