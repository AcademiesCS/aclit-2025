#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;

#define endll '\n'
 
inline void open(string name){
    freopen((name + ".in").c_str(), "r", stdin);
	freopen((name + ".out").c_str(), "w", stdout);
}
 
void solve(int num_tc)
{
    ll N, a, b; cin >> N >> a >> b;
    
    b += a;
    vector<ll> arr(N), pref(N+1);
    for(int i = 0; i < N; i++) cin >> arr[i];
 
    ll ans = -1e15, rSum = 0;;
    multiset<ll> ends{};
    for(ll i = 0; i < N; i++)
    {
        if(i + 1 - a >= 0)
        {
            ends.insert(pref[i + 1 - a]);
        }
 
        rSum += arr[i];
        pref[i+1] = rSum;
 
        if(!ends.empty())
        {
            ll minEnd = *ends.begin();
            ans = max(ans, rSum - minEnd);
        }
 
        if(i + 1 - b >= 0)
        {
            ends.erase(ends.find(pref[i+1-b]));
        }
    }
 
    cout << ans << endll;
}
 
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);  
    solve(0);
}