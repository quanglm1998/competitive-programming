import java.io.*;
import java.util.*;
 
public class Main{
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int tc = in.nextInt();
        while (tc--) {
            int n = in.nextInt();
            int c = in.nextInt();
            int sum = 0;
            ArrayList<Integer> a = new ArrayList<Integer>(n);
            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
                sum += a[i];
            }
            BitSet s = new BitSet(sum + 1);
            for (int i = 0; i < n; i++) {
                s = 
            }
        }
    }
}