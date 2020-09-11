package myAlgorithms;

public class BiggestSearchSubtree {

    static class Node{
        int value;
        Node left;
        Node right;
    }

    static class ReturnData{
        int size;
        Node head;
        int min;
        int max;
        public ReturnData(int size, Node head, int min, int max) {
            this.size = size;
            this.head = head;
            this.min = min;
            this.max = max;
        }
    }

    public static ReturnData process(Node head) {
        if (head == null) {
            return new ReturnData(0, null, Integer.MAX_VALUE, Integer.MIN_VALUE);
        }
        ReturnData leftData = process(head.left);
        ReturnData rightData = process(head.right);

        int mergeSize = 0;
        if (leftData.head == head.left && rightData.head == head.right &&
                leftData.max < head.value && rightData.min > head.value) {
            mergeSize = leftData.size + rightData.size + 1;
        }
        int maxSize = Math.max(Math.max(leftData.size, rightData.size), mergeSize);
        Node returnHead = leftData.size > rightData.size ? leftData.head : rightData.head;
        if (maxSize == mergeSize) {
            returnHead = head;
        }
        return new ReturnData(maxSize, returnHead,
                Math.min(Math.min(leftData.min, rightData.min), head.value),
                Math.max(Math.max(leftData.max, rightData.max), head.value));
    }

    public static void main(String[] args) {
        Node head = null;
        System.out.println(process(head).size);
    }
}
