import java.util.ArrayList;
class Solution {
    public boolean isValid(String s) {
        ArrayList<Character> c = new ArrayList<Character>();
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '(' || s.charAt(i) == '{' || s.charAt(i) == '[') {
                c.add(s.charAt(i));
            } else {
                char d = c.get(c.size() - 1);
                if(s.charAt(i) == ')') {
                    if(d == '(') {
                        c.remove(c.size() - 1);
                        continue;
                    } else {
                        return false;
                    }
                } else if(s.charAt(i) == '}') {
                    if(d == '{') {
                        c.remove(c.size() - 1);
                        continue;
                    } else {
                        return false;
                    }
                } else if(s.charAt(i) == ']') {
                    if(d == '[') {
                        c.remove(c.size() - 1);
                        continue;
                    } else {
                        return false;
                    }
                }
            }
        }
        return true;
    }  
}