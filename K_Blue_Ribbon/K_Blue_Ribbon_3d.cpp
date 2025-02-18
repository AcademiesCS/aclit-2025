#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 40;
const int MAX_SUM = 100;
const int MAX_XOR = 256;  // 0..31
// dp dimensions: count 0..n, sum 0..100, xor 0..31.
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n; 
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
 
    // DP table: dp[count][sum][xor]
    // Use 3D vector with dimensions (n+1) x (MAX_SUM+1) x (MAX_XOR+1)
    vector<vector<vector<long long>>> dp(n+1, vector<vector<long long>>(MAX_SUM+1, vector<long long>(MAX_XOR+1, 0)));
    dp[0][0][0] = 1;
 
    for (int a : arr){
        // update backwards for count
        for (int cnt = n-1; cnt >= 0; cnt--){
            for (int s = 0; s <= MAX_SUM - a; s++){
                for (int x = 0; x <= MAX_XOR; x++){
                    long long ways = dp[cnt][s][x];
                    if (ways){
                        dp[cnt+1][s+a][x ^ a] += ways;
                    }
                }
            }
        }
    }
 
    // Build 3D prefix sum array P over dimensions: count (0..n), sum (0..MAX_SUM), xor (0..MAX_XOR)
    int N = n; // maximum count index
    int S = MAX_SUM, X = MAX_XOR;
    vector<vector<vector<long long>>> P(N+1, vector<vector<long long>>(S+1, vector<long long>(X+1, 0)));
 
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= S; j++){
            for (int k = 0; k <= X; k++){
                P[i][j][k] = dp[i][j][k];
                if(i > 0) P[i][j][k] += P[i-1][j][k];
                if(j > 0) P[i][j][k] += P[i][j-1][k];
                if(k > 0) P[i][j][k] += P[i][j][k-1];
                if(i > 0 && j > 0) P[i][j][k] -= P[i-1][j-1][k];
                if(i > 0 && k > 0) P[i][j][k] -= P[i-1][j][k-1];
                if(j > 0 && k > 0) P[i][j][k] -= P[i][j-1][k-1];
                if(i > 0 && j > 0 && k > 0) P[i][j][k] += P[i-1][j-1][k-1];
            }
        }
    }
 
    auto getP = [&](int i, int j, int k) -> long long {
        if(i < 0 || j < 0 || k < 0) return 0;
        return P[i][j][k];
    };
 
    // Process queries
    int q; 
    cin >> q;
    while(q--){
        int A, B, C, D, E, F;
        cin >> A >> B >> C >> D >> E >> F;
        // We want the sum over count in [E, F], sum in [A, B], xor in [C, D].
        // Use inclusion–exclusion (here count dimension = i, sum dimension = j, xor dimension = k):
        long long ans = 0;
        ans = getP(F, B, D)
            - getP(E-1, B, D)
            - getP(F, A-1, D)
            - getP(F, B, C-1)
            + getP(E-1, A-1, D)
            + getP(E-1, B, C-1)
            + getP(F, A-1, C-1)
            - getP(E-1, A-1, C-1);
        cout << ans << "\n";
    }
    return 0;
}
