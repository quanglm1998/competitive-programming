//import java.io.*;
//import java.util.StringTokenizer;
//
//
//public class Template {
//
//    public static void main(String[] args) {
//        FastScanner in = new FastScanner(System.in);
//    }
//
//    static class FastScanner {
//        BufferedReader br;
//        StringTokenizer st;
//
//        public FastScanner(File f) {
//            try {
//                br = new BufferedReader(new FileReader(f));
//            } catch (FileNotFoundException e) {
//                e.printStackTrace();
//            }
//        }
//
//        public FastScanner(InputStream f) {
//            br = new BufferedReader(new InputStreamReader(f));
//        }
//
//        String next() {
//            while (st == null || !st.hasMoreTokens()) {
//                String s = null;
//                try {
//                    s = br.readLine();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//                if (s == null)
//                    return null;
//                st = new StringTokenizer(s);
//            }
//            return st.nextToken();
//        }
//
//        boolean hasMoreTokens() {
//            while (st == null || !st.hasMoreTokens()) {
//                String s = null;
//                try {
//                    s = br.readLine();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//                if (s == null)
//                    return false;
//                st = new StringTokenizer(s);
//            }
//            return true;
//        }
//
//        int nextInt() {
//            return Integer.parseInt(next());
//        }
//
//        long nextLong() {
//            return Long.parseLong(next());
//        }
//
//        double nextDouble() {
//            return Double.parseDouble(next());
//        }
//    }
//}