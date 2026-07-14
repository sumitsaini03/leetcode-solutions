class Solution {
public:
    int minOperations(vector<int>& nums, int x) {

        int n = nums.size();

        // Step 1: Calculate the total sum of the array
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // Step 2: Find the sum of the subarray we want to KEEP
        int target = totalSum - x;

        // If target is negative, it's impossible
        if (target < 0)
            return -1;

        // If target is 0, we must remove every element
        if (target == 0)
            return n;

        int left = 0;
        int currentSum = 0;
        int longest = -1;

        // Step 3: Sliding Window
        for (int right = 0; right < n; right++) {

            // Expand the window
            currentSum += nums[right];

            // Shrink the window if the sum becomes too large
            while (currentSum > target && left <= right) {
                currentSum -= nums[left];
                left++;
            }

            // If we found a subarray with sum = target
            if (currentSum == target) {
                longest = max(longest, right - left + 1);
            }
        }

        // If no such subarray exists
        if (longest == -1)
            return -1;

        // Minimum operations = remove everything except the longest subarray
        return n - longest;
    }
};


// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna