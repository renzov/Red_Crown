#include<iostream>
#include<string>
using namespace std;
int main(){

  int c=0,r=0;
  string s;
  cin >> s;
  int l,j;
  int i=0;
  
  int res = 0;
  while ( i < s.size() ){
	 j = i; l = 0;
	 while ( j < s.size() && s[i] == s[j] ){ l++; j++; }
	 i = j;
	 res += l/5;
	 if ( l%5 ) res++;
  }
  cout << res << endl;
  return 0;
}