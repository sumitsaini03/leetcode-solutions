class Solution {
public:
    int candy(vector<int>& ratings) {

        int n = ratings.size();

        // Step 1:
        // Give every child at least one candy.
        vector<int> candy(n, 1);

        // --------------------------------------------------
        // Left to Right Pass
        // --------------------------------------------------
        // If current child's rating is greater than the left child,
        // then current child must get one more candy than the left child.
        //
        // Example:
        // Ratings : 1 2 3
        // Candies : 1 2 3
        //
        for (int i = 1; i < n; i++) {

            if (ratings[i] > ratings[i - 1]) {
                candy[i] = candy[i - 1] + 1;
            }
        }

        // --------------------------------------------------
        // Right to Left Pass
        // --------------------------------------------------
        // Now check the opposite direction.
        //
        // Example:
        // Ratings : 3 2 1
        //
        // Left pass gives:
        // Candies : 1 1 1
        //
        // But this is incorrect because
        // 3 > 2 > 1
        //
        // We update from the right.
        //
        // max() is used because
        // the left pass may already have assigned more candies.
        //
        for (int i = n - 2; i >= 0; i--) {

            if (ratings[i] > ratings[i + 1]) {
                candy[i] = max(candy[i], candy[i + 1] + 1);
            }
        }

        // --------------------------------------------------
        // Count total candies
        // --------------------------------------------------
        int total = 0;

        for (int x : candy)
            total += x;

        return total;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna