
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class J_Senior_Research {
    static class FastReader {
        BufferedReader b;
        StringTokenizer s;
        public FastReader() {
            b = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (s == null || !s.hasMoreElements()) {
                try {
                    s = new StringTokenizer(b.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return s.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
        double nextDouble() {
            return Double.parseDouble(next());
        }
        String nextLine() {
            String str = "";
            try {
                if (s.hasMoreTokens()) {
                    str = s.nextToken("\n");
                } else {
                    str = b.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

    public static FastReader sc = new FastReader();
    public static DecimalFormat round = new DecimalFormat("#.00");
    public static double EPS = 1e-6;
    public static int MOD = (int) (1e9 + 7);
    public static int[] dx = {0, 0, 1, -1};
    public static int[] dy = {1, -1, 0, 0};

    public static void dbg(String varName, Object value) {
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + value);
    }

    public static long invMod(long x) {
        if (x <= 1) {
            return x;
        }
        return MOD - MOD / x * invMod(MOD % x) % MOD;
    }

    public static List<Long> primes = new ArrayList<>();
    static void sieve(int n){
        primes.clear();
        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true);
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                primes.add((long) i);
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    
    public static long sigma(long n){
        long ans = 1;
        for (long p : primes) {
            if(p * p > n) break;
            long m = p;
            while(n % p == 0){
                n /= p;
                m = (m * p);
            }
            ans = (ans * (m - 1) / (p - 1));
        }
        if (n > 1) {
            ans = (ans * ((n * n - 1) / (n - 1)));
        }
        return ans;
    }

    public static void solve(int num_tc) {
        long n = sc.nextLong();
        sieve((int)(2e6+1));
        long[] pref = new long[(int) (2e6 + 1)];
        pref[0] = 1l;
        for (int i = 1; i <= 2e6; i++) {
            pref[i] = (pref[i - 1] * sigma(i)) % MOD;
        }

        StringBuilder out = new StringBuilder();
        for(int i = 0; i < n; i++){
            int l = sc.nextInt();
            int r = sc.nextInt();
            long ans = (pref[r] * invMod(pref[l - 1])) % MOD;
            out.append(ans).append("\n");
        }
        System.out.print(out);
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
