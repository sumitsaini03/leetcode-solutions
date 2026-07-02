class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> Result;              // stores all valid quadruplets found
        sort(nums.begin(), nums.end());          // sorting lets us use two-pointer + easy duplicate skip
        int n = nums.size();

        // fix1 is the first fixed element of the quadruplet
        for (int i = 0; i < n - 3; i++) {
            // skip duplicate values for fix1 (but allow the very first occurrence, i > 0 check)
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int fix1 = nums[i];

            // fix2 is the second fixed element, always searched after fix1
            for (int j = i + 1; j < n - 2; j++) {
                // skip duplicate values for fix2 (only skip if not the first fix2 for this fix1)
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int fix2 = nums[j];

                // two pointers scan the remaining sorted range for the last two numbers
                int left = j + 1, right = n - 1;

                while (left < right) {
                    // use long long to avoid integer overflow when summing 4 elements
                    long long sum = (long long)fix1 + fix2 + nums[left] + nums[right];

                    if (sum == target) {
                        // found a valid quadruplet, save it
                        Result.push_back({fix1, fix2, nums[left], nums[right]});

                        // skip duplicate values at left so we don't push the same quadruplet again
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        // skip duplicate values at right for the same reason
                        while (left < right && nums[right] == nums[right - 1]) right--;

                        // move both pointers inward to look for the next distinct pair
                        left++;
                        right--;
                    } 
                    else if (sum < target) {
                        // sum too small, move left pointer right to increase the sum
                        left++;
                    } 
                    else {
                        // sum too large, move right pointer left to decrease the sum
                        right--;
                    }
                }
            }
        }

        return Result;   // list of all unique quadruplets summing to target
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna