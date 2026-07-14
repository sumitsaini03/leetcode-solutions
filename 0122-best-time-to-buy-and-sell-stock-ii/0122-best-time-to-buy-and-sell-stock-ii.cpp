class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Coach: Excellent work! Your greedy approach is correct.
        // Time Complexity: O(N) - You traverse the prices array once.
        // Space Complexity: O(1) - You use only a constant amount of extra space.
        // This logic is optimal as it captures every upward trend, effectively summing up all positive differences between consecutive days.
        // You are ready to submit!
        int n = prices.size();
        int profit = 0;

        for (int buy = 0, sell = 1; sell < n; buy++, sell++) {
            if (prices[sell] > prices[buy]) {
                profit += prices[sell] - prices[buy];
            }
        }

        return profit;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna