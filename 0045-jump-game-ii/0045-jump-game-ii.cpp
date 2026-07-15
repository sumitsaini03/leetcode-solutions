class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size() ;
        int current =  0 ;
        int jump = 0 ;
        int maxIndex = 0 ;
        for(int i = 0 ; i<n-1 ;i++){
            maxIndex = max(maxIndex , i + nums[i]) ;
             if (i == current){
                jump++ ;
            current = maxIndex ;

             }
        }
         return jump ; }

        
    
}; 

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna