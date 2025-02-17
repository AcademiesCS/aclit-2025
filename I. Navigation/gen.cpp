#include <bits/stdc++.h>
#include <cstdio>
#include <vector>


#define endll '\n'
using namespace std; 

vector<vector<int>> adjList{};
vector<int> visited{};
 
set<int> special{};
int dest, numSeen, e1, e2;
bool possible = true;
vector<int> stk{};

void dfsFind(int node, int dist)
{
    visited[node] = dist;
    for(int neighbor : adjList[node]) 
    {
        if(visited[neighbor] == -1) dfsFind(neighbor, dist + 1);
    }
}

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

int solve(int N, vector<pair<int, int>>& edges, int K, vector<int>& specialList)
{
    adjList = vector<vector<int>>(N);
    visited = vector<int>(N, -1);
    possible = true;
    special.clear();
    stk.clear();
    e1 = 0, e2 = 0;
    numSeen = 0;
    dest = -1;
 
    for(int i = 0; i < N - 1; i++)
    {
        auto [u, v] = edges[i];
        u--; v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    for(int i = 0; i < K; i++)
    {
        special.insert(specialList[i] - 1);
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
        return -1;
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

    return fdist + dA + dB;
}

int main()
{
    srand(time(0));
    for(int t = 0; t < 10; t++)
    {
        string fname = "maxt" + to_string(t);
        FILE* f = freopen((fname + ".in").c_str(), "w", stderr);

        int MAXN = 100000;

        int N = rand() % MAXN + 2; 
        int K = N;

        cerr << N << endll;
        vector<pair<int, int>> edges{};
        for(int i = 0; i < N - 1; i++)
        {
            cerr << i + 1 << " " << i + 2 << endll;
            edges.push_back({i + 1, i + 2});
        }

        set<int> special{};
        cerr << K << endll;
        while(special.size() < K)
        {
            int node = rand() % N + 1;
            special.insert(node);
        }

        vector<int> specialList{};
        for(int i : special) 
        {
            specialList.push_back(i);
            cerr << i << " ";
        }

        fclose(f);

        cout << solve(N, edges, K, specialList) << endll;
    }

}