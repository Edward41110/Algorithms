package myAlgorithms;

import java.util.Random;

public class Manacher {

	public static char[]manacherString(String str) {
		char[]charArr = str.toCharArray();
		char[]res = new char[str.length() * 2 + 1];
		int index = 0;
		for (int i = 0;i != res.length;i++) {
			res[i] = (i & 1) == 0 ? '#' : charArr[index++];
		}
		return res;
	}
	
	public static int maxLcpsLength(String str) {
		if (str == null || str.length() == 0) {
			return 0;
		}
		char[]charArr = manacherString(str);
		int[]pArr = new int[charArr.length];
		int C = -1;
		int R = -1;
		int max = Integer.MIN_VALUE;
		for (int i = 0;i != charArr.length;i++) {
			pArr[i] = R > i ? Math.min(pArr[2 * C - i], R - i) : 1;
			while(i + pArr[i] < charArr.length && i - pArr[i] > -1) {
				if (charArr[i + pArr[i]] == charArr[i - pArr[i]]) {
					pArr[i]++;
				} else {
					break;
				}
			}
			if (i + pArr[i] > R) {
				R = i + pArr[i];
				C = i;
			}
			max = Math.max(max, pArr[i]);
		}
		return max - 1;
	}
	
	public static int method(String str) {
		if (str == null || str.length() == 0) {
			return 0;
		}
		char[]charArr = manacherString(str);
		int[]pArr = new int[charArr.length];
		int C = -1;
		int R = -1;
		int max = Integer.MIN_VALUE;
		for (int i = 0;i < charArr.length;i++) {
			if (i > R || i + pArr[2 * C - i] == R) {
				int j = i > R ? 1 : R - i + 1;
				while (i - j >= 0 && i + j < charArr.length && charArr[i - j] == charArr[i + j]) {
					j++;
				}
				pArr[i] = --j;
				if (j > R - i + 1) {
					C = i;
					R = i + j;
					max = Math.max(max, j);
				}
			} else if (i + pArr[2 * C - i] < R) {
				pArr[i] = pArr[2 * C - i];
			} else if (i + pArr[2 * C - i] > R) {
				pArr[i] = R - i;
			}
		}
		return max;
	}
	
	public static String getRandomString(int length){
	     String str = "0123456789";
	     Random random = new Random();
	     StringBuffer sb = new StringBuffer();
	     for(int i = 0;i < length;i++){
	       int number = random.nextInt(10);
	       sb.append(str.charAt(number));
	     }
	     return sb.toString();
	 }
	
	public static void test() {
		final int TEST_TIMES = (int) 1e6;
		final int MAX_LENGTH = 20;
		boolean nice = true;
		for (int i = 0;i < TEST_TIMES;i++) {
			String str = getRandomString((int)(Math.random() * MAX_LENGTH + 1));
			if (maxLcpsLength(str) != method(str)) {
				System.out.println(str);
				nice = false;
				break;
			}
		}
		if (nice) {
			System.out.println("Nice!");
		} else {
			System.out.println("Fuck!");
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test();
	}
}
