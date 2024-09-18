import java.util.Scanner;

public class a {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input: number of elements in stack N and number of elements to remove K
        int N = sc.nextInt();
        int K = sc.nextInt();

        // Stack elements
        int[] stack = new int[N];
        for (int i = 0; i < N; i++) {
            stack[i] = sc.nextInt();
        }

        int maxSum = 0;

        // Try removing i elements from the top and K-i elements from the bottom
        for (int i = 0; i <= K; i++) {
            int sum = 0;

            // Pick i elements from the top of the stack
            for (int j = 0; j < i; j++) {
                sum += stack[j];
            }

            // Pick (K-i) elements from the bottom of the stack
            for (int j = 0; j < K - i; j++) {
                sum += stack[N - 1 - j];
            }

            // Update maxSum with the maximum sum obtained
            maxSum = Math.max(maxSum, sum);
        }

        // Output the maximum possible sum
        System.out.println(maxSum);
    }
}
