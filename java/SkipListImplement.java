package myAlgorithms;

import java.util.ArrayList;
import java.util.Iterator;

public class SkipListImplement {

    static class SkipListNode {
        Integer value;
        ArrayList<SkipListNode> nextNodes;

        public SkipListNode(Integer value) {
            this.value = value;
            this.nextNodes = new ArrayList<>();
        }
    }

    static class SkipListIterator implements Iterator<Integer> {

        SkipList skipList;
        SkipListNode current;

        public SkipListIterator(SkipList skipList) {
            this.skipList = skipList;
            this.current = skipList.getHead();
        }

        @Override
        public boolean hasNext() {
            return this.current.nextNodes.get(0) != null;
        }

        @Override
        public Integer next() {
            this.current = current.nextNodes.get(0);
            return this.current.value;
        }

        public void init() {
            this.current = this.skipList.getHead();
        }
    }


    public static class SkipList {
        private final SkipListNode head;
        private int maxLevel;
        private int size;
        private static final double PROBABILITY = 0.5;

        public SkipList() {
            this.head = new SkipListNode(null);
            this.head.nextNodes.add(null);
            this.maxLevel = 0;
            this.size = 0;
        }

        /**
         * 返回跳表的头节点
         */
        public SkipListNode getHead() {
            return this.head;
        }

        /**
         * 向跳表中添加值为newValue的新节点
         */
        public void add(Integer newValue) {
            if (!contains(newValue)) {
                this.size++;
                int level = 0;
                while (Math.random() < PROBABILITY) {
                    level++;
                }
                while (level > this.maxLevel) {
                    this.head.nextNodes.add(null);
                    this.maxLevel++;
                }
                SkipListNode newNode = new SkipListNode(newValue);
                SkipListNode current = this.head;
                int currentLevel = this.maxLevel;
                do {
                    current = findNext(newValue, current, currentLevel);
                    if (currentLevel <= level) {
                        newNode.nextNodes.add(0, current.nextNodes.get(currentLevel));
                        current.nextNodes.set(currentLevel, newNode);
                    }
                } while (currentLevel-- > 0);
            }
        }

        /**
         * 从跳表中删除值为deleteValue的节点
         */
        public void delete(Integer deleteValue) {
            if (contains(deleteValue)) {
                SkipListNode deleteNode = find(deleteValue);
                this.size--;
                int level = this.maxLevel;
                SkipListNode current = this.head;
                do {
                    current = findNext(deleteValue - 1, current, level);
                    if (deleteNode.nextNodes.size() > level) {
                        current.nextNodes.set(level, deleteNode.nextNodes.get(level));
                    }
                } while (level-- > 0);
            }
        }

        /**
         * 找到值为value的节点
         * 若value不存在,会返回小于value中最大的节点
         */
        private SkipListNode find(Integer value) {
            int level = this.maxLevel;
            SkipListNode current = this.head;
            do {
                current = findNext(value, current, level);
            } while (level-- > 0);
            return current;
        }

        /**
         * 在level层从current开始找到最后一个节点值小于等于value的node
         */
        private SkipListNode findNext(Integer value, SkipListNode current, int level) {
            SkipListNode next = current.nextNodes.get(level);
            while (next != null && next.value <= value) {
                current = next;
                next = current.nextNodes.get(level);
            }
            return current;
        }

        /**
         * 返回跳表的节点数size
         */
        public int size() {
            return this.size;
        }

        /**
         * 返回跳表中值为value的节点是否存在
         */
        public boolean contains(Integer value) {
            SkipListNode node = find(value);
            return node != null && node.value != null && node.value.equals(value);
        }

        /**
         * 返回跳表中值比value小的最大元素,没有时返回null
         */
        public Integer getLast(Integer value) {
            return find(value - 1).value;
        }

        /**
         * 返回跳表中值比value大的最小元素,没有时返回null
         */
        public Integer getNext(Integer value) {
            SkipListNode currentNode = find(value);
            return currentNode.nextNodes.get(0) == null ? null : currentNode.nextNodes.get(0).value;
        }
    }

    public static void main(String[] args) {
        
    }
}
