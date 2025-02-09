#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'


int main()
{
    vector<string> words{};
    for(char c = 'a'; c <= 'z'; c++)
    {
        for(char b = 'a'; b <= 'z'; b++)
        {
            words.push_back(c + string("sigma") + b);
        }
    }

    srand(time(0));
    cout << words.size() << endll;
    for(int j = 0; j < 10; j++)
    {
        FILE* f = freopen((string("maxtest") + to_string(j) + string(".in")).c_str(), "w", stdout);
        if(rand()%2==0)
        {
            cout << "100 100\n";
            for(int i = 0; i < 100; i++)
            {
                cout << words[rand() % (words.size()/2)] << " ";
            }

            cout << endll;
            for(int i = 0; i < 100; i++)
            {
                cout << words[words.size()/2 + rand() % (words.size()/2)] << " ";
            }

        }
        else 
        {
            cout << "100 100\n";
            for(int i = 0; i < 100; i++)
            {
                cout << words[rand() % (words.size())] << " ";
            }

            cout << endll;
            for(int i = 0; i < 100; i++)
            {
                cout << words[rand() % (words.size())] << " ";
            }
        }
        fclose(f);
    }
}