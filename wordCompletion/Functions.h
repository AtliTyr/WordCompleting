#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "Trie.h"
#include "WordInput.h"

extern string FileName;

// Диалог для добавления в словарь
void AddToDictDialog(fstream& file, TrieNode* root, string newWord)
{
	char cont;
	cout << "Слово \"" << newWord << "\" отсутствует в словаре.\nХотите добавить его в словарь?";
	cout << "Введите 'y' если согласны: ";

	cin >> cont;
	if (cont != 'y')
		return;

	file << "\n";
	file << newWord;
	insert(root, newWord);

}

// Диалог , который знакомит с горячими клавишами
void StartDialog()
{
	cout << "\nГорячие клавиши: \n";
	cout << "Enter - \"Автодополнить слово\" \n";
	cout << "Backspace - \"Стереть последний введённый символ\" \n";
	cout << "0 - \"Завершить программу\" \n";

	cout << "Нажмите любую клавишу чтобы продолжить...";
}

// Основной цикл программы
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

// Заполнение дерева из файла, хранящего все слова
void FillingDictionary(TrieNode* root)
{
	fstream f(FileName, ios_base::in | ios_base::out);

	if (f.is_open())
	{
		TrieInit(f, root);
	}
	f.close();
}