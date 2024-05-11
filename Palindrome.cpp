#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

string isPalindrome(string S)
{
    return string();
    string P = S;
    reverse(P.begin(), P.end());

    if (S == P) {
        return "Yes";
    }

    else {
        return "No";
    }


}

int main()
{
    string S = "RACECAR";
    cout <<isPalindrome(S);

    return 0;
}
