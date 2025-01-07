#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int N, M, X; cin >> N >> M >> X;

    vector<int> residues(M);

    for(int i = 0; i < N; i++)
    {
        int x; cin >> x;
        residues[x % M]++;
    }

    sort(residues.rbegin(), residues.rend());

    ll ans = 0;
    for(int i = 0; i < min(X, M); i++)
    {
        ans += residues[i];
    }

    cout << ans << endl;
}
