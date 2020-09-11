package myAlgorithms;

public class FindNumber {

	public static void findNumber(int[][]matrix, int target) {
		int row = 0;
		int col = matrix[0].length - 1;
		int loc = matrix[row][col];
		while (loc != target) {
			if (loc > target) {
				System.out.print(loc + " -> ");
				if (col >= 0) {
					loc = matrix[row][--col];
				} else {
					return;
				}
			} else {
				System.out.print(loc + " -> ");
				if (row < matrix.length - 1) {
					loc = matrix[++row][col];
				} else {
					return;
				}
			}
		}
		if (loc == target) {
			System.out.print(loc);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]matrix = {{1, 3, 5, 6}, {2, 5, 7, 9}, {4, 6, 8, 10}};
		findNumber(matrix, 4);
	}
}
