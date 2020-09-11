package myAlgorithms;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class SpecialBinaryTree {
	
	public static class Node{
		int value;
		Node left;
		Node right;
		public Node(int val) {
			this.value = val;
		}
	}
	
	public static boolean isBalance(Node head) {
		if (process(head) == -1) {
			return false;
		}
		return true;
	}
	
	public static int process(Node head) {
		if (head == null) {
			return 0;
		}
		int leftData = process(head.left);
		int rightData = process(head.right);
		if (leftData == -1 || rightData == -1 || Math.abs(leftData - rightData) > 1) {
			return -1;
		}
		return Math.max(leftData, rightData) + 1;
	}
	
	public static boolean isBST(Node head) {
		if (head != null) {
			Stack<Node> stack = new Stack<Node>();
			int pre = Integer.MAX_VALUE;
			while (!stack.isEmpty() || head != null) {
				if (head != null) {
					stack.push(head);
					head = head.left;
				} else {
					head = stack.pop();
					if (pre > head.value) {
						return false;
					}
					pre = head.value;
					head = head.right;
				}
			}
		}
		return true;
	}
	
	public static boolean isCBT(Node head) {
		if (head == null) {
			return true;
		}
		Queue<Node> queue = new LinkedList<Node>();
		boolean leaf = false;
		Node l = null;
		Node r = null;
		queue.offer(head);
		while (!queue.isEmpty()) {
			head = queue.poll();
			l = head.left;
			r = head.right;
			if ((leaf && (l != null || r != null)) || (l == null && r != null)) {
				return false;
			}
			if (l != null) {
				queue.offer(l);
			}
			if (r != null) {
				queue.offer(r);
			} else {
				leaf = true;
			}
		}
		return true;
	}
	
	public static int CBTNodeNum(Node head) {
		if (head == null) {
			return 0;
		}
		return bs(head, 1, mostLeftLevel(head, 1));
	}
	
	public static int bs(Node node, int level, int h) {
		if (level == h) {
			return 1;
		}
		if (mostLeftLevel(node.right, level + 1) == h) {
			return (1 << (h - 1) + bs(node.right, level + 1, h));
		} else {
			return (1 << (h - 2) + bs(node.left, level + 1, h));
		}
	}
	
	public static int mostLeftLevel(Node node, int level) {
		while (node != null) {
			level++;
			node = node.left;
		}
		return level - 1;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	}

}
