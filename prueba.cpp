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
  
    cout << s_b << endl;
  
    return 0;
}