#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    // DP state: dp[s][x][k] = number of subsets with sum = s, XOR = x, using exactly k elements.
    // s ranges from 0 to MAX_SUM = 100.
    // x ranges from 0 to MAX_XOR = 511 (we need 9 bits because numbers can be 256).
    // k ranges from 0 to n.
    const int MAX_SUM = 100;
    const int MAX_XOR = 511;  // 0..511
    // n is at most 40 so k dimension is 0..40.
    
    // Allocate dp array. We use slight over-estimates for array dimensions.
    static long long dp[105][520][50];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1; // the empty subset.
    
    // Process each number from arr.
    // We update in-place in reverse order for k (and for s) so that each element is used at most once.
    for (int a : arr) {
        // Loop over k in descending order (from n-1 to 0)
        for (int k = n - 1; k >= 0; k--) {
            // Loop over sums in descending order.
            for (int s = MAX_SUM; s >= 0; s--) {
                // Loop over all possible XOR values.
                for (int x = 0; x <= MAX_XOR; x++) {
                    long long ways = dp[s][x][k];
                    if(ways != 0){
                        int ns = s + a;
                        if(ns <= MAX_SUM){
                            int nx = x ^ a;
                            dp[ns][nx][k + 1] += ways;
                        }
                    }
                }
            }
        }
    }
    
    // Build 2D prefix sums for each count k.
    // For queries, the XOR condition is for x in [c,d] with d <= 256.
    // So we precompute prefix sums only for x in [0, MAX_XOR_QUERY] where MAX_XOR_QUERY = 256.
    const int MAX_XOR_QUERY = 256;
    // Let prefix[k][s][x] = sum_{i=0..s, j=0..x} dp[i][j][k]
    // Dimensions: k in 0..n, s in 0..100, x in 0..256.
    static long long prefix[50][110][270]; // safe margins.
    memset(prefix, 0, sizeof(prefix));
    
    for (int k = 0; k <= n; k++){
        for (int s = 0; s <= MAX_SUM; s++){
            for (int x = 0; x <= MAX_XOR_QUERY; x++){
                long long cur = dp[s][x][k];
                if(s > 0) cur += prefix[k][s - 1][x];
                if(x > 0) cur += prefix[k][s][x - 1];
                if(s > 0 && x > 0) cur -= prefix[k][s - 1][x - 1];
                prefix[k][s][x] = cur;
            }
        }
    }
    
    // Process queries.
    int q;
    cin >> q;
    while(q--){
        // Each query gives: a, b (sum range), c, d (XOR range), e, f (subset size range).
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        long long ans = 0;
        // Sum over all valid counts k in [e, f].
        for (int k = e; k <= f; k++){
            // Use the 2D prefix sum to get the sum of dp[s][x][k] for s in [a,b] and x in [c,d].
            long long sumRegion = prefix[k][b][d];
            if(a > 0) sumRegion -= prefix[k][a - 1][d];
            if(c > 0) sumRegion -= prefix[k][b][c - 1];
            if(a > 0 && c > 0) sumRegion += prefix[k][a - 1][c - 1];
            ans += sumRegion;
        }
        cout << ans << "\n";
    }
    
    return 0;
}