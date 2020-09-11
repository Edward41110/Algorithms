package myAlgorithms;

public class CoinsWay {

    public static int method(int[] arr, int aim) {
        int[]dp = new int[aim + 1];
        // base case
        dp[0] = 1;
        for (int i = 1; i < aim + 1; i++) {
            dp[i] = 0;
        }
        // state transition
        for (int i = arr.length - 1; i >= 0; i--) {
            for (int j = 0; j <= aim; j++) {
                dp[j] += j - arr[i] >= 0 ? dp[j - arr[i]] : 0;
            }
        }
        return dp[aim];
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{5, 3, 2}, 10));
    }
}
