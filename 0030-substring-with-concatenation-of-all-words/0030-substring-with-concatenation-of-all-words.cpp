class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {

        vector<int> ans;

        if (words.empty())
            return ans;

        int wordLen = words[0].size();
        int wordCount = words.size();
        int n = s.size();

        // Store required frequencies
        unordered_map<string, int> need;

        for (string word : words)
            need[word]++;

        // We need to start from every possible offset
        // Example:
        // wordLen = 3
        //
        // start = 0 : bar foo the ...
        // start = 1 : arf oot hef ...
        // start = 2 : rfo oth efo ...
        //
        // Therefore run the sliding window wordLen times.

        for (int start = 0; start < wordLen; start++) {

            unordered_map<string, int> current;

            int left = start;
            int count = 0;

            // Move right one WORD at a time
            for (int right = start; right + wordLen <= n; right += wordLen) {

                string word = s.substr(right, wordLen);

                // If word exists in dictionary
                if (need.count(word)) {

                    current[word]++;
                    count++;

                    // Too many copies of this word
                    while (current[word] > need[word]) {

                        string leftWord = s.substr(left, wordLen);

                        current[leftWord]--;
                        left += wordLen;
                        count--;
                    }

                    // Found complete window
                    if (count == wordCount) {

                        ans.push_back(left);

                        // Slide window forward
                        string leftWord = s.substr(left, wordLen);

                        current[leftWord]--;
                        left += wordLen;
                        count--;
                    }
                }
                else {

                    // Invalid word
                    current.clear();
                    count = 0;
                    left = right + wordLen;
                }
            }
        }

        return ans;
    }
};






// class Solution {
// public:
//     vector<int> findSubstring(string s, vector<string>& words) {
//         map<char, int> need ;
//         map<char,int>current ;
//         map<char, int>chunk ;
//         vector<int>ans ;
//         int n = s.size();
//         int m = words.size() ;
//         if(n<m)
//         return {} ;
//         for(char c: words){
//             need[c]++ ;
//         // combinenig the need element into one and calulating the size of minimum window
//         string combined = 0 ;
//         for(string new : words){
//             combined += new ;
//         }
//         for(int right = 0 ; right< n;right++){
//             // current map fill till the its size equla to window
//             if(current.size() > combined.size() ){
//               current.erase(s[left]) ;
//               left++ ; }
//               if(current.size() < combined.size() ){
//                 current[s[right]]++ ;
//               } else{
//                 // chunking into 3 pices word length
//                 for(j = 0  ; j<curren.size() ; j++){
//                     chunk +=current ;
//                     if(chunk.size == 3 && chunk==need ){
//                         ans++ ; }
//                         if (chunk.size() <3){
//                             chunk[current[j]] ++ ;
//                         }else{
//                             chunk.erase(current[j]) ;
//                         }
//                 }
//               }
//               return ans ;
//         }
        
//         }
//         }
    

        
//     }
// };



// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna