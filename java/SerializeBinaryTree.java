package myAlgorithms;

import java.util.LinkedList;
import java.util.Queue;

public class SerializeBinaryTree {
	
	public static class Node{
		int value;
		Node left;
		Node right;
		public Node(int val) {
			this.value = val;
		}
	}
	
	public static String serialize(Node head) {
		if (head == null) {
			return "#_";
		}
		String preStr = head.value + "_";
		preStr += serialize(head.left);
		preStr += serialize(head.right);
		return preStr;
	}
	
	public static Node reconByPreString(String preStr) {

		String[]values = preStr.split("_");
		Queue<String> queue = new LinkedList<String>();
		for (int i = 0;i < values.length;i++) {
			queue.offer(values[i]);
		}
		return reconPreOrder(queue);
	}
	
	public static Node reconPreOrder(Queue<String> queue) {
		String value = queue.poll();
		if ("#".equals(value)) {
			return null;
		}
		Node head = new Node(Integer.parseInt(value));
		head.left = reconPreOrder(queue);
		head.right = reconPreOrder(queue);
		return head;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}
}
