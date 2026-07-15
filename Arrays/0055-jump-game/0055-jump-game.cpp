class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0 ;
        int n = nums.size() ;
        for(int i = 0 ; i< n;i++){
            if(i>reach){
                return false ;
            }
            reach = max(reach , i + nums[i] );
            if(reach>n-1){
                return true ;
            }
        }
     return true ;   
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna