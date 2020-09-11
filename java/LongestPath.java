package myAlgorithms;

public class LongestPath {

    static class Node{
        int value;
        Node left;
        Node right;
    }

    static class ReturnData{
        int maxDis;
        int maxDepth;
        public ReturnData(int maxDis, int maxDepth) {
            this.maxDis = maxDis;
            this.maxDepth = maxDepth;
        }
    }

    public static ReturnData process(Node head) {
        if (head == null) {
            return new ReturnData(0, 0);
        }
        ReturnData leftData = process(head.left);
        ReturnData rightData = process(head.right);
        return new ReturnData(
                Math.max(Math.max(leftData.maxDis, rightData.maxDis), leftData.maxDepth + rightData.maxDepth + 1),
                Math.max(leftData.maxDepth, rightData.maxDepth) + 1);
    }

    public static void main(String[] args) {
        Node head = null;
        System.out.println(process(head).maxDis);
    }
}
