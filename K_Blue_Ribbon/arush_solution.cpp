#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;

typedef vector<long long> vi;
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
//!#define dbg(x)

#ifndef dbg
#define dbg(x) cerr << __LINE__ << ": " << #x << "=" << x << endl;
//edit for specific DS
#include "../../../../cp-templates/Debugging/alldebug.h"
#endif

typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;

void solve(int num_tc)
{
    int n;
    cin >> n;
    vi a(n);
    fillv(a, n);
    //dp[i][sum][xor][size] = count
    int MAX_SUM = 100;
    int MAX_XOR = 511;  
    //vvvvi dp(n + 1, vvvi(MAX_SUM + 1, vvi(MAX_XOR + 1, vi(n + 1, 0))));
    unique_ptr<vvvi> curlayerptr = make_unique<vvvi>(MAX_SUM + 1, vvi(MAX_XOR + 1, vi(n + 1, 0)));
    (*curlayerptr)[0][0][0] = 1;
    for(int i = 0; i < n; i++){
        unique_ptr<vvvi> nextlayerptr = make_unique<vvvi>(MAX_SUM + 1, vvi(MAX_XOR + 1, vi(n + 1, 0)));
        vvvi& nextlayer = *nextlayerptr;
        vvvi& curlayer = *curlayerptr;
        // dbg(i);
        for(int j = 0; j <= MAX_SUM; j++){
            // cerr << "  ";
            // dbg(j);
            for(int k = 0; k <= MAX_XOR; k++){
                // cerr << "    ";
                // dbg(k);
                for(int l = 0; l <= n; l++){
                    // cerr << "      ";
                    // dbg(l);
                    
                    nextlayer[j][k][l] += curlayer[j][k][l];
                    // dp[i + 1][j][k][l] += dp[i][j][k][l];
                    if((j + a[i] <= MAX_SUM) && (l < n) && ((k ^ a[i]) <= MAX_XOR)){
                        // dp[i + 1][j + a[i]][k ^ a[i]][l + 1] += dp[i][j][k][l];
                        nextlayer[j + a[i]][k ^ a[i]][l + 1] += curlayer[j][k][l];
                    }
                }
            }
        } 
        curlayerptr = move(nextlayerptr);
    }
    dbg(*curlayerptr)
    //dbg(dp[n]);
    //dp[n] is the thing we need to take prefs on
    vvvi pref(MAX_SUM + 2, vvi(MAX_XOR + 2, vi(n + 2, 0)));
    pref[0][0][0] = 0;
    for(int i = 1; i <= MAX_SUM + 1; i++){
        for(int j = 1; j <= MAX_XOR + 1; j++){
            for(int k = 1; k <= n + 1; k++){
                pref[i][j][k] = pref[i - 1][j][k] + pref[i][j - 1][k] + pref[i][j][k - 1]
                 - pref[i - 1][j - 1][k] - pref[i - 1][j][k - 1] - pref[i][j - 1][k - 1] 
                 + pref[i - 1][j - 1][k - 1] + (*curlayerptr)[i - 1][j - 1][k - 1];
            }
        }
    }
    //dbg(pref);
    //pref[i][j][k] corresponds to [i - 1][j - 1][k - 1]
    int q;
    cin >> q;
    auto get = [&](int x, int y, int z) -> ll {
        if (x < 0 || y < 0 || z < 0) return 0;
        return pref[x + 1][y + 1][z + 1];
    };
    for(int i = 0; i < q; i++){
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        ll ans = get(b, d, f)
        - get(a - 1, d, f) - get(b, c - 1, f) - get(b, d, e - 1)
        + get(a - 1, c - 1, f) + get(a - 1, d, e - 1) + get(b, c - 1, e - 1)
        - get(a - 1, c - 1, e - 1);
        cout << ans << endll;
    }
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
