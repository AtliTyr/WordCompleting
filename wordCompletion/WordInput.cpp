#include "WordInput.h"

void WordInput::insert(char ch)
{
	switch (ch)
	{
	case '\b':
		if(str.size() > 0)
			str.pop_back();
		break;	
	case '\t':
		str.clear();
		break;
	default:
		if(ch < 'a' || ch > 'z')
		{ }
		else
			str.push_back(ch);
		break;
	}
}

string WordInput::getString() const
{
	string s;
	//std::cout << "fsa";
	for (int i = 0; i < str.size(); i++)
	{
		//std::cout << i << std::endl;
		s.push_back(str[i]);
	}
	return s;
}

void WordInput::setStr(string s)
{
	str.clear();
	for (int i = 0; i < s.size(); i++)
	{
		str.push_back(s.at(i));
	}
}