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

	// ��������� ������ � str
	void insert(char);

	// ���������� ������, ���������� � str
	string getString() const;
		
	// ����� str �� �������� ������
	void setStr(string);
};

