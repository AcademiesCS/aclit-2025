#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>
using namespace std;

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
#define dbg(x) cerr << __LINE__ << ": " << #x << "=" << x << endl;

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& arr){
	os << "[";
    for(const T x : arr){
		os << x << " ";
	}
	os << "]";
    return os;
}

template <typename T, typename U>
ostream& operator<< (ostream& os, const pair<T, U>& x){
    os << "(" << x.first << ", " << x.second << ")";
    return os;
}

template <typename T, typename U>
ostream& operator<< (ostream& os, const vector<pair<T, U>>& arr){
	os << "{\n";
    for(const pair<T,U>& x : arr){
		os << "    " << x << endll;
	}
	os << "}";
    return os;
}

template <typename T, typename U>
ostream& operator<< (ostream& os, const map<T, U>& arr){
	os << "{\n";
    for(const pair<T,U>& x : arr){
		os << "    " << x << endll;
	}
	os << "}";
    return os;
}

template <typename T>
inline void fillv(vector<T>& v, int n) {
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
}
template <typename T, typename U>
inline void fillv(vector<pair<T, U>>& v, int n, bool inv = false){
	if(inv){
		for(int i = 0 ; i < n; ++i){
			cin >> v[i].second >> v[i].first;
		}
		return;
	}
	for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
	return;
}

inline void open(string name){
    freopen((name + ".in").c_str(), "r", stdin);
	freopen((name + ".out").c_str(), "w", stdout);
}

template <typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& os, const std::priority_queue<T, U, V>& pq) {
    std::priority_queue<T, U, V> copy = pq;
    os << "[";
    bool first = true;
    while (!copy.empty()) {
        if (!first) os << ", ";
        os << copy.top();
        copy.pop();
        first = false;
    }
    os << "]";
    return os;
}

void solve(int num_tc)
{
    ll n, x;
    cin >> n >> x;
    vi a(n);
    vi d(n);
    vi b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i] >> d[i] >> b[i];
    }
    set<pair<int, int>, greater<pair<int, int>>> q;
    for(int i = 0; i < n; i++){
        q.insert({a[i], i});
    }

    ll bottles = 0;
    ll moneyspend = 0;

    while(!q.empty() && moneyspend < x){
        pair<int, int> top = *q.rbegin();
        q.erase(--q.end());
        if(!b[top.second]){
            continue;
        }
        if(top.first + moneyspend > x){
            break;
        }
        bottles += 1;
        moneyspend += top.first;
        b[top.second] -= 1;
        q.insert({top.first + d[top.second], top.second});
    }

    cout << bottles << " " << moneyspend << endll;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);  

    ll T = 1;
    //cin >> T;
    for(ll t = 0; t < T; t++){
        solve(t+1);
    }
}
