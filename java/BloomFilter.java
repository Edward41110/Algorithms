package myAlgorithms;

public class BloomFilter {

	static final int INT_SIZE = 1000000;
	static final int HASH_TIMES = 5;
	int[]map;
	
	public BloomFilter() {
		map = new int[INT_SIZE];
	}
	
	public void put(int key) {
		int hashCode = myHash(Integer.toString(key));
		mark(hashCode);
		for (int i = 0; i < HASH_TIMES - 1; i++) {
			hashCode = myHash(Integer.toString(hashCode));
			mark(hashCode);
		}
	}
	
	public boolean isExist(int key) {
		int hashCode = myHash(Integer.toString(key));
		boolean isExist = true;
		for (int i = 0; i < HASH_TIMES; i++) {
			if (check(hashCode)) {
				isExist = false;
				break;
			}
			hashCode = myHash(Integer.toString(hashCode));
		}
		return isExist;
	}
	
	private int myHash(String str) {
		int hashCode = str.hashCode();
		return hashCode < 0 ? hashCode + Integer.MAX_VALUE : hashCode;
	}
	
	private void mark(int hashCode) {
		hashCode %= 32 * INT_SIZE;
		int intIndex = hashCode / 32;
		int bitIndex = hashCode % 32;
		this.map[intIndex] = (this.map[intIndex] | (1 << bitIndex));
	}
	
	private boolean check(int hashCode) {
		hashCode %= 32 * INT_SIZE;
		int intIndex = hashCode / 32;
		int bitIndex = hashCode % 32;
		return ((this.map[intIndex] & (1 << bitIndex)) == 0);
		
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final int nums = (int)1e6;
		final int time = 3;
		BloomFilter bf = new BloomFilter();
		for (int i = 0;i < nums;i++) {
			bf.put(time * i);
		}
		int cnt = 0;
		for (int i = 0;i < nums * time;i++) {
			if (i % time != 0 && bf.isExist(i)) {
				cnt++;
				System.out.println(i);
			}
		}
		System.out.printf("wrong: %.6f %%", (double)(100 * cnt) / (nums * time));
	}
}
