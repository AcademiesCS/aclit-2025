#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
  
#define endll '\n'
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std; 
vector<vector<int>> adjList{};
vector<int> visited{};
 
void dfs(int node, int dist)
{
    visited[node] = dist;
    for(int neighbor : adjList[node]) if(!visited[neighbor]) dfs(neighbor, dist + 1);
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int N; cin >> N;
    adjList.resize(N);
    visited.resize(N);
 
    for(int i = 0; i < N - 1; i++)
    {
        int u, v; cin >> u >> v;
        u--; v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
 
    dfs(0, 0);
    int farthest = 0, fdist = 0;
    for(int i = 0; i < N; i++) if(visited[i] > fdist)
    {
        fdist = visited[i];
        farthest = i;
    }
 
    if(N <= 2)
    {
        cout << N - 1 << endll;
        return 0;
    }
 
    visited.clear();
    visited.resize(N);
 
    dfs(farthest, 0);
    farthest = 0, fdist = 0;
    for(int i = 0; i < N; i++) if(visited[i] > fdist)
    {
        fdist = visited[i];
        farthest = i;
    }
 
    cout << fdist << endll;
}