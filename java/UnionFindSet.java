package myAlgorithms;

import java.util.HashMap;
import java.util.List;

public class UnionFindSet {

	public static class Node{
		int value;
		public Node(int val) {
			this.value = val;
		}
	}

	// child, parent
	public HashMap<Node, Node> parentMap;
	public HashMap<Node, Integer> sizeMap;
	
	public UnionFindSet(List<Integer> nums) {
		this.parentMap = new HashMap<>();
		this.sizeMap = new HashMap<>();
		makeSets(nums);
	}
	
	private void makeSets(List<Integer> nums) {
		for (int num : nums) {
			Node newNode = new Node(num);
			this.parentMap.put(newNode, newNode);
			this.sizeMap.put(newNode, 1);
		}
	}
	
	private Node findHead(Node node) {
		Node head = parentMap.get(node);
		while (parentMap.get(head) != head) {
			head = parentMap.get(head);
		}
		Node node2 = parentMap.get(node);
		while (node2 != head) {
			parentMap.put(node, head);
			node = node2;
			node2 = parentMap.get(node);
		}
		return head;
	}
	
	public boolean isSameSet(Node a, Node b) {
		return findHead(a) == findHead(b);
	}
	
	public void union(Node a, Node b) {
		if (a == null || b == null) {
			return;
		}
		Node head1 = findHead(a);
		Node head2 = findHead(b);
		if (sizeMap.get(head1) >= sizeMap.get(head2)) {
			parentMap.put(head2, head1);
			sizeMap.remove(head2);
		} else {
			parentMap.put(head1, head2);
			sizeMap.remove(head1);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		
		
		
	}

}
