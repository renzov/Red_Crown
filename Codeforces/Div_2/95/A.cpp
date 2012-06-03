#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int main(){

  string s;
  cin >> s;
  int n = 0;
  for (int i=0; i < s.size(); ++i) if (s[i]>='A' && s[i] <='Z') n++;
  if ( n == s.size() ){
	 for (int i=0; i < s.size(); ++i) s[i] = tolower(s[i]);
  }
  else if ( n == (s.size()-1) && !(s[0]>='A' && s[0] <='Z') ){
	 for (int i=1; i < s.size(); ++i) s[i] = tolower(s[i]);
	 s[0] = toupper(s[0]);
  }
  cout << s << endl;
  return 0;
}