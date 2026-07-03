class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                height[left] >= leftMax ? leftMax = height[left] 
                                         : water += leftMax - height[left];
                left++;
            } else {
                height[right] >= rightMax ? rightMax = height[right] 
                                           : water += rightMax - height[right];
                right--;
            }
        }
        return water;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna