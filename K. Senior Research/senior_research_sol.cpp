#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#include <bits/stdc++.h>

using namespace std;

#define endll '\n'

long long SumOfDivisors(long long num, vector<long long>& primes) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}

void sieve(vector<bool>& is_prime, long long n)
{
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= n; i++) {
        if (is_prime[i] && i * i <= n) {
            for (long long j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

long long binExp(long long a, long long b, long long mod) {
    if (b == 0)
        return 1;

    long long res = binExp(a, b / 2, mod) % mod;
    if (b & 1) {
        return (a * ((res * res) % mod)) % mod;
    } else
        return (res * res) % mod;
}

void solveEfficient()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long MAXN = 2e6+1, MOD = 1e9 + 7;
    vector<bool> is_prime(MAXN+692, true);
    sieve(is_prime, MAXN+692);

    vector<long long> primes{};
    for(int i = 0; i < is_prime.size(); i++)
    {
        if(is_prime[i]) primes.push_back(i);
    }

    vector<long long> prefixes{1};

    for(long long i = 2; i <= MAXN; i++)
    {
        prefixes.push_back(SumOfDivisors(i, primes));
        prefixes[i-1] *= prefixes[i - 2];
        prefixes[i-1] %= MOD;
    }

    int T; cin >> T;
    while(T--)
    {
        long long l, r; cin >> l >> r;
        cout << prefixes[r - 1] * binExp(prefixes[l - 2], MOD - 2, MOD) % MOD << endll;
    }
}

void solveBrute()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long T; cin >> T;
    for(int t = 0; t < T; t++)
    {
        long long l, r; cin >> l >> r;
        long long ans = 1;
        for(int j = l; j <= r; j++)
        {
            long long cur = 0;
            for(int d = 1; d <= j; d++)
            {
                if(j % d == 0) cur += d;
            }
            ans *= cur;
            ans %= (long long)(1e9+7);
        }

        cout << ans << endll;
    }
}

int main()
{
    //solveBrute();
    //solveEfficient();
}
