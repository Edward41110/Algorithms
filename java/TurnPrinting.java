package myAlgorithms;

public class TurnPrinting {

	public static void turnPrinting(int[][]matrix) {
		for (int i = 0; i < matrix.length + matrix[0].length - 1;i++) {
			if (i % 2 == 1) {
				for (int j = (i >= matrix[0].length ? i - matrix[0].length + 1 : 0);
				 j <= (i >= matrix.length ? matrix.length - 1 : i);j++) {
					System.out.print(matrix[j][i - j] + " ");
				}
			} else {
				for (int j = (i >= matrix.length ? matrix.length - 1 : i);
				 j >= (i >= matrix[0].length ? i - matrix[0].length + 1 : 0);j--) {
					System.out.print(matrix[j][i - j] + " ");
				}
			}
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
		turnPrinting(matrix);
	}
}
