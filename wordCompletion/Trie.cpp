#include "Trie.h"

using namespace std;

// ������������� ������ �� �����
void TrieInit(fstream& f, TrieNode* root)
{
    cout << "����������� �������\n";

    string s;
    while (!f.eof())
    {
        //f << s;
        getline(f, s);
        insert(root, s);
    }

    cout << "������� ���������\n";
}

string wordCompleteInner(TrieNode* root, vector<char> buf)
{
    if (root->isEndOfWord == true)
    {
        string str;
        for (int i : buf)
        {
            str += i;
        }
        return str;

    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            buf.push_back('a' + i);
            if (wordCompleteInner(root->children[i], buf) != "")
                return wordCompleteInner(root->children[i], buf);
            buf.pop_back();
        }
    }
    return "";
}

// ���������� ������ ���������� �� �������� �����,
// ���� ����� ����������� � �������, �� ���������� 
// ����������� �������
string wordCompleting(TrieNode* root, string key)
{
    int ind = 0;
    vector<char> buf;
    
    TrieNode* node = root;

    while (ind < key.size())
    {
        if (!node->children[int(key.at(ind) - 'a')])
            return "";

        node = node->children[int(key.at(ind) - 'a')];
        buf.push_back(key.at(ind));
        ind++;
    }

    return wordCompleteInner(node, buf);

}


// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}

//void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
//{
//    for (int i = 0; i < ALPHABET_SIZE; i++)
//    {
//        if (root->children[i])
//        {
//            if (wordCount(root->children[i]) == 1)
//            {
//                for (int j = 0; j < ind; j++)
//                {
//                    res += char(buf[j]);
//                }
//                res += char(i + 'a');
//                res += ' ';
//            }
//            else
//            {
//                buf[ind++] = 'a' + i;
//                findMinPrefixes(root->children[i], buf, ind, res);
//                ind--;
//            }
//        }
//    }
//}

// ����� ���� ����, ������� ����� ������� key
void display(TrieNode* root, string key)
{
    cout << "\n ��������� ��������: \n";

    int count = 0;
    
    vector<char> buf;
    int ind = 0;
    TrieNode* node = root;

    while (ind < key.size())
    {
        if (!node->children[int(key.at(ind) - 'a')])
            return;

        node = node->children[int(key.at(ind) - 'a')];

        buf.push_back(key.at(ind));
        ind++;
    }



    displayWords(node, count, buf);
}

// ����� ���� ���� �� ������������ ����
// �������� ����������� �� 10 ������ ����,
// ����� �� ����������� �������
void displayWords(TrieNode* root, int& count, vector<char> buf)
{
    if (root->isEndOfWord)
    {
        for(int i : buf)
            cout << char(i);
        cout << endl;
        count++;
    }

    if(count != 10)
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (root->children[i] && count != 10)
            {
                    buf.push_back('a' + i);

                    displayWords(root->children[i], count, buf);
                    
                    buf.pop_back();
            }
        }
}

// ���������� ���� ������� ����� �������� �� ����
int wordCount(TrieNode* root)
{
    TrieNode* temp;

    std::stack<TrieNode*> s;
    int count = 0;

    s.push(root);
    while (!s.empty())
    {
        temp = s.top();
        s.pop();

        if (temp->isEndOfWord == true)
        {
            count++;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (temp->children[i])
            {
                s.push(temp->children[i]);
            }
        }
    }

    return count;
}