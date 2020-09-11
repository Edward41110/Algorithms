package myAlgorithms;

import java.util.Stack;

public class BinaryTreeTraversal {

	class Node{
		int value;
		Node left;
		Node right;
		public Node(int val) {
			this.value = val;
		}
	}
	
	public static void preOrderRecur(Node head) {
		if (head == null) {
			return;
		}
		System.out.println(head.value);
		preOrderRecur(head.left);
		preOrderRecur(head.right);
	}
	
	public static void inOrderRecur(Node head) {
		if (head == null) {
			return;
		}
		inOrderRecur(head.left);
		System.out.println(head.value);
		inOrderRecur(head.right);
	}
	
	public static void posOrderRecur(Node head) {
		if (head == null) {
			return;
		}
		posOrderRecur(head.left);
		posOrderRecur(head.right);
		System.out.println(head.value);
	}
	
	public static void preOrderUnRecur(Node head) {
		if (head != null) {
			Stack<Node> stack = new Stack<Node>();
			stack.add(head);
			while (!stack.isEmpty()) {
				head = stack.pop();
				System.out.println(head.value);
				if (head.right != null) {
					stack.push(head.right);
				}
				if (head.left != null) {
					stack.push(head.left);
				}
			}
		}
	}
	
	public static void inOrderUnRecur(Node head) {
		if (head != null) {
			Stack<Node> stack = new Stack<Node>();
			while (!stack.isEmpty() || head != null) {
				if (head != null) {
					stack.push(head);
					head = head.left;
				} else {
					head = stack.pop();
					System.out.println(head.value);
					head = head.right;
				}
			}
		}
	}
	
	public static void posOrderUnRecur1(Node head) {
		Stack<Node> stack = new Stack<Node>();
		if (head != null) {
			Stack<Node> help = new Stack<Node>();
			help.add(head);
			while (!help.isEmpty()) {
				head = help.pop();
				stack.push(head);
				if (head.left != null) {
					help.push(head.left);
				}
				if (head.right != null) {
					help.push(head.right);
				}
			}
		}
		while (!stack.isEmpty()) {
			System.out.println(stack.pop().value);
		}
	}
	
	public static void posOrderUnRecur2(Node head) {
		if (head != null) {
			Stack<Node> stack = new Stack<Node>();
			stack.push(head);
			Node c = null;
			while (!stack.isEmpty()) {
				c = stack.peek();
				if (c.left != null && c.right != null && head != c.right) {
					stack.push(c.left);
				} else if (c.right != null && head != c.right) {
					stack.push(c.right);
				} else {
					System.out.println(stack.pop().value);
					head = c;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}

}
