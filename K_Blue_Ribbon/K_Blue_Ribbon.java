
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class K_Blue_Ribbon {
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
    public static StringBuilder out = new StringBuilder();
    public static DecimalFormat round = new DecimalFormat("#.00");
    public static double EPS = 1e-6;
    public static int MOD = (int) (1e9 + 7);
    public static int[] dx = {0, 0, 1, -1};
    public static int[] dy = {1, -1, 0, 0};

    public static void dbg(String varName, Object value) {
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + value);
    }
    public static void dbg(String varName, Object[] arr){
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + Arrays.toString(arr));
    }

    static long[][][] pref;

    static void print(long[][][] a){
        StringBuilder res = new StringBuilder();
        res.append("[\n");
        for(long[][] g : a){
            res.append("  {\n");
            for(long[] r : g){
                res.append("    ").append(Arrays.toString(r)).append("\n");
            }
            res.append("  }");
        }
        res.append("]");
        System.out.println(res.toString());
    
    }
    static void print(long[][] a){
        StringBuilder res = new StringBuilder();
        res.append("[\n");
        for(long[] r : a){
            res.append("    ").append(Arrays.toString(r)).append("\n");
        }
        res.append("]");
        System.out.println(res.toString());
    }


    static long get(int x, int y, int z){
        if(x < 0 || y < 0 || z < 0){
            return 0;
        }
        return pref[x + 1][y + 1][z + 1];
    }

    public static void solve(int num_tc) {
        int n = sc.nextInt();
        int[] t = new int[n];
        for(int i = 0; i < n; i++){
            t[i] = sc.nextInt();
        }
        int X = 511;
        int S = 100;
        long[][][] currentLayer = new long[S + 1][X + 1][n + 1];
        currentLayer[0][0][0] = 1;
        for(int i = 0; i < n ;i++){
            if(t[i] > S){
                continue;
            }
            long[][][] nextLayer = new long[S + 1][X + 1][n + 1];
            for(int j = 0; j <= S; j++){
                for(int k = 0; k <= X; k++){
                    for(int l = 0; l < n; l++){
                        nextLayer[j][k][l] += currentLayer[j][k][l];
                        if((j + t[i] <= S) && ((k ^ t[i]) <= X) && (l + 1 <= n)){
                            nextLayer[j + t[i]][k ^ t[i]][l + 1] += currentLayer[j][k][l];
                        }
                    }
                }
            }
            currentLayer = nextLayer;
        }
        //print(currentLayer);
        pref = new long[S + 2][X + 2][n + 2];
        for(int s = 1; s <= S + 1; s++){
            for(int x = 1; x <= X + 1; x++){
                for(int c = 1; c <= n + 1; c++){
                    pref[s][x][c] =
                        pref[s-1][x][c] + pref[s][x-1][c] + pref[s][x][c-1]
                        - pref[s-1][x-1][c] - pref[s-1][x][c-1] - pref[s][x-1][c-1]
                        + pref[s-1][x-1][c-1]
                        + currentLayer[s-1][x-1][c-1];
                }
            }
        }
        //print(pref);


        int q = sc.nextInt();
        for(int i = 0; i < q; i++){
            int a = sc.nextInt();
            int b = sc.nextInt();
            int c = sc.nextInt();
            int d = sc.nextInt();
            int e = sc.nextInt();
            int f = sc.nextInt();
            long ans = get(b, d, f)
                - get(a - 1, d, f) 
                - get(b, c - 1, f) 
                - get(b, d, e - 1)
                + get(a - 1, c - 1, f) 
                + get(b, c - 1, e - 1) 
                + get(a - 1, d, e - 1)
                - get(a - 1, c - 1, e - 1);
            out.append(ans).append("\n");
        }
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
        System.out.println(out.toString());
    }
}
