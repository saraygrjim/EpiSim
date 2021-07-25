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
    char* temp;
    temp = (char*)malloc (2048);

    sprintf(temp, "hola%d", 1);
    sprintf(temp, "hola%d", 1);
    return 0;
}