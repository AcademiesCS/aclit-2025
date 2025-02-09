#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;
    vector<string> banned(N);
    for(int i = 0; i < N; i++) cin >> banned[i];

    for(int i = 0; i < M; i++)
    {
        string s; cin >> s;
        if(count(banned.begin(), banned.end(), s))
        {
            cout << "YES" << endll;
            return 0;
        }
    }

    cout << "NO" << endll;
}