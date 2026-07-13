// // brute force
// class Solution {
// public:
//     int subarraysDivByK(vector<int>& nums, int k) {

//         int n = nums.size();
//         int count = 0;

//         vector<int> prefix(n);

//         prefix[0] = nums[0];

//         for (int i = 1; i < n; i++) {
//             prefix[i] = prefix[i - 1] + nums[i];
//         }

//         for (int right = 0; right < n; right++) {

//             for (int left = 0; left <= right; left++) {

//                 int sum;

//                 if (left == 0)
//                     sum = prefix[right];
//                 else
//                     sum = prefix[right] - prefix[left - 1];

//                 if (sum % k == 0)
//                     count++;
//             }
//         }

//         return count;
//     }
// };
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {

        // Stores: remainder -> frequency
        unordered_map<int, int> mp;

        // Prefix sum = 0 has remainder 0 once
        // This helps count subarrays starting from index 0
        mp[0] = 1;

        int prefixSum = 0;
        int count = 0;

        for (int num : nums) {

            // Update running prefix sum
            prefixSum += num;

            // Compute remainder
            // The extra +k handles negative prefix sums
            int rem = ((prefixSum % k) + k) % k;

            // If this remainder was seen before,
            // every previous occurrence forms a valid subarray
            count += mp[rem];

            // Store the current remainder
            mp[rem]++;
        }

        return count;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna