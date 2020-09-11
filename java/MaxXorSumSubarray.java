package myAlgorithms;

public class MaxXorSumSubarray {

    static class NumTrieNode {
        NumTrieNode[] next = new NumTrieNode[2];
    }

    static class NumTrie {
        NumTrieNode head = new NumTrieNode();

        public void add(int num) {
            NumTrieNode cur = this.head;
            for (int move = 31; move >= 0; move--) {
                int path = (num >> move) & 1;
                cur.next[path] = cur.next[path] == null ? new NumTrieNode() : cur.next[path];
                cur = cur.next[path];
            }
        }

        public int getMax(int num) {
            NumTrieNode cur = this.head;
            int res = 0;
            for (int move = 31; move >= 0; move--) {
                int path = (num >> move) & 1;
                int best = move == 31 ? path : path ^ 1;
                best = cur.next[best] == null ? best ^ 1 : best;
                res |= (path ^ best) << move;
                cur = cur.next[best];
            }
            return res;
        }
    }

    public static int method(int[] arr) {
        NumTrie numTrie = new NumTrie();
        numTrie.add(0);
        int max = Integer.MIN_VALUE;
        int xor = 0;
        for (int value : arr) {
            xor ^= value;
            max = Math.max(max, numTrie.getMax(xor));
            numTrie.add(xor);
        }
        return max;
    }

    public static void main(String[] args) {
        System.out.println(method(new int[]{1, 2, 3, 4, 5, 6}));
    }
}
