
    import java.io.*;
    import java.text.DecimalFormat;
    import java.util.*;

    public class C_Laptops {
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

        public static Scanner sc = new Scanner(System.in);
        public static DecimalFormat round = new DecimalFormat("#.00");
        public static double EPS = 1e-6;
        public static int MOD = (int) (1e9 + 7);
        public static int[] dx = {0, 0, 1, -1};
        public static int[] dy = {1, -1, 0, 0};

        public static void dbg(String varName, Object value) {
            int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
            System.err.println(lineNumber + ": " + varName + " = " + value);
        }

        public static String process(String s){
            if(s.length() < 5) return s;
            return s.substring(0, 2) + s.substring(s.length() - 4);
        }

        public static void solve(int num_tc) {
            int n, m;
            n = sc.nextInt();
            m = sc.nextInt();
            String[] a = new String[n];
            String[] b = new String[m];
            for(int i = 0; i < n; i++){
                a[i] = sc.next();
                //a[i] = process(a[i]);
            }
            for(int i = 0; i < m; i++){
                b[i] = sc.next();
                //b[i] = process(b[i]);
            }
            for(int i=  0; i < n; i++){
                for(int j= 0; j < m; j++){
                    if(a[i].equals(b[j])){
                        System.out.println("YES");
                        return;
                    }
                }
            }
            System.out.println("NO");
        }

        public static void main(String[] args) {
            int t = 1;
            //t = sc.nextInt();
            for (int T = 0; T < t; T++) {
                solve(T + 1);
            }
        }
    }
