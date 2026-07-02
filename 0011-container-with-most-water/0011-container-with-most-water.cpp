class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1;   // start pointers at the two extreme ends
        int best = 0;                   // running maximum area found so far

        while (left < right) {
            // container height is limited by the SHORTER of the two walls
            int h = min(height[left], height[right]);
            int width = right - left;
            int area = h * width;

            best = max(best, area);     // keep track of the largest area seen

            // move the pointer at the SHORTER wall inward —
            // moving the taller wall can only keep area same or shrink it,
            // since width always decreases and height is capped by the shorter side
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return best;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna