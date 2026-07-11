class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> firstIndex;

        firstIndex[0] = -1;   // Handles subarrays starting at index 0

        int prefix = 0;

        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];

            int rem = prefix % k;

            if (firstIndex.count(rem)) {
                if (i - firstIndex[rem] >= 2)
                    return true;
            } else {
                firstIndex[rem] = i;   // Store first occurrence only
            }
        }

        return false;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna