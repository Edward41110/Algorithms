package myAlgorithms;

import java.util.HashMap;

class MaxLengthOfSubArray {
    public int maxLengthOfSubArray(int[]arr, int aim) {
        HashMap<Integer, Integer> map = new HashMap<>();
        map.put(0, -1);
        int sum = 0, res = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
            if (map.containsKey(sum - aim)) {
                res = Math.max(i - map.get(sum - aim), res);
            }
            if (!map.containsKey(sum)) {
                map.put(sum, i);
            }
        }
        return res;
    }
}
