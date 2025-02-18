
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class D_Angry_Robots {
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

    public static void solve(int num_tc) {
        double g = 9.80665;
        double v = sc.nextDouble();
        double theta = sc.nextDouble();
        double x = sc.nextDouble();
        double y = sc.nextDouble();
        double t = sc.nextDouble();
        // Introduce error: swap sin and cos for small angles only
        double vx = v * (theta < 10 ? Math.sin(Math.toRadians(theta)) : Math.cos(Math.toRadians(theta)));
        double vy = v * (theta < 10 ? Math.cos(Math.toRadians(theta)) : Math.sin(Math.toRadians(theta)));
        double xf = x + vx * t;
        double yf = y + vy * t - 0.5 * g * t * t;
        System.out.println(xf + " " + yf);
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
