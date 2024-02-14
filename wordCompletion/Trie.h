#pragma once
#include <string>
#include <fstream>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

// Структура узела дерева 

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

void TrieInit(fstream& input, TrieNode* root);

TrieNode* getNewNode(void);

void insert(TrieNode*, string);

bool search(TrieNode*, string);
bool isEmpty(TrieNode*);

string wordCompleting(TrieNode*, string);

TrieNode* remove(TrieNode*, string, int depth = 0);

void display(TrieNode*, string);
void displayWords(TrieNode*, int&, vector<char>);

//void findMinPrefixes(TrieNode*, char[], int, string&);
int wordCount(TrieNode* root);

