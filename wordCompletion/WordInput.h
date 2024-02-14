#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class WordInput
{
private:
	vector<char> str;

public:

	WordInput() = default;
	~WordInput() = default;

	// Дополняет строку в str
	void insert(char);

	// Возвращает строку, хранящуюся в str
	string getString() const;
		
	// Задаёт str по входящей строке
	void setStr(string);
};

