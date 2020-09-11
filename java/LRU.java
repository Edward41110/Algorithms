package myAlgorithms;

import java.util.HashMap;

public class LRU {

    static class Node{
        public String key;
        public String value;
        public Node pre;
        public Node next;

        public Node(String key, String value) {
            this.key = key;
            this.value = value;
        }
    }

    static class DoubleLinkedList{
        private Node head;
        private Node tail;

        public void addNode(Node node) {
            if (node == null) {
                return;
            }
            if (this.head == null) {
                this.head = node;
            } else {
                this.tail.next = node;
                node.pre = this.tail;
            }
            this.tail = node;
        }

        public void moveNodeToTail(Node node) {
            if (this.tail == node) {
                return;
            } else if (this.head == node) {
                this.head = node.next;
                this.head.pre = null;
            } else {
                node.pre.next = node.next;
                node.next.pre = node.pre;
            }
            node.next = null;
            node.pre = this.tail;
            this.tail.next = node;
            this.tail = node;
        }

        public Node removeHead() {
            Node headNode = head;
            if (this.head == this.tail) {
                this.head = null;
                this.tail = null;
            } else {
                this.head = this.head.next;
                headNode.next = null;
                this.head.pre = null;
            }
            return headNode;
        }
    }

    int capacity;
    HashMap<String, Node> map;
    DoubleLinkedList list;
    final static int DEFAULT_CAPACITY = 3;

    public LRU(int capacity) {
        this.capacity = capacity < 1 ? DEFAULT_CAPACITY : capacity;
        this.map = new HashMap<>();
        this.list = new DoubleLinkedList();
    }

    public String get(String key) {
        if (!this.map.containsKey(key)) {
            return null;
        }
        Node node = map.get(key);
        this.list.moveNodeToTail(node);
        return node.value;
    }

    public void put(String key, String value) {
        if (this.map.containsKey(key)) {
            Node node = map.get(key);
            node.value = value;
            this.list.moveNodeToTail(node);
        } else {
            if (this.map.size() == capacity) {
                Node deleteNode = this.list.removeHead();
                this.map.remove(deleteNode.key);
            }
            Node newNode = new Node(key, value);
            this.map.put(key, newNode);
            this.list.addNode(newNode);
        }
    }

    public static void main(String[] args) {
        LRU myCache = new LRU(3);
        myCache.put("A", "123");
        myCache.put("B", "234");
        myCache.put("C", "345");
        System.out.println(myCache.get("A"));
        myCache.put("D", "456");
        System.out.println(myCache.get("B"));
    }
}
