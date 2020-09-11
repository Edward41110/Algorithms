package myAlgorithms;

public class RegularExpression {

    public static boolean process(char[] str, char[] exp, int i, int j) {
        if (j == exp.length) {
            return i == str.length;
        }
        if (j + 1 == exp.length || exp[j + 1] != '*') {
            return i != str.length && (str[i] == exp[j] || exp[j] == '.') &&
                    process(str, exp, i + 1, j + 1);
        }
        while (i < str.length && ((str[i] == exp[j] || exp[j] == '.'))) {
            if (process(str, exp, i, j + 2)) {
                return true;
            }
            i++;
        }
        return process(str, exp, i, j + 2);
    }

    public static boolean method(String str, String exp) {
        return process(str.toCharArray(), exp.toCharArray(), 0, 0);
    }

    public static boolean dp(char[]str, char[]exp) {
        if (str == null || exp == null) {
            return false;
        }
        int strLen = str.length;
        int expLen = exp.length;
        boolean[][]dp = new boolean[strLen + 1][expLen + 1];
        dp[strLen][expLen] = true;

        for (int j = expLen - 2; j >= 0; j -= 2) {
            if (exp[j] != '*' && exp[j + 1] == '*') {
                dp[strLen][j] = true;
            } else {
                break;
            }
        }
        if (strLen > 0 && expLen > 0) {
            if ((str[strLen - 1] == exp[expLen - 1] || exp[expLen - 1] == '.')) {
                dp[strLen - 1][expLen - 1] = true;
            }
        }

        for (int i = strLen - 1; i >= 0; i--) {
            for (int j = expLen - 2; j >= 0; j--) {
                if (exp[j + 1] != '*') {
                    dp[i][j] = (str[i] == exp[j] || exp[j] == '.') && dp[i + 1][j + 1];
                } else {
                    int k = i;
                    while (k != strLen && (str[k] == exp[j] || exp[j] == '.')) {
                        if (dp[k][j + 2]) {
                            dp[i][j] = true;
                            break;
                        }
                        k++;
                    }
                    if (!dp[i][j]) {
                        dp[i][j] = dp[k][j + 2];
                    }
                }
            }
        }
        return dp[0][0];
    }

    public static void main(String[] args) {
        System.out.println(dp("mississippi".toCharArray(),"mis*is*p*.".toCharArray()));
    }
}
