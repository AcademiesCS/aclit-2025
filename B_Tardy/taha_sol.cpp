#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int K; cin >> K;
    int ans = 0;
    for(int i = 0; i < 4; i++)
    {
        int a; cin >> a;
        ans += a > K;
    }

    if(ans >= 2) cout << "YES" << endll;
    else cout << "NO" << endll;
}