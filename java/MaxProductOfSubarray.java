package myAlgorithms;

public class MaxProductOfSubarray {
    public static int method(int[]arr) {
        if (arr == null || arr.length == 0) {
            return 0;
        }
        int a = 1;
        int max = arr[0];
        for (int num : arr) {
            a *= num;
            max = Math.max(max, a);
            a = num == 0 ? 1 : a;
        }
        a = 1;
        for (int i = arr.length - 1; i >= 0; i--) {
            a *= arr[i];
            max = Math.max(max, a);
            a = arr[i] == 0 ? 1 : a;
        }
        return max;
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{2, 3, -2, 4}));
        System.out.println(method(new int[]{-2, 0, -1}));
        System.out.println(method(new int[]{-2}));
    }
}
