package myAlgorithms;

public class LongestSubarraySumEqualToAim {

    public static int method(int[]arr, int aim) {
        int left = 0, right = 1;
        int maxLength = 0;
        int sum = arr[0];
        while (right < arr.length || sum >= aim) {
            if (sum < aim) {
                sum += arr[right++];
            } else {
                maxLength = sum == aim ? Math.max(maxLength, right - left) : maxLength;
                sum -= arr[left++];
            }
        }
        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{3, 2, 1, 5, 1, 1, 1, 1, 1, 1}, 6));
    }
}
