package myAlgorithms;

public class NumOfoPaths {

    /**
     * 返回路径数
     * @param n 位置数(0~n-1)
     * @param m 初始位置
     * @param p 步数
     * @param k 待求位置
     */
    public static int method(int n, int m, int p, int k) {
        if (m < 0 || m >= n || p < 0 || k < 0 || k >= n) {
            return 0;
        }
        int[]numOfPaths = new int[n];
        int[]help = new int[n];
        numOfPaths[m] = 1;
        while (p-- > 0) {
            help[0] = numOfPaths[1];
            help[n - 1] = numOfPaths[n - 2];
            for (int j = 1; j < n - 1; j++) {
                help[j] = numOfPaths[j - 1] + numOfPaths[j + 1];
            }
            int[]temp = numOfPaths;
            numOfPaths = help;
            help = temp;
        }
        return numOfPaths[k];
    }

    public static void main(String[] args) {
        System.out.println(method(7, 2, 3, 3));
    }
}
