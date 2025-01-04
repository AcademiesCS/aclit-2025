#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less_equal<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

typedef long long ll;
#define endll '\n'

void solve(int num_tc)
{
    ll N; cin >> N;
    vector<ll> h1(N/2), h2(N/2);
 
    for(ll i = 0; i < h1.size(); i++) cin >> h1[i];
    for(ll i = 0; i < h2.size(); i++) cin >> h2[i];
 
    map<pair<int, int>, indexed_set> first{};
 
    for(ll mask = 0; mask < (1 << h1.size()); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < h1.size(); i++) if(mask & (1 << i))
        {
            sum += h1[i];
            xorVal ^= h1[i];
        }
        first[{sum, xorVal}].insert(__builtin_popcount(mask));
    }
 
    ll ans = 0;
    for(ll mask = 0; mask < (1 << h2.size()); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < h2.size(); i++) if(mask & (1 << i))
        {
            sum += h2[i];
            xorVal ^= h2[i];
        }

        auto possibleSet = first[{100 - sum, xorVal}];
        ans += ;
    }
 
    cout << ans << endll;
}

int32_t main()
{
    freopen("bunches_data.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);  

    solve(0);
}
