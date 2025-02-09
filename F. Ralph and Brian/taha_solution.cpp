#include <bits/stdc++.h>
#include <queue>

using namespace std;

typedef long long ll;

int main()
{
    ll N, X; cin >> N >> X;

    vector<array<ll, 3>> sodas(N);
    for(ll i = 0; i < N; i++) for(int j = 0; j < 3; j++) cin >> sodas[i][j];

    priority_queue<array<ll, 2>> pq{};
    for(ll i = 0; i < N; i++)
    {
        pq.push({-sodas[i][0], i});
    }

    ll minCost = 0, maxBottles = 0;
    while(!pq.empty())
    {
        auto [price, ind] = pq.top();
        pq.pop();

        if(X + price < 0) break;

        maxBottles++;
        minCost -= price;
        X += price;

        sodas[ind][2]--;
        price -= sodas[ind][1];

        if(sodas[ind][2] > 0) pq.push({price, ind});
    }

    cout << maxBottles << " " << minCost << "\n";
}