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

set<int> required;
vvi adj;
int maxdepth = 0;
int maxnode = 0;

void first_dfs(int node, int par, int depth){
    if(required.count(node)){
        if(depth > maxdepth){
            maxdepth = depth;
            maxnode = node;
        }
    }
    for(int nb : adj[node]){
        if(nb == par) continue;
        first_dfs(nb, node, depth + 1);
    }
}

vi reqseen;
bool done = false;
vi cc;
void second_dfs(int node, int par, int depth){
    cc.push_back(node);
    if(required.count(node)){
        reqseen.push_back(node);
        if(reqseen.size() == required.size()){
            done = true;
            return;
        }
    }
    for(int nb : adj[node]){
        if(nb == par) continue;
        second_dfs(nb, node, depth + 1);
        if(done) return;
    }
    if(required.count(node)) reqseen.pop_back();
    cc.pop_back();
}

void k1dfs(int node, int par, int depth){
    if(depth > maxdepth){
        maxdepth = depth;
        maxnode = node;
    }
    for(int nb : adj[node]){
        if(nb == par) continue;
        k1dfs(nb, node, depth + 1);
    }
}

void solve1(){
    int a;
    cin >> a;
    a--;
    multiset<int, greater<int>> pathlens;
    for(int nb : adj[a]){
        k1dfs(nb, a, 1);
        pathlens.insert(maxdepth);
        maxdepth = 0;
    }
    int ans = *pathlens.begin();
    pathlens.erase(pathlens.begin());
    cout << ans + *pathlens.begin() << endll;
}

void third_dfs(int node, int par, int depth){
    if(depth > maxdepth){
        maxdepth = depth;
        maxnode = node;
    }
    for(int nb : adj[node]){
        if(nb == par) continue;
        third_dfs(nb, node, depth + 1);
    }
}

void solve(int num_tc)
{
    int n;
    cin >> n;
    adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int k;
    cin >> k;
    if(k == 1){
        solve1();
        return;
    }
    for(int i = 0; i < k; i++){
        int a;
        cin >> a;
        a--;
        required.insert(a);
    }
    first_dfs(*required.begin(), -1, 0);
    int firstreqnode = maxnode;
    second_dfs(firstreqnode, -1, 0);
    if(!done){
        cout << -1 << endll;
        return;
    }
    maxdepth = 0;
    int requiredclasspath = cc.size() - 1;
    third_dfs(cc[0], cc[1], 0);
    requiredclasspath += maxdepth;
    maxdepth = 0;
    third_dfs(cc.back(), cc[cc.size() - 2], 0);
    cout << requiredclasspath + maxdepth << endll;
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
