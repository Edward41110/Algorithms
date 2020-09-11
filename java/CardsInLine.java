package myAlgorithms;

public class CardsInLine {

    public static int win(int[]arr) {
        if (arr == null || arr.length == 0) {
            return 0;
        }
        return Math.max(first(arr, 0, arr.length - 1), second(arr, 0, arr.length - 1));
    }

    private static int first(int[] arr, int i, int j) {
        if (i == j) {
            return arr[i];
        }
        return Math.max(arr[i] + second(arr, i + 1, j), arr[j] + second(arr, i, j - 1));
    }

    private static int second(int[] arr, int i, int j) {
        if (i == j) {
            return 0;
        }
        return Math.min(first(arr, i + 1, j), first(arr, i, j - 1));
    }

    public static int method(int[]arr) {
        if (arr == null || arr.length == 0) {
            return 0;
        }
        if (arr.length == 1) {
            return arr[0];
        }
        int[][]f = new int[arr.length][arr.length];
        int[][]s = new int[arr.length][arr.length];
        for (int i = 0; i < arr.length; i++) {
            f[i][i] = arr[i];
            s[i][i] = 0;
        }
        for (int i = arr.length - 2; i >= 0; i--) {
            for (int j = i + 1; j < arr.length; j++) {
                f[i][j] = Math.max(arr[i] + s[i + 1][j], arr[j] + s[i][j - 1]);
                s[i][j] = Math.min(f[i + 1][j], f[i][j - 1]);
            }
        }
        return Math.max(f[0][arr.length - 1], s[0][arr.length - 1]);
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{70, 100, 2, 6}));
    }
}
