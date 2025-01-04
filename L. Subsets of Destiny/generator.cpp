#include <cstdio>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

#define endll '\n'
typedef long long ll;

void solveEfficient(ll N, ll S, ll X, ll Y, vector<ll> arr)
{
    vector<ll> h1(N/2), h2(N/2);
 
    for(ll i = 0; i < h1.size(); i++) 
    {
        h1[i] = arr.back();
        arr.pop_back();
    }
    for(ll i = 0; i < h2.size(); i++) 
    {
        h2[i] = arr.back();
        arr.pop_back();
    }
 
    map<pair<int, int>, indexed_set> first{};
 
    for(ll mask = 0; mask < (1 << h1.size()); mask++)
    {
        ll sum = 0, xorVal = 0;
        for(ll i = 0; i < h1.size(); i++) if(mask & (1 << i))
        {
            sum += h1[i];
            xorVal ^= h1[i];

            if(sum > S) break;
        }

        if(sum > S) continue;

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
            if(sum > S) break;
        }

        if(sum > S) continue;
        if(!first.count({S - sum, xorVal})) continue;

        auto possibleSet = first[{S - sum, xorVal}];
        int low = X - __builtin_popcount(mask);
        int high = Y - __builtin_popcount(mask);
        ans += possibleSet.order_of_key(high) - possibleSet.order_of_key(low);
    }
 
    cout << ans << endll;
}

int32_t main()
{
    
    /*
    MAX TEST GEN
    int n = 35;
    int s = rand() % 40 + 1;
    int x = rand() % n;
    int y = max(n, x + rand() % n);

    

    */
    srand(time(0));

    for(int j = 0; j < 5; j++)
    {
        FILE* f = freopen((string("test") + to_string(j+1) + string(".in")).c_str(), "w", stdout);

        int n = 36;
        int s = rand() % 4 + 2;
        int x = rand() % n + 1;
        int y = max(n, x + rand() % n + 1);
        cout << n << " " << s << " " << x << " " << y << endl;
        
        vector<ll> arr{};

        for(int i = 0; i < n; i++)
        {
            arr.push_back(rand() % s);
            cout << arr.back() << " ";
        }

        fclose(f);

        f = freopen((string("test") + to_string(j+1) + string(".out")).c_str(), "w", stdout);
        solveEfficient(n, s, x, y, arr);

        fclose(f);
    }

}