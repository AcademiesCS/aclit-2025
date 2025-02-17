#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, Q; cin >> N >> Q;
    vector<ll> arr(N), psum(N+1);
    for(int i = 0; i < N; i++) 
    {
        cin >> arr[i];
        psum[i+1] = psum[i] + arr[i];
    }

    for(int q = 0; q < Q; q++)
    {
        ll b; cin >> b;
        ll lb = lower_bound(psum.begin(), psum.end(), b) - psum.begin();
        ll ans = abs(b - psum[lb]);
        if(lb != 0)
        {
            ans = min(ans, abs(b - psum[lb - 1]));
        }

        if(lb != N - 1)
        {
            ans = min(ans, abs(b - psum[lb + 1]));
        }

        cout << ans << endll;
    }
}
