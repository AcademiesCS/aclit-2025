#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<bool> vb;

#define endll '\n'

#define all(x) (x).begin(), (x).end()

#define MOD ll(1e9+7)
#define inf int(1e9+1)
#define INF ll(1e18+1)
#define EPS ld(1e-9)

template <typename T>
inline void fillv(vector<T>& v, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
}

inline void open(string name){
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}    



//comment to enable debugging
#define dbg(x)

#ifndef dbg
#define dbg(x) cerr << __LINE__ << ": " << #x << "=" << x << endl;
//edit for specific DS
#include "cp-templates/Debugging/alldebug.h"
#endif

map<ll, map<ll, vector<ll>>> subsets1;
map<ll, map<ll, vector<ll>>> subsets2;
//first key: XOR, then sum, result length

void solve(int num_tc)
{
    int n, s, x, y;
    cin >> n >> s >> x >> y;
    vll fullset(n);
    fillv(fullset, n);
    vll a(n/2), b(n/2 + n%2);
    for(int i = 0; i < n/2; i++){
        a[i] = fullset[i];
    }
    for(int i = 0; i < n/2 + n%2; i++){
        b[i] = fullset[i + n/2];
    }
    for(int amask = 0; amask < (1 << a.size()); amask++){
        ll sum = 0;
        ll xor_val = 0;
        ll size = 0;
        for(int i = 0; i < a.size(); i++){
            if(amask & (1 << i)){
                sum += a[i];
                xor_val ^= a[i];
                size++;
            }
        }
        subsets1[xor_val][sum].push_back(size);
    }
    for(int bmask = 0; bmask < (1 << b.size()); bmask++){
        ll sum = 0;
        ll xor_val = 0;
        ll size = 0;
        for(int i = 0; i < b.size(); i++){
            if(bmask & (1 << i)){
                sum += b[i];
                xor_val ^= b[i];
                size++;
            }
        }
        subsets2[xor_val][sum].push_back(size);
    }
    auto numsetthatmath = [x, y] (vll& ares, vll& bres){
        sort(all(ares));
        sort(all(bres));
        ll ans = 0;
        for(ll a : ares){
            int up = upper_bound(all(bres), y - a) - bres.begin();
            int low = lower_bound(all(bres), x - a) - bres.begin();
            ans += up - low;
        }
        return ans;
    };

    ll ans = 0;

    for(auto it1 = subsets1.begin(); it1 != subsets1.end(); it1++){
        int xor_val = it1->first;
        map<ll, vector<ll>>& secondaryamap = it1->second;
        map<ll, vector<ll>>& secondarybmap = subsets2[xor_val];
        for(auto it2 = secondaryamap.begin(); it2 != secondaryamap.end(); it2++){
            ll asum = it2->first;
            ll bsum = s - asum;
            if(secondarybmap.count(bsum) == 0) continue;
            vector<ll>& aresult = it2->second;
            vector<ll>& bresult = secondarybmap[bsum];
            dbg(aresult);
            dbg(bresult);
            ans += numsetthatmath(aresult, bresult);
        }
    }
    cout << ans << endll;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);  
    dbg("turn off debugging");
    ll T = 1;
    //cin >> T;
    for(ll t = 0; t < T; t++){
        solve(t+1);
    }
}
