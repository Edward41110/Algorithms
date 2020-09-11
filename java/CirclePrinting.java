package myAlgorithms;

public class CirclePrinting {

	static void circlePrinting(int[][]matrix, int bR, int bC, int eR, int eC) {
		if (bR > eR || bC > eC) {
			return;
		}
		if (bR == eR) {
			for (int i = bC;i <= eC;i++) {
				System.out.print(matrix[bR][i] + " ");
			}
		} else if (bC == eC) {
			for (int i = bR;i <= eR;i++) {
				System.out.print(matrix[i][bC] + " ");
			}
		} else {
			for (int i = bC;i < eC;i++) {
				System.out.print(matrix[bR][i] + " ");
			}
			for (int i = bR;i < eR;i++) {
				System.out.print(matrix[i][eC] + " ");
			}
			for (int i = eC;i > bC;i--) {
				System.out.print(matrix[eR][i] + " ");
			}
			for (int i = eR;i > bR;i--) {
				System.out.print(matrix[i][bC] + " ");
			}
			circlePrinting(matrix, bR + 1, bC + 1, eR - 1, eC - 1);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
		circlePrinting(matrix, 0, 0, matrix.length - 1, matrix[0].length - 1);
	}
}
