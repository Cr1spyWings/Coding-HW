class Solution {
    public boolean isPalindrome(String s) {
        String low = s.toLowerCase();
        String newS = "";
        for(int i = 0; i < low.length(); i++) {
            if(low.charAt(i) >= 97) {
                newS += low.charAt(i);
            }
        }

        String rev = "";
        for (int i = 0; i < newS.length(); i++) {
            rev = newS.charAt(i) + rev;
        }

        if(newS.equals(rev) == true) {
            return true;
        } else {
            return false;
        }
    }
}