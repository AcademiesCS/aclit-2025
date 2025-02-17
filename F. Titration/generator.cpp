#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

void solve(ll N, ll Q, vector<ll>& arr, vector<ll>& queries)
{
    vector<ll> psum(N+1);
    for(int i = 0; i < N; i++) 
    {
        psum[i+1] = psum[i] + arr[i];
    }

    for(int q = 0; q < Q; q++)
    {
        ll b = queries[q];
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

int main()
{
    freopen("input.txt", "w", stdout);

    srand(time(0));

    for(int j = 0; j < 6; j++)
    {
        FILE* f = freopen((string("maxtest") + to_string(j) + string(".in")).c_str(), "w", stdout);

        ll n = 2e5, q = 2e5;
        cout << n << ' ' << q << endl;
        vector<ll> arr(n), queries(q);

        for(int i = 0; i < n; i++)
        {
            arr[i] = rand() % (ll)(1e5);
            cout << arr[i] << " ";
        }

        cout << endl;

        for(int i = 0; i < q; i++)
        {
            queries[i] = rand() % (ll)(1e5);
            cout << queries[i] << endl;
        }

        fclose(f);
    }
    

}
