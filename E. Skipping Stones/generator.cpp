#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    srand(time(0));

    for(int j = 0; j < 6; j++)
    {
        FILE* f = freopen((string("maxtest") + to_string(j) + string(".in")).c_str(), "w", stdout);

        ll n = 1e5, m = rand() % n + 1, x = rand() % n + 1;
        cout << n << ' ' << m << " " << x << endl;
        vector<ll> arr(n);

        for(int i = 0; i < n; i++)
        {
            arr[i] = rand() % (ll)(1e9) + 1;
            cout << arr[i] << " ";
        }

        cout << endl;

        fclose(f);
    }
    

}