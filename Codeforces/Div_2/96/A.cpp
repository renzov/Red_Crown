#include<iostream>
#include<string>
using namespace std;
int main(){
  string s;
  getline(cin,s);
  bool ok = false;
  for (int i=0; i < s.size() && !ok; ++i){
	 if ( s[i] == '9' || s[i] == 'H' || s[i] == 'Q' ) ok = true;
  }
  if (ok) cout << "YES" << endl;
  else cout << "NO" << endl;
  return 0;
}