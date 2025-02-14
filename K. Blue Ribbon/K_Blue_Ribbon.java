
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
    public static DecimalFormat round = new DecimalFormat("#.00");
    public static double EPS = 1e-6;
    public static int MOD = (int) (1e9 + 7);
    public static int[] dx = {0, 0, 1, -1};
    public static int[] dy = {1, -1, 0, 0};

    public static void dbg(String varName, Object value) {
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + value);
    }
    public static void dbga(String varName, Object[] arr){
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + Arrays.toString(arr));
    }

    static class SubsetInfo implements Iterable<Map.Entry<Long, Map<Long, ArrayList<Long>>>>{
        Map<Long, Map<Long, ArrayList<Long>>> map;
        public SubsetInfo(){
            map = new HashMap<>();
        }
        public void add(long xorsum, long subsetsum, long size){
            if(!map.containsKey(xorsum)){
                map.put(xorsum, new HashMap<>());
            }
            Map<Long, ArrayList<Long>> submap = map.get(xorsum);
            if(!submap.containsKey(subsetsum)){
                submap.put(subsetsum, new ArrayList<>());
            }
            submap.get(subsetsum).add(size);
        }
        public static long calculateMatchingSets(ArrayList<Long> ares, ArrayList<Long> bres, int x, int y){
            Collections.sort(ares);
            Collections.sort(bres);
            int ans = 0;
            for(long a : ares){
                int up = upperBound(bres, y - a);
                //dbg("up: ", up);
                int low = lowerBound(bres, x - a);
                //dbg("low: ", low);
                ans += up - low;
            }
            return ans;
        }
        public static int lowerBound(List<Long> list, long key) {
            int left = 0, right = list.size();
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (list.get(mid) >= key) {
                    right = mid; // Move left to find the first occurrence
                } else {
                    left = mid + 1;
                }
            }
            return left; // First index where element is >= key
        }        
        public static int upperBound(List<Long> list, long key) {
            return lowerBound(list, key + 1);
        }        
        public Map<Long, ArrayList<Long>> getxor(long xorsum){
            return map.get(xorsum);
        }
        @Override
        public Iterator<Map.Entry<Long, Map<Long, ArrayList<Long>>>> iterator() {
            return map.entrySet().iterator();
        }
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("{\n");
            for(Map.Entry<Long, Map<Long, ArrayList<Long>>> entry : map.entrySet()){
                for(Map.Entry<Long, ArrayList<Long>> subentry : entry.getValue().entrySet()){
                    sb.append("    [").append(entry.getKey()).append("]");
                    sb.append("[").append(subentry.getKey()).append("]");
                    sb.append(" = ").append(subentry.getValue()).append("\n");
                }
            }
            sb.append("}\n");
            return sb.toString();
        }
    }
    static SubsetInfo ainfo = new SubsetInfo();
    static SubsetInfo binfo = new SubsetInfo();

    public static void solve(int num_tc) {
        int n = sc.nextInt();
        long s = sc.nextLong();
        int x = sc.nextInt();
        int y = sc.nextInt();
        Long[] fullset = new Long[n];
        for(int i = 0; i < n; i++){
            fullset[i] = sc.nextLong();
        }
        Long[] seta = new Long[n / 2];
        Long[] setb = new Long[n / 2 + n % 2];
        System.arraycopy(fullset, 0, seta, 0, n / 2);
        System.arraycopy(fullset, n / 2, setb, 0, n / 2 + n % 2);
        //dbga("seta", seta);
        //dbga("seta", setb);
        for(long mask = 0; mask < (1 << seta.length); mask++){
            long subsetsum = 0;
            long subsetxor = 0;
            long subsetsize = 0;
            for(int i = 0; i < seta.length; i++){
                if((mask & (1 << i)) != 0){
                    subsetsum += seta[i];
                    subsetxor ^= seta[i];
                    subsetsize++;
                }
            }
            ainfo.add(subsetxor, subsetsum, subsetsize);
        }
        //dbg("ainfo", ainfo);
        for(long mask = 0; mask < (1 << setb.length); mask++){
            long subsetsum = 0;
            long subsetxor = 0;
            long subsetsize = 0;
            for(int i = 0; i < setb.length; i++){
                if((mask & (1 << i)) != 0){
                    subsetsum += setb[i];
                    subsetxor ^= setb[i];
                    subsetsize++;
                }
            }
            binfo.add(subsetxor, subsetsum, subsetsize);
        }
        //dbg("binfo", binfo);
        long ans = 0;
        for(Map.Entry<Long, Map<Long, ArrayList<Long>>> entry : ainfo){
            long xor_val = entry.getKey();
            //dbg("xor_val", xor_val);
            Map<Long, ArrayList<Long>> asubmap = entry.getValue();
            //dbg("asubmap", asubmap);
            Map<Long, ArrayList<Long>> bsubmap = binfo.getxor(xor_val);
            //dbg("bsubmap", bsubmap);
            for(Map.Entry<Long, ArrayList<Long>> aEntry : asubmap.entrySet()){
                long asum = aEntry.getKey();
                //dbg("asum", asum);
                long bsum = s - asum;
                //dbg("bsum", bsum);
                if(!bsubmap.containsKey(bsum)) continue;
                ArrayList<Long> ares = aEntry.getValue();
                //dbg("ares", ares);
                ArrayList<Long> bres = bsubmap.get(bsum);
                //dbg("bres", bres);
                long delta = SubsetInfo.calculateMatchingSets(ares, bres, x, y);
                //dbg("delta", delta);
                ans += delta;
            }
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
