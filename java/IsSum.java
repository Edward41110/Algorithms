package myAlgorithms;

public class IsSum {
	
	public static boolean isSum(int[]arr, int i, int sum, int aim) {
		if (sum > aim) {
			return false;
		}
		if (i == arr.length) {
			return sum == aim;
		}
		return isSum(arr, i + 1, sum, aim) || isSum(arr, i + 1, sum + arr[i], aim);
	}
	
	public static boolean isSum(int[]arr, int aim) {
		int sum = 0;
		for (int value : arr) {
			sum += value;
		}
		if (aim > sum) {
			return false;
		}
		boolean[][]dp = new boolean[arr.length + 1][aim + 1];
		for (int i = 0;i < dp.length;i++) {
			dp[i][aim] = true;
		}
		for (int i = arr.length - 1;i >= 0;i--) {
			for (int j = aim;j >= 0;j--) {
				if (j + arr[i] <= aim) {
					dp[i][j] = dp[i + 1][j] || dp[i + 1][j + arr[i]];
				}
			}
		}
		return dp[0][0];
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]arr = {3, 2, 7, 13};
		System.out.println(isSum(arr, 12));
	}
}
