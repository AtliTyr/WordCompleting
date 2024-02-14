#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "Trie.h"
#include "WordInput.h"

extern string FileName;

// ������ ��� ���������� � �������
void AddToDictDialog(fstream& file, TrieNode* root, string newWord)
{
	char cont;
	cout << "����� \"" << newWord << "\" ����������� � �������.\n������ �������� ��� � �������?";
	cout << "������� 'y' ���� ��������: ";

	cin >> cont;
	if (cont != 'y')
		return;

	file << "\n";
	file << newWord;
	insert(root, newWord);

}

// ������ , ������� �������� � �������� ���������
void StartDialog()
{
	cout << "\n������� �������: \n";
	cout << "Enter - \"������������� �����\" \n";
	cout << "Backspace - \"������� ��������� �������� ������\" \n";
	cout << "0 - \"��������� ���������\" \n";

	cout << "������� ����� ������� ����� ����������...";
}

// �������� ���� ���������
void MainCycle(TrieNode* root)
{
	fstream f(FileName, ios_base::out | ios_base::app);

	WordInput word;
	char s = ' ';
	string w;

	while (s != '0')
	{
		s = _getch();

		if (s == '0')
			break;


		word.insert(s);

		system("cls");

		if (s == '\r')
		{
			if (wordCompleting(root, w) == "")
			{
				/*w = wordCompleting(root, w);*/
				AddToDictDialog(f, root, w);
			}
			w = (wordCompleting(root, w));


			word.setStr(w);
		}
		else
			w = word.getString();
		cout << w;

		display(root, w);

	}

	f.close();
}

// ���������� ������ �� �����, ��������� ��� �����
void FillingDictionary(TrieNode* root)
{
	fstream f(FileName, ios_base::in | ios_base::out);

	if (f.is_open())
	{
		TrieInit(f, root);
	}
	f.close();
}