
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class I_2_Navigation_Hard_Version {
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
    public static void dbg(String varName, Object[] arr){
        int lineNumber = Thread.currentThread().getStackTrace()[2].getLineNumber();
        System.err.println(lineNumber + ": " + varName + " = " + Arrays.toString(arr));
    }

    static ArrayList<Integer> adj[];
    static TreeSet<Integer> requiredClasses;
    static int maxdepth;
    static int maxnode;

    static void dfsOnlyRequiredClasses(int node, int parent, int depth){
        if(requiredClasses.contains(node)){
            if(depth > maxdepth){
                maxdepth = depth;
                maxnode = node;
            }
        }
        for(int nb : adj[node]){
            if(nb == parent){
                continue;
            }
            dfsOnlyRequiredClasses(nb, node, depth + 1);
        }
    }

    static ArrayList<Integer> currentPath;
    static ArrayList<Integer> requiredClassesSeen;
    static boolean foundAllClasses = false;
    static void dfsAllRequired(int node, int parent){
        currentPath.add(node);
        if(requiredClasses.contains(node)){
            requiredClassesSeen.add(node);
            if(requiredClassesSeen.size() == requiredClasses.size()){
                foundAllClasses = true;
                return;
            }
        }
        for(int nb : adj[node]){
            if(nb == parent){
                continue;
            }
            dfsAllRequired(nb, node);
            if(foundAllClasses){
                return;
            }
        }
        if(requiredClasses.contains(node)) requiredClassesSeen.remove(requiredClassesSeen.size() - 1);
        currentPath.remove(currentPath.size() - 1);
    }
    
    public static void solve(int num_tc) {
        int n = sc.nextInt();
        adj = new ArrayList[n];
        for(int i = 0; i < n; i++){
            adj[i] = new ArrayList<>();
        }
        for(int i = 0; i < n - 1; i++){
            int u = sc.nextInt() - 1;
            int v = sc.nextInt() - 1;
            adj[u].add(v);
            adj[v].add(u);
        }
        int k = sc.nextInt();
        if(k == 1){
            solveK1();
            return;
        }
        requiredClasses = new TreeSet<>();
        for(int i = 0; i < k; i++){
            requiredClasses.add(sc.nextInt() - 1);
        }
        maxdepth = 0;
        dfsOnlyRequiredClasses(requiredClasses.first(), -1, 0);
        int firstRequiredClass = maxnode;
        currentPath = new ArrayList<>();
        requiredClassesSeen = new ArrayList<>();
        dfsAllRequired(firstRequiredClass, -1);
        if(!foundAllClasses){
            System.out.println(-1);
            return;
        }
        int allClassesPathSize = currentPath.size() - 1;
        maxdepth = 0;
        simpledfs(currentPath.get(0), currentPath.get(1), 0);
        allClassesPathSize += maxdepth;
        maxdepth = 0;
        simpledfs(currentPath.get(currentPath.size() - 1), currentPath.get(currentPath.size() - 2), 0);
        allClassesPathSize += maxdepth;
        System.out.println(allClassesPathSize);        
    }
    public static void simpledfs(int node, int parent, int depth){
        if(depth > maxdepth){
            maxdepth = depth;
            maxnode = node;
        }
        for(int nb : adj[node]){
            if(nb == parent) continue;
            simpledfs(nb, node, depth + 1);
        }
    }
    public static void solveK1(){
        int requiredClass = sc.nextInt() - 1;
        ArrayList<Integer> pathLengths = new ArrayList<>();
        for(int nb : adj[requiredClass]){
            maxdepth = 0;
            simpledfs(nb, requiredClass, 1);
            pathLengths.add(maxdepth);
        }  
        Collections.sort(pathLengths, Collections.reverseOrder());
        System.out.println(pathLengths.get(0) + pathLengths.get(1));
    }

    public static void main(String[] args) {
        int t = 1;
        //t = sc.nextInt();
        for (int T = 0; T < t; T++) {
            solve(T + 1);
        }
    }
}
