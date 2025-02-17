
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class F_Ralph_and_Brian {
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

    static class II{
        public long price;
        public int index;
        public II(long price, int index){
            this.price = price;
            this.index = index;
        }
    }
    public static void solve(int num_tc) {
        int n = sc.nextInt();
        long x = sc.nextLong();
        long[] prices = new long[n];
        long[] increments = new long[n];
        long[] amount = new long[n];
        PriorityQueue<II> pq = new PriorityQueue<>((a, b) -> {
            if(a.price == b.price){
                return a.index - b.index;
            }
            return Long.compare(a.price, b.price);
        });
        for(int i = 0; i < n ;i++){
            prices[i] = sc.nextLong();
            increments[i] = sc.nextLong();
            amount[i] = sc.nextLong();
            pq.add(new II(prices[i], i));
        }
        long moneyspent = 0;
        long bottles = 0;
        while(!pq.isEmpty()){
            II soda = pq.poll();
            if(amount[soda.index] == 0){
                continue;
            }
            if(moneyspent + prices[soda.index] > x){
                break;
            }
            moneyspent += prices[soda.index];
            bottles++;
            amount[soda.index]--;
            prices[soda.index] += increments[soda.index];
            if(amount[soda.index] > 0){
                pq.add(new II(soda.price + increments[soda.index], soda.index));
            }
        }
        System.out.println(bottles + " " + moneyspent);
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
