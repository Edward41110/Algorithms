package myAlgorithms;

import java.util.Arrays;
import java.util.Comparator;

public class LowestString {
	
	public static class MyComparator implements Comparator<String> {
		@Override
		public int compare(String a, String b) {
			return (a + b).compareTo(b + a);
		}
	}
	
	public static String lowestString(String[]strs) {
		Arrays.sort(strs, new MyComparator());
		StringBuilder res = new StringBuilder();
		for (String str : strs) {
			res.append(str);
		}
		return res.toString();
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
