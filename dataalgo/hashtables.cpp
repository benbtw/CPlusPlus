#include <iostream>
#include <map>

using namespace std;

bool isAnagram(string s, string t) {
        /*sort(t.begin(), t.end());
        sort(s.begin(), s.end());
        return s == t;*/
        if(s.size() != t.size()) return false;
        map<char, int> sMap;

        for(int i = 0; i < s.length(); i++) {
            sMap[s[i]]++; // adds char value then increments int by 1 making it 1
            sMap[t[i]]--; // adds char value unless already in then decrements int making it -1 if its not in or 0 if its already in
        }

        for(auto x : sMap) //checks if all the int values = 0 if so then all the chars were the same
            if(x.second != 0)
                return false;
        
        return true;
    }

int main() {
    cout << isAnagram("anagram", "nagaram");
}

