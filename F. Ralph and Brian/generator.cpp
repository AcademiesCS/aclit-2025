#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    srand(time(0));

    for(int j = 0; j < 15; j++)
    {
        FILE* f = freopen((string("test") + to_string(j) + string(".in")).c_str(), "w", stdout);

        ll n = rand() % ((int)1e5), x = rand() % ((int)1e5);
        cout << n << ' ' << x << endl;

        ll maxV = 2e4;

        for(int i = 0; i < n; i++)
        {
            cout << rand()%(maxV) << " ";
            cout << rand()%(maxV) << " ";
            cout << rand()%(maxV) << "\n";
        }

        fclose(f);
    }
    

}