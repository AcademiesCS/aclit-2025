
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class G_Titration {

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

    // Will TLE on large inputs but give correct answers
    public static void solve(int num_tc) {
        int n = sc.nextInt();
        int q = sc.nextInt();
        long[] pref = new long[n + 1];
        
        for(int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + sc.nextLong();
        }
        
        for(int i = 0; i < q; i++) {
            long b = sc.nextLong();
            long minDiff = Long.MAX_VALUE;
            // Linear search instead of binary search
            for(int j = 0; j <= n; j++) {
                minDiff = Math.min(minDiff, Math.abs(pref[j] - b));
            }
            System.out.println(minDiff);
        }
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
