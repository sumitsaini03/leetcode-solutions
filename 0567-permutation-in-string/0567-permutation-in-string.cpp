class Solution {
public:
    bool checkInclusion(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        if (n > m)
            return false;

        map<char, int> need;
        map<char, int> current;

        for (char c : s1) {
            need[c]++;
        }

        int left = 0;

        for (int right = 0; right < m; right++) {

            current[s2[right]]++;

            // Keep window size equal to n
            if (right - left + 1 > n) {

                current[s2[left]]--;

                if (current[s2[left]] == 0)
                    current.erase(s2[left]);

                left++;
            }

            if (current == need)
                return true;
        }

        return false;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna