package myAlgorithms;

import java.util.HashMap;

public class RandomPool {
	
	private int size;
	private HashMap<String, Integer> keyIndexMap;
	private HashMap<Integer, String> indexKeyMap;
	
	public RandomPool(){
		this.size = 0;
		this.keyIndexMap = new HashMap<>();
		this.indexKeyMap = new HashMap<>();
	}
	
	public void insert(String key) {
		if (keyIndexMap.containsKey(key)) {
			return;
		}
		keyIndexMap.put(key, this.size);
		indexKeyMap.put(this.size++, key);
	}
	
	public void delete(String key) {
		if (!this.keyIndexMap.containsKey(key)) {
			return;
		}
		int index = keyIndexMap.remove(key);
		indexKeyMap.remove(index);
		String lastKey = indexKeyMap.remove(--size);
		keyIndexMap.remove(lastKey);
		keyIndexMap.put(lastKey, index);
		indexKeyMap.put(index, lastKey);
	}
	
	public String getRandom() {
		if (size == 0) {
			return null;
		}
		int index = (int)(Math.random() * size);
		return indexKeyMap.get(index);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
