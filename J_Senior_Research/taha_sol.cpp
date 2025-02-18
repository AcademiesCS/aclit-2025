#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define endll '\n'

const long long MAXN = 2e6 + 5;
long long MOD = 1e9 + 7;

ll invMod(ll x) 
{
  if (x <= 1) {
    return x;
  }
  return MOD - MOD / x * invMod(MOD % x) % MOD;
}

ll prefixes[MAXN + 1];
ll sigma[MAXN + 1];

void solveEfficient()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    for (int d = 1; d <= MAXN; ++d) {
        for (int m = d; m <= MAXN; m += d) {
            sigma[m] += d;
            sigma[m] %= MOD;
        }
    }

    prefixes[0] = 1;

    for(long long i = 2; i <= MAXN; i++)
    {
        prefixes[i-1] = sigma[i];
        prefixes[i-1] *= prefixes[i - 2];
        prefixes[i-1] %= MOD;
    }

    int T; cin >> T;
    while(T--)
    {
        long long l, r; cin >> l >> r;
        cout << prefixes[r - 1] * invMod(prefixes[l - 2]) % MOD << endll;
    }
}

void solveBrute()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long T; cin >> T;
    for(int t = 0; t < T; t++)
    {
        long long l, r; cin >> l >> r;
        long long ans = 1;
        for(int j = l; j <= r; j++)
        {
            long long cur = 0;
            for(int d = 1; d <= j; d++)
            {
                if(j % d == 0) cur += d;
            }
            ans *= cur;
            ans %= (long long)(1e9+7);
        }

        cout << ans << endll;
    }
}

int main()
{
    //solveBrute();
    solveEfficient();
}