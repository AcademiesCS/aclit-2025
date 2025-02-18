#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
  
#define endll '\n'
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std; 

/*
Given a graph with N nodes out of which K nodes that you must visit, find the longest path in the graph that goes through those nodes
1. Pick one of the K nodes, and find the farthest node in K away from it. Call this node A.
2. Find the farthest K node away from A. Call this node B.
3. For the answer to exist, all K nodes must be on the singular path between A and B since the graph is a tree
4. Then, do a DFS at A and B to find the farthest node away from the path that has the other nodes 
*/


vector<vector<int>> adjList{};
vector<int> visited{};
 
void dfsFind(int node, int dist)
{
    visited[node] = dist;
    for(int neighbor : adjList[node]) 
    {
        if(visited[neighbor]==-1) dfsFind(neighbor, dist + 1);
    }
}

set<int> special{};
int dest, numSeen = 0;
bool possible = true;

vector<int> stk{};
int e1, e2;

void dfsCheck(int node, int parent)
{
    stk.push_back(node);
    if(special.count(node)) numSeen++;

    if(node == dest)
    {
        if(numSeen != special.size()) 
        {
            possible = false;
        }
        e1 = stk[1], e2 = stk[stk.size() - 2];
        return;
    }

    for(int neighbor : adjList[node]) 
    {
        if(neighbor != parent) dfsCheck(neighbor, node);
    }

    if(special.count(node)) numSeen--;
    stk.pop_back();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int N; cin >> N;
    adjList.resize(N);
    visited = vector<int>(N, -1);
 
    for(int i = 0; i < N - 1; i++)
    {
        int u, v; cin >> u >> v;
        u--; v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int K; cin >> K;
    for(int i = 0; i < K; i++)
    {
        int x; cin >> x;
        special.insert(x-1);
    }
    
    dfsFind(*special.begin(), 0);
    int A = *special.begin(), fdist = 0;
    for(int i = 0; i < N; i++) 
    {
        if(visited[i] > fdist && special.count(i))
        {
            fdist = visited[i];
            A = i;
        }
    }
 
    visited = vector<int>(N, -1);
 
    dfsFind(A, 0);
    int B = A;
    fdist = 0;
    for(int i = 0; i < N; i++) 
    {
        if(visited[i] >= fdist && special.count(i))
        {
            fdist = visited[i];
            B = i;
        }
    }

    dest = B;
    numSeen = 0;
    dfsCheck(A, -1);
    if(!possible) 
    {
        cout << -1 << endll;
        return 0;
    }


    adjList[A].erase(find(adjList[A].begin(), adjList[A].end(), e1));
    adjList[B].erase(find(adjList[B].begin(), adjList[B].end(), e2));
    visited = vector<int>(N, -1);

    int dA = 0, dB = 0;
    dfsFind(A, 0);
    dA = *max_element(visited.begin(), visited.end());

    visited = vector<int>(N, -1);
    dfsFind(B, 0);
    dB = *max_element(visited.begin(), visited.end());

    cout << fdist + dA + dB << endll;
}