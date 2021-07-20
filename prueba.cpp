#include <bits/stdc++.h>
using namespace std;
  
// uses overloaded '=' operator from string class
// to convert character array to string
string convertToString(char* a)
{
    string s = a;
    return s;
}
  
// Driver code
int main()
{
    char b[] = "geeksforgeeks";
  
    string s_b = convertToString(b);
    double z = true;
    int x = 2*3.75;
    bool m = 0.1;
    cout << m << endl;
  
    return 0;
}