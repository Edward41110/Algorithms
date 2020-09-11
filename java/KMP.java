package myAlgorithms;

public class KMP {
	
	public static int[]getNextArray(char[]charArr) {
		if (charArr == null || charArr.length < 2) {
			return new int[]{-1};
		}
		int[]next = new int[charArr.length];
		next[0] = -1;
		next[1] = 0;
		int i = 2;
		int cn = 0;
		while (i < charArr.length) {
			if (charArr[i - 1] == charArr[cn]) {
				next[i++] = ++cn;
			} else if (cn > 0) {
				cn = next[cn];
			} else {
				next[i++] = 0;
			}
		}
		return next;
	}
	
	public static int method(String str1, String str2) {
		if (str2 == null || str2.length() > str1.length()) {
			return -1;
		}
		char[]charArr1 = str1.toCharArray();
		char[]charArr2 = str2.toCharArray();
		int[]next = getNextArray(charArr2);
		int i = 0;
		int j = 0;
		while (i < charArr1.length && j < charArr2.length) {
			if (charArr1[i] == charArr2[j]) {
				i++;
				j++;
			} else if (next[j] == -1) {
				i++;
			} else {
				j = next[j];
			}
		}
		return j == charArr2.length ? i - j : -1;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(method("abababac", "ababac"));
	}

}
