package myAlgorithms;

import java.util.LinkedList;
import java.util.List;

public class BiggestActivity {

    static class Node{
        int value;
        List<Node> children;

        public Node(int value, List<Node> children) {
            this.value = value;
            this.children = children;
        }
    }

    static class ReturnData{
        int present;
        int absent;
        public ReturnData(int present, int absent) {
            this.present = present;
            this.absent = absent;
        }
    }

    public static ReturnData process(Node head) {
        if (head == null) {
            return new ReturnData(0, 0);
        }
        ReturnData[]data = getData(head);
        int present = head.value;
        int absent = 0;
        for (ReturnData d : data) {
            present += d.absent;
            absent += Math.max(d.present, d.absent);
        }
        return new ReturnData(present, absent);
    }

    public static ReturnData[] getData(Node head) {
        if (head.children == null) {
            return new ReturnData[]{new ReturnData(0, 0)};
        }
        ReturnData[] data = new ReturnData[head.children.size()];
        for (int i = 0; i < head.children.size(); i++) {
            data[i] = process(head.children.get(i));
        }
        return data;
    }

    public static void main(String[] args) {

        List<Node> list = new LinkedList<>();
        List<Node> list1 = new LinkedList<>();
        list1.add(new Node(1, null));
        list1.add(new Node(2, null));
        list.add(new Node(300, list1));

        List<Node> list2 = new LinkedList<>();
        list2.add(new Node(10, null));

        list.add(new Node(5, list2));
        Node head = new Node(100, list);

        ReturnData data = process(head);
        System.out.println(Math.max(data.present, data.absent));
    }
}
