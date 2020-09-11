package myAlgorithms;

public class TrieTree {

	public static class TrieNode{
		public int path;
		public int end;
		public TrieNode[]nexts;
		public TrieNode() {
			this.path = 0;
			this.end = 0;
			this.nexts = new TrieNode[26];
		}
	}
	
	private final TrieNode root;
	public TrieTree() {
		root = new TrieNode();
	}
	
	public void insert(String word) {
		if (word == null) {
			return;
		}
		char[] chars = word.toCharArray();
		TrieNode node = root;
		int index;
		for (char aChar : chars) {
			index = aChar - 'a';
			if (node.nexts[index] == null) {
				node.nexts[index] = new TrieNode();
			}
			node = node.nexts[index];
			node.path++;
		}
		node.end++;
	}
	
	public void delete(String word) {
		if (search(word) == 0) {
			return;
		}
		char[]chars = word.toCharArray();
		TrieNode node = root;
		int index;
		for (char aChar : chars) {
			index = aChar - 'a';
			if (--node.nexts[index].path == 0) {
				node.nexts[index] = null;
				return;
			}
			node = node.nexts[index];
		}
		node.end--;
	}
	
	public int search(String word) {
		if (word == null) {
			return 0;
		}
		char[]chars = word.toCharArray();
		TrieNode node = root;
		int index;
		for (char aChar : chars) {
			index = aChar - 'a';
			if (node.nexts[index] == null) {
				return 0;
			}
			node = node.nexts[index];
		}
		return node.end;
	}
	
	public int prefixNum(String pre) {
		if (pre == null) {
			return 0;
		}
		char[]chars = pre.toCharArray();
		TrieNode node = root;
		int index;
		for (char aChar : chars) {
			index = aChar - 'a';
			if (node.nexts[index] == null) {
				return 0;
			}
			node = node.nexts[index];
		}
		return node.path;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}
}
