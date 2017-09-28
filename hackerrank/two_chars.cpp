#include <bits/stdc++.h>

using namespace std;

bool isTwoChar(string s, int n){
    if (n <= 1)
        return false;
    else if (n==2 && s[0]==s[1] )
        return false;
    else if (n==2 && s[0]!=s[1] )
        return true;

    char s1, s2 = '\0';
    s1 = s[0];
    bool s2_found =false;
    for(unsigned int i = 1; i < n-1; i++) 
    {
        if (s[i] != s1) 
        {
            if (!s2_found){
                s2 = s[i];
                s2_found = true;
            } 
            else
            {
                if (s[i] != s2)
                    return false;
                else if ( (s[i-1] == s2) || (s2 == s[i+1]) )
                    return false;
            }
        }
        else if ( (s[i-1] == s1) || (s1 == s[i+1]) )
            return false;
    }

    if (s[n-1] != s1 && s[n-1]!=s2 )
        return false;
    else if (
        (s[n-1]== s2 && s[n-2] == s2) ||
        (s[n-1]== s1 && s[n-2] == s1) )
        return false;

    return true;

}

int maxLen(string s, int n){
    
    return 0;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;


    cout << ":" << isTwoChar(s,n) << endl;

    //int result = maxLen(s, n);
    // cout << result << endl;
    return 0;
}
