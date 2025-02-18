
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class H_Field_Day {
    static class Multiset<T> {
        private final NavigableMap<T, Integer> map;
        
        public Multiset() {
            map = new TreeMap<>();
        }
        
        public Multiset(Iterable<T> arr){ 
            map = new TreeMap<>();
            initialize(arr);
        }
    
        private void initialize(Iterable<T> arr) {
            for (T a : arr) add(a);
        }
        
        public void add(T a) {
            map.put(a, map.getOrDefault(a, 0) + 1);
        }
        
        public void remove(T a){
            if(map.containsKey(a)){
                map.put(a, map.get(a) - 1);
                if(map.get(a) == 0){
                    map.remove(a);
                }
            }
        }
        
        public int count(T a) {
            return map.getOrDefault(a, 0);
        }
        
        // Additional methods
        public boolean isEmpty() {
            return map.isEmpty();
        }
        
        public int size() {
            return map.values().stream().mapToInt(Integer::intValue).sum();
        }
        
        public void clear() {
            map.clear();
        }
        
        public T first() {
            return map.firstKey();
        }
        
        public T last() {
            return map.lastKey();
        }
        
        public T ceiling(T a) {
            return map.ceilingKey(a);
        }
        
        public T floor(T a) {
            return map.floorKey(a);
        }
        
        public Set<T> elementSet() {
            return map.keySet();
        }
        
        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder("[");
            for (Map.Entry<T, Integer> entry : map.entrySet()) {
                for (int i = 0; i < entry.getValue(); i++) {
                    sb.append(entry.getKey()).append(", ");
                }
            }
            if (sb.length() > 1) {
                sb.setLength(sb.length() - 2);
            }
            return sb.append("]").toString();
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Multiset)) return false;
            Multiset<?> multiset = (Multiset<?>) o;
            return map.equals(multiset.map);
        }
        
        @Override
        public int hashCode() {
            return map.hashCode();
        }
    }
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

    public static void solve(int num_tc) {
        int n = sc.nextInt();
        int a = sc.nextInt();
        int b = sc.nextInt();
        b += a;
        long[] pref = new long[n + 1];
        pref[0] = 0;
        for(int i = 0; i < n; i++){
            pref[i + 1] = pref[i] + sc.nextLong();
        }
        Multiset<Long> window = new Multiset<>();
        long ans = Long.MIN_VALUE;
        for(int i = a; i <= n; i++){
            if(i > b){
                window.remove(pref[i - b - 1]);
            }
            window.add(pref[i - a]);
            ans = Math.max(ans, pref[i] - window.first());
        }
        System.out.println(ans);
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
