#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;


typedef long long ll;
#define endll '\n'

void solveEfficient(int num_tc)
{
    ll N, S, X, Y; cin >> N >> S >> X >> Y;
    vector<ll> h1(N/2), h2(N/2 + N%2);
 
    for(ll i = 0; i < h1.size(); i++) cin >> h1[i];
    for(ll i = 0; i < h2.size(); i++) cin >> h2[i];
 
    map<pair<int, int>, vector<int>> first{};
 
    for(ll mask = 0; mask < (1 << h1.size()); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < h1.size(); i++) if(mask & (1 << i))
        {
            sum += h1[i];
            xorVal ^= h1[i];
        }
        
        first[{sum, xorVal}].push_back(__builtin_popcount(mask));
    }

    for(auto &entry : first) sort(entry.second.begin(), entry.second.end());
 
    ll ans = 0;
    for(ll mask = 0; mask < (1 << h2.size()); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < h2.size(); i++) if(mask & (1 << i))
        {
            sum += h2[i];
            xorVal ^= h2[i];
        }

        auto possibleSet = first[{S - sum, xorVal}];
        int low = X - __builtin_popcount(mask);
        int high = Y - __builtin_popcount(mask);
        ans += 
            upper_bound(possibleSet.begin(), possibleSet.end(), high) - 
            lower_bound(possibleSet.begin(), possibleSet.end(), low);
    }
 
    cout << ans << endll;
}

void solveBrute(int num_tc)
{
    ll N, S, X, Y; cin >> N >> S >> X >> Y;
    vector<ll> arr(N);

    for(ll i = 0; i < N; i++) cin >> arr[i];
 

    ll ans = 0;
    for(ll mask = 0; mask < (1LL << N); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < arr.size(); i++) if(mask & (1LL << i))
        {
            sum += arr[i];
            xorVal ^= arr[i];
        }

        int num = __builtin_popcount(mask);
        if(sum == S && xorVal == 0 && num >= X && num <= Y)
        {
            ans++;
        }
    }

    cout << ans << endll;
}


int32_t main()
{
    solveEfficient(0);
}
