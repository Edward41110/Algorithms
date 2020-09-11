package myAlgorithms;

import java.util.Stack;

public class Calculate {

    /**
     * 从算式开始或左括号起到右括号或算式结束为止
     * @param str 算式字符串
     * @param index 本次开始计算的下标
     * @return {本次计算结果, 本次计算到的下标}
     */
    private static int[] calculate(String str, int index) {
        Stack<String> stack = new Stack<>();
        while (index < str.length() && str.charAt(index) != ')') {
            int nextNumber;
            if (str.charAt(index) == '(') {
                int[] result = calculate(str, index + 1);
                nextNumber = result[0];
                index = result[1] + 1;
            } else {
                int i = str.charAt(index) == '-' ? index + 1 : index;
                while (i < str.length() && str.charAt(i) >= '0' && str.charAt(i) <= '9') {
                    i++;
                }
                nextNumber = Integer.parseInt(str.substring(index, i));
                index = i;
            }
            if (!stack.isEmpty()) {
                String operator = stack.pop();
                if ("*".equals(operator)) {
                    nextNumber = Integer.parseInt(stack.pop()) * nextNumber;
                } else if ("/".equals(operator)) {
                    nextNumber = Integer.parseInt(stack.pop()) / nextNumber;
                } else {
                    stack.push(operator);
                }
            }
            stack.push(Integer.toString(nextNumber));
            if (index < str.length() && str.charAt(index) != ')') {
                stack.push(String.valueOf(str.charAt(index)));
                index++;
            }
        }
        int ret = Integer.parseInt(stack.pop());
        while (!stack.isEmpty()) {
            String operator = stack.pop();
            if ("+".equals(operator)) {
                ret = Integer.parseInt(stack.pop()) + ret;
            } else {
                ret = Integer.parseInt(stack.pop()) - ret;
            }
        }
        return new int[]{ret, index};
    }

    public static int method(String str) {
        return calculate(str, 0)[0];
    }

    public static void main(String[] args) {
        System.out.println(method("-3+4*2-(5-1)"));
    }
}
