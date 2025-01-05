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

typedef long long ll;

void solveEfficient(vector<pair<ll, ll>> testcases)
{
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

    for(auto [l, r] : testcases)
    {
        cout << prefixes[r - 1] * binExp(prefixes[l - 2], MOD - 2, MOD) % MOD << endll;
    }
}

int32_t main()
{
    srand(time(0));

    for(int j = 0; j < 5; j++)
    {
        FILE* f = freopen((string("maxtest") + to_string(j) + string(".in")).c_str(), "w", stdout);

        int T = 1e6;
        vector<pair<ll, ll>> arr{};

        for(int i = 1; i <= T; i++)
        {
            int l = rand()%((int)2e6-1) + 2;
            int r = rand()%((int)2e6-1) + 2;
            r = max(r, (int)2e6-1);
            arr.push_back({l, r});
            cout << l << " " << r << endll;
        }

        f = freopen((string("maxtest") + to_string(j) + string(".out")).c_str(), "w", stdout);
        solveEfficient( arr);

        fclose(f);
    }

}