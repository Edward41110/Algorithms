package myAlgorithms;

import java.util.ArrayDeque;
import java.util.Deque;

public class RingedMountains {
    static class info{
        int height;
        int times;
        public info(int height) {
            this.height = height;
            this.times = 1;
        }
    }

    private int getInternal(int num) {
        return num * (num - 1) / 2;
    }

    public int method(int[]arr) {
        if (arr == null || arr.length < 2) {
            return 0;
        }
        if (arr.length == 2) {
            return 1;
        }
        int maxIdx = arr.length - 1;
        for (int i = arr.length - 2; i >= 0; i--) {
            maxIdx = arr[i] > arr[maxIdx] ? i : maxIdx;
        }

        int ret = 0;
        Deque<info> dq = new ArrayDeque<>();
        dq.push(new info(arr[maxIdx]));
        for (int i = 1; i < arr.length; i++) {
            assert dq.peek() != null;
            int j = (i + maxIdx) % arr.length;
            if (arr[j] < dq.peek().height) {
                dq.push(new info(arr[j]));
            } else if (arr[j] == dq.peek().height) {
                dq.peek().times++;
            } else {
                int times = dq.pop().times;
                ret += getInternal(times) + times * 2;
                i--;
            }
        }

        while (dq.size() > 1) {
            int times = dq.pop().times;
            ret += getInternal(times) + times * 2;
            if (dq.size() == 1 && dq.peek().times == 1) {
                ret -= times;
            }
        }
        ret += getInternal(dq.pop().times);
        return ret;
    }

    public static void main(String[] args) {
        RingedMountains rm = new RingedMountains();
        System.out.println(rm.method(new int[]{1, 2, 4, 5, 3}));
    }
}
