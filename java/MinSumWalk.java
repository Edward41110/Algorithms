package myAlgorithms;

public class MinSumWalk {

	public static int walk(int[][]matrix, int i, int j) {
		if (i == matrix.length - 1 && j == matrix[0].length - 1) {
			return matrix[i][j];
		}
		if (i == matrix.length - 1) {
			return matrix[i][j] + walk(matrix, i, j + 1);
		}
		if (j == matrix[0].length - 1) {
			return matrix[i][j] + walk(matrix, i + 1, j);
		}
		int right = walk(matrix, i, j + 1);
		int down = walk(matrix, i + 1, j);
		return matrix[i][j] + Math.min(right, down);
	}
	
	public static int walk(int[][]matrix) {
		if (matrix == null || matrix.length == 0 || matrix[0] == null || matrix[0].length ==0) {
			return 0;
		}
		int row = matrix.length;
		int col = matrix[0].length;
		int[][]dp = new int[row][col];
		dp[row - 1][col - 1] = matrix[row - 1][col - 1];		// base case
		for (int i = row - 2;i >= 0;i--) {
			dp[i][col - 1] = dp[i + 1][col - 1] + matrix[i][col - 1];
		}
		for (int j = row - 2;j >= 0;j--) {
			dp[row - 1][j] = dp[row - 1][j + 1] + matrix[row - 1][j];
		}
		for (int i = row - 2;i >= 0;i--) {
			for (int j = col - 2;j >= 0;j--) {
				dp[i][j] = matrix[i][j] + Math.min(dp[i + 1][j], dp[i][j + 1]);
			}
		}
		return dp[0][0];
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]matrix = {{1, 3, 5, 9}, {8, 1, 3, 4}, {5, 0, 6, 1}, {8, 8, 4, 0}};
		System.out.println(walk(matrix));
	}

}
