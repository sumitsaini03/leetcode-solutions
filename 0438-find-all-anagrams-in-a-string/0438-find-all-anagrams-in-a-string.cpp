class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        map<char, int> need;
        map<char, int> current;
        vector<int> ans;

        int m = s.size();
        int n = p.size();

        if (m < n)
            return {};

        // Store frequency of characters in p
        for (char c : p) {
            need[c]++;
        }

        int left = 0;

        for (int right = 0; right < m; right++) {

            // Always add the new character
            current[s[right]]++;

            // If window size becomes greater than n, shrink it
            if (right - left + 1 > n) {
                current[s[left]]--;

                // Remove character if frequency becomes 0
                if (current[s[left]] == 0) {
                    current.erase(s[left]);
                }

                left++;
            }

            // If window size is exactly n, compare maps
            if (right - left + 1 == n && current == need) {
                ans.push_back(left);
            }
        }

        return ans;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna