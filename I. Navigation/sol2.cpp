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

void dfsCheck(int node, int dest)
{
    if(node == dest) return;


}

/*
Given a graph with N nodes out of which K nodes that you must visit, find the longest path in the graph that goes through those nodes
1. Pick one of the K nodes, and find the farthest node in K away from it. Call this node A.
2. Find the farthest K node away from A. Call this node B.
3. For the answer to exist, all K nodes must be on the singular path between A and B since the graph is a tree
4. Then, do a DFS at A and B to find the farthest node away from the path that has the other nodes 
*/

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

    int K; cin >> K;
    set<int> special{};
    for(int i = 0; i < K; i++)
    {
        int x; cin >> x;
        special.insert(x-1);
    }
    
    dfs(*special.begin(), 0);
    int A = *special.begin(), fdist = 0;
    for(int i = 0; i < N; i++) 
    {
        if(visited[i] > fdist && special.count(i))
        {
            fdist = visited[i];
            A = i;
        }
    }
 
    visited.clear();
    visited.resize(N);
 
    dfs(A, 0);
    int B = A;
    fdist = 0;
    for(int i = 0; i < N; i++) 
    {
        if(visited[i] > fdist && special.count(i))
        {
            fdist = visited[i];
            B = i;
        }
    }
 
    cout << fdist << endll;
}