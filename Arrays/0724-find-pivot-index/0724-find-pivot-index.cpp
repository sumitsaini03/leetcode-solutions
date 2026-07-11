class Solution {
public:
    int pivotIndex(vector<int>& nums) {

        int n = nums.size();

        // Create prefix sum array
        vector<int> prefix(n);

        prefix[0] = nums[0];

        // Build prefix sum array
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }

        // Total sum of the array
        int total = prefix[n - 1];

        // Check every index
        for (int i = 0; i < n; i++) {

            // Left sum
            int left = (i == 0) ? 0 : prefix[i - 1];

            // Right sum
            int right = total - prefix[i];

            // If both sums are equal, return the pivot index
            if (left == right)
                return i;
        }

        // No pivot index found
        return -1;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna