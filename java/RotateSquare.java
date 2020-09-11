package myAlgorithms;

public class RotateSquare {

	public static void rotateSquare(int[][]square, int topLeft, int bottomRight) {
		if (topLeft >= bottomRight) {
			return;
		}
		for(int i = topLeft;i < bottomRight;i++) {
			int temp = square[i][bottomRight];
			square[i][bottomRight] = square[topLeft][i];
			square[topLeft][i] = square[bottomRight + topLeft - i][topLeft];
			square[bottomRight + topLeft - i][topLeft] = square[bottomRight][bottomRight + topLeft - i];
			square[bottomRight][bottomRight + topLeft - i] = temp;
		}
		rotateSquare(square, topLeft + 1, bottomRight - 1);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]square =	{	{1, 2, 3, 4, 5},
							{6, 7, 8, 9, 10},
							{11, 12, 13, 14, 15},
							{16, 17, 18, 19, 20},
							{21, 22, 23, 24, 25}
						};
		rotateSquare(square, 0, square.length - 1);
		for(int i = 0;i < square.length;i++) {
			for(int j = 0;j < square[0].length;j++) {
				System.out.print(square[i][j] + "\t");
			}
			System.out.println();
		}
	}

}
