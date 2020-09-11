package myAlgorithms;

public class LongestSubarraySumLessThanAim {

    public static int method(int[]arr, int aim) {
        int[]minSum = new int[arr.length];
        int[]minSumIndex = new int[arr.length];
        minSum[arr.length - 1] = arr[arr.length - 1];
        minSumIndex[arr.length - 1] = arr.length - 1;
        for (int i = arr.length - 2; i >= 0; i--) {
            if (minSum[i + 1] <= 0) {
                minSum[i] = arr[i] + minSum[i + 1];
                minSumIndex[i] = minSumIndex[i + 1];
            } else {
                minSum[i] = arr[i];
                minSumIndex[i] = i;
            }
        }

        int sum = 0;
        int end = 0;
        int maxLength = 0;
        for (int start = 0; start < arr.length; start++) {
            while (end < arr.length && sum + minSum[end] <= aim) {
                sum += minSum[end];
                end = minSumIndex[end] + 1;
            }
            sum -= end > start ? arr[start] : 0;
            maxLength = Math.max(maxLength, end - start);
            end = Math.max(end, start + 1);
        }
        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{100, 100, 100, 100, 100, 100, 100, 1}, 7));
    }
}
