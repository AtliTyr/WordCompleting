#include "Trie.h"

using namespace std;

// Инициализация дерева из файла
void TrieInit(fstream& f, TrieNode* root)
{
    cout << "Подключение словаря\n";

    string s;
    while (!f.eof())
    {
        //f << s;
        getline(f, s);
        insert(root, s);
    }

    cout << "Словарь подключен\n";
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

// Возвращает первое подходящее по префиксу слово,
// если слово отсутствует в словаре, То возвращает 
// изначальный префикс
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


// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
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

// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
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

// Вывод всех слов, имеющих общий префикс key
void display(TrieNode* root, string key)
{
    cout << "\n Возможные варианты: \n";

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

// Вывод всех слов из определённого узла
// Поставил ограничение на 10 первых слов,
// чтобы не перегружать консоль
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

// Количество слов которые можно получить из узла
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