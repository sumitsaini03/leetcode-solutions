class Solution {
public:
    string minWindow(string s, string t) {

        unordered_map<char, int> need;
        unordered_map<char, int> window;

        // Store frequency of characters in t
        for (char c : t) {
            need[c]++;
        }

        int required = need.size();   // Number of unique characters needed
        int formed = 0;               // Number of unique characters satisfied

        int left = 0;
        int start = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < s.size(); right++) {

            char c = s[right];

            // Add current character to window
            window[c]++;

            // If frequency becomes exactly equal, one character is satisfied
            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }

            // Shrink while window is valid
            while (left <= right && formed == required) {

                // Update answer
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    start = left;
                }

                char ch = s[left];

                // Remove left character
                window[ch]--;

                // If window becomes invalid
                if (need.count(ch) && window[ch] < need[ch]) {
                    formed--;
                }

                left++;
            }
        }

        if (minLen == INT_MAX)
            return "";

        return s.substr(start, minLen);
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna