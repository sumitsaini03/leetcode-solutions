class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {

        // remainder -> first index where this remainder appeared
        unordered_map<int, int> mp;

        // Assume remainder 0 occurred before the array starts.
        // This helps detect subarrays starting from index 0.
        mp[0] = -1;

        int prefixSum = 0;

        for (int i = 0; i < nums.size(); i++) {

            // Build prefix sum
            prefixSum += nums[i];

            // Current remainder
            int rem = prefixSum % k;

            // (Optional) Handles negative numbers safely.
            // LeetCode 523 has non-negative nums, so this isn't required.
            // if (rem < 0) rem += k;

            // Have we seen this remainder before?
            if (mp.count(rem)) {

                // WHY DOES THIS WORK?
                //
                // If:
                // prefix1 % k == prefix2 % k
                //
                // Then:
                // (prefix2 - prefix1) % k == 0
                //
                // And:
                // prefix2 - prefix1 = sum of the subarray
                //
                // Therefore, that subarray's sum is divisible by k.

                // Check that the subarray length is at least 2
                if (i - mp[rem] >= 2)
                    return true;
            }
            else {

                // IMPORTANT:
                // Store ONLY the first occurrence of this remainder.
                //
                // Example:
                // remainder 5 appears at indices:
                // 0, 2, 4
                //
                // We keep:
                // 5 -> 0
                //
                // because the earliest index gives the longest possible
                // subarray and helps satisfy the length >= 2 condition.
                mp[rem] = i;
            }
        }

        return false;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna